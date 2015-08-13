#ifndef _SESSION_H_
#define _SESSION_H_

#include"stdxafx.h"


class Session{
private:
	tcp::socket socket; //
	int id;

	boost::asio::streambuf wsbuf;       //д����Ϣ������//x
	boost::asio::streambuf rsbuf;       //��ȡ��Ϣ������
	string strbuff;                     //д����Ϣ������  
public:
	Session(tcp::socket& s):socket(std::move(s)){}
	void do_read();
	void do_write(string);
	int getId();
	string getAddress();
	void start();                       //��ʼ��Ϣѭ��
};


#endif // !_SESSION_HPP_


