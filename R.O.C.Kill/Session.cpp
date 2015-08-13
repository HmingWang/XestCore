#include "Session.h"

void Session::do_read()
{
	boost::asio::async_read_until(socket, rsbuf, '\0', [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[P]Message:==end== " << ec.message() << std::endl;
			std::cout << "[P]exit" << std::endl;
			socket.close();
			return;
		}
		std::ostringstream oss;
		oss << &rsbuf;
		std::string msg = oss.str();
		std::cout << "[P]Message:" << msg << ":" << msg.size() << std::endl;
		//do_write(parser.parserCommand(msg));
		//sParserX.parserCommand(msg);

		do_read();

	});
}

void Session::do_write(string s="")
{
	strbuff = s;
	boost::asio::async_write(socket, boost::asio::buffer(strbuff, strbuff.size()), [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[P]Ð´Èë³ö´í£º " << ec.message() << std::endl;
			std::cout << "[P]exit" << std::endl;
			socket.close();
			return;
		}
		std::cout << "[S]" << strbuff << std::endl;
	});
}

int Session::getId()
{
	return id;
}

string Session::getAddress()
{
	return socket.remote_endpoint().address().to_string();
}

void Session::start()
{
	do_write(string(
		"\n====================================================\n") +
		"================welcome to new world================\n" +
		"====================================================\n");
	do_read();
}
