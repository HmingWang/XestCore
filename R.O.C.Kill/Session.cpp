#include "Session.h"
#include "ParserX.hpp"
#include "Command.hpp"

Session::~Session()
{
	cout << "Session析构：" << id << endl;
	pSocket->close();
}

void Session::do_read()
{
	boost::asio::async_read_until(*pSocket, rsbuf, '\0', [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]读取错误: " << ec.message() << std::endl;
			//std::cout << "[SESS]==exit==" << std::endl;
			//pSocket->close();
			sSessionMgr.erase(id);
			return;
		}
		std::ostringstream oss;
		oss << &rsbuf;
		std::string msg = oss.str();
		std::cout << "[SESS][" <<getAddress()<<":"<<getPort()<<"]["<< msg.size()<<"]>>>" << msg  << std::endl;
		//do_write(parser.parserCommand(msg));
		//sParserX.parserCommand(msg);
		//sParserX();
		sParserX.parserCommand(Command(id,msg));
		do_read();

	});
}

void Session::do_write(string s="")
{
	strbuff = s;
	boost::asio::async_write(*pSocket, boost::asio::buffer(strbuff, strbuff.size()), [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]写入出错： " << ec.message() << std::endl;
			//std::cout << "[SESS]exit" << std::endl;
			//pSocket->close();
			return;
		}
		std::cout << "[SESS][" << getAddress()<< ":" << getPort() <<"]<<<"<< strbuff << std::endl;
	});
}

int Session::getId()
{
	return id;
}

string Session::getAddress()
{
	return pSocket->remote_endpoint().address().to_string();
}

int Session::getPort() 
{
	return pSocket->remote_endpoint().port();
}

void Session::start()
{
	do_write(string(
		"\n====================================================\n") +
		"===        天下风云出我辈， 一入江湖岁月催；     ===\n" +
		"===        皇图霸业谈笑间， 不胜人生一场醉。     ===\n" +
		"===        提剑跨骑挥鬼雨， 白骨如山鸟惊飞；     ===\n" +
		"===        尘事如潮人如水， 只叹江湖几人回。     ===\n" +
		"====================================================\n");
	do_read();
}
