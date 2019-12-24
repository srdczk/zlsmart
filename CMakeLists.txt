cmake_minimum_required(VERSION 3.10)
project(zlsmart)

set(CMAKE_CXX_STANDARD 17)

add_executable(zlsmart
        Buffer.h
        main.cpp
        ReadConfig.cpp
        ReadConfig.h
        Logger.cpp
        Logger.h
        NotCopyable.h)

target_link_libraries(zlsmart pthread)
