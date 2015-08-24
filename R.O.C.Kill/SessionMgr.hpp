//#pragma once
#ifndef _SESSIONMGR_HPP_
#define _SESSIONMGR_HPP_
#include "stdxafx.h"
#include "Session.h"

class SessionMgr
{
private:
	map<int, std::shared_ptr<Session>> sessionMap;
	SessionMgr() = default;
public:
	Session& getSessionByID(int id) { return *sessionMap[id]; }
	bool insert(int id, sptr_Socket psocket) { return sessionMap.insert(make_pair(id,std::make_shared<Session>(id,psocket))).second; }
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
