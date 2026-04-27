#include "../include/Solution301.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    Solution301 solver;
    
    cout << "=========================================" << endl;
    cout << "   MODO INTERACTIVO: LEETCODE 301        " << endl;
    cout << "=========================================" << endl;
    
    string custom_input;
    cout << "Ingresa una cadena de parentesis y letras (o 'salir' para terminar): ";
    
    while (cin >> custom_input && custom_input != "salir") {
        cout << "\n[TEST] Prueba del Usuario" << endl;
        cout << "Entrada original: \"" << custom_input << "\"" << endl;
        
        vector<string> respuestas = solver.removeInvalidParentheses(custom_input);
        
        cout << "Respuestas validas:" << endl;
        if (respuestas.empty() || (respuestas.size() == 1 && respuestas[0] == "")) {
            cout << " -> [\"\"] (Cadena vacia)" << endl;
        } else {
            for (const string& resp : respuestas) {
                cout << " -> " << resp << endl;
            }
        }
        cout << "\nIngresa otra cadena (o escribe 'salir'): ";
    }
    
    cout << "Programa finalizado." << endl;
    return 0;
}