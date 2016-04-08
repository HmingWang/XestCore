project(Common)

set(LIB_COMMON_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/CompilerDefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Define.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Util.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Util.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/MessageBuffer.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Appender.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Appender.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/AppenderFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/AppenderFile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Log.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Logger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Logger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/AppenderConsole.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/AppenderConsole.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/LogOperation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Logging/LogOperation.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Configuration/Config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Configuration/Config.h Utilities/ByteConvert.h)

add_library(Common ${LIB_COMMON_SOURCE})