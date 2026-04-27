#include "../include/Solution301.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void runTest(Solution301& solver, string testName, string input) {
    cout << "\n[TEST] " << testName << endl;
    cout << "Entrada original: \"" << input << "\"" << endl;
    
    vector<string> respuestas = solver.removeInvalidParentheses(input);
    
    cout << "Respuestas validas:" << endl;
    if (respuestas.empty() || (respuestas.size() == 1 && respuestas[0] == "")) {
        cout << " -> [\"\"] (Cadena vacia)" << endl;
    } else {
        for (const string& resp : respuestas) {
            cout << " -> " << resp << endl;
        }
    }
}

int main() {
    Solution301 solver;
    
    cout << "=== EJECUTANDO BATERIA DE PRUEBAS AUTOMATICAS ===" << endl;
    
    // Caso 1: Estándar con múltiples respuestas válidas
    runTest(solver, "Caso estandar mixto", "()())()");
    
    // Caso 2: Letras minúsculas intercaladas (Regla oficial de LeetCode)
    runTest(solver, "Caso con caracteres de texto", "(a)())()");
    
    // Caso 3: Invariante ya cumplido (No debe hacer nada)
    runTest(solver, "Caso Borde: Ya es valida", "()()");
    
    // Caso 4: Inversión estricta (Demuestra que evita ramas imposibles)
    runTest(solver, "Caso Borde: Inversion total", ")(");
    
    // Caso 5: Letras puras (Demuestra que no altera texto base)
    runTest(solver, "Caso Borde: Solo texto puro", "abc");

    // Caso 6: El caso vacío
    runTest(solver, "Caso Extremo: Cadena vacia", "");

    // Caso 7: Un solo carácter inválido
    runTest(solver, "Caso Extremo: Un solo caracter invalido", ")");
    
    cout << "\nTodos los tests han finalizado." << endl;
    return 0;
}