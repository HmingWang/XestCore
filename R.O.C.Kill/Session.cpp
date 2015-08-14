#include "Session.h"
#include "ParserX.hpp"
#include "Command.hpp"

void Session::do_read()
{
	boost::asio::async_read_until(*pSocket, rsbuf, '\0', [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]读取错误: " << ec.message() << std::endl;
			std::cout << "[SESS]==exit==" << std::endl;
			pSocket->close();
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
			std::cout << "[SESS]exit" << std::endl;
			pSocket->close();
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
		"===          十载江湖十载愁 夜风夜雨夜中人          ===\n" +
		"====================================================\n");
	do_read();
}
