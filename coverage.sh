#!/bin/bash

# 1. Obtener la ruta absoluta de la carpeta del proyecto
BASE_DIR=$(pwd)
BINARY="$BASE_DIR/build/tests/ejecutar_tests"
COVERAGE_DIR="$BASE_DIR/coverage_results"

# Definir archivos con rutas completas
PROFRAW="$COVERAGE_DIR/proyecto.profraw"
PROFDATA="$COVERAGE_DIR/proyecto.profdata"
HTML_REPORT="$COVERAGE_DIR/index.html"

echo "🚀 Iniciando proceso de cobertura..."

# 2. Crear carpeta si no existe
mkdir -p "$COVERAGE_DIR"

# 3. Ejecutar los tests
# Forzamos la ruta absoluta en la variable de entorno
echo "Running tests..."
LLVM_PROFILE_FILE="$PROFRAW" "$BINARY"

if [ $? -eq 0 ]; then
    echo "✅ Tests pasados."
    
    # 4. Procesar datos (Merge)
    xcrun llvm-profdata merge -sparse "$PROFRAW" -o "$PROFDATA"
    
    # 5. Generar reporte
    xcrun llvm-cov show "$BINARY" -instr-profile="$PROFDATA" -format=html > "$HTML_REPORT"
    
    # 6. Resumen en consola
    xcrun llvm-cov report "$BINARY" -instr-profile="$PROFDATA"
    
    echo "🌐 Abriendo: $HTML_REPORT"
    open "$HTML_REPORT"
else
    echo "❌ Error: Los tests fallaron."
    exit 1
fi
