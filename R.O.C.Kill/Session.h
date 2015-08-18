#ifndef _SESSION_H_
#define _SESSION_H_

#include"stdxafx.h"

typedef std::shared_ptr<tcp::socket> sptr_Socket;

class Session {
private:
	sptr_Socket pSocket; //
	int id;

	boost::asio::streambuf wsbuf;       //д����Ϣ������//x
	boost::asio::streambuf rsbuf;       //��ȡ��Ϣ������
	string strbuff;                     //д����Ϣ������
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
	void start();                       //��ʼ��Ϣѭ��
};

#endif // !_SESSION_HPP_
