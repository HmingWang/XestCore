#pragma once

#include "stdxafx.h"
class Command
{
public:
	Command(int id, string s) :sid(id), cmdmsg(s) {}
	int    sid;
	String cmdmsg;
};

