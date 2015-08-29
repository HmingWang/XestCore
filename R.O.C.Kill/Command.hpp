//#pragma once
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "stdxafx.h"
class Command
{
	int    m_SessionID;
	String m_Message;
public:
	Command(int id, string s) :m_SessionID(id), m_Message(s) {}
	int GetSessionID() { return m_SessionID; }
	String GetMessage() { return m_Message; }
};

#endif
