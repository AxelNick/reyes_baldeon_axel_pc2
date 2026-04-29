# Análisis de Rendimiento (Benchmark)

Este directorio está reservado para los scripts, métricas y análisis de rendimiento del algoritmo (profiling) que se desarrollarán en fases posteriores del curso.

## Objetivos de evaluación
* **Tiempo de ejecución:** Medición empírica del tiempo real versus el tiempo asintótico teórico $O(2^n)$.
* **Consumo de memoria:** Análisis del impacto espacial $O(n)$ en el *Call Stack* durante el límite máximo de recursión.
* **Impacto de la Poda:** Pruebas comparativas (A/B testing) midiendo los milisegundos ahorrados al evitar los desplazamientos en memoria contigua provocados por `std::string::erase()`.