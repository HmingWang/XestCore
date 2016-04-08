//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_NETWORKTHREAD_H
#define XESTCORE_NETWORKTHREAD_H

#include "Define.h"
//#include "Errors.h"
#include "Log.h"
//#include "Timer.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <set>
#include <thread>

using boost::asio::ip::tcp;

template<class SocketType>
class NetworkThread
{
public:
    NetworkThread() : _connections(0), _stopped(false), _thread(nullptr),
                      _acceptSocket(_io_service), _updateTimer(_io_service)
    {
    }

    virtual ~NetworkThread()
    {
        Stop();
        if (_thread)
        {
            Wait();
            delete _thread;
        }
    }

    void Stop()
    {
        _stopped = true;
        _io_service.stop();
    }

    bool Start()
    {
        if (_thread)
            return false;

        _thread = new std::thread(&NetworkThread::Run, this);
        return true;
    }

    void Wait()
    {
        //ASSERT(_thread);

        _thread->join();
        delete _thread;
        _thread = nullptr;
    }

    int32 GetConnectionCount() const
    {
        return _connections;
    }

    virtual void AddSocket(std::shared_ptr<SocketType> sock)
    {
        std::lock_guard<std::mutex> lock(_newSocketsLock);

        ++_connections;
        _newSockets.push_back(sock);
        SocketAdded(sock);
    }

    tcp::socket* GetSocketForAccept() { return &_acceptSocket; }

protected:
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

    void Run()
    {
        TC_LOG_DEBUG("misc", "Network Thread Starting");

        _updateTimer.expires_from_now(boost::posix_time::milliseconds(10));
        _updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));
        _io_service.run();

        TC_LOG_DEBUG("misc", "Network Thread exits");
        _newSockets.clear();
        _sockets.clear();
    }

    void Update()
    {
        if (_stopped)
            return;

        _updateTimer.expires_from_now(boost::posix_time::milliseconds(10));
        _updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));

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

private:
    typedef std::vector<std::shared_ptr<SocketType>> SocketContainer;

    std::atomic<int32> _connections;
    std::atomic<bool> _stopped;

    std::thread* _thread;

    SocketContainer _sockets;

    std::mutex _newSocketsLock;
    SocketContainer _newSockets;

    boost::asio::io_service _io_service;
    tcp::socket _acceptSocket;
    boost::asio::deadline_timer _updateTimer;
};

#endif //XESTCORE_NETWORKTHREAD_H
