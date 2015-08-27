//#pragma once
#ifndef _SESSIONMGR_HPP_
#define _SESSIONMGR_HPP_
#include "stdxafx.h"
#include "Session.h"

typedef std::shared_ptr<Session> sptr_Session;

class SessionMgr
{
private:
	map<int, sptr_Session> m_SessionsMap;
	SessionMgr() = default;
public:
	Session& getSessionByID(int id) { return *m_SessionsMap[id]; }

	static SessionMgr& getInstance()
	{
		static SessionMgr instance;
		return instance;
	}

	bool emplace(int id, sptr_Socket psocket)
	{
		return m_SessionsMap.emplace(id,std::make_shared<Session>(psocket)).second;
	}
	void erase(int id) 
	{
		m_SessionsMap.erase(id);
	}

	void SendTo(int nId, string strMsg) 
	{
		getSessionByID(nId).do_write(strMsg);
	}

	void RecieveFrom(int nId) 
	{
		getSessionByID(nId).do_read();
	}


};

#define sSessionMgr SessionMgr::getInstance()

#endif
