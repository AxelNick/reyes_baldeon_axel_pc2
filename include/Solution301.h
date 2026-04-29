#ifndef SOLUTION301_H
#define SOLUTION301_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution301 {
private:
    unordered_set<string> valid_expressions;

    // SIMULACIÓN DE PILA (SEMANA 3): 
    // Verifica el invariante LIFO sin gastar memoria instanciando un ADT Stack real.
    // Invariante: balance >= 0 en todo momento, y balance == 0 al final.
    bool isValid(const string& s) {
        
        // ESPACIO RESERVADO PARA LA CODIFICACION EN VIVO (BLOQUE 4)

    }

    // ESTRATEGIA: Backtracking (Búsqueda en Profundidad - DFS)
    void backtrack(const string& s, int index, int left_removed, int right_removed) {
        // Caso Base: Si ya eliminamos la cuota mínima calculada
        if (left_removed == 0 && right_removed == 0) {
            if (isValid(s)) {
                valid_expressions.insert(s); // Garantiza unicidad
            }
            return;
        }

        for (int i = index; i < s.length(); ++i) {
            // PODA 1: Evitar explorar duplicados adyacentes (genera ramas idénticas)
            if (i != index && s[i] == s[i - 1]) continue;

            // PODA 2 y COSTO ESPACIAL: 
            // string.erase() cuesta O(n) porque desplaza elementos en MEMORIA CONTIGUA (Semana 2).
            // Abortamos si intentamos borrar algo sin tener cuota, salvando rendimiento.
            if (s[i] == '(' && left_removed > 0) {
                string next_str = s;
                next_str.erase(i, 1); // Desplazamiento contiguo O(n-i)
                backtrack(next_str, i, left_removed - 1, right_removed);
            } 
            else if (s[i] == ')' && right_removed > 0) {
                string next_str = s;
                next_str.erase(i, 1); // Desplazamiento contiguo O(n-i)
                backtrack(next_str, i, left_removed, right_removed - 1);
            }
        }
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        valid_expressions.clear();
        int left_removed = 0;
        int right_removed = 0;

        // PRE-CÁLCULO: Determinar la remoción mínima exacta para acotar el Backtracking
        for (char c : s) {
            if (c == '(') {
                left_removed++;
            } else if (c == ')') {
                if (left_removed > 0) {
                    left_removed--; // Hacen pareja
                } else {
                    right_removed++; // Excedente de cierre
                }
            }
        }

        // Iniciar árbol de recursión
        backtrack(s, 0, left_removed, right_removed);
        return vector<string>(valid_expressions.begin(), valid_expressions.end());
    }
};

#endif // SOLUTION301_H