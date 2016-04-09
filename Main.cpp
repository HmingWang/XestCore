#include <iostream>
#include <atomic>
#include "Log.h"
#include "SessionManager.h"

using namespace std;

static boost::asio::io_service* _ioService;
static boost::asio::deadline_timer* _serviceStatusWatchTimer;

/*
* -1 - not in service mode
*  0 - stopped
*  1 - running
*  2 - paused
*/
int m_ServiceStatus = -1;

void ServiceStatusWatcher(boost::system::error_code const& error);

int main()
{
    sLog->Initialize(nullptr);
    TC_LOG_INFO("server","Server is Starting...");
    TRACE("trace info on.");

    _ioService = new boost::asio::io_service();
    sSessionMgr.StartNetwork(*_ioService, "0.0.0.0", 1986);

    _serviceStatusWatchTimer = new boost::asio::deadline_timer(*_ioService);
    _serviceStatusWatchTimer->expires_from_now(boost::posix_time::seconds(30));
    _serviceStatusWatchTimer->async_wait(ServiceStatusWatcher);

    _ioService->run();


    return 0;
}

void ServiceStatusWatcher(boost::system::error_code const& error)
{
    static int count=0;
    if (!error)
    {
        if (m_ServiceStatus == 0)
        {
            _ioService->stop();
            delete _serviceStatusWatchTimer;
        }
        else
        {
            TRACE("[服务器状态正常]当前线程数：%d",sSessionMgr.GetNetworkThreadCount());
            _serviceStatusWatchTimer->expires_from_now(boost::posix_time::seconds(30));
            _serviceStatusWatchTimer->async_wait(ServiceStatusWatcher);
        }
    }
}