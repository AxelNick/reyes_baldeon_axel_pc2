# Demos y Material de Sustentación

Este directorio centraliza los recursos multimedia, documentos de soporte y **scripts educativos** utilizados para la defensa y exposición técnica del proyecto (CC232).

## Scripts de Demostración
A diferencia del motor de pruebas automatizado (`tests/`) o la aplicación principal (`src/`), este directorio contiene código diseñado para visualizar conceptos teóricos:

* **`demo_pila_visual.cpp`:** Un script didáctico que imprime en consola el comportamiento paso a paso del invariante matemático ($balance \ge 0$). Dibuja gráficamente las operaciones LIFO (`PUSH` y `POP`) simuladas mediante un entero $O(1)$, demostrando visualmente los conceptos de la Semana 3 del sílabo.

## Material Multimedia y Documental
* **`presentacion_tecnica.pdf`:** Diapositivas de soporte visual utilizadas durante el video. Incluye esquemas de la memoria contigua, el árbol de recursión de Backtracking y la Poda (Pruning).
* **`enlace_sustentacion.txt`:** Documento que contiene el enlace directo al video de la sustentación técnica.

## Compilación del Demo
Para compilar y ejecutar la demostración visual de forma aislada usando GCC:
```bash
g++ demos/demo_pila_visual.cpp -o build/demo_visual.exe
./build/demo_visual.exe