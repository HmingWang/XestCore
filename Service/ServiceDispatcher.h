//
// Created by whaim on 16-4-9.
//

#ifndef XESTCORE_SERVICEDISPATCHER_H
#define XESTCORE_SERVICEDISPATCHER_H


#include <functional>
#include <unordered_map>
#include "Define.h"
#include "MessageBuffer.h"

class Session;

class ServiceDispatcher
{
public:
    void Dispatch(Session* session, uint32 serviceHash, uint32 token, uint32 methodId, MessageBuffer buffer);

    static ServiceDispatcher& Instance();

private:
    ServiceDispatcher();

    template<class Service>
    void AddService()
    {
        _dispatchers[Service::OriginalHash::value] = &ServiceDispatcher::Dispatch<Service>;
    }

    template<class Service>
    static void Dispatch(Session* session, uint32 token, uint32 methodId, MessageBuffer buffer)
    {
        Service(session).CallServerMethod(token, methodId, std::forward<MessageBuffer>(buffer));
    }

    std::unordered_map<uint32, std::function<void(Session*, uint32, uint32, MessageBuffer)>> _dispatchers;
};

#define sServiceDispatcher ServiceDispatcher::Instance()

#endif //XESTCORE_SERVICEDISPATCHER_H
