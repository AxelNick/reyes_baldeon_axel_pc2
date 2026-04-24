cmake_minimum_required(VERSION 3.10)
project(PC2_CC232_Reyes_Axel)

set(CMAKE_CXX_STANDARD 17)

# Obligatorio: Directorio de cabeceras .h
include_directories(include)

# Le decimos que compile src/main.cpp y genere 'pc2_ejecutable'
add_executable(pc2_ejecutable src/main.cpp)