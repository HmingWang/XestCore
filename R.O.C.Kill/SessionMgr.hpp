#pragma once
#include "stdxafx.h"
#include "Session.h"

class SessionMgr
{
private:
	map<int, Session> sessionMap;
	SessionMgr() = default;
public:
	Session& getSessionByID(int id) { return sessionMap[id]; }
	bool insert(int id, sptr_Socket psocket) { return sessionMap.insert(pair<int, Session>(id,Session(id,psocket))).second; }

	static SessionMgr& getInstance() {
		static SessionMgr instance;
		return instance;
	}

};

#define sSessionMgr SessionMgr::getInstance()
