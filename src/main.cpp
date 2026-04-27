#include "../include/Solution301.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función auxiliar para imprimir las pruebas de forma limpia y modular
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
    
    cout << "=== PRUEBAS LEETCODE 301 - REMOVE INVALID PARENTHESES ===" << endl;
    
    // 1. Caso estándar de prueba
    runTest(solver, "Caso estandar mixto", "()())()");
    
    // 2. Caso con ruido alfanumérico
    runTest(solver, "Caso con caracteres de texto", "(a)())()");
    
    // 3. Caso Borde: Cadena ya válida (No debería eliminar nada)
    runTest(solver, "Caso Borde: Ya es valida", "()()");
    
    // 4. Caso Borde: Inversión estricta (Debería vaciar la cadena)
    runTest(solver, "Caso Borde: Inversion total", ")(");
    
    // 5. Caso Borde: Sin paréntesis (El algoritmo debe ignorarlo y devolver lo mismo)
    runTest(solver, "Caso Borde: Solo texto puro", "abc");
    
    return 0;
}