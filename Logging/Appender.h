//
// Created by whaim on 16-3-30.
//

#ifndef XESTCORE_APPENDER_H
#define XESTCORE_APPENDER_H

#include "../Define.h"

enum LogLevel
{
    LOG_LEVEL_DISABLED                           = 0,
    LOG_LEVEL_TRACE                              = 1,
    LOG_LEVEL_DEBUG                              = 2,
    LOG_LEVEL_INFO                               = 3,
    LOG_LEVEL_WARN                               = 4,
    LOG_LEVEL_ERROR                              = 5,
    LOG_LEVEL_FATAL                              = 6
};

enum AppenderType
{
    APPENDER_NONE,
    APPENDER_CONSOLE,
    APPENDER_FILE,
    APPENDER_DB
};

enum AppenderFlags
{
    APPENDER_FLAGS_NONE                          = 0x00,
    APPENDER_FLAGS_PREFIX_TIMESTAMP              = 0x01,
    APPENDER_FLAGS_PREFIX_LOGLEVEL               = 0x02,
    APPENDER_FLAGS_PREFIX_LOGFILTERTYPE          = 0x04,
    APPENDER_FLAGS_USE_TIMESTAMP                 = 0x08, // only used by FileAppender
    APPENDER_FLAGS_MAKE_FILE_BACKUP              = 0x10  // only used by FileAppender
};

struct TC_COMMON_API LogMessage
        {
                LogMessage(LogLevel _level, std::string const& _type, std::string&& _text)
        : level(_level), type(_type), text(std::forward<std::string>(_text)), mtime(time(NULL))
        { }

        LogMessage(LogMessage const& /*other*/) = delete;
        LogMessage& operator=(LogMessage const& /*other*/) = delete;

        static std::string getTimeStr(time_t time);
        std::string getTimeStr();

        LogLevel const level;
        std::string const type;
        std::string const text;
        std::string prefix;
        std::string param1;
        time_t mtime;

        ///@ Returns size of the log message content in bytes
        uint32 Size() const
        {
            return static_cast<uint32>(prefix.size() + text.size());
        }
        };

class Appender {

};


#endif //XESTCORE_APPENDER_H
