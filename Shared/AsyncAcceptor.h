//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_ASYNCACCEPTOR_H
#define XESTCORE_ASYNCACCEPTOR_H

#include "Log.h"
#include <boost/asio.hpp>
#include <functional>
#include <atomic>

using boost::asio::ip::tcp;

class AsyncAcceptor
{
public:
    typedef void(*AcceptCallback)(tcp::socket&& newSocket, uint32 threadIndex);

    AsyncAcceptor(boost::asio::io_service& ioService, std::string const& bindIp, uint16 port) :
            _acceptor(ioService, tcp::endpoint(boost::asio::ip::address::from_string(bindIp), port)),
            _socket(ioService), _closed(false), _socketFactory(std::bind(&AsyncAcceptor::DefeaultSocketFactory, this))
    {
    }

    template<class T>
    void AsyncAccept();

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
                    TC_LOG_INFO("network", "Failed to initialize client's socket %s", err.what());
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

    void SetSocketFactory(std::function<std::pair<tcp::socket*, uint32>()> func) { _socketFactory = func; }

private:
    std::pair<tcp::socket*, uint32> DefeaultSocketFactory() { return std::make_pair(&_socket, 0); }

    tcp::acceptor _acceptor;
    tcp::socket _socket;
    std::atomic<bool> _closed;
    std::function<std::pair<tcp::socket*, uint32>()> _socketFactory;
};

template<class T>
void AsyncAcceptor::AsyncAccept()
{
    _acceptor.async_accept(_socket, [this](boost::system::error_code error)
    {
        if (!error)
        {
            try
            {
                // this-> is required here to fix an segmentation fault in gcc 4.7.2 - reason is lambdas in a templated class
                std::make_shared<T>(std::move(this->_socket))->Start();
            }
            catch (boost::system::system_error const& err)
            {
                TC_LOG_INFO("network", "Failed to retrieve client's remote address %s", err.what());
            }
        }

        // lets slap some more this-> on this so we can fix this bug with gcc 4.7.2 throwing internals in yo face
        if (!_closed)
            this->AsyncAccept<T>();
    });
}
#endif //XESTCORE_ASYNCACCEPTOR_H
