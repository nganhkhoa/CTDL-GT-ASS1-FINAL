cmake_minimum_required(VERSION 2.8)
project(a01)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(WARNING "-Wall")
set(CPPVERSION "-DAVL_USE_HEIGHT -DUSE_CUSTOM_COMPARE -DUSE_HASH -std=c++11")

set(CMAKE_CXX_FLAGS ${WARNING}\ ${PUBLIC}\ ${IDENTIFIER}\ ${CPPVERSION})

set(SOURCE_FILES main.cpp eventLib.cpp dbLib.cpp processData.cpp)
add_executable(a01 ${SOURCE_FILES})