cmake_minimum_required(VERSION 3.26)
project(diplom)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        random
        duration
        operations
        containerTest
        thread
        dataGenerator
)

add_executable(diplom main.cpp
        containerTest/ContainerTest.h
        random/PRNG.cpp
        random/PRNG.h
        duration/DurationCounter.cpp
        duration/DurationCounter.h
        operations/TestOperations.h
        thread/Pool.h
        operations/ContainerPreparer.h
        operations/ContainerFunctions.h
        dataGenerator/Generator.h
)
