cmake_minimum_required(VERSION 3.14)
project(PathfindingVisualizer VERSION 1.0 LANGUAGES C CXX)

##### Compilation #####

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Activando instrumentación para Coverage...")
    # Usamos las flags nativas de LLVM/Clang para Apple Silicon
    add_compile_options("-fprofile-instr-generate" "-fcoverage-mapping" "-O0" "-g")
    add_link_options("-fprofile-instr-generate" "-fcoverage-mapping")
endif()

# Recogemos todos los .cpp de la lógica (excepto el main.cpp)
file(GLOB_RECURSE SOURCES "src/core/*.cpp" "src/algorithms/*.cpp")

# Creamos la librería
add_library(PathfindingLib ${SOURCES})
target_include_directories(PathfindingLib PUBLIC include)

# App principal
add_executable(PathfindingApp src/main.cpp)
target_link_libraries(PathfindingApp PathfindingLib)


##### Tests #####

enable_testing()
add_subdirectory(tests)
