#ifndef _SESSION_MGR_H_
#define _SESSION_MGR_H_

#include <boost/make_shared.hpp>
#include "SocketMgr.h"
#include "Session.h"

class SessionManager :public SocketMgr<Session> 
{
	typedef SocketMgr<Session> BaseSocketMgr;
	typedef std::shared_ptr<NetworkThread<Session>> sptr_NetworkThread;

public:
	static SessionManager& GetInstance() 
	{
		static SessionManager instance;
		return instance;
	}

	static void OnSocketAccept(tcp::socket&& sock, uint32 threadIndex)
	{
		SessionManager::GetInstance().OnSocketOpen(std::forward<tcp::socket>(sock), threadIndex);
	}

	virtual bool StartNetwork(boost::asio::io_service& ioService, std::string const& bindIp, uint16 port, int threadCount) override
	{
		if (!BaseSocketMgr::StartNetwork(ioService, bindIp, port, threadCount))
			return false;

		_acceptor->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForAccept, this));
		_acceptor->AsyncAcceptWithCallback<&OnSocketAccept>();

		return true;
	}

private:
	SessionManager() = default;


};

#define sSessionMgr SessionManager::GetInstance()
#endif //!_SESSION_MGR_H_