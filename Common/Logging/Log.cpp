//
// Created by whaim on 2016/3/31.
//

#include "Log.h"
#include "AppenderFile.h"
#include "AppenderConsole.h"
#include "Config.h"
#include "Util.h"
#include "LogOperation.h"


Log::Log() : AppenderId(0), lowestLogLevel(LOG_LEVEL_FATAL), _ioService(nullptr), _strand(nullptr)
{
    m_logsTimestamp = "_" + GetTimestampStr();
    RegisterAppender<AppenderConsole>();
    RegisterAppender<AppenderFile>();
}

Log::~Log()
{
    delete _strand;
    Close();
}

uint8 Log::NextAppenderId()
{
    return AppenderId++;
}

int32 GetConfigIntDefault(std::string base, const char* name, int32 value)
{
    base.append(name);
    return sConfigMgr->GetIntDefault(base.c_str(), value);
}

std::string GetConfigStringDefault(std::string base, const char* name, const char* value)
{
    base.append(name);
    return sConfigMgr->GetStringDefault(base.c_str(), value);
}

Appender* Log::GetAppenderByName(std::string const& name)
{
    AppenderMap::iterator it = appenders.begin();
    while (it != appenders.end() && it->second && it->second->getName() != name)
        ++it;

    return it == appenders.end() ? NULL : it->second;
}

void Log::CreateAppenderFromConfig(std::string const& appenderName)
{
    if (appenderName.empty())
        return;

    // Format=type, level, flags, optional1, optional2
    // if type = File. optional1 = file and option2 = mode
    // if type = Console. optional1 = Color
    std::string options = sConfigMgr->GetStringDefault(appenderName.c_str(), "");

    Tokenizer tokens(options, ',');
    Tokenizer::const_iterator iter = tokens.begin();

    size_t size = tokens.size();
    std::string name = appenderName.substr(9);

    if (size < 2)
    {
        fprintf(stderr, "Log::CreateAppenderFromConfig: Wrong configuration for appender %s. Config line: %s\n", name.c_str(), options.c_str());
        return;
    }

    AppenderFlags flags = APPENDER_FLAGS_NONE;
    AppenderType type = AppenderType(atoi(*iter++));
    LogLevel level = LogLevel(atoi(*iter++));

    if (level > LOG_LEVEL_FATAL)
    {
        fprintf(stderr, "Log::CreateAppenderFromConfig: Wrong Log Level %d for appender %s\n", level, name.c_str());
        return;
    }

    if (size > 2)
        flags = AppenderFlags(atoi(*iter++));

    auto factoryFunction = appenderFactory.find(type);
    if (factoryFunction == appenderFactory.end())
    {
        fprintf(stderr, "Log::CreateAppenderFromConfig: Unknown type %d for appender %s\n", type, name.c_str());
        return;
    }

    try
    {
        Appender* appender = factoryFunction->second(NextAppenderId(), name, level, flags, ExtraAppenderArgs(iter, tokens.end()));
        appenders[appender->getId()] = appender;
    }
    catch (InvalidAppenderArgsException const& iaae)
    {
        fprintf(stderr, "%s", iaae.what());
    }
}

void Log::CreateLoggerFromConfig(std::string const& appenderName)
{
    if (appenderName.empty())
        return;

    LogLevel level = LOG_LEVEL_DISABLED;
    uint8 type = uint8(-1);

    std::string options = sConfigMgr->GetStringDefault(appenderName.c_str(), "");
    std::string name = appenderName.substr(7);

    if (options.empty())
    {
        fprintf(stderr, "Log::CreateLoggerFromConfig: Missing config option Logger.%s\n", name.c_str());
        return;
    }

    Tokenizer tokens(options, ',');
    Tokenizer::const_iterator iter = tokens.begin();

    if (tokens.size() != 2)
    {
        fprintf(stderr, "Log::CreateLoggerFromConfig: Wrong config option Logger.%s=%s\n", name.c_str(), options.c_str());
        return;
    }

    Logger& logger = loggers[name];
    if (!logger.getName().empty())
    {
        fprintf(stderr, "Error while configuring Logger %s. Already defined\n", name.c_str());
        return;
    }

    level = LogLevel(atoi(*iter++));
    if (level > LOG_LEVEL_FATAL)
    {
        fprintf(stderr, "Log::CreateLoggerFromConfig: Wrong Log Level %u for logger %s\n", type, name.c_str());
        return;
    }

    if (level < lowestLogLevel)
        lowestLogLevel = level;

    logger.Create(name, level);
    //fprintf(stdout, "Log::CreateLoggerFromConfig: Created Logger %s, Level %u\n", name.c_str(), level);

    std::istringstream ss(*iter);
    std::string str;

    ss >> str;
    while (ss)
    {
        if (Appender* appender = GetAppenderByName(str))
        {
            logger.addAppender(appender->getId(), appender);
            //fprintf(stdout, "Log::CreateLoggerFromConfig: Added Appender %s to Logger %s\n", appender->getName().c_str(), name.c_str());
        }
        else
            fprintf(stderr, "Error while configuring Appender %s in Logger %s. Appender does not exist", str.c_str(), name.c_str());
        ss >> str;
    }
}

void Log::ReadAppendersFromConfig()
{
    std::list<std::string> keys = sConfigMgr->GetKeysByString("Appender.");

    while (!keys.empty())
    {
        CreateAppenderFromConfig(keys.front());
        keys.pop_front();
    }
}

void Log::ReadLoggersFromConfig()
{
    std::list<std::string> keys = sConfigMgr->GetKeysByString("Logger.");

    while (!keys.empty())
    {
        CreateLoggerFromConfig(keys.front());
        keys.pop_front();
    }

    // Bad config configuration, creating default config
    if (loggers.find(LOGGER_ROOT) == loggers.end())
    {
        fprintf(stderr, "Wrong Loggers configuration. Review your Logger config section.\n"
                "Creating default loggers [root (Error), server (Info)] to console\n");

        Close(); // Clean any Logger or Appender created

        AppenderConsole* appender = new AppenderConsole(NextAppenderId(), "Console", LOG_LEVEL_DEBUG, APPENDER_FLAGS_NONE, ExtraAppenderArgs());
        appenders[appender->getId()] = appender;

        Logger& rootLogger = loggers[LOGGER_ROOT];
        rootLogger.Create(LOGGER_ROOT, LOG_LEVEL_ERROR);
        rootLogger.addAppender(appender->getId(), appender);

        Logger& serverLogger = loggers["server"];
        serverLogger.Create("server", LOG_LEVEL_INFO);
        serverLogger.addAppender(appender->getId(), appender);
    }
}

void Log::write(std::unique_ptr<LogMessage>&& msg) const
{
    Logger const* logger = GetLoggerByType(msg->type);

    if (_ioService) //?
    {
        auto logOperation = std::shared_ptr<LogOperation>(new LogOperation(logger, std::move(msg)));

        _ioService->post(_strand->wrap([logOperation](){ logOperation->call(); }));
    }
    else
        logger->write(msg.get());
}

std::string Log::GetTimestampStr()
{
    time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::tm aTm;
    localtime_r(&tt, &aTm);

    //       YYYY   year
    //       MM     month (2 digits 01-12)
    //       DD     day (2 digits 01-31)
    //       HH     hour (2 digits 00-23)
    //       MM     minutes (2 digits 00-59)
    //       SS     seconds (2 digits 00-59)
    return fmt::sprintf("%04d-%02d-%02d_%02d-%02d-%02d", aTm.tm_year + 1900, aTm.tm_mon + 1, aTm.tm_mday, aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
}