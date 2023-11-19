cmake_minimum_required(VERSION 3.26)
project(diplom)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        random
        duration
        operations
        containerTest
        thread
        testGenerator
)

add_executable(${PROJECT_NAME} main.cpp
        duration/DurationCounter.cpp
        duration/DurationCounter.h
        generator/Generator.cpp
        generator/Generator.h
)
