# Análisis de Rendimiento y Profiling (Benchmark)

Este directorio aloja el script de medición empírica (`benchmark.cpp`) diseñado para evaluar la complejidad en tiempo de ejecución del problema **LeetCode 301 (Remove Invalid Parentheses)**. 

Debido a que la naturaleza del problema de validación genera un árbol de exploración combinatorio con un costo asintótico teórico de $O(2^n)$, este módulo demuestra cuantitativamente la efectividad de la técnica de **Poda (Pruning)** aplicada en el código.

## Herramientas de Medición Implementadas
* **`std::chrono`:** Se utiliza `high_resolution_clock` de la librería estándar de C++ para capturar los tiempos de ejecución precisos de la función principal en microsegundos ($\mu s$).

## Escenarios de Prueba de Estrés (Stress Testing)
El script evalúa el rendimiento del algoritmo de *Backtracking* frente a escenarios críticos:

1. **Caso Estándar:** Medición base con las entradas típicas del problema.
2. **Caso de Poda Intensiva (Heavy Pruning):** Cadenas con excesivos duplicados adyacentes (ej. `"(((((((((a)))))))))"`). Cuantifica el ahorro de tiempo al evitar el costo $O(n)$ del método `std::string::erase()` en ramas redundantes.
3. **Estrés de Recursión:** Cadenas largas y balanceadas que exigen explorar múltiples caminos válidos en el *Call Stack*.
4. **Inversión Masiva:** Evalúa la velocidad de rechazo del algoritmo ante cadenas estrictamente inválidas, demostrando la eficiencia del invariante matemático simulado.

## Ejecución
Para compilar y ejecutar el benchmark de forma independiente (utilizando GCC):
```bash
g++ benchmark/benchmark.cpp -o build/benchmark_test.exe
./build/benchmark_test.exe