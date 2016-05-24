//
// Created by whaim on 16-4-8.
//

#include "SessionManager.h"

bool SessionManager::StartNetwork(boost::asio::io_service& service, std::string const& bindIp, uint16 port, int threadCount)
{
    if (!BaseSocketMgr::StartNetwork(service, bindIp, port, threadCount))
        return false;

    _acceptor->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForAccept, this));
    _acceptor->AsyncAcceptWithCallback<&OnSocketAccept>();
    return true;
}

NetworkThread<Session>* SessionManager::CreateThreads() const
{
    return new NetworkThread<Session>[GetNetworkThreadCount()];
}

void SessionManager::OnSocketAccept(tcp::socket&& sock, uint32 threadIndex)
{
    sSessionMgr.OnSocketOpen(std::forward<tcp::socket>(sock), threadIndex);
}

SessionManager& SessionManager::Instance()
{
    static SessionManager instance;
    return instance;
}