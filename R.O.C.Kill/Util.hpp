#ifndef _UTIL_HPP_
#define _UTIL_HPP_
#include <string>

using std::string;

class Util
{
public:
	static void Trace(const string strMsg, ...);
};

#endif