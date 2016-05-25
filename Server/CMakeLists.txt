project(Server)

set(LIB_SERVER_SOURCE Session.cpp Session.h SessionManager.cpp SessionManager.h
        proto/Client/rpc_types.pb.h
        proto/Client/rpc_types.pb.cc)


add_library(Server ${LIB_SERVER_SOURCE})

