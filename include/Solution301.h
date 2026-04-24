#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution301 {
private:
    // Teoría Semana 3 (Stack): En lugar de usar la estructura std::stack explícita, 
    // simulamos la pila con un contador entero (O(1) espacio) para validar el invariante LIFO.
    bool isValid(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') count++;
            else if (c == ')') count--;
            if (count < 0) return false; // El invariante se rompe si hay un cierre sin apertura previa
        }
        return count == 0;
    }

    void backtrack(const string& s, int start, int left_removed, int right_removed, vector<string>& result) {
        // Caso base (Finitud - Semana 1): Detenemos la recursión cuando ya no quedan caracteres por remover.
        if (left_removed == 0 && right_removed == 0) {
            if (isValid(s)) {
                result.push_back(s);
            }
            return;
        }

        for (int i = start; i < s.length(); i++) {
            // Poda (Pruning) de duplicados: Evitamos generar la misma rama del árbol.
            if (i != start && s[i] == s[i - 1]) continue;

            // Teoría Semana 2 (Memoria Contigua): erase() obliga a desplazar físicamente todos 
            // los elementos a la derecha (O(n)). La poda superior evita hacer esto innecesariamente.
            if (left_removed > 0 && s[i] == '(') {
                string next_str = s;
                next_str.erase(i, 1);
                backtrack(next_str, i, left_removed - 1, right_removed, result);
            }
            if (right_removed > 0 && s[i] == ')') {
                string next_str = s;
                next_str.erase(i, 1);
                backtrack(next_str, i, left_removed, right_removed - 1, result);
            }
        }
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        int left_removed = 0;
        int right_removed = 0;

        // 1. Análisis de correctitud: Determinamos la remoción mínima por adelantado
        // para acotar el tamaño del árbol recursivo y no caer en un costo de O(2^n) puro.
        for (char c : s) {
            if (c == '(') {
                left_removed++;
            } else if (c == ')') {
                if (left_removed > 0) left_removed--;
                else right_removed++;
            }
        }

        vector<string> result;
        backtrack(s, 0, left_removed, right_removed, result);
        return result;
    }
};