#!/bin/bash
# 1. Limpiar restos de ejecuciones anteriores
find . -name "*.gcda" -delete

# 2. Compilar con flags de cobertura
cmake -B build -DENABLE_COVERAGE=ON
cmake --build build

# 3. Ejecutar los tests
./build/tests/ejecutar_tests

# 4. Generar el reporte HTML con gcovr
# --root . : busca el código fuente en la raíz
# --html-details : genera archivos HTML separados por archivo (muy visual)
# -o coverage/index.html : dónde guardar el resultado
gcovr -r . --html-details -o coverage_results/index.html --filter src/ --filter include/

echo "Informe generado en: coverage_results/index.html"