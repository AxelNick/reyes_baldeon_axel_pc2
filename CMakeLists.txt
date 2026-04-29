cmake_minimum_required(VERSION 3.10)
project(PC2_CC232_Reyes_Axel)

set(CMAKE_CXX_STANDARD 17)

# Obligatorio: Directorio de cabeceras .h
include_directories(include)

# Ejecutable principal (Modo interactivo)
add_executable(pc2_ejecutable src/main.cpp)

# Ejecutable secundario (Batería de pruebas automatizadas)
add_executable(run_tests tests/test_solution.cpp)


# EJECUTABLES ADICIONALES (DEMOS Y BENCHMARK)

# 1. Compilar el script de Benchmark
add_executable(run_benchmark benchmark/benchmark.cpp)

# 2. Compilar la Demo Visual (es independiente, no necesita enlazar otras librerías)
add_executable(demo_visual demos/demo_pila_visual.cpp)