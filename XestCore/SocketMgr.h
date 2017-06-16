#ifndef _SOCKET_MGR_H_
#define _SOCKET_MGR_H_

#include "AsyncAcceptor.h"
#include "NetworkThread.h"

template<typename SocketType>
class SocketMgr 
{
	typedef std::shared_ptr<AsyncAcceptor> sptr_AsyncAcceptor;
	typedef std::vector<std::shared_ptr<NetworkThread<SocketType>>> sptrNetworkThread_Container;
	typedef std::shared_ptr<tcp::socket> sptr_socket;
public:
	SocketMgr() : _acceptor(nullptr), _threads(), _threadCount(1)
	{
	}
	virtual ~SocketMgr()
	{
	}
	virtual void CreateThreads() 
	{
		for (int i = 0;i < _threadCount;++i)
		{
			_threads.emplace_back(std::make_shared<NetworkThread<SocketType>>());
		}
	}

	virtual bool StartNetwork(boost::asio::io_service& ioService, std::string const& bindIp, uint16 port, int threadCount=1) 
	{

		try
		{
			_acceptor = std::make_shared<AsyncAcceptor>(ioService, bindIp, port);
		}
		catch (boost::system::system_error const& err)
		{
			Trace("[SKMR]Æô¶¯ÍøÂç·þÎñ´íÎó(%s:%u): %s", bindIp.c_str(), port, err.what());
			return false;
		}

		if (!_acceptor->Bind())
		{
			Trace( "StartNetwork failed to bind socket acceptor");
			return false;
		}

		_threadCount = threadCount;
		CreateThreads();


		for (auto& t: _threads)
			t->Start();

		return true;
	}

	virtual void StopNetwork()
	{
		_acceptor->Close();

		if (_threadCount != 0)
			for (auto& t : _threads)
				t->Stop();

		Wait();

		
		_acceptor = nullptr;
		_threads.clear();
		_threadCount = 0;
	}

	void Wait()
	{
		if (_threadCount != 0)
			for (auto& t : _threads)
				t->Wait();
	}

	std::pair<tcp::socket*, uint32> GetSocketForAccept()
	{
		uint32 threadIndex = SelectThreadWithMinConnections();
		return std::make_pair(_threads[threadIndex]->GetSocketForAccept(), threadIndex);
	}

	uint32 SelectThreadWithMinConnections() const
	{
		uint32 min = 0;

		for (int32 i = 1; i < _threadCount; ++i)
			if (_threads[i]->GetConnectionCount() < _threads[min]->GetConnectionCount())
				min = i;

		return min;
	}

	virtual void OnSocketOpen(tcp::socket&& sock, uint32 threadIndex)
	{
		try
		{
			std::shared_ptr<SocketType> newSocket = std::make_shared<SocketType>(std::move(sock));
			newSocket->Start();

			_threads[threadIndex]->AddSocket(newSocket);
		}
		catch (boost::system::system_error const& err)
		{
			Trace("Failed to retrieve client's remote address %s", err.what());
		}
	}
protected:
	int _threadCount;
	sptr_AsyncAcceptor _acceptor;
	sptrNetworkThread_Container _threads;
};

#endif