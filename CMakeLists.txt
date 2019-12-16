cmake_minimum_required(VERSION 3.10)
project(zlsmart)

set(CMAKE_CXX_STANDARD 17)

add_executable(zlsmart
        base/Noncopyable.h
        base/Socket.cpp
        base/Socket.h
        base/InetAddress.cpp
        base/InetAddress.h
        )
