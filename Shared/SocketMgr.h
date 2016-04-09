//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_SOCKETMGR_H
#define XESTCORE_SOCKETMGR_H

#include "AsyncAcceptor.h"
//#include "Errors.h"
#include "NetworkThread.h"
#include <boost/asio/ip/tcp.hpp>
#include <memory>

using boost::asio::ip::tcp;

template<class SocketType>
class SocketMgr
{
public:
    virtual ~SocketMgr()
    {
        //ASSERT(!_threads && !_acceptor && !_threadCount, "StopNetwork must be called prior to SocketMgr destruction");
    }

    virtual bool StartNetwork(boost::asio::io_service& service, std::string const& bindIp, uint16 port, int threadCount)
    {
        //ASSERT(threadCount > 0);

        try
        {
            _acceptor = new AsyncAcceptor(service, bindIp, port);
        }
        catch (boost::system::system_error const& err)
        {
            TC_LOG_ERROR("network", "Exception caught in SocketMgr.StartNetwork (%s:%u): %s", bindIp.c_str(), port, err.what());
            return false;
        }

        _threadCount = threadCount;
        _threads = CreateThreads();

        //ASSERT(_threads);

        for (int32 i = 0; i < _threadCount; ++i)
            _threads[i].Start();

        return true;
    }

    virtual void StopNetwork()
    {
        _acceptor->Close();

        if (_threadCount != 0)
            for (int32 i = 0; i < _threadCount; ++i)
                _threads[i].Stop();

        Wait();

        delete _acceptor;
        _acceptor = nullptr;
        delete[] _threads;
        _threads = nullptr;
        _threadCount = 0;
    }

    void Wait()
    {
        if (_threadCount != 0)
            for (int32 i = 0; i < _threadCount; ++i)
                _threads[i].Wait();
    }

    virtual void OnSocketOpen(tcp::socket&& sock, uint32 threadIndex)
    {
        try
        {
            std::shared_ptr<SocketType> newSocket = std::make_shared<SocketType>(std::move(sock));
            newSocket->Start();

            _threads[threadIndex].AddSocket(newSocket);
        }
        catch (boost::system::system_error const& err)
        {
            TC_LOG_WARN("network", "Failed to retrieve client's remote address %s", err.what());
        }
    }

    int32 GetNetworkThreadCount() const { return _threadCount; }

    uint32 SelectThreadWithMinConnections() const
    {
        uint32 min = 0;

        for (int32 i = 1; i < _threadCount; ++i)
            if (_threads[i].GetConnectionCount() < _threads[min].GetConnectionCount())
                min = i;

        return min;
    }

    std::pair<tcp::socket*, uint32> GetSocketForAccept()
    {
        uint32 threadIndex = SelectThreadWithMinConnections();

        return std::make_pair(_threads[threadIndex].GetSocketForAccept(), threadIndex);
    }

protected:
    SocketMgr() : _acceptor(nullptr), _threads(nullptr), _threadCount(1)
    {
    }

    virtual NetworkThread<SocketType>* CreateThreads() const = 0;

    AsyncAcceptor* _acceptor;
    NetworkThread<SocketType>* _threads;
    int32 _threadCount;
};

#endif //XESTCORE_SOCKETMGR_H
