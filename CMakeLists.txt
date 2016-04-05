cmake_minimum_required(VERSION 3.4)
project(XestCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dep
        ${CMAKE_CURRENT_SOURCE_DIR}/Common
        ${CMAKE_CURRENT_SOURCE_DIR}/Configuration
)

add_subdirectory(Logging)
add_subdirectory(Common)
add_subdirectory(dep)
add_subdirectory(Configuration)


set(SOURCE_FILES Main.cpp)

add_executable(XestCore ${SOURCE_FILES})
target_link_libraries(XestCore Logging cppformat)