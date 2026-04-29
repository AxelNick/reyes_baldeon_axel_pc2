# Evidencia de Ejecución: Benchmark y Demos

Este documento registra de forma inmutable las salidas estándar (stdout) generadas por las herramientas de análisis de rendimiento y demostración visual del proyecto, ejecutadas en el entorno **UCRT64**.

## 1. Análisis de Rendimiento (Benchmark)
Ejecución del script `run_benchmark.exe` utilizando `std::chrono` para medir el tiempo real de respuesta frente a casos de estrés.

```
$ ./build/run_benchmark.exe
=== INICIANDO ANALISIS DE RENDIMIENTO (BENCHMARK) ===

[Benchmark] Caso 1: Estandar LeetCode
Entrada: "()())()" (Longitud: 7)
Soluciones encontradas: 2
Tiempo de ejecucion: 7 microsegundos.

[Benchmark] Caso 2: Poda Intensiva (Heavy Pruning)
Entrada: "(((((((((a)))))))))" (Longitud: 19)
Soluciones encontradas: 1
Tiempo de ejecucion: 3 microsegundos.

[Benchmark] Caso 3: Estres de Recursion
Entrada: "()()()()()()()()" (Longitud: 16)
Soluciones encontradas: 1
Tiempo de ejecucion: 3 microsegundos.

[Benchmark] Caso 4: Inversion Masiva
Entrada: "))))))))((((((((" (Longitud: 16)
Soluciones encontradas: 1
Tiempo de ejecucion: 22 microsegundos.

=== BENCHMARK FINALIZADO ===
```

## 2. Demo Visual: Simulación de Pila LIFO
Ejecución del script `demo_visual.exe` que demuestra el comportamiento en $O(1)$ de espacio del invariante matemático de validación (basado en conceptos de la **Semana 3**).

```
$ ./build/demo_visual.exe
=== DEMO VISUAL: SIMULACION DE PILA LIFO (SEMANA 3) ===

Analizando cadena: "(a)()"
----------------------------------------------------------
Caracter | Accion       | Balance | Simulacion Grafica
----------------------------------------------------------
   (     | PUSH (+1)    |    1    | [O] 
   a     | IGNORAR      |    1    | [O] 
   )     | POP  (-1)    |    0    | 
   (     | PUSH (+1)    |    1    | [O] 
   )     | POP  (-1)    |    0    | 
----------------------------------------------------------
Resultado final: VALIDA (Balance exacto de 0)

Analizando cadena: ")("
----------------------------------------------------------
Caracter | Accion       | Balance | Simulacion Grafica
----------------------------------------------------------
   )     | POP  (-1)    |   -1    |  [! INVARIANTE ROTO: Cierre sin pareja !]
----------------------------------------------------------
Resultado final: INVALIDA (Fallo por balance negativo)
```
