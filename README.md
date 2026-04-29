## PC2 - CC232

### Estudiante
- **Nombre:** Axel Alberto Reyes Baldeón
- **Código:** 20200485B
- **Problema asignado:** 25. LeetCode 301 - Remove Invalid Parentheses
- **Enlace:** [LeetCode 301](https://leetcode.com)

### Referencia oficial
- **Archivo de asignación:** [Problemas-Evaluacion2.csv](https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv)

### Tema principal
- **Semana:** Semana 4
- **Estructura o técnica principal:** Backtracking (Búsqueda en profundidad) y Poda (Pruning).

### Resumen de la solución
La solución implementa un algoritmo de búsqueda exhaustiva optimizada mediante **Backtracking**. Primero, se realiza un pre-procesamiento para calcular la cantidad mínima de paréntesis de apertura y cierre que deben ser eliminados para balancear la cadena. Durante la exploración, se aplican criterios de **poda** para evitar ramas redundantes (omitiendo duplicados adyacentes) y se garantiza la unicidad de los resultados mediante el uso de un `unordered_set` (Tabla Hash).

### Complejidad
- **Tiempo:** $O(2^n)$ en el peor caso teórico, aunque el tiempo de ejecución amortizado es significativamente menor gracias a la poda agresiva.
- **Espacio:** $O(n)$ debido a la profundidad máxima del *Call Stack* de la recursión y el almacenamiento de cadenas temporales en memoria contigua.

### Invariante o idea clave
El invariante de validación establece que en cualquier prefijo de la cadena, el número de paréntesis de cierre nunca debe exceder al de apertura, y la cadena final debe tener un balance neto de cero. Se utiliza una **Simulación de Pila (LIFO)** con costo espacial $O(1)$ para verificar este invariante sin instanciar objetos adicionales.

### Archivos relevantes
- `include/Solution301.h`: Definición de la clase y lógica algorítmica principal.
- `src/main.cpp`: Interfaz de usuario y modo interactivo por consola.
- `tests/test_solution.cpp`: Batería de pruebas automatizadas.
- `benchmark/benchmark.cpp`: Script de análisis de rendimiento usando `std::chrono`.
- `demos/demo_pila_visual.cpp`: Herramienta didáctica para visualizar el invariante de balanceo.
- `docs/`: Documentación técnica vinculada a las actividades de las semanas 1, 2 y 3.

### Compilación y Ejecución
El proyecto utiliza **CMake** para la gestión de la construcción:

```bash
cmake -S . -B build
cmake --build build
```

**Ejecutables generados:**
- **Batería de pruebas:** `./build/run_tests.exe`
- **Modo interactivo:** `./build/pc2_ejecutable.exe`
- **Análisis de rendimiento:** `./build/run_benchmark.exe`

### Casos de Prueba y Validación
El sistema valida la correctitud observable mediante 7 escenarios críticos:

1.  **Caso estándar mixto ("()())()"):** Generación de múltiples combinaciones válidas con remoción mínima.
2.  **Caso con caracteres de texto ("(a)())()"):** Validación de que los caracteres alfanuméricos se mantienen intactos.
3.  **Caso Borde - Ya es válida ("()()"):** El algoritmo detecta la validez previa y no realiza cambios.
4.  **Caso Borde - Inversión total (")("):** Detección inmediata de inviabilidad, retornando cadena vacía `[""]`.
5.  **Caso Borde - Solo texto puro ("abc"):** Manejo de cadenas sin paréntesis.
6.  **Caso Extremo - Cadena vacía (""):** Manejo seguro de entradas de longitud cero.
7.  **Caso Extremo - Un solo carácter inválido (")"):** Resolución de balance negativo inmediato.

### Historial de commits
El desarrollo se realizó de forma progresiva durante 5 días, integrando modularmente la lógica de búsqueda, las optimizaciones de poda, la suite de pruebas y la documentación técnica, garantizando la trazabilidad total del proyecto mediante Git.

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación y sustentación.
