#ifndef _ASYNC_ACCEPTOR_H_
#define _ASYNC_ACCEPTOR_H_
#include <atomic>
#include <boost/asio.hpp>
#include "Log.h"
#include "Socket.h"

using boost::asio::ip::tcp;

class AsyncAcceptor
{
	typedef void(*AcceptCallback)(tcp::socket&& newSocket, uint32 threadIndex);
public:
	AsyncAcceptor(boost::asio::io_service& ioService, std::string ipAddress, uint16 ipPort):
		_acceptor(ioService), _endpoint(tcp::endpoint(boost::asio::ip::address::from_string(ipAddress), ipPort)),
		_socket(ioService), _closed(false), _socketFactory(std::bind(&AsyncAcceptor::DefeaultSocketFactory, this))
	{
	}
	template<typename T>
	void AsyncAccept() 
	{
		_acceptor.async_accept(_socket, [this](boost::system::error_code errorCode) 
		{
			if (!errorCode) 
			{
				try 
				{
					std::make_shared<T>(std::move(_socket))->Start();
				}
				catch (boost::system::system_error const& err) 
				{
					Trace("[ACCE]�������ӳ���:(%d)%s", err.code().value(), err.what());
				}
			}

			AsyncAccept<T>();
		});
	}

	template<AcceptCallback acceptCallback>
	void AsyncAcceptWithCallback()
	{
		tcp::socket* socket;
		uint32 threadIndex;
		std::tie(socket, threadIndex) = _socketFactory();
		_acceptor.async_accept(*socket, [this, socket, threadIndex](boost::system::error_code error)
		{
			if (!error)
			{
				try
				{
					socket->non_blocking(true);

					acceptCallback(std::move(*socket), threadIndex);
				}
				catch (boost::system::system_error const& err)
				{
					Trace("Failed to initialize client's socket %s", err.what());
				}
			}

			if (!_closed)
				this->AsyncAcceptWithCallback<acceptCallback>();
		});
	}

	void Close()
	{
		if (_closed.exchange(true))
			return;

		boost::system::error_code err;
		_acceptor.close(err);
	}

	bool Bind()
	{
		boost::system::error_code errorCode;
		_acceptor.open(_endpoint.protocol(), errorCode);
		if (errorCode)
		{
			Trace("Failed to open acceptor %s", errorCode.message().c_str());
			return false;
		}

		_acceptor.bind(_endpoint, errorCode);
		if (errorCode)
		{
			Trace( "Could not bind to %s:%u %s", _endpoint.address().to_string().c_str(), _endpoint.port(), errorCode.message().c_str());
			return false;
		}

		_acceptor.listen(boost::asio::socket_base::max_connections, errorCode);
		if (errorCode)
		{
			Trace( "Failed to start listening on %s:%u %s", _endpoint.address().to_string().c_str(), _endpoint.port(), errorCode.message().c_str());
			return false;
		}

		return true;
	}

	void SetSocketFactory(std::function<std::pair<tcp::socket*, uint32>()> func) { _socketFactory = func; }

private:
	tcp::acceptor _acceptor;
	tcp::socket _socket;
	tcp::endpoint _endpoint;
	std::atomic<bool> _closed;

	std::pair<tcp::socket*, uint32> DefeaultSocketFactory() { return std::make_pair(&_socket, 0); }
	std::function<std::pair<tcp::socket*, uint32>()> _socketFactory;
};

#endif //!_ASYNC_ACCEPTOR_H_