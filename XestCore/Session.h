#ifndef _SESSION_H_
#define _SESSION_H_

#include "Socket.h"
#include "format.h"
#include "Error.h"
#include "Define.h"

#define MODECODE "SESS"

class Session:public Socket<Session>
{
public:
	Session(tcp::socket&& socket) :Socket<Session>(std::move(socket)),_packetBuffer()
	{
		
	}
	void Start() 
	{
		Trace("接收连接:[%s]", GetClientInfo().c_str());
		SendRequest(cstr_login);
		SendRequest("请输入阁下尊姓大名：");
		AsyncRead();
	}
	void ReadHandler() override 
	{
		if (!IsOpen())
			return;

		MessageBuffer& packet = GetReadBuffer();
		while (packet.GetActiveSize() > 0)
		{
			if (!PartialProcessPacket<&Session::ReadDataHandler, &Session::_packetBuffer>(this, packet))
				break;

			_packetBuffer.Reset();
		}

		Trace(">>(%d)%s", _packetBuffer.GetActiveSize(), _packetBuffer.GetReadPointer());
		_packetBuffer.ReadCompleted(_packetBuffer.GetActiveSize());
	}

	template<bool(Session::*processMethod)(), MessageBuffer Session::*outputBuffer>
	inline bool PartialProcessPacket(Session* session, MessageBuffer& inputBuffer)
	{
		MessageBuffer& buffer = session->*outputBuffer;

		// We have full read header, now check the data payload
		if (buffer.GetRemainingSpace() > 0)
		{
			// need more data in the payload
			std::size_t readDataSize = std::min(inputBuffer.GetActiveSize(), buffer.GetRemainingSpace());
			buffer.Write(inputBuffer.GetReadPointer(), readDataSize);
			inputBuffer.ReadCompleted(readDataSize);
		}

		if (buffer.GetRemainingSpace() > 0)
		{
			// Couldn't receive the whole data this time.
			ASSERT(inputBuffer.GetActiveSize() == 0);
			return false;
		}

		// just received fresh new payload
		if (!(session->*processMethod)())
		{
			session->CloseSocket();
			return false;
		}

		return true;
	}

	void SendRequest(const char * request) 
	{
		MessageBuffer packet;
		packet.Write(request, strlen(request)+1);
		packet.WriteCompleted(strlen(request) + 1);

		AsyncWrite(packet);
	}

	bool ReadDataHandler()
	{
		//Header header;
		//ASSERT(header.ParseFromArray(_headerBuffer.GetReadPointer(), _headerBuffer.GetActiveSize()));

		//if (header.service_id() != 0xFE)
		//{
		//	sServiceDispatcher.Dispatch(this, header.service_hash(), header.token(), header.method_id(), std::move(_packetBuffer));
		//}
		//else
		//{
		//	auto itr = _responseCallbacks.find(header.token());
		//	if (itr != _responseCallbacks.end())
		//	{
		//		itr->second(std::move(_packetBuffer));
		//		_responseCallbacks.erase(header.token());
		//	}
		//	else
		//		_packetBuffer.Reset();
		//}

		return true;
	}

	void Session::AsyncWrite(MessageBuffer& packet)
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

	MessageBuffer _packetBuffer;
};
#endif // _SESSION_H_
