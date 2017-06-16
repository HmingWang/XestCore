#ifndef _NETWORK_THREAD_H_
#define _NETWORK_THREAD_H_

#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <set>
#include <thread>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>

#define MODECODE "THRE"
#define UPDATETIME 10000 //线程状态刷新时间（毫秒）

using boost::asio::ip::tcp;

template<typename SocketType>
class NetworkThread 
{
	typedef std::shared_ptr<std::thread> sptr_thread;
	typedef std::vector<std::shared_ptr<SocketType>> SocketContainer;
public:
	NetworkThread() :
		_connections(0),
		_acceptSocket(_ioService),
		_updateTimer(_ioService),
		_threadId(),
		_thread(nullptr)
	{
	}

	bool Start() 
	{
		if (_thread)
			return false;

		_thread = std::make_shared<std::thread>(&NetworkThread::Run, this);
		_threadId = _thread->get_id();
		return true;
	}

	void Run() 
	{
		Trace("线程启动");
		_updateTimer.expires_from_now(boost::posix_time::milliseconds(UPDATETIME));
		_updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));
		_ioService.run();
		Trace("线程结束");
	}
	void Update() 
	{
		_updateTimer.expires_from_now(boost::posix_time::milliseconds(UPDATETIME));
		_updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));
		Trace("线程当前连接数:(ID:%d)%d",_threadId, _connections.load());

		AddNewSockets();

		_sockets.erase(std::remove_if(_sockets.begin(), _sockets.end(), [this](std::shared_ptr<SocketType> sock)
		{
			if (!sock->Update())
			{
				if (sock->IsOpen())
					sock->CloseSocket();

				this->SocketRemoved(sock);

				--this->_connections;
				return true;
			}

			return false;
		}), _sockets.end());
	}

	void Stop()
	{
		_stopped = true;
		_ioService.stop();
	}

	tcp::socket* GetSocketForAccept() { return &_acceptSocket; }

	int32 GetConnectionCount() const
	{
		return _connections;
	}

	void Wait()
	{
		_thread->join();
		_thread = nullptr;
	}

	virtual void AddSocket(std::shared_ptr<SocketType> sock)
	{
		std::lock_guard<std::mutex> lock(_newSocketsLock);

		++_connections;
		_newSockets.push_back(sock);
		SocketAdded(sock);
	}


protected:
	//
	virtual void SocketAdded(std::shared_ptr<SocketType> /*sock*/) { }
	virtual void SocketRemoved(std::shared_ptr<SocketType> /*sock*/) { }

	void AddNewSockets()
	{
		std::lock_guard<std::mutex> lock(_newSocketsLock);

		if (_newSockets.empty())
			return;

		for (std::shared_ptr<SocketType> sock : _newSockets)
		{
			if (!sock->IsOpen())
			{
				SocketRemoved(sock);
				--_connections;
			}
			else
				_sockets.push_back(sock);
		}

		_newSockets.clear();
	}

private:

	std::atomic<bool> _stopped;
	std::atomic<int32> _connections;
	std::mutex _newSocketsLock;

	sptr_thread _thread;
	SocketContainer _sockets;
	SocketContainer _newSockets;

	boost::asio::io_service _ioService;
	tcp::socket _acceptSocket;
	boost::asio::deadline_timer _updateTimer;
	std::thread::id _threadId;


	
};

#endif //!_NETWORK_THREAD_H_