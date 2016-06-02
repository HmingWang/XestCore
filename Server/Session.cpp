//
// Created by whaim on 16-4-8.
//

#include "Session.h"
#include "ServiceDispatcher.h"
#include "Message.h"

Session::Session(tcp::socket&& socket) : SessionSocket(std::move(socket))
{
    //_headerLengthBuffer.Resize(2);
    _headerBuffer.Resize(sizeof(Header));
}

Session::~Session()
{
}

void Session::Start()
{
    std::string ip_address = GetRemoteIpAddress().to_string();
    TRACE("%s Accepted connection", GetClientInfo().c_str());

    // Verify that this IP is not in the ip_banned table
    //LoginDatabase.Execute(LoginDatabase.GetPreparedStatement(LOGIN_DEL_EXPIRED_IP_BANS));

    //PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_IP_INFO);
    //stmt->setString(0, ip_address);
    //stmt->setUInt32(1, inet_addr(ip_address.c_str()));

    //_queryCallback = std::bind(&Session::CheckIpCallback, this, std::placeholders::_1);
    //_queryFuture = LoginDatabase.AsyncQuery(stmt);

    AsyncRead();
}

bool Session::Update()
{
    if (!SessionSocket::Update())
        return false;

    // Do Update things...

    return true;
}

void Session::AsyncWrite(MessageBuffer* packet)
{
    if (!IsOpen())
        return;

    QueuePacket(std::move(*packet));
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
        //ASSERT(inputBuffer.GetActiveSize() == 0);
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

void Session::ReadHandler()
{
    if (!IsOpen())
        return;

    MessageBuffer& packet = GetReadBuffer();
    while (packet.GetActiveSize() > 0)
    {

        if (!PartialProcessPacket<&Session::ReadHeaderHandler, &Session::_headerBuffer>(this, packet))
            break;

        if (!PartialProcessPacket<&Session::ReadDataHandler, &Session::_packetBuffer>(this, packet))
            break;

        //_headerLengthBuffer.Reset();
        _headerBuffer.Reset();
    }

    AsyncRead();
}

/*bool Session::ReadHeaderLengthHandler()
{
    uint16 len = *reinterpret_cast<uint16*>(_headerLengthBuffer.GetReadPointer());
    EndianConvertReverse(len);
    _headerBuffer.Resize(len); //根据头部长度设置头部Buffer大小
    TRACE("报文头部长度[%d]",len);
    return true;
}*/

bool Session::ReadHeaderHandler()
{
    Header header;
    if (!header.ParseFromArray(_headerBuffer.GetReadPointer(), _headerBuffer.GetActiveSize()))
        return true;

    header.Print();

    _packetBuffer.Resize(header.Get_DataLenth());
    return true;
}

bool Session::ReadDataHandler()
{
    Header header;
    header.ParseFromArray(_headerBuffer.GetReadPointer(), _headerBuffer.GetActiveSize());

    /*if (header.service_id() != 0xFE)
    {
        sServiceDispatcher.Dispatch(this, header.service_hash(), header.token(), header.method_id(), std::move(_packetBuffer));
    }
    else
    {
        auto itr = _responseCallbacks.find(header.token());
        if (itr != _responseCallbacks.end())
        {
            itr->second(std::move(_packetBuffer));
            _responseCallbacks.erase(header.token());
        }
        else
            _packetBuffer.Reset();
    }*/

    return true;
}

std::string Session::GetClientInfo() const
{
    std::ostringstream stream;
    stream << '[' << GetRemoteIpAddress() << ':' << GetRemotePort() << ']';
    return stream.str();
}
