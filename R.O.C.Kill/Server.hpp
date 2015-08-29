#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include<iostream>
#include<set>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
//#include "desktop.h"
//#include "Player.h"
#include "Session.h"
#include "ParserX.hpp"
#include "SessionMgr.hpp"

using boost::asio::ip::tcp;

class Server
{
public:
	Server();
	void run();
	void start();

private:
	boost::asio::io_service     io_service;
	boost::system::error_code   error_code;
	tcp::endpoint               endpoint;
	tcp::socket                 socket;
	tcp::acceptor               acceptor;
	map<int, Session>            SessionMap;
	int                         idseq;

	void acceptHandler(std::shared_ptr<tcp::socket>&, boost::system::error_code);
};

Server::Server() :
	io_service(),
	idseq(1000),
	endpoint(tcp::v4(), 1986),
	socket(io_service),
	acceptor(io_service, endpoint)
{
	std::cout << "[SERV]服务器初始化完成..." << std::endl;
}
void Server::start()
{
	std::cout << "[SERV]等待客户端接入..." << std::endl;
	auto pSocket = std::make_shared<tcp::socket>(io_service);
	acceptor.async_accept(*pSocket, boost::bind(&Server::acceptHandler, this, pSocket, this->error_code));
}
void Server::acceptHandler(std::shared_ptr<tcp::socket>& pSocket, boost::system::error_code ec)
{
	if (ec)
	{
		std::cout << "[SERV]连接错误：" << ec.message() << std::endl;
		return;
	}

	std::cout << "[SERV]客户端接入：[IP:" << pSocket->remote_endpoint().address()<<"][PORT:"<<pSocket->remote_endpoint().port()<<"]" << std::endl;

	sSessionMgr.emplace(idseq,pSocket);
	sSessionMgr.getSessionByID(idseq)->start();
	sSessionMgr.SendTo(idseq++, cstr_login);

	start();
}
void Server::run()
{
	try 
	{
		io_service.run();
	}
	catch (...)
	{
		cout << "[SERV]IOSERVICE异常，程序重启" << endl;
		io_service.run();
	}
}

#endif