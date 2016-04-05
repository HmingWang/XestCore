//
// Created by whaim on 2016/3/31.
//

#include <linux/limits.h>
#include "AppenderFile.h"
#include "Log.h"
#include "Define.h"

AppenderFile::AppenderFile(uint8 id, std::string const& name, LogLevel level, AppenderFlags flags, ExtraAppenderArgs extraArgs) :
        Appender(id, name, level, flags),
        logfile(NULL),
        _logDir(sLog->GetLogsDir()),
        _maxFileSize(0),
        _fileSize(0)
{
    if (extraArgs.empty())//参数不能为空
        throw InvalidAppenderArgsException(fmt::sprintf("Log::CreateAppenderFromConfig: Missing file name for appender %s\n", name.c_str()));

    _fileName = extraArgs[0]; //第一个参数是文件名

    char const* mode = "a";
    if (extraArgs.size() > 1)
        mode = extraArgs[1]; //第二个参数是文件写模式

    if (flags & APPENDER_FLAGS_USE_TIMESTAMP)//文件名添加时间戳
    {
        size_t dot_pos = _fileName.find_last_of(".");
        if (dot_pos != std::string::npos) //npos  没找到位置
            _fileName.insert(dot_pos, sLog->GetLogsTimestamp());
        else
            _fileName += sLog->GetLogsTimestamp();
    }

    if (extraArgs.size() > 2)
        _maxFileSize = atoi(extraArgs[2]);
    else
        _maxFileSize = 0;

    _dynamicName = std::string::npos != _fileName.find("%s");  //动态文件名
    _backup = (flags & APPENDER_FLAGS_MAKE_FILE_BACKUP) != 0;

    if (!_dynamicName)
        logfile = OpenFile(_fileName, mode, !strcmp(mode, "w") && _backup);
}

AppenderFile::~AppenderFile()
{
    CloseFile();
}

void AppenderFile::_write(LogMessage const* message)
{
    bool exceedMaxSize = _maxFileSize > 0 && (_fileSize.load() + message->Size()) > _maxFileSize;

    if (_dynamicName)
    {
        char namebuf[PATH_MAX];
        snprintf(namebuf, PATH_MAX, _fileName.c_str(), message->param1.c_str());
        // always use "a" with dynamic name otherwise it could delete the log we wrote in last _write() call
        FILE* file = OpenFile(namebuf, "a", _backup || exceedMaxSize);
        if (!file)
            return;
        fprintf(file, "%s%s\n", message->prefix.c_str(), message->text.c_str());
        fflush(file);
        _fileSize += uint64(message->Size());
        fclose(file);
        return;
    }
    else if (exceedMaxSize)
        logfile = OpenFile(_fileName, "w", true);

    if (!logfile)
        return;

    fprintf(logfile, "%s%s\n", message->prefix.c_str(), message->text.c_str());
    fflush(logfile);
    _fileSize += uint64(message->Size());
}

FILE* AppenderFile::OpenFile(std::string const& filename, std::string const& mode, bool backup)
{
    std::string fullName(_logDir + filename);
    if (backup)
    {
        CloseFile();
        std::string newName(fullName);
        newName.push_back('.');
        newName.append(LogMessage::getTimeStr(time(NULL)));
        std::replace(newName.begin(), newName.end(), ':', '-');
        //stdio标准裤函数  文件改名
        rename(fullName.c_str(), newName.c_str()); // no error handling... if we couldn't make a backup, just ignore
    }

    if (FILE* ret = fopen(fullName.c_str(), mode.c_str()))
    {
        _fileSize = ftell(ret);
        return ret;
    }

    return NULL;
}

void AppenderFile::CloseFile()
{
    if (logfile)
    {
        fclose(logfile);
        logfile = NULL;
    }
}