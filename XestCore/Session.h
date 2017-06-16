#ifndef _SESSION_H_
#define _SESSION_H_

#include "Socket.h"
#include "format.h"

#define MODECODE "SESS"

class Session:public Socket<Session>
{
public:
	Session(tcp::socket&& socket) :Socket<Session>(std::move(socket)),_packet()
	{
		
	}
	void Start() 
	{
		Trace("接收连接:[%s]", GetClientInfo().c_str());
		AsyncRead();
	}
	void ReadHandler() override 
	{
		Trace(">>(%d)%s",GetReadBuffer().GetActiveSize(), GetReadBuffer().GetReadPointer());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());
	}

	void Session::AsyncWrite(MessageBuffer&& packet)
	{
		if (!IsOpen())
			return;

		QueuePacket(std::move(packet));
	}

	void OnClose() override 
	{
	}
	std::string GetClientInfo() 
	{
		return fmt::sprintf("%s:%d", GetRemoteIpAddress().to_string(), GetRemotePort());
	}
private:
	MessageBuffer _packet;
};
#endif // _SESSION_H_
