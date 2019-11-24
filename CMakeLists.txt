cmake_minimum_required(VERSION 3.10)
project(zlsmart)

set(CMAKE_CXX_STANDARD 17)

add_executable(zlsmart
        src/socket.h
        src/socket.cc
        src/address.h src/noncopyable.h src/epoll.h src/epoll.cc src/event.h src/address.cc src/types.h)