cmake_minimum_required(VERSION 2.8)
project(a01)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(WARNING "-Wall")
set(PUBLIC "-static -static-libgcc -static-libstdc++")
set(IDENTIFIER "-fextended-identifiers --input-charset=utf-8 -finput-charset=utf-8 --exec-charset=utf-8")
set(CPPVERSION "-std=c++11")

set(CMAKE_CXX_FLAGS ${WARNING}\ ${PUBLIC}\ ${IDENTIFIER}\ ${CPPVERSION})

set(SOURCE_FILES main.cpp eventLib.cpp dbLib.cpp processData.cpp)
add_executable(a01 ${SOURCE_FILES})