//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_SESSION_H
#define XESTCORE_SESSION_H

#include <google/protobuf/message.h>
#include "Socket.h"
namespace pb = google::protobuf;

namespace bgs
{
    namespace protocol
    {
        class Variant;

        namespace account
        {
            namespace v1
            {
                class GetAccountStateRequest;
                class GetAccountStateResponse;
                class GetGameAccountStateRequest;
                class GetGameAccountStateResponse;
            }
        }

        namespace authentication
        {
            namespace v1
            {
                class LogonRequest;
                class VerifyWebCredentialsRequest;
            }
        }

        namespace game_utilities
        {
            namespace v1
            {
                class ClientRequest;
                class ClientResponse;
                class GetAllValuesForAttributeRequest;
                class GetAllValuesForAttributeResponse;
            }
        }
    }
}

using namespace bgs::protocol;
class Session : public Socket<Session>
{
    typedef Socket<Session> SessionSocket; //Base Class
public:
    explicit Session(tcp::socket&& socket);
    ~Session();

    void Start() override;
    bool Update() override;

    std::string GetClientInfo() const;

protected:
    void ReadHandler() override;
    bool ReadHeaderLengthHandler();
    bool ReadHeaderHandler();
    bool ReadDataHandler();

private:
    void AsyncWrite(MessageBuffer* packet);

    MessageBuffer _headerLengthBuffer; //?
    MessageBuffer _headerBuffer;
    MessageBuffer _packetBuffer;

    std::unordered_map<uint32, std::function<void(MessageBuffer)>> _responseCallbacks;
};


#endif //XESTCORE_SESSION_H
