#include "Session.h"
#include "ParserX.hpp"
#include "Command.hpp"

Session::~Session()
{
	cout << "[SESS]["<<m_ID<<"][" << getAddress() << ":" << getPort() << "]析构会话" << endl;
	cout << "[SESS][" << m_ID << "]========The End========" << endl;
	m_spSocket->close();
}

Session::Session(int id,sptr_Socket ps):m_ID(id),m_spSocket(ps)
{
	cout << "[SESS]["<< m_ID <<"][" << getAddress() << ":" << getPort() << "]构造会话" << endl;
}

bool Session::isConnected()
{
	return this->m_spSocket !=nullptr&&this->m_spSocket->is_open();
}

void Session::do_read() 
{
	try {
		boost::asio::async_read_until(*m_spSocket, m_ReadBuffer, '\0', [&](boost::system::error_code ec, size_t t) {
			if (ec) {
				std::cout << "[SESS]读取错误: " << ec.message() << std::endl;
				sSessionMgr.erase(m_ID);
				return;
			}
			std::ostringstream oss;
			oss << &m_ReadBuffer;
			std::string msg = oss.str();
			std::cout << "[SESS][" << getAddress() << ":" << getPort() << "][" << msg.size() << "]>>>" << msg << std::endl;
			//调用命令解析
			sParserX.parserCommand(Command(m_ID,msg));
			do_read();

		});
	}
	catch (string &e) 
	{
		throw e;
	}
}

void Session::do_write(string strMsg="") 
{
	m_WriteBuffer = strMsg;
	boost::asio::async_write(*m_spSocket, boost::asio::buffer(m_WriteBuffer, m_WriteBuffer.size()), [&](boost::system::error_code ec, size_t t) {
		if (ec) {
			std::cout << "[SESS]写入出错： " << ec.message() << std::endl;
			sSessionMgr.erase(m_ID);
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

int Session::GetID()
{
	return m_ID;
}

void Session::start()
{
	//do_write(cstr_login);
	do_read();
}

void Session::close()
{
	return m_spSocket->close();
}
