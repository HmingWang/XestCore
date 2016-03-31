project(Logging)

include_directories(XESTCORE_SOURCE_DIR)

set(LIB_LOG_SOURCE
        Appender.cpp
        Appender.h
        AppenderFile.cpp
        AppenderFile.h
        Log.cpp
        Log.h)

add_library(Logging SHARED ${LIB_LOG_SOURCE})
