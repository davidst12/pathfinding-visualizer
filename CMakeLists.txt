cmake_minimum_required(VERSION 3.14)
project(PathfindingVisualizer VERSION 1.0 LANGUAGES CXX)

##### Compilation #####

set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(Pathfinding ${SOURCES})

target_include_directories(Pathfinding PRIVATE ${HEADER_DIR})


##### Tests #####

add_executable(unit_tests
    tests/test_main.cpp
)

target_include_directories(unit_tests PRIVATE tests)
enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
