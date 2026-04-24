#include "../include/Solution301.h"
#include <iostream>

using namespace std;

int main() {
    Solution301 solver;
    string caso_prueba_1 = "()())()";
    string caso_prueba_2 = "(a)())()"; // Caso borde con letras
    
    cout << "--- PRUEBA LEETCODE 301 ---" << endl;
    
    cout << "\nProbando cadena: " << caso_prueba_1 << endl;
    vector<string> respuestas1 = solver.removeInvalidParentheses(caso_prueba_1);
    for (const string& resp : respuestas1) {
        cout << " -> " << resp << endl;
    }
    
    cout << "\nProbando cadena: " << caso_prueba_2 << endl;
    vector<string> respuestas2 = solver.removeInvalidParentheses(caso_prueba_2);
    for (const string& resp : respuestas2) {
        cout << " -> " << resp << endl;
    }
    
    return 0;
}