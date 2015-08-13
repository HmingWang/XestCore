#include "Player.h"
#include "ParserX.hpp"

Player::Player(tcp::socket& s,int i) :socket(std::move(s)), sessionId(i){
	std::cout << "[P][ID: "<<getId()<<"][IP: " << getAddress() << "]进入房间" << std::endl;
}
Player::~Player(){
	socket.close();
	std::cout << "[P][ID: " << getId() << "][IP: " << getAddress() << "]断开连接" << std::endl;
}

string Player::getAddress(){
	return socket.remote_endpoint().address().to_string();

}

void Player::start(){
	do_write(string(
		"\n====================================================\n") +
		  "================welcome to new world================\n" +
		  "====================================================\n");
	do_read();
}
string Player::getMsg(){
	string str;
	if (msgQueue.empty())return NULL;
	str = msgQueue.front();
	msgQueue.pop();
	return str;
}

void Player::do_read(){
	boost::asio::async_read_until(socket, rsbuf, '\0', [&](boost::system::error_code ec, size_t t){
		if (ec){
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
		sParserX.parserCommand(msg);

		do_read();

	});
}

void Player::do_write(string s = ""){
	strbuff = s;
	boost::asio::async_write(socket, boost::asio::buffer(strbuff, strbuff.size()), [&](boost::system::error_code ec, size_t t){
		if (ec){
			std::cout << "[P]写入出错： " << ec.message() << std::endl;
			std::cout << "[P]exit" << std::endl;
			socket.close();
			return;
		}
		std::cout << "[S]" << strbuff << std::endl;
	});
}

int Player::getId(){
	return sessionId;
}