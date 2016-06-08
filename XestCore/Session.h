#ifndef _SESSION_H_
#define _SESSION_H_

#include"stdxafx.h"

typedef std::shared_ptr<tcp::socket> sptr_Socket;

class Session {
	
private:
	sptr_Socket m_spSocket;                //Socket
	int m_ID;
	boost::asio::streambuf wsbuf;       //д����Ϣ������//x
	boost::asio::streambuf m_ReadBuffer;       //��ȡ��Ϣ������
	string m_WriteBuffer;                     //д����Ϣ������
public:
	~Session();
	Session(int id,sptr_Socket ps);
	bool isConnected();
	void do_read();
	void do_write(string);
	string getAddress();
	int getPort();
	int GetID();
	void start();                       //��ʼ��Ϣѭ��
	void close();
};

#endif // !_SESSION_HPP_
