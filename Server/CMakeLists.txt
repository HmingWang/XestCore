project(Server)

set(LIB_SERVER_SOURCE Session.cpp Session.h SessionManager.cpp SessionManager.h
        Message.cpp Message.h)

add_library(Server ${LIB_SERVER_SOURCE})

