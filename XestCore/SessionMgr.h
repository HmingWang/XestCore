#ifndef _SESSION_MGR_H_
#define _SESSION_MGR_H_

#include <boost/make_shared.hpp>
#include "SocketMgr.h"
#include "Session.h"

class SessionMgr :public SocketMgr<Session> 
{
	typedef SocketMgr<Session> BaseSocketMgr;
	typedef std::shared_ptr<NetworkThread<Session>> sptr_NetworkThread;

public:
	static SessionMgr& GetInstance() 
	{
		static SessionMgr instance;
		return instance;
	}
	virtual bool StartNetwork(boost::asio::io_service& ioService, std::string const& bindIp, uint16 port, int threadCount) override
	{
		if (!BaseSocketMgr::StartNetwork(ioService, bindIp, port, threadCount))
			return false;

		_acceptor->AsyncAccept<Session>();
		return true;
	}



private:
	SessionMgr() = default;


};

#define sSessionMgr SessionMgr::GetInstance()
#endif //!_SESSION_MGR_H_