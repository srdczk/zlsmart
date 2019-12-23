cmake_minimum_required(VERSION 3.10)
project(zlsmart)

set(CMAKE_CXX_STANDARD 17)

add_executable(zlsmart
        Buffer.h
        main.cpp
        Noncopyable.h
        ReadConfig.cpp
        ReadConfig.h
        Logger.cpp
        Logger.h
        )
