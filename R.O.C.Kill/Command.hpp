//#pragma once
#ifndef _STDXAFX_H_
#define _STDXAFX_H_

#include "stdxafx.h"
class Command
{
public:
	Command(int id, string s) :sid(id), cmdmsg(s) {}
	int    sid;
	String cmdmsg;
};

#endif
