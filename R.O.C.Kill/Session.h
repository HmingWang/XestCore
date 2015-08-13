#ifndef _SESSION_H_
#define _SESSION_H_

#include"stdxafx.h"


class Session{
private:
	tcp::socket socket; //
	int id;

	boost::asio::streambuf wsbuf;       //写入消息缓冲区//x
	boost::asio::streambuf rsbuf;       //读取消息缓冲区
	string strbuff;                     //写入消息缓冲区  
public:
	Session(tcp::socket& s):socket(std::move(s)){}
	void do_read();
	void do_write(string);
	int getId();
	string getAddress();
	void start();                       //开始消息循环
};


#endif // !_SESSION_HPP_


