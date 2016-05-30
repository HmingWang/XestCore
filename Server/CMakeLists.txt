project(Server)

set(LIB_SERVER_SOURCE Session.cpp Session.h SessionManager.cpp SessionManager.h
        proto/Client/rpc_types.pb.h
        proto/Client/rpc_types.pb.cc
        proto/Client/global_extensions/field_options.pb.cc
        proto/Client/global_extensions/field_options.pb.h
        proto/Client/global_extensions/method_options.pb.h
        proto/Client/global_extensions/method_options.pb.cc
        proto/Client/global_extensions/service_options.pb.cc
        proto/Client/global_extensions/service_options.pb.h)

add_library(Server ${LIB_SERVER_SOURCE})

