#include "Session.h"

void Session::do_read()
{
	boost::asio::async_read_until(*pSocket, rsbuf, '\0', [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]¶ÁÈ¡´íÎó: " << ec.message() << std::endl;
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
		sParserX();
		do_read();

	});
}

void Session::do_write(string s="")
{
	strbuff = s;
	boost::asio::async_write(*pSocket, boost::asio::buffer(strbuff, strbuff.size()), [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]Ð´Èë³ö´í£º " << ec.message() << std::endl;
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
		"================welcome to new world================\n" +
		"====================================================\n");
	do_read();
}
