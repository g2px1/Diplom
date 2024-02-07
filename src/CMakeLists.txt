cmake_minimum_required(VERSION 3.27)
project(diplom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(
        duration
        generator
        ${diplom_SOURCE_DIR}
)

find_package(LibCDS REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        duration/DurationCounter.cpp
        duration/DurationCounter.h
        generator/Generator.cpp
        generator/Generator.h
        test/ContainerTest.cpp
        test/ContainerTest.h
        wrapper/ContainerWrapper.cpp
        wrapper/ContainerWrapper.h
        wrapper/QueueWrapper.cpp
        wrapper/QueueWrapper.h
        manager/TaskManager.cpp
        manager/TaskManager.h
)

target_link_libraries(${PROJECT_NAME}
        LibCDS::cds
)