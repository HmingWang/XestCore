

include_directories(
        ${XESTCORE_SOURCE_DIR}/dep
        ${XESTCORE_SOURCE_DIR}/Common
)

set(LIB_LOG_SOURCE
        Appender.cpp
        Appender.h
        AppenderFile.cpp
        AppenderFile.h
        Log.cpp
        Log.h Logger.cpp Logger.h)

add_library(Logging SHARED ${LIB_LOG_SOURCE})
