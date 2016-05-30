cmake_minimum_required(VERSION 3.2)
project(XestCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dep/cppformat
        ${CMAKE_CURRENT_SOURCE_DIR}/dep/protobuf/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Common
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Utilities
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Logging
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/Configuration
        ${CMAKE_CURRENT_SOURCE_DIR}/Shared
        ${CMAKE_CURRENT_SOURCE_DIR}/Server
        ${CMAKE_CURRENT_SOURCE_DIR}/Service
)


add_subdirectory(Common)
add_subdirectory(dep)
add_subdirectory(Server)
add_subdirectory(Service)


set(SOURCE_FILES Main.cpp)

add_executable(XestCore ${SOURCE_FILES})
target_link_libraries(XestCore Server Service Common cppformat boost_system protobuf pthread)