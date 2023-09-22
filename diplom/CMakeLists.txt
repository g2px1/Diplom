cmake_minimum_required(VERSION 3.26)
project(diplom)

set(CMAKE_CXX_STANDARD 20)

add_executable(diplom main.cpp
        ContainerTest.cpp
        ContainerTest.h
        PRNG.cpp
        PRNG.h
        DurationCounter.cpp
        DurationCounter.h)
