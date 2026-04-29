#include <iostream>
#include <string>

using namespace std;

// Función educativa para demostrar visualmente el Invariante LIFO
void simulateStackVisually(const string& s) {
    int balance = 0;
    cout << "Analizando cadena: \"" << s << "\"\n";
    cout << "----------------------------------------------------------\n";
    cout << "Caracter | Accion       | Balance | Simulacion Grafica\n";
    cout << "----------------------------------------------------------\n";

    for (char c : s) {
        cout << "   " << c << "     | ";
        if (c == '(') {
            balance++;
            cout << "PUSH (+1)    |    " << balance << "    | ";
        } else if (c == ')') {
            balance--;
            cout << "POP  (-1)    |   " << balance << "    | ";
        } else {
            cout << "IGNORAR      |    " << balance << "    | ";
        }

        // Dibuja 'bloques' para representar el tamaño de la pila en memoria
        if (balance >= 0) {
            for(int i = 0; i < balance; ++i) cout << "[O] ";
        }
        
        if (balance < 0) {
            cout << " [! INVARIANTE ROTO: Cierre sin pareja !]";
            break; // Corta la ejecución (Invariante LIFO violado)
        }
        cout << "\n";
    }
    cout << "----------------------------------------------------------\n";
    if (balance == 0) cout << "Resultado final: VALIDA (Balance exacto de 0)\n\n";
    else if (balance > 0) cout << "Resultado final: INVALIDA (Sobran " << balance << " aperturas)\n\n";
    else cout << "\nResultado final: INVALIDA (Fallo por balance negativo)\n\n";
}

int main() {
    cout << "=== DEMO VISUAL: SIMULACION DE PILA LIFO (SEMANA 3) ===\n\n";
    
    // Demuestra un caso válido con letras
    simulateStackVisually("(a)()");
    
    // Demuestra cómo el invariante corta el proceso en el caso de inversión
    simulateStackVisually(")(");
    
    return 0;
}