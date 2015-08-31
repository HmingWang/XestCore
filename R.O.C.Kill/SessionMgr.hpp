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
	sptr_Session getSessionByID(int id) { return m_SessionsMap[id]; }

	static SessionMgr& getInstance()
	{
		static SessionMgr instance;
		return instance;
	}

	bool emplace(int id, sptr_Socket psocket)
	{
		cout << "[SMGR]增加会话[ID:" << id << "]当前会话数["<< m_SessionsMap.size()+1<<"]" << endl;
		return m_SessionsMap.emplace(id,std::make_shared<Session>(id,psocket)).second;

	}
	void erase(int id) 
	{
		cout << "[SMGR]移除会话[ID:" << id << "]当前会话数[" << m_SessionsMap.size()-1 << "]" << endl;
		m_SessionsMap.erase(id);
	}

	void SendTo(int nId, string strMsg) 
	{
		getSessionByID(nId)->do_write(strMsg);
	}

	void RecieveFrom(int nId) 
	{
		getSessionByID(nId)->do_read();
	}


};

#define sSessionMgr SessionMgr::getInstance()

#endif
