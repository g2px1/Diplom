cmake_minimum_required(VERSION 3.26)
project(diplom)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        duration
        generator
)

find_package(LibCDS REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

add_executable(${PROJECT_NAME} main.cpp
        duration/DurationCounter.cpp
        duration/DurationCounter.h
        generator/Generator.cpp
        generator/Generator.h
        utils/test/ContainerTest.cpp
        utils/test/ContainerTest.h
        utils/wrapper/ContainerWrapper.cpp
        utils/wrapper/ContainerWrapper.h
        utils/wrapper/QueueWrapper.cpp
        utils/wrapper/QueueWrapper.h
)

target_link_libraries(${PROJECT_NAME}
        LibCDS::cds
        Boost::boost
        Boost::thread
)