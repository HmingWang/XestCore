#ifndef _MSG_QUEUE_HPP_
#define _MSG_QUEUE_HPP_

#include <iostream>
#include <queue>
#include <string>

using std::cout;
using std::cin;
using std::queue;
using std::string;

class MsgQueue{

public:
	size_t msgPut();
	size_t msgGet();
private:
	queue<string> sendQ;
	queue<string> recvQ;
};


#endif