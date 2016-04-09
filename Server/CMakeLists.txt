project(Server)

set(LIB_SERVER_SOURCE Session.cpp Session.h SessionManager.cpp SessionManager.h proto/Client/rpc_types.pb.h)

add_library(Server ${LIB_SERVER_SOURCE})