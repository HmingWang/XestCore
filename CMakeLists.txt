cmake_minimum_required(VERSION 3.7)
project(XestCore)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CLIENT/chat_message.hpp
        CLIENT/Main.cpp
        XestCore/AsyncAcceptor.h
        XestCore/Command.hpp
        XestCore/CompilerDefs.h
        XestCore/DBUtil.hpp
        XestCore/Define.h
        XestCore/Desktop.cpp
        XestCore/Desktop.h
        XestCore/format.cc
        XestCore/format.h
        XestCore/GameCard.hpp
        XestCore/IdentityCard.hpp
        XestCore/Log.h
        XestCore/Main.cpp
        XestCore/MessageBuffer.h
        XestCore/MsgQueue.hpp
        XestCore/NetworkThread.h
        XestCore/ObjectCard.hpp
        XestCore/ParserX.hpp
        XestCore/Player.cpp
        XestCore/Player.h
        XestCore/PowerCard.hpp
        XestCore/RoleCard.hpp
        XestCore/Session.h
        XestCore/SessionMgr.h
        XestCore/Socket.h
        XestCore/SocketMgr.h
        XestCore/stdxafx.h
        XestCore/Util.hpp
        XestCore/XString.hpp
        .gitattributes
        .gitignore
        README.md)

add_executable(XestCore ${SOURCE_FILES})