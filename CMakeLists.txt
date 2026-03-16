cmake_minimum_required(VERSION 3.14)
project(PathfindingVisualizer VERSION 1.0 LANGUAGES C CXX)

##### Compilation #####

# set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ENABLE_COVERAGE)
    # Estos flags son los que necesita GCC para generar la telemetría de código
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

##### External libraries #####

include(FetchContent)

# --- 1. Google Test (GTest) ---
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2 # Versión estable actual
)
# Forzamos que GTest use el runtime de la librería estándar de forma coherente
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- 2. nlohmann_json ---
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3
)
# Esta librería es "header-only", así que es muy ligera de incluir
FetchContent_MakeAvailable(json)

# --- 3. SFML (Versión 3) ---
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        3.0.0 # Asegúrate de usar el tag de la versión 3
)
# Opciones para que SFML no compile cosas innecesarias (ejemplos)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(sfml)

# Recogemos todos los .cpp de la lógica (excepto el main.cpp)
file(GLOB_RECURSE SOURCES 
    "src/core/*.cpp"
    "src/algorithms/*.cpp"
    "src/visualization/*.cpp"
    "src/app/*.cpp"
    "src/player/*.cpp"
    "src/managers/*.cpp")

# Creamos la librería
add_library(PathfindingLib ${SOURCES})
target_include_directories(PathfindingLib PUBLIC 
    include
    ${json_SOURCE_DIR}/include
    ${sfml_SOURCE_DIR}/include
)

# App principal
add_executable(PathfindingApp src/main.cpp)
target_link_libraries(PathfindingApp 
    PathfindingLib
    sfml-graphics 
    sfml-window 
    sfml-system
    nlohmann_json::nlohmann_json)


##### Tests #####

enable_testing()
add_subdirectory(tests)
