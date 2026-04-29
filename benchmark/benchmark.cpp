#include "../include/Solution301.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

// Función para ejecutar y medir el tiempo de un caso de prueba
void runBenchmark(Solution301& solver, const string& testName, const string& input) {
    cout << "\n[Benchmark] " << testName << endl;
    cout << "Entrada: \"" << input << "\" (Longitud: " << input.length() << ")" << endl;

    // Iniciar cronómetro
    auto start = high_resolution_clock::now();
    
    // Ejecutar algoritmo
    vector<string> result = solver.removeInvalidParentheses(input);
    
    // Detener cronómetro
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Soluciones encontradas: " << result.size() << endl;
    cout << "Tiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
}

int main() {
    Solution301 solver;
    cout << "=== INICIANDO ANALISIS DE RENDIMIENTO (BENCHMARK) ===" << endl;

    // Caso 1: Estándar
    runBenchmark(solver, "Caso 1: Estandar LeetCode", "()())()");

    // Caso 2: Poda Intensiva (Muchos duplicados, el Backtracking debe cortarlos rápido)
    runBenchmark(solver, "Caso 2: Poda Intensiva (Heavy Pruning)", "(((((((((a)))))))))");

    // Caso 3: Peor Caso de Exploración (Múltiples combinaciones válidas)
    runBenchmark(solver, "Caso 3: Estres de Recursion", "()()()()()()()()");

    // Caso 4: Inversión masiva (Debe fallar rápido por el invariante LIFO)
    runBenchmark(solver, "Caso 4: Inversion Masiva", "))))))))((((((((");

    cout << "\n=== BENCHMARK FINALIZADO ===" << endl;
    return 0;
}