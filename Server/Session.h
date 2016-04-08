//
// Created by whaim on 16-4-8.
//

#ifndef XESTCORE_SESSION_H
#define XESTCORE_SESSION_H


#include "Socket.h"

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
};


#endif //XESTCORE_SESSION_H
