project(Logging)



set(LIB_LOG_SOURCE
        Appender.cpp
        Appender.h
        AppenderFile.cpp
        AppenderFile.h
        Log.cpp
        Log.h Logger.cpp Logger.h AppenderConsole.cpp AppenderConsole.h LogOperation.cpp LogOperation.h)

add_library(Logging SHARED ${LIB_LOG_SOURCE})
