//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_SOCKET_H
#define XESTCORE_SOCKET_H

#include "MessageBuffer.h"
#include "Log.h"
#include <atomic>
#include <queue>
#include <memory>
#include <functional>
#include <type_traits>
#include <boost/asio/ip/tcp.hpp>
using boost::asio::ip::tcp;

#define READ_BLOCK_SIZE 4096
#ifdef BOOST_ASIO_HAS_IOCP
#define TC_SOCKET_USE_IOCP
#endif

/**
    @class Socket

    Base async socket implementation

    @tparam T derived class type (CRTP)
    @tparam Stream stream type used for operations on socket
            Stream must implement the following methods:

            void close(boost::system::error_code& error);

            void shutdown(boost::asio::socket_base::shutdown_type what, boost::system::error_code& shutdownError);

            template<typename MutableBufferSequence, typename ReadHandlerType>
            void async_read_some(MutableBufferSequence const& buffers, ReadHandlerType&& handler);

            template<typename ConstBufferSequence, typename WriteHandlerType>
            void async_write_some(ConstBufferSequence const& buffers, WriteHandlerType&& handler);

            template<typename ConstBufferSequence>
            std::size_t write_some(ConstBufferSequence const& buffers, boost::system::error_code& error);

            template<typename SettableSocketOption>
            void set_option(SettableSocketOption const& option, boost::system::error_code& error);

            tcp::socket::endpoint_type remote_endpoint() const;
*/

#endif //XESTCORE_SOCKET_H
