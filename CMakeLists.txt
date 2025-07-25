cmake_minimum_required(VERSION 3.14)
project(PathfindingVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ejecutable principal
add_executable(pathfinding_visualizer src/main.cpp)

# Tests
add_executable(unit_tests
    tests/test_main.cpp
)

target_include_directories(unit_tests PRIVATE tests)
enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
