cmake_minimum_required(VERSION 3.4)
project(XestCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES  Main.cpp Logging/Appender.cpp Logging/Appender.h Define.h CompilerDefs.h)
add_executable(XestCore ${SOURCE_FILES})