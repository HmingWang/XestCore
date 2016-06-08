#ifndef _SESSION_H_
#define _SESSION_H_

#include"stdxafx.h"

typedef std::shared_ptr<tcp::socket> sptr_Socket;

class Session {
	
private:
	sptr_Socket m_spSocket;                //Socket
	int m_ID;
	boost::asio::streambuf wsbuf;       //写入消息缓冲区//x
	boost::asio::streambuf m_ReadBuffer;       //读取消息缓冲区
	string m_WriteBuffer;                     //写入消息缓冲区
public:
	~Session();
	Session(int id,sptr_Socket ps);
	bool isConnected();
	void do_read();
	void do_write(string);
	string getAddress();
	int getPort();
	int GetID();
	void start();                       //开始消息循环
	void close();
};

#endif // !_SESSION_HPP_
