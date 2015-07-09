#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include"stdxafx.h"
class Session{
private:
	tcp::socket socket;
public:
	Session(tcp::socket& s):socket(std::move(s)){}
};


#endif // !_SESSION_HPP_


