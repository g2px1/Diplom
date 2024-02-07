cmake_minimum_required(VERSION 3.27)
project(cdsTest)

set(CMAKE_CXX_STANDARD 20)

add_definitions(
        -DMSQUEUE_TEST=0
        -DBUCKETQUEUE_TEST=0
        -DBRONSONTREE_TEST=0 # Not working as for now
)

find_package(LibCDS REQUIRED)
find_package(benchmark REQUIRED)

add_executable(cdsTest main.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        benchmark::benchmark
        benchmark::benchmark_main
        LibCDS::cds
)