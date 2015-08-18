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
	//std::shared_ptr<Desktop>    sptr_desktop;
	//std::shared_ptr<Player>     sptr_player;
	//set<Session>                Sessions;
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
	std::cout << "[SERV]��������ʼ�����..." << std::endl;
}
void Server::start()
{
	std::cout << "[SERV]�ȴ��ͻ��˽���..." << std::endl;
	auto pSocket = std::make_shared<tcp::socket>(io_service);
	acceptor.async_accept(*pSocket, boost::bind(&Server::acceptHandler, this, pSocket, this->error_code));
}
void Server::acceptHandler(std::shared_ptr<tcp::socket>& pSocket, boost::system::error_code ec)
{
	if (ec)
	{
		std::cout << "[SERV]���Ӵ���" << ec.message() << std::endl;
		return;
	}

	std::cout << "[SERV]�ͻ��˽��룺[IP:" << pSocket->remote_endpoint().address()<<"][PORT:"<<pSocket->remote_endpoint().port()<<"]" << std::endl;

	sSessionMgr.insert(idseq,pSocket);
	sSessionMgr.getSessionByID(idseq++).start();

	start();
}
void Server::run()
{
	io_service.run();
}

#endif