//
// Created by whaim on 16-4-7.
//

#include "LogOperation.h"
#include "Logger.h"

int LogOperation::call()
{
    logger->write(msg.get());
    return 0;
}
