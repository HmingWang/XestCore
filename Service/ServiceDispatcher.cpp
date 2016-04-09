//
// Created by whaim on 16-4-9.
//

#include "ServiceDispatcher.h"
#include "Log.h"
#include "Session.h"

ServiceDispatcher::ServiceDispatcher()
{
/*    AddService<Services::Account>();
    AddService<Services::Authentication>();
    AddService<Service<challenge::v1::ChallengeService>>();
    AddService<Service<channel::v1::ChannelService>>();
    AddService<Services::Connection>();
    AddService<Service<friends::v1::FriendsService>>();
    AddService<Services::GameUtilities>();
    AddService<Service<presence::v1::PresenceService>>();
    AddService<Service<report::v1::ReportService>>();
    AddService<Service<resources::v1::ResourcesService>>();
    AddService<Service<user_manager::v1::UserManagerService>>();
*/
}

void ServiceDispatcher::Dispatch(Session* session, uint32 serviceHash, uint32 token, uint32 methodId, MessageBuffer buffer)
{
    auto itr = _dispatchers.find(serviceHash);
    if (itr != _dispatchers.end())
        itr->second(session, token, methodId, std::forward<MessageBuffer>(buffer));
    else
        TC_LOG_DEBUG("session.rpc", "%s tried to call invalid service 0x%X", session->GetClientInfo().c_str(), serviceHash);
}

ServiceDispatcher& ServiceDispatcher::Instance()
{
    static ServiceDispatcher instance;
    return instance;
}