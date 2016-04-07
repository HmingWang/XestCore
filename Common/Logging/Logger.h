//
// Created by whaim on 16-4-5.
//

#ifndef XESTCORE_LOGGER_H
#define XESTCORE_LOGGER_H


#include "Appender.h"

class TC_COMMON_API Logger
{
    public:
        Logger();

        void Create(std::string const& name, LogLevel level);
        void addAppender(uint8 type, Appender *);
        void delAppender(uint8 type);

        std::string const& getName() const;
        LogLevel getLogLevel() const;
        void setLogLevel(LogLevel level);
        void write(LogMessage* message) const;

    private:
        std::string name;
        LogLevel level;
        AppenderMap appenders;
};


#endif //XESTCORE_LOGGER_H
