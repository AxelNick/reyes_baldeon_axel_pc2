#include <iostream>
#include <string>
#include <vector>
#include "../include/Solution301.h"

using namespace std;

// Función auxiliar para imprimir los tests con un formato limpio
void runTest(Solution301& solver, const string& testName, const string& input) {
    cout << "\n[TEST] " << testName << "\n";
    cout << "Entrada original: \"" << input << "\"\n";
    
    // Ejecución del algoritmo
    vector<string> result = solver.removeInvalidParentheses(input);
    
    cout << "Respuestas validas:\n";
    for (const string& res : result) {
        if (res.empty()) {
            cout << " -> [\"\"] (Cadena vacia)\n";
        } else {
            cout << " -> " << res << "\n";
        }
    }
}

int main() {
    Solution301 solver;
    
    cout << "=== EJECUTANDO BATERIA DE PRUEBAS AUTOMATICAS ===\n";

    // 1. Caso estándar con múltiples respuestas
    runTest(solver, "Caso estandar mixto", "()())()");

    // 2. Caso que evalúa que se ignoren las letras (Ruido alfanumérico)
    runTest(solver, "Caso con caracteres de texto", "(a)())()");

    // 3. Caso borde: La cadena no necesita ser modificada
    runTest(solver, "Caso Borde: Ya es valida", "()()");

    // 4. Caso borde: Inversión estricta que exige fallar rápido
    runTest(solver, "Caso Borde: Inversion total", ")(");

    // 5. Caso borde: Texto sin paréntesis
    runTest(solver, "Caso Borde: Solo texto puro", "abc");

    // 6. Caso extremo exigido: Manejo de memoria sin elementos
    runTest(solver, "Caso Extremo: Cadena vacia", "");

    // 7. Caso extremo exigido: Imposibilidad matemática inmediata
    runTest(solver, "Caso Extremo: Un solo caracter invalido", ")");

    cout << "\nTodos los tests han finalizado.\n";

    return 0;
}