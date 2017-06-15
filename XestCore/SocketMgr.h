#ifndef _SOCKET_MGR_H_
#define _SOCKET_MGR_H_

#include "AsyncAcceptor.h"
#include "NetworkThread.h"

template<typename SocketType>
class SocketMgr 
{
	typedef std::shared_ptr<AsyncAcceptor> sptr_AsyncAcceptor;
	typedef std::vector<std::shared_ptr<NetworkThread<SocketType>>> sptrNetworkThread_Container;
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
protected:
	int _threadCount;
	sptr_AsyncAcceptor _acceptor;
	sptrNetworkThread_Container _threads;
};

#endif