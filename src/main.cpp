#include "Solution301.h"

int main() {
    Solution301 solver;
    string caso_prueba = "()())()";
    
    cout << "Probando cadena: " << caso_prueba << endl;
    vector<string> respuestas = solver.removeInvalidParentheses(caso_prueba);
    
    cout << "Respuestas validas:" << endl;
    for (const string& resp : respuestas) {
        cout << "- " << resp << endl;
    }
    
    return 0;
}