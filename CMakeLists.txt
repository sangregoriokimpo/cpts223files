cmake_minimum_required(VERSION 3.29)
project(MA2)

set(CMAKE_CXX_STANDARD 26)

add_executable(MA2 main.cpp
        Queue.cpp
        Queue.h
        QueueNode.cpp
        QueueNode.h)
