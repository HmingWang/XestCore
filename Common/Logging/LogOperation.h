//
// Created by whaim on 16-4-7.
//

#ifndef XESTCORE_LOGOPERATION_H
#define XESTCORE_LOGOPERATION_H


#include <memory>
#include "Define.h"

class Logger;
struct LogMessage;

class TC_COMMON_API LogOperation
{
public:
    LogOperation(Logger const* _logger, std::unique_ptr<LogMessage>&& _msg)
            : logger(_logger), msg(std::forward<std::unique_ptr<LogMessage>>(_msg))
    { }

    ~LogOperation() { }

    int call();

protected:
    Logger const* logger;
    std::unique_ptr<LogMessage> msg;
};

#endif //XESTCORE_LOGOPERATION_H
