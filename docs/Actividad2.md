# Actividad 2 - Semana 2

## Integrantes
- Axel Alberto Reyes Baldeon
- Andre Dylan Chumbimuni Ricci

## Bloque 0 - Instalación y preparación

- [x] Carpeta de trabajo lista
- [x] Acceso a Semana2, lecturas y archivos de entrega verificados
- [x] Archivo `actividad2_semana2.md` creado
- [x] Compilación y ejecución de demos y pruebas públicas completadas

### Compilación realizada

```bash
cmake -S . -B build
cmake --build build --config Debug
```

### Demo ejecutada

- **sem2_demo_array_basico.exe**
  ```
  array.length = 5
  contenido: 10 20 30 40 50
  antes de la asignacion, b[0] = -1
  despues de b = a, b.length = 5
  b: 10 20 30 40 50
  nota: esta version de array usa una asignacion por transferencia de ownership.
  ```
  **Observación**: Muestra creación de arreglo con 5 elementos, acceso por índice y asignación con transferencia de ownership (no copia profunda).

### Prueba pública ejecutada
```
Test project C:/Users/AXEL/OneDrive/Documentos/Codes/2026_1/Algoritmos y estructura de datos/CC-232-main/cc-232/CC-232/Libreria_cc232/Semana2/build
    Start 1: semana2_public
1/5 Test #1: semana2_public ...................   Passed    0.01 sec
    Start 2: semana2_internal
2/5 Test #2: semana2_internal .................   Passed    0.02 sec
    Start 3: semana2_resize_stress
3/5 Test #3: semana2_resize_stress ............   Passed    0.02 sec
    Start 4: semana2_public_cap2
4/5 Test #4: semana2_public_cap2 ..............   Passed    0.02 sec
    Start 5: semana2_internal_cap2
5/5 Test #5: semana2_internal_cap2 ............   Passed    0.02 sec

100% tests passed, 0 tests failed out of 5
Total Test time (real) =   0.09 sec
```
**Resultado**: **5/5 tests pasaron** - Todas las pruebas públicas e internas funcionan correctamente.

---

## Bloque 1 - Núcleo conceptual de la semana

### Material de Revisión:

- `Semana2/README.md`
- `Lectura4-Deng`
- `Lectura5-Morin`
- `Semana2/include/ArrayStack.h`
- `Semana2/include/FastArrayStack.h`
- `Semana2/include/RootishArrayStack.h`
- `Semana2/include/DengVector.h`

### 1. Expliquen con sus palabras qué significa que un arreglo use memoria contigua.

   La memoria contigua significa que los elementos del arreglo se almacenan uno tras otro, ocupando posiciones consecutivas en la RAM sin espacios intermedio. La dirección física de cualquier elemento se calcula mediante una fórmula lineal: `dirección = dirección_base + índice × tamaño_elemento`. Esta característica es el fundamento del acceso directo.

### 2. Expliquen por qué acceder a A[i] es una operación de costo O(1).

   Acceder a un elemento por índice es O(1) porque la CPU puede calcular directamente su dirección de memoria sin necesidad de recorrer elementos anteriores. Dado que el vector es contiguo, la operación se reduce a una simple suma y un acceso a memoria, que son operaciones de hardware con tiempo constante.

### 3. Expliquen la diferencia entre size y capacity.

   - `size` es la cantidad **lógica** de elementos realmente almacenados en el vector. 
   - `capacity` es la cantidad **física** de celdas que han sido reservadas en memoria. La capacidad es siempre ≥ al size. Esta diferencia permite crecer dinámicamente: cuando insertamos, usamos espacio libre antes de expandir.

### 4. Expliquen por qué un arreglo dinámico no puede crecer "en el mismo sitio" y necesita reservar un bloque nuevo al hacer resize().

   Un arreglo requiere memoria contigua. Cuando la capacidad se agota, no podemos "crecer" en el mismo sitio porque la RAM que viene inmediatamente después puede estar ocupada por otros datos del programa. 
   Por eso `resize()` debe: 
   - Primero reservar un nuevo bloque más grande
   - Despues copiar todos los elementos antiguos al nuevo bloque
   - Y finalmente liberar el bloque antiguo.

### 5. Expliquen por qué duplicar capacidad permite defender costo amortizado O(1) para inserciones al final.

   Si duplicamos capacidad, entre dos expansiones sucesivas deben ocurrir muchas inserciones. El costo total de expandir a lo largo de n inserciones es O(n) porque las expansiones forman una suma geométrica (costo 1, luego 2, luego 4, 8, 16... que suma ~2n). Repartido entre n operaciones, da O(1) por operación. Si creciéramos por una cantidad fija, necesitaríamos muchas más expansiones.

### 6. Comparen ArrayStack y DengVector: ¿qué comparten y qué cambia en interfaz o intención didáctica?

   Ambos implementan un stack con arreglo dinámico. `ArrayStack` (del autor Morin) es una implementación clásica y general que sirve de base para variantes. `DengVector` (del autor Deng) es una implementación de propósito educativo que ilustra explícitamente los conceptos de size, capacity, expand(), shrink() y operaciones como inserción, eliminación y búsqueda. Comparten la misma lógica básica pero DengVector es más completo.

### 7. Expliquen qué mejora FastArrayStack respecto a ArrayStack.

   `FastArrayStack` hereda de `ArrayStack` pero reemplaza los bucles manuales de copia y desplazamiento por rutinas optimizadas como `std::copy` y `std::copy_backward`. Esto no cambia la complejidad asintótica, pero mejora significativamente el rendimiento práctico porque esas rutinas están ajustadas a bajo nivel y aprovechan instrucciones especiales del procesador.

### 8. Expliquen cuál es la idea espacial central de RootishArrayStack

   En lugar de un único arreglo grande, usa múltiples bloques más pequeños de tamaños 1, 2, 3, 4, 5, ... El primer bloque almacena 1 elemento, el segundo 2, el tercero 3, etc. Los bloques se almacenan en un `ArrayStack<T*>` de apuntadores. Esto reduce significativamente el desperdicio de memoria en comparación con duplicar un arreglo grande.

### 9. Expliquen por qué RootishArrayStack usa bloques de tamaños 1, 2, 3, ....

El diseño de asignar bloques de memoria con tamaños secuenciales ($1, 2, 3, \dots, b$) tiene como objetivo principal resolver la ineficiencia espacial de los arreglos dinámicos sin sacrificar la velocidad de acceso. Se fundamenta en dos pilares:

* **Reducción drástica del espacio desperdiciado (de $O(n)$ a $O(\sqrt{n})$):**
Un vector tradicional duplica su capacidad al llenarse, lo que genera un desperdicio de memoria proporcional a la cantidad de elementos ($O(n)$). El `RootishArrayStack`, al crecer de forma aritmética (la suma de los primeros $b$ números naturales es $\frac{b(b+1)}{2}$), requiere aproximadamente $b \approx \sqrt{2n}$ bloques para alojar $n$ elementos. El desperdicio máximo se limita al espacio sobrante en el último bloque, reduciendo la memoria inactiva a **$O(\sqrt{n})$**.

* **Acceso directo en tiempo constante ($O(1)$):**
A pesar de que los datos se dividen en múltiples bloques de distintos tamaños, ubicar un elemento no exige recorrer la estructura. La ubicación física de cualquier índice lógico $i$ (el bloque $b$ y su posición interna) se calcula directamente resolviendo una inecuación cuadrática en tiempo **$O(1)$**.

**En conclusión:** Esta arquitectura matemática elimina la gran penalización de memoria ($O(n)$) del redimensionamiento clásico, conservando la inmediatez matemática ($O(1)$) para las operaciones de lectura y escritura.

### 10. Expliquen qué relación hay entre representación, costo temporal y desperdicio espacial en estas estructuras.

La relación entre estos tres factores se define por un compromiso estructural (**trade-off**) fundamental, donde la mejora de uno suele exigir el sacrificio de otro:

*   **Representación y Tiempo:** Mantener una representación de memoria estrictamente contigua (como en `ArrayStack` o `DengVector`) garantiza un costo temporal óptimo para el acceso directo ($O(1)$). Sin embargo, esto penaliza el tiempo de modificación ($O(n-i)$), ya que obliga a desplazar masivamente los elementos para no romper la contigüidad.

*   **Tiempo y Espacio:** Para lograr que el crecimiento de la estructura tenga un costo temporal amortizado de $O(1)$ (mediante redimensionamiento geométrico), la representación está obligada a reservar mucha más memoria de la que usa. Esto asume deliberadamente un desperdicio espacial elevado de orden $O(n)$.

*   **Flexibilización y Optimización:** Si se altera la representación física para fragmentar la memoria (como en `RootishArrayStack` con bloques incrementales), se logra reducir drásticamente el desperdicio espacial a solo $O(\sqrt{n})$. A cambio, aunque el costo asintótico se mantiene, el costo temporal real aumenta debido a la sobrecarga matemática necesaria para calcular posiciones y desplazar datos a través de las fronteras de los bloques.

**En resumen:** la representación dicta qué tan rápido se accede y se modifica (**tiempo**), pero la necesidad de mantener esos tiempos bajos obliga a sacrificar memoria inactiva (**espacio**).

---

## Bloque 2 - Demostración y trazado guiado

### Material de Revisión:

- `Semana2/demos/demo_array_basico.cpp`
- `Semana2/demos/demo_arraystack.cpp`
- `Semana2/demos/demo_arraystack_explicado.cpp`
- `Semana2/demos/demo_fastarraystack.cpp`
- `Semana2/demos/demo_rootisharraystack.cpp`
- `Semana2/demos/demo_rootisharraystack_explicado.cpp`
- `Semana2/demos/demo_deng_vector.cpp`
- `Semana2/demos/demo_stl_vector_contraste.cpp`

### Tabla de análisis de demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
| :--- | :--- | :--- | :--- |
| **`demo_array_basico.cpp`** | `b = a` cambia el dueño del arreglo (evidencia transferencia de *ownership*). | Es un *wrapper* simple. Al asignar, transfiere el puntero en lugar de hacer una copia profunda. | Asignar cuesta $O(1)$. Al no duplicar memoria, se evita el costo tradicional de $O(n)$ de una copia profunda. |
| **`demo_arraystack.cpp`** y **`_explicado`** | La consola detalla cómo los elementos se desplazan (izquierda/derecha) al insertar o eliminar. | Arreglo dinámico clásico. Mantiene datos contiguos y usa expansión geométrica para crecer. | Desplazar elementos cuesta $O(n-i)$. El redimensionamiento genera un desperdicio espacial de hasta $O(n)$. |
| **`demo_fastarraystack.cpp`** | Resultados idénticos a `ArrayStack`, pero con tiempos de ejecución menores. | Conserva la contigüidad, pero delega el desplazamiento a funciones optimizadas como `std::copy` o `memmove`. | La complejidad es $O(n-i)$, pero la **constante de ejecución** es menor gracias a optimizaciones de bajo nivel. |
| **`demo_rootisharraystack.cpp`** y **`_explicado`** | Visualiza el mapeo de índices a bloques físicos (`bloque b`, `offset j`) de tamaño 1, 2, 3... | Estructura basada en una lista de bloques. Usa una ecuación cuadrática para ubicar elementos. | El desperdicio de memoria baja de $O(n)$ a $O(\sqrt{n})$. El acceso aleatorio se mantiene en $O(1)$. |
| **`demo_deng_vector.cpp`** | Muestra expansión de capacidad y confirma que una copia no altera el vector original. | ADT vectorial. Separa `size` de `capacity` y asegura gestión de memoria con copias profundas. | La inserción al final es $O(1)$ amortizado. La eliminación por intervalo optimiza desplazamientos a $O(n - lo)$. |
| **`demo_stl_vector_contraste.cpp`** | Imprime el patrón de crecimiento de `capacity`, evidenciando el factor de crecimiento (usualmente 2 o 1.5). | Uso de `std::vector`. Sirve como línea base (*benchmark*) para comparar con las implementaciones propias. | Valida el análisis amortizado: $O(1)$ en inserciones al final, con un costo espacial residual de $O(n)$. |

### Evidencias de Compilación y Ejecución

### Evidencia: demo_array_basico.cpp

```
$ ./sem2_demo_array_basico
array.length = 5
contenido: 10 20 30 40 50
antes de la asignacion, b[0] = -1
despues de b = a, b.length = 5
b: 10 20 30 40 50
nota: esta version de array usa una asignacion por transferencia de ownership.
```

### Evidencia: demo_arraystack.cpp

```
$ ./sem2_demo_arraystack
size = 3
10 15 20
remove(1) = 15
```

### Evidencia: demo_arraystack_explicado.cpp

```
$ ./sem2_demo_arraystack_explicado
ArrayStack explicado (Morin, capitulo 2)
Operacion 1: push_back(10)
size=1, capacity=1
layout=[10]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Operacion 2: push_back(20)
size=2, capacity=2
layout=[10 | 20]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Operacion 3: add(1, 15)
Se desplazan a la derecha los elementos desde i hasta n-1.
size=3, capacity=4
layout=[10 | 15 | 20 | _]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Operacion 4: remove(0)
Se desplazan a la izquierda los elementos desde i+1 hasta n-1.
Valor removido = 10
size=2, capacity=4
layout=[15 | 20 | _ | _]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Idea central: add(i,x) y remove(i) cuestan O(n-i) por los desplazamientos.
```

### Evidencia: demo_fastarraystack.cpp

```
$ ./sem2_demo_fastarraystack
size = 7
0 1 2 99 3 4 5
```

### Evidencia: demo_rootisharraystack.cpp

```
$ ./sem2_demo_rootisharraystack
size = 8
0 10 20 30 40 50 60 70
remove(3) = 30
```
### Evidencia: demo_rootisharraystack_explicado.cpp

```
$ ./sem2_demo_rootisharraystack_explicado
RootishArrayStack explicado (Morin, capitulo 2)
size=6, blocks=3, capacidad total=6

 bloque 0 (tam=1): [0:10]
 bloque 1 (tam=2): [1:20 | 2:30]
 bloque 2 (tam=3): [3:40 | 4:50 | 5:60]
invariante: el bloque b tiene capacidad b+1 y guarda una porcion contigua logica de la secuencia

Como se ubican algunos indices:
 indice logico 0 -> bloque 0, offset 0, valor=10
 indice logico 2 -> bloque 1, offset 1, valor=30
 indice logico 5 -> bloque 2, offset 2, valor=60

Operacion: add(2, 99)
size=7, blocks=4, capacidad total=10

 bloque 0 (tam=1): [0:10]
 bloque 1 (tam=2): [1:20 | 2:99]
 bloque 2 (tam=3): [3:30 | 4:40 | 5:50]
 bloque 3 (tam=4): [6:60 | _ | _ | _]
invariante: el bloque b tiene capacidad b+1 y guarda una porcion contigua logica de la secuencia

Operacion: remove(4)
Valor removido = 40
size=6, blocks=4, capacidad total=10

 bloque 0 (tam=1): [0:10]
 bloque 1 (tam=2): [1:20 | 2:99]
 bloque 2 (tam=3): [3:30 | 4:50 | 5:60]
 bloque 3 (tam=4): [_ | _ | _ | _]
invariante: el bloque b tiene capacidad b+1 y guarda una porcion contigua logica de la secuencia

Idea central: se usan bloques de tamano 1, 2, 3, ...
Esto reduce espacio desperdiciado frente a duplicar un arreglo grande.
```

### Evidencia: demo_deng_vector.cpp

```
$ ./sem2_demo_deng_vector
insert(0) -> size=1, capacity=3
insert(10) -> size=2, capacity=3
insert(20) -> size=3, capacity=3
insert(30) -> size=4, capacity=6
insert(40) -> size=5, capacity=6
insert(50) -> size=6, capacity=6
insert(60) -> size=7, capacity=12
insert(70) -> size=8, capacity=12
Luego de insert(2, 99): 0 10 99 20 30 40 50 60 70
remove(3) = 20
remove(1, 3) elimina 2 elementos
Copia + increaseByOne: 1 31 41 51 61 71
Asignado * 2: 0 60 80 100 120 140
find(50) = -1
Estado final -> size=6, capacity=12
```

### Evidencia: demo_stl_vector_contraste.cpp

```
$ ./sem2_demo_stl_vector_contraste 
push_back(0) -> size=1, capacity=1
push_back(10) -> size=2, capacity=2
push_back(20) -> size=3, capacity=4
push_back(30) -> size=4, capacity=4
push_back(40) -> size=5, capacity=8
push_back(50) -> size=6, capacity=8
push_back(60) -> size=7, capacity=8
push_back(70) -> size=8, capacity=8
```
Luego respondemos : 

### 1. En demo_array_basico.cpp, ¿qué deja claro sobre arreglo, longitud y asignación?

Muestra que la estructura encapsula un arreglo primitivo junto a su longitud. En cuanto a la asignación (`b = a`), evidencia una **transferencia de propiedad** (*ownership transfer*): intercambia punteros en tiempo $O(1)$ en lugar de realizar una costosa copia profunda.

### 2. En demo_arraystack_explicado.cpp, ¿qué operación muestra mejor el costo por desplazamientos?

Las operaciones `add(1, 15)` y `remove(0)`. Los mensajes de consola y la impresión del *layout* visualizan el movimiento físico de la memoria (hacia la derecha o izquierda), ilustrando gráficamente el costo temporal $O(n-i)$.

### 3. En demo_fastarraystack.cpp, ¿qué cambia en la implementación aunque no cambie la complejidad asintótica?

Cambia el mecanismo subyacente. Aunque el costo asintótico de desplazar sigue siendo $O(n-i)$, se reemplazan los ciclos iterativos por instrucciones de movimiento de memoria a nivel de hardware (como `std::copy`), reduciendo drásticamente la constante de tiempo oculta.

### 4. En demo_rootisharraystack_explicado.cpp, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?

La impresión de la función `locate` (ej. `índice logico 5 -> bloque 2, offset 2`). Demuestra cómo la estructura localiza físicamente un elemento resolviendo ecuaciones matemáticas, logrando un acceso $O(1)$ sin necesidad de iterar.

### 5. En demo_deng_vector.cpp, ¿qué observable permite defender el crecimiento de capacity?

Los saltos impresos en consola (ej. `capacity=3` $\to$ `6` $\to$ `12`). Esto evidencia empíricamente la política de **expansión geométrica** (duplicación), necesaria para absorber los costos de reasignación y lograr inserciones en $O(1)$ amortizado.

### 6. En demo_stl_vector_contraste.cpp, ¿qué similitud conceptual observan con DengVector?

La estricta separación entre elementos válidos (`size`) y memoria física (`capacity`), además de utilizar el mismo modelo de **crecimiento geométrico** ($1 \to 2 \to 4 \to 8$) validando que ambos se rigen por el mismo análisis de costo amortizado.

### 7. ¿Qué demo sirve mejor para defender amortización y cuál sirve mejor para defender uso de espacio?

* **Para amortización:** `demo_stl_vector_contraste.cpp` (o `demo_deng_vector.cpp`), ya que exhiben explícitamente la reserva deliberada de memoria ociosa ($O(n)$) para "comprar" inserciones en tiempo constante.

* **Para uso de espacio:** `demo_rootisharraystack_explicado.cpp`, porque su mapa visual comprueba que los bloques vacíos quedan confinados exclusivamente al último fragmento reservado, desplomando el desperdicio espacial a solo $O(\sqrt{n})$.

---

## Bloque 3 - Pruebas públicas, stress y correctitud

### Material de Revisión:

- `Semana2/pruebas_publicas/README.md`
- `Semana2/pruebas_publicas/test_public_week2.cpp`
- `Semana2/pruebas_internas/test_internal_week2.cpp`
- `Semana2/pruebas_internas/resize_stress_week2.cpp`

### 1. ¿Qué operaciones mínimas valida la prueba pública para ArrayStack?

- **Inserción:** `add(x)` (agregar al final) y `add(i, x)` (insertar en un índice específico).
- **Consulta:** `size()` (obtener la cantidad de elementos) y `get(i)` (leer un elemento en un índice).
- **Elimación:** `remove(i)` (eliminar un elemento en un índice y retornarlo).

### 2. ¿Qué operaciones mínimas valida la prueba pública para FastArrayStack?

Valida exactamente el mismo conjunto operativo (`add`, `size`, `get`, `remove`), pero hace un énfasis particular en eliminar el primer elemento (`remove(0)`) para asegurar que el desplazamiento masivo hacia la izquierda funcione correctamente bajo el capó.

### 3. ¿Qué operaciones mínimas valida la prueba pública para RootishArrayStack?

Además de validar `add`, `size`, `get` y `remove`, esta prueba introduce explícitamente la validación de la operación de actualización en una posición específica mediante el método `set(i, x)`.

- **Modificación:** `set(i, x)` (sobreescribir un valor existente y retornar el antiguo).

### 4. ¿Qué sí demuestra una prueba pública sobre una estructura?

- Demuestra la **correctitud funcional básica**.
- Asegura empíricamente que la estructura obedece el contrato de su interfaz (devuelve los valores correctos en las posiciones correctas) bajo casos de uso pequeños y controlados.

### 5. ¿Qué no demuestra una prueba pública?

No demuestra la **eficiencia asintótica** (si una operación es $O(1)$ u $O(n)$), no revela el desperdicio de espacio en memoria, ni garantiza la ausencia de fugas de memoria (*memory leaks*) o fallas operativas bajo alta demanda.

### 6. En `resize_stress_week2.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, reducción o estabilidad?

Este archivo está diseñado para estresar la lógica de redimensionamiento de los arreglos subyacentes (`grow` y `shrink`). Al forzar la inserción masiva de cientos de elementos (crecimiento) seguida de la eliminación masiva (reducción), la prueba verifica que:

- La estructura pueda reasignar memoria dinámicamente y copiar los datos sin perderlos ni corromperlos.
- El cálculo del tamaño de los nuevos arreglos sea correcto tanto al expandirse (para no quedarse sin espacio) como al contraerse (para no desperdiciar memoria excesiva).

### 7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?

Porque las pruebas empíricas solo confirman que el código produce salidas esperadas para entradas finitas y específicas. La **explicación de invariantes** demuestra rigurosamente por qué el algoritmo es siempre correcto, y el **análisis de complejidad** es el único mecanismo formal para garantizar cómo escalará el consumo de tiempo y espacio cuando $n$ tienda al infinito.

---

## Bloque 4 - Vector como puente entre teoría y código

### Material de Revisión:

- `Semana2/include/DengVector.h`
- `Semana2/demos/demo_deng_vector.cpp`
- `Lectura4-Deng`

### 1. ¿Qué papel cumplen `_size`, `_capacity` y `_elem`?

Definen la separación entre el estado lógico y la memoria física.
- `_elem` : apunta al arreglo interno 
- `_size` : indica la cantidad real de elementos válidos (tamaño lógico)
- `_capacity` : señala el límite máximo de almacenamiento antes de requerir redimensionamiento (tamaño físico)

### 2. ¿Cuándo debe ejecutarse `expand()`?

Estrictamente antes de una inserción cuando el arreglo está lleno (`_size == _capacity`). Su ejecución duplica la capacidad física para garantizar que las futuras inserciones mantengan un costo amortizado de $O(1)$.

### 3. ¿Por qué `insert(r, e)` necesita desplazar elementos?

Debido a la restricción fundamental de memoria contigua. Para insertar un elemento en la posición `r` sin sobrescribir datos, el algoritmo está obligado a empujar todos los sucesores (el sufijo) una posición hacia la derecha, lo que cuesta $O(n-r)$.

### 4. ¿Qué diferencia conceptual hay entre `remove(r)` y `remove(lo, hi)`?

La eliminación por intervalo `remove(lo, hi)` es la operación estructural principal, ya que desplaza el sufijo sobreviviente una sola vez. 
La eliminación individual `remove(r)` no es un algoritmo independiente, sino un simple caso particular de la primera (un intervalo de longitud 1), lo que centraliza la lógica y evita ineficiencias.

### 5. ¿Qué evidencia de copia profunda aparece en la demo?

Se evidencia cuando las funciones `increaseByOne` y `MultiplyByTwo` modifican las instancias copia y asignado, respectivamente. Las salidas en consola son totalmente distintas e independientes, demostrando que los objetos poseen bloques de memoria separados y no simples referencias compartidas.

### 6. ¿Por qué `traverse()` es una buena interfaz didáctica?

Porque ilustra la separación entre el mecanismo de iteración (el ciclo `for`) y la lógica algorítmica. Enseña paradigmas de programación funcional en C++ al aceptar tanto punteros a función clásicos como objetos de tipo función (*functores*) mediante plantillas.

### 7. ¿Qué ventaja tiene implementar un vector propio antes de depender de `std::vector`?

Obliga a dominar de primera mano la gestión de memoria dinámica manual (prevención de fugas o *memory leaks*), la codificación segura de invariantes estructurales (constructores por copia y destructores) y la implementación real del análisis de costo amortizado que hace tan eficiente a la biblioteca estándar.

## Bloque 5 - RootishArrayStack: espacio y mapeo

### Material de Revisión: 

- `Semana2/include/RootishArrayStack.h`
- `Semana2/include/RootishArrayStackExplicado.h`
- `Semana2/demos/demo_rootisharraystack.cpp`
- `Semana2/demos/demo_rootisharraystack_explicado.cpp`
- `Lectura5-Morin`

### 1. ¿Cómo se distribuyen los elementos entre bloques?

Los elementos se distribuyen en una secuencia de arreglos (bloques) físicamente independientes, pero lógicamente contiguos. El bloque 0 tiene capacidad para 1 elemento, el bloque 1 para 2 elementos, el bloque 2 para 3, y así sucesivamente, formando una progresión aritmética en el tamaño de los bloques asignados.

### 2. ¿Por qué con $r$ bloques la capacidad total es $r(r+1)/2$?

Porque la capacidad total es la suma de una serie aritmética simple. Si los tamaños de los bloques son $1, 2, 3 \dots r$, la suma de los primeros $r$ números naturales está dada por la fórmula matemática $\frac{r(r+1)}{2}$.

### 3. ¿Qué problema resuelve `i2b(i)`?

Resuelve el problema de localización física sin iteración. Dado un índice lógico `i` de la lista, la función calcula matemáticamente a qué bloque físico (`b`) pertenece dicho índice resolviendo una inecuación cuadrática. Esto garantiza que el acceso siga costando tiempo constante $O(1)$.

### 4. ¿Qué información produce `locate(i)` en la versión explicada?

Produce una tupla o par de valores `[b, j]`. El valor `b` indica el índice del bloque donde reside el elemento, y `j` representa el offset o desplazamiento interno exacto dentro de ese bloque específico para encontrar el dato.

### 5. ¿Qué se gana en espacio frente a `ArrayStack`?
Se reduce asintóticamente el espacio desperdiciado. Mientras un `ArrayStack` tradicional desperdicia memoria proporcional a la cantidad de elementos, es decir de orden $O(n)$, el `RootishArrayStack` solo desperdicia espacio en el último bloque asignado, reduciendo la memoria inactiva a un límite superior de $O(\sqrt{n})$.

### 6. ¿Qué se conserva igual respecto a la interfaz?

Se conserva intacto el contrato del ADT List (Lista indexada). Para el usuario, la estructura sigue comportándose como un arreglo lineal contiguo donde `get(i)`, `set(i, x)`, `add(i, x)` y `remove(i)` operan lógicamente de la misma manera que en un vector tradicional.

### 7. ¿Qué parte les parece más difícil de defender oralmente: el mapeo, el análisis espacial o el costo amortizado de grow/shrink?

La parte más difícil de defender oralmente es el costo amortizado de `grow`/`shrink` y los desplazamientos entre bloques, por tres razones principales:
1. **Naturaleza dinámica:** El mapeo y el análisis espacial son matemáticas estáticas y directas (fáciles de demostrar en una pizarra). En cambio, el análisis amortizado exige explicar el rendimiento temporal a través de secuencias largas de operaciones.
2. **Amortización anidada:** La operación `grow()` no solo crea un arreglo, sino que inserta un puntero en otra estructura subyacente (el `ArrayStack` de bloques). Explicar este "crecimiento dentro de un crecimiento" es muy abstracto.
3. **Desplazamiento en cascada:** Justificar verbalmente cómo los elementos "saltan" las fronteras entre bloques fragmentados durante un `add` o `remove` sin perder el tiempo asintótico de $O(n-i)$ es el punto conceptualmente más denso.

--- 

## Bloque 6 - Refuerzo de lectura

### Material de Revisión: 

- `Lectura4-Deng`

### Conceptos Adicionales y Vínculo Teórico

### 1. ¿Qué aporta `operator[]` a la idea de vector?

Aporta naturalidad sintáctica. Permite que el vector, siendo una estructura abstracta y compleja (ADT), conserve la interfaz intuitiva de un arreglo primitivo (acceso directo por índice) sin romper su encapsulación interna.

### 2. ¿Qué supone `find(e)` sobre igualdad entre elementos?

Supone la existencia de un operador de comparación. Exige que el tipo de dato almacenado soporte la evaluación lógica de equivalencia (típicamente mediante la sobrecarga del operador `==`) para poder verificar coincidencias exactas durante la iteración secuencial.

### 3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?

Muestra la separación entre almacenamiento y comportamiento funcional. Evidencia que el vector puede tratarse como una unidad lógica, permitiendo inyectar funciones externas para transformar o analizar toda la colección sin que el usuario deba programar manualmente el ciclo de iteración.

### 4. ¿Por qué esta lectura sirve como refuerzo natural de `DengVector` aunque no sea el centro exclusivo de la semana?

Porque proporciona el sustento teórico de sus decisiones de diseño. La lectura explica el "porqué" matemático y algorítmico detrás de las líneas de código de `DengVector`: justifica formalmente la separación entre tamaño y capacidad, defiende el redimensionamiento geométrico mediante el análisis amortizado y explica la lógica de los desplazamientos masivos.

---

## Bloque 7 - Cierre comparativo

### De Arreglo Primitivo a Estructura Dinámica (ADT)

Pasar de un arreglo primitivo a una estructura dinámica implica crear un **Tipo de Dato Abstracto (ADT)** autónomo. Este cambio se define por cinco puntos clave:

1.  **Representación:** Se independiza la gestión de memoria, separando estrictamente el **tamaño lógico** (elementos válidos para el usuario) de la **capacidad física** (espacio total reservado).

2.  **Correctitud:** La estructura asume la responsabilidad de mantener sus invariantes internamente (desplazar elementos, hacer copias profundas), asegurando el orden y previniendo errores de memoria sin intervención del usuario.

3.  **Costo amortizado:** Al utilizar un crecimiento geométrico (ej. duplicar la capacidad), el alto costo temporal de reasignar memoria se diluye, garantizando matemáticamente un costo amortizado de **$O(1)$** por inserción.

4.  **Uso de espacio:** Se acepta un desperdicio estratégico de memoria (sobreaprovisionamiento temporal). Esta memoria inactiva es el precio que se paga para ganar velocidad y evitar reubicaciones constantes.

5.  **Comparación de variantes:**

    *   **ArrayStack:** Es la implementación base. Mantiene memoria estrictamente contigua, desperdiciando espacio en $O(n)$ y usando bucles iterativos lentos para desplazar datos.
    *   **FastArrayStack:** Conserva el mismo diseño teórico y espacial ($O(n)$), pero acelera la ejecución delegando los desplazamientos a funciones nativas de bajo nivel (optimizaciones de hardware).
    *   **RootishArrayStack:** Rompe la contigüidad absoluta usando bloques de tamaño incremental. Mantiene el acceso rápido en $O(1)$ mediante ecuaciones matemáticas y logra reducir drásticamente el desperdicio de espacio de $O(n)$ a **$O(\sqrt{n})$**.
---
