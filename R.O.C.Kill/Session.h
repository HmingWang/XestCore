#ifndef _SESSION_H_
#define _SESSION_H_

#include"stdxafx.h"

typedef std::shared_ptr<tcp::socket> sptr_Socket;

class Session {
private:
	sptr_Socket pSocket; //
	int id;

	boost::asio::streambuf wsbuf;       //写入消息缓冲区//x
	boost::asio::streambuf rsbuf;       //读取消息缓冲区
	string strbuff;                     //写入消息缓冲区
public:
	Session() = default;
	~Session();
	Session(int id, sptr_Socket ps);
	Session(Session& s):pSocket(s.pSocket),id(s.id) {}
	void do_read();
	void do_write(string);
	int getId();
	string getAddress();
	int getPort();
	void start();                       //开始消息循环
};

#endif // !_SESSION_HPP_
