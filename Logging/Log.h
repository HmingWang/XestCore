//
// Created by whaim on 2016/3/31.
//

#ifndef XESTCORE_LOG_H
#define XESTCORE_LOG_H

#include <unordered_map>
#include "Define.h"

class TC_COMMON_API Log
{
    typedef std::unordered_map<std::string, Logger> LoggerMap;
private:
    Log();
    ~Log();

public:
    static Log* instance();
    void Initialize(boost::asio::io_service* ioService);

};


#endif //XESTCORE_LOG_H
