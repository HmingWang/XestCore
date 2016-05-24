//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_SESSIONMANAGER_H
#define XESTCORE_SESSIONMANAGER_H

#include "SocketMgr.h"
#include "Session.h"

class SessionManager : public SocketMgr<Session>
{
    typedef SocketMgr<Session> BaseSocketMgr;

public:
    static SessionManager& Instance();

    bool StartNetwork(boost::asio::io_service& service, std::string const& bindIp, uint16 port, int threadCount = 10) override;

protected:
    NetworkThread<Session>* CreateThreads() const override;

private:
    static void OnSocketAccept(tcp::socket&& sock, uint32 threadIndex);
};

#define sSessionMgr SessionManager::Instance()

#endif //XESTCORE_SESSIONMANAGER_H
