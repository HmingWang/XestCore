//#pragma once
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "stdxafx.h"
class Command
{
public:
	Command(int id, string s) :sid(id), cmdmsg(s) {}
	int    sid;
	String cmdmsg;
};

#endif
