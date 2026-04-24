## PC2 - CC232

### Estudiante
- **Nombre:** Axel Alberto Reyes Baldeón
- **Código:** (Ingresa aquí tu código de alumno)
- **Problema asignado:** 25. LeetCode 301 - Remove Invalid Parentheses
- **Enlace:** [LeetCode 301](https://leetcode.com/problems/remove-invalid-parentheses/)

### Referencia oficial
- **Archivo de asignación:** 
  [Problemas-Evaluacion2.csv](https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv)

### Tema principal
- **Semana:** Semana 4
- **Estructura o técnica principal:** Backtracking (Búsqueda en profundidad) y Poda (Pruning).

### Resumen de la solución
La solución implementa un algoritmo de búsqueda exhaustiva optimizada. Primero, se realiza un pre-procesamiento para calcular la cantidad mínima de paréntesis de apertura y cierre que deben ser eliminados para balancear la cadena. Posteriormente, se utiliza una estrategia de **Backtracking** para generar las combinaciones posibles, aplicando criterios de **poda** para evitar ramas redundantes y omitiendo caracteres duplicados adyacentes para garantizar la unicidad de los resultados sin necesidad de estructuras de post-procesamiento costosas.

### Complejidad
- **Tiempo:** $O(2^n)$ en el peor caso teórico, aunque la poda por remoción mínima y la omisión de duplicados reduce drásticamente el espacio de búsqueda efectivo.
- **Espacio:** $O(n)$ debido a la profundidad de la pila de llamadas (*call stack*) de la recursión y el almacenamiento de la cadena temporal.

### Invariante o idea clave
El invariante de validación establece que en cualquier prefijo de la cadena, el número de paréntesis de cierre nunca debe exceder al de apertura, y la cadena final resultante debe tener un balance neto de cero. La búsqueda está acotada por el cálculo previo de remociones mínimas, lo que garantiza que solo se exploren soluciones con el menor número de cambios posibles.

### Archivos relevantes
- `include/Solution301.h`: Contiene la definición de la clase y la lógica algorítmica.
- `src/main.cpp`: Implementación del punto de entrada y casos de prueba.
- `docs/Actividad1.md`: Análisis conceptual de la Semana 1.
- `docs/Actividad2.md`: Análisis de estructuras contiguas de la Semana 2.
- `docs/Actividad3.md`: Análisis de estructuras enlazadas de la Semana 3.

### Compilación
```bash
cmake -S . -B build
cmake --build build
```

### Ejecución
```bash
./build/pc2_ejecutable.exe
```

### Casos de prueba
- **Entrada estándar:** `"()())()"` -> Retorna las combinaciones válidas con remoción mínima: `("(())()", "()()()")`.
- **Entrada con texto:** `"(a)())()"` -> Valida que los caracteres alfanuméricos se preserven correctamente.
- **Caso de inversión:** `")("` -> El algoritmo detecta la inviabilidad y retorna una cadena vacía `[""]`.

### Historial de commits
El historial de commits refleja un proceso de desarrollo progresivo realizado en días distintos, el cual será demostrado detalladamente durante la sustentación en video.

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.
