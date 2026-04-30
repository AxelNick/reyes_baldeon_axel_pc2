#ifndef SOLUTION301_H
#define SOLUTION301_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution301 {
private:
    // Simulación LIFO (Semana 3) - Mantiene costo espacial O(1)
    
    bool isValid(const string& s) {
        int balance = 0;
        for (char c : s) {
            if (c == '(') balance++;
            else if (c == ')') balance--;
            
            // Control estricto del invariante de estructura
            if (balance < 0) return false;
        }
        return balance == 0;
    }

    // Búsqueda en Profundidad (DFS) con Backtracking
    void backtrack(const string& s, int index, int left_removed, int right_removed, unordered_set<string>& valid_expressions) {
        // Caso Base: Cuota de eliminaciones agotada
        if (left_removed == 0 && right_removed == 0) {
            if (isValid(s)) {
                valid_expressions.insert(s); // Inserción en promedio O(1)
            }
            return;
        }

        // Navegación sobre la memoria contigua
        for (int i = index; i < s.length(); i++) {
            
            // Poda Criterio 2: Saltar duplicados adyacentes para evitar ramas clonadas
            if (i != index && s[i] == s[i - 1]) continue;

            // Procesamiento de paréntesis (se ignoran las letras)
            if (s[i] == '(' || s[i] == ')') {
                string next_str = s;
                
                // Poda Criterio 1: Verificación estricta de cuota antes de asumir el costo O(n) del erase()
                if (s[i] == '(' && left_removed > 0) {
                    next_str.erase(i, 1);
                    backtrack(next_str, i, left_removed - 1, right_removed, valid_expressions);
                } 
                else if (s[i] == ')' && right_removed > 0) {
                    next_str.erase(i, 1);
                    backtrack(next_str, i, left_removed, right_removed - 1, valid_expressions);
                }
            }
        }
    }

public:
    // API Pública
    vector<string> removeInvalidParentheses(string s) {
        int left_removed = 0;
        int right_removed = 0;

        // Pre-cálculo de remoción mínima en O(n) para definir la cuota inicial
        for (char c : s) {
            if (c == '(') {
                left_removed++;
            } else if (c == ')') {
                if (left_removed > 0) {
                    left_removed--;
                } else {
                    right_removed++;
                }
            }
        }

        // Contenedor basado en Tabla Hash para unicidad rápida
        unordered_set<string> valid_expressions;
        
        // Inicio de la exploración del árbol
        backtrack(s, 0, left_removed, right_removed, valid_expressions);

        return vector<string>(valid_expressions.begin(), valid_expressions.end());
    }
};

#endif // SOLUTION301_H