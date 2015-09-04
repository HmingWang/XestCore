#ifndef _X_EXCEPTION_H_
#define _X_EXCEPTION_H_

#include <exception>

class XExcepiton :public std::exception
{
public:
	XExcepiton(const char *Message) :std::exception(Message) {}
};

#endif
