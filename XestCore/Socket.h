#ifndef _SOCKET_H_
#define _SOCKET_H_

//==============================
//Socket 模板基类
//==============================
#include <atomic>
#include <queue>
#include <boost/asio/ip/tcp.hpp>
#include "Define.h"
#include "MessageBuffer.h"
#include "Log.h"

using boost::asio::ip::tcp;
template<typename T>
class Socket : public std::enable_shared_from_this<T>
{

public:
	Socket(tcp::socket&& socket) :
		_socket(std::move(socket)),
		_remoteAddress(_socket.remote_endpoint().address()),
		_remotePort(_socket.remote_endpoint().port()),
		_readBuffer(),
		_writeQueue(),
		_closed(false)
	{
	}
	virtual ~Socket() 
	{
	}

	virtual void Start() = 0;
	virtual void OnClose() = 0;
	virtual void ReadHandler() = 0;

	virtual bool Update()
	{
		if (_closed)
			return false;

		return true;
	}

	void AsyncRead()
	{
		if (!IsOpen())
			return;
		_readBuffer.Normalize();
		_readBuffer.EnsureFreeSpace();
		_socket.async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
			std::bind(&Socket<T>::ReadHandlerInternal, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
	bool IsOpen()
	{
		return _socket.is_open();
	}
	void CloseSocket()
	{
		Trace("[SOCK]关闭连接");
		boost::system::error_code shutdownError;
		_socket.shutdown(boost::asio::socket_base::shutdown_send, shutdownError);
		if (shutdownError)
			Trace("[SOCK]关闭连接出错:(%d)%s", shutdownError.value(), shutdownError.message().c_str());

		OnClose();
	}

	MessageBuffer& GetReadBuffer() 
	{
		return _readBuffer; 
	}
	void QueuePacket(MessageBuffer&& packet)
	{
		_writeQueue.push(std::move(packet));
		AsyncProcessQueue();
	}
	boost::asio::ip::address GetRemoteIpAddress() const
	{
		return _remoteAddress;
	}
	uint16 GetRemotePort() 
	{
		return _remotePort;
	}
private:
	void AsyncProcessQueue()
	{
		MessageBuffer& buffer = _writeQueue.front();
		_socket.async_write_some(boost::asio::buffer(buffer.GetReadPointer(), buffer.GetActiveSize()),
			std::bind(&Socket<T>::WriteHandler, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
	void WriteHandler(boost::system::error_code errorCode, std::size_t transferredBytes)
	{
		if (errorCode)
		{
			Trace("[SOCK]写入消息出错:(%d)%s", errorCode.value(), errorCode.message().c_str());
			CloseSocket();
			return;
		}

		_writeQueue.front().ReadCompleted(transferredBytes);
		if (!_writeQueue.front().GetActiveSize())
			_writeQueue.pop();
		if (!_writeQueue.empty())
			AsyncProcessQueue();
		//CloseSocket();
	}
	void ReadHandlerInternal(boost::system::error_code errorCode, std::size_t transferredBytes)
	{
		if (errorCode)
		{
			Trace("[SOCK]读取消息出错:(%d)%s", errorCode.value(), errorCode.message().c_str());
			CloseSocket();
			return;
		}
		_readBuffer.WriteCompleted(transferredBytes);

		ReadHandler();
		AsyncRead();
	}


private:
	tcp::socket _socket;
	std::atomic<bool> _closed;
	MessageBuffer _readBuffer;
	std::queue<MessageBuffer> _writeQueue;
	boost::asio::ip::address _remoteAddress;
	uint16 _remotePort;



};


#endif //!_SOCKET_H_


