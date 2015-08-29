#include "Session.h"
#include "ParserX.hpp"
#include "Command.hpp"

Session::~Session()
{
	cout << "[SESS][" << getAddress() << ":" << getPort() << "]关闭会话" << endl;
	m_spSocket->close();
}

Session::Session(sptr_Socket ps):m_spSocket(ps)
{
	cout << "[SESS][" << getAddress() << ":" << getPort() << "]创建会话" << endl;
}

bool Session::isConnected()
{
	return this->m_spSocket !=nullptr&&this->m_spSocket->is_open();
}

void Session::do_read() throw()
{
	boost::asio::async_read_until(*m_spSocket, m_ReadBuffer, '\0', [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]读取错误: " << ec.message() << std::endl;
			throw ec.message();
			//std::cout << "[SESS]==exit==" << std::endl;
			//m_spSocket->close();
			//sSessionMgr.erase(id);
			return;
		}
		std::ostringstream oss;
		oss << &m_ReadBuffer;
		std::string msg = oss.str();
		std::cout << "[SESS][" <<getAddress()<<":"<<getPort()<<"]["<< msg.size()<<"]>>>" << msg  << std::endl;
		//do_write(parser.parserCommand(msg));
		//sParserX.parserCommand(msg);
		//sParserX();
		//sParserX.parserCommand(Command(id,msg));
		do_read();

	});
}

void Session::do_write(string strMsg="") throw()
{
	m_WriteBuffer = strMsg;
	boost::asio::async_write(*m_spSocket, boost::asio::buffer(m_WriteBuffer, m_WriteBuffer.size()), [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]写入出错： " << ec.message() << std::endl;
			throw ec.message();
			//std::cout << "[SESS]exit" << std::endl;
			//m_spSocket->close();

			return;
		}
		std::cout << "[SESS][" << getAddress()<< ":" << getPort() <<"]<<<"<< m_WriteBuffer << std::endl;
	});
}

string Session::getAddress()
{
	return m_spSocket->remote_endpoint().address().to_string();
}

int Session::getPort() 
{
	return m_spSocket->remote_endpoint().port();
}

void Session::start()
{
	//do_write(cstr_login);
	do_read();
}
