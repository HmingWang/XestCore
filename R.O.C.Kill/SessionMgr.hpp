//#pragma once
#ifndef _SESSIONMGR_HPP_
#define _SESSIONMGR_HPP_
#include "stdxafx.h"
#include "Session.h"

typedef std::shared_ptr<Session> sptr_Session;

class SessionMgr
{
private:
	map<int, sptr_Session> sessionMap;
	SessionMgr() = default;
public:
	Session& getSessionByID(int id) { return *sessionMap[id]; }
	bool insert(int id, sptr_Socket psocket)
	{
		return sessionMap.emplace(id, std::make_shared<Session>(id, psocket)).second;
		//return sessionMap.insert(make_pair(id, std::make_shared<Session>(id, psocket))).second;
	}
	void erase(int id) 
	{
		sessionMap.erase(id); 
	}
	static SessionMgr& getInstance() {
		static SessionMgr instance;
		return instance;
	}

};

#define sSessionMgr SessionMgr::getInstance()

#endif
