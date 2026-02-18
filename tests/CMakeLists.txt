# 1. Buscar GTest instalado en el sistema
find_package(GTest REQUIRED)

# 2. Crear el ejecutable de test con todos sus .cpp
file(GLOB TEST_SOURCES "*.cpp" "core/*.cpp" "algorithms/*.cpp" "algorithms/*.hpp")
add_executable(ejecutar_tests ${TEST_SOURCES})

# 3. Enlazar con GTest y tu código
# GTest::gtest_main ya incluye el main(), así que no necesitas crearlo tú
target_link_libraries(ejecutar_tests 
    GTest::gtest_main 
    PathfindingLib
)

# 4. Registrar para usar con el comando 'ctest'
add_test(NAME TodoElProyecto COMMAND ejecutar_tests)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_options(ejecutar_tests PRIVATE "-fprofile-instr-generate" "-fcoverage-mapping")
endif()