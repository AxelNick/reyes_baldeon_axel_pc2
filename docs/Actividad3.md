# Actividad 2 - Semana 2

## Integrantes
- Axel Alberto Reyes Baldeon

## Bloque 0 - Instalación y preparación

### Tareas de Configuración:
- [X] Carpeta de trabajo lista.
- [X] Verificación de acceso a:
    - Directorio `Semana3`
    - Lecturas correspondientes.
    - Archivo de entrega.
- [X] Archivo `Actividad3-CC232.md` creado.
- [X] Nombres de integrantes anotados.

---

### Verificación de Entorno (Semana 3)

**Estado de Compilación y Ejecución:**
*   **Demo ejecutada:** `demo_capitulo3_panorama.cpp`
```
$ ./sem3_demo_capitulo3_panorama
Semana 3 cargada correctamente
SLList size = 3, peek = 0
DLList: 10 20 30 
SEList: 8 6 7 
LinkedStack top = 200
LinkedQueue front = 11
LinkedDeque front/back = 5/9
ArrayDeque first/last = 4/6
```

*   **Prueba pública ejecutada:** 
```
$ ctest
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/Algoritmos y estructura de datos/Repositorio/Personal/CC-232_Personal-2026--main/Libreria_cc232/Semana3/build
    Start 1: semana3_public
1/7 Test #1: semana3_public ...................   Passed    0.02 sec
    Start 2: semana3_public_extras
2/7 Test #2: semana3_public_extras ............   Passed    0.02 sec
    Start 3: semana3_internal
3/7 Test #3: semana3_internal .................   Passed    0.02 sec
    Start 4: semana3_internal_extras
4/7 Test #4: semana3_internal_extras ..........   Passed    0.02 sec
    Start 5: semana3_stress_selist
5/7 Test #5: semana3_stress_selist ............   Passed    0.02 sec
    Start 6: semana3_public_linked_adapters
6/7 Test #6: semana3_public_linked_adapters ...   Passed    0.02 sec
    Start 7: semana3_public_compare
7/7 Test #7: semana3_public_compare ...........   Passed    0.02 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.13 sec
```

> *Nota: Se confirma que el entorno de desarrollo está correctamente configurado para trabajar con las estructuras de la Semana 3.*

# Bloque 1 - Núcleo conceptual de la semana

### Material de Revisión:
- `Semana3/README.md`
- `Parte3-Deng.pdf`
- `Parte3-Morin.pdf`
- `Semana3/include/SLList.h`
- `Semana3/include/DLList.h`
- `Semana3/include/SEList.h`
- `Semana3/include/DengList.h`
- `Semana3/include/MorinDengBridge.h`

### 1. ¿Qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico?

Cambia el mecanismo que define el orden de la secuencia. 
En el modelo contiguo (arreglos), la sucesión de datos está dada por la adyacencia física en la memoria, lo que permite el cálculo aritmético de posiciones. 
En el modelo dinámico (listas), la contigüidad física desaparece; el orden se sostiene de manera abstracta mediante referencias (punteros) que enlazan nodos distribuidos arbitrariamente.

### 2. ¿Qué diferencia hay entre acceso por rango y acceso por posición o enlace?

- El acceso por rango utiliza un índice numérico para denotar la distancia desde el inicio, obligando a las estructuras dinámicas a realizar una iteración secuencial. 
- El acceso por posición o enlace utiliza la dirección de memoria exacta del nodo, permitiendo intervenir la estructura de manera directa e inmediata, en tiempo constante $O(1)$.

### 3. ¿Por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice?

Mejora las actualizaciones locales porque, al poseer la referencia exacta, la inserción o eliminación se reduce a reasignar un par de punteros adyacentes $O(1)$, sin desplazar el resto de datos. Empeora el acceso por índice porque la ausencia de contigüidad física imposibilita la aritmética de punteros, obligando a recorrer los enlaces iterativamente $O(n)$ para llegar al elemento deseado.

### 4. ¿Por qué SLList implementa bien operaciones de Stack y Queue?

Porque la estructura mantiene referencias explícitas hacia sus dos extremos (`head` y `tail`). Esto permite que las inserciones y eliminaciones por la cabecera (operaciones de Pila o Stack) y las inserciones por la cola (operaciones de Cola o Queue) se realicen resolviendo un número constante de referencias en tiempo $O(1)$.


### 5. ¿Por qué SLList no implementa naturalmente todas las operaciones de un Deque con el mismo costo?

Un Deque exige máxima eficiencia de inserción y eliminación en ambos extremos. Aunque la `SLList` inserta en la cola rápidamente, eliminar el último elemento requiere actualizar el puntero `tail` hacia el penúltimo nodo. Al poseer únicamente enlaces unidireccionales, localizar dicho nodo previo exige iterar la lista desde la cabecera, degradando el costo a $O(n)$.

### 6. ¿Qué aporta el nodo centinela dummy en DLList?**

Aporta uniformidad estructural al convertir la lista en una topología circular. 
Al garantizar que todos los nodos reales posean siempre un predecesor y un sucesor definidos (nunca nulos), suprime la necesidad de programar lógica condicional para casos frontera (como insertar en una lista vacía o modificar los extremos).

### 7. ¿Por qué DLList permite justificar get(i), set(i,x), add(i,x) y remove(i) con costo $O(1 + \min(i, n-i))$?

Gracias al doble enlace y al conocimiento estático del tamaño ($n$), el algoritmo de búsqueda decide inteligentemente la ruta más corta: itera hacia adelante desde la cabeza si el índice corresponde a la primera mitad, o retrocede desde la cola si corresponde a la segunda. En consecuencia, el recorrido máximo nunca supera la mitad de la estructura.

### 8. ¿Cuál es la idea espacial central de SEList?

Su propósito es mitigar la alta sobrecarga espacial (*overhead*) de las listas enlazadas puras, donde cada elemento requiere memoria extra para los punteros. Lo resuelve agrupando múltiples elementos dentro de un bloque continuo por cada nodo. Así, el costo estructural de las referencias se diluye y "amortiza" al compartirse entre todos los datos del bloque.

### 9. ¿Por qué SEList reutiliza una BDeque basada en ArrayDeque?**

Al operar con bloques de elementos en lugar de datos individuales, la estructura necesita reacomodar internamente sus componentes de forma ágil para mantener el equilibrio de ocupación. Utilizar un `ArrayDeque` (un arreglo circular dinámico) dota a cada nodo de la eficiencia necesaria para absorber estos micromovimientos (inserciones o eliminaciones locales) sin sobrecarga adicional.

### 10. ¿Qué papel cumple DengList dentro de esta semana y por qué no reemplaza a las estructuras de Morin?**

`DengList` actúa exclusivamente como una capa de abstracción (un *wrapper* o adaptador) diseñada para proveer la interfaz del Tipo de Dato Abstracto formulada teóricamente por Deng (como los métodos de ordenamiento y deduplicación). No reemplaza a las estructuras de Morin (`SLList`, `DLList`) porque estas últimas constituyen el diseño arquitectónico subyacente que gestiona eficientemente la memoria y los punteros a bajo nivel.

---
## Bloque 2 - Demostración y trazado guiado

### Material de Revisión:
- `Semana3/demos/demo_sllist.cpp`
- `Semana3/demos/demo_dllist.cpp`
- `Semana3/demos/demo_selist.cpp`
- `Semana3/demos/demo_deng_list.cpp`
- `Semana3/demos/demo_morin_deng_bridge.cpp`
- `Semana3/demos/demo_capitulo3_panorama.cpp`
- `Semana3/demos/demo_min_structures.cpp`
- `Semana3/demos/demo_xor_list.cpp`
- `Semana3/demos/demo_linked_adapters.cpp`
- `Semana3/demos/demo_contiguous_vs_linked.cpp`

### Tabla de análisis de demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| **`demo_sllist.cpp`** | `peek = 5`, `pop = 5`, `remove = 10` | Lista simplemente enlazada que mantiene referencias a la cabeza (`head`) y la cola (`tail`). | Las operaciones en el frente (`peek`, `pop`, `remove`) y la inserción al final cuestan $O(1)$. No es apta para deques porque eliminar al final costaría $O(n)$. |
| **`demo_dllist.cpp`** | `DLList: 10 30 20` | Lista doblemente enlazada con nodo centinela (`dummy`) para simular circularidad. | La simetría bidireccional optimiza el acceso: encontrar un índice cuesta $O(1 + \min(i, n-i))$. El centinela simplifica el código al eliminar condicionales de frontera. |
| **`demo_selist.cpp`** | `SEList: 0 10 20 ... 90` | Combina nodos enlazados con bloques internos (`BDeque`) de tamaño fijo (ej. 3). | Reduce el desperdicio espacial de los punteros agrupando elementos. La búsqueda es más rápida que en una `DLList` pura al saltar por bloques enteros. |
| **`demo_deng_list.cpp`** | `ordenada: 5 10 20 30` | Actúa como un *wrapper* o adaptador (DengList) sobre una lista preexistente. | Demuestra el patrón de diseño Adapter: provee métodos abstractos avanzados (como `sort`) sin alterar el diseño de bajo nivel de la lista original. |
| **`demo_morin_deng_bridge.cpp`** | `DLList reforzada...: 1 2 3 4` | Muestra la interoperabilidad: una `DLList` de Morin se transforma, se limpia de duplicados y se reasigna. | Valida la arquitectura del proyecto: permite aplicar algoritmos teóricos costosos (como `dedup`) a estructuras de memoria optimizada mediante un "puente" de traducción. |
| **`demo_capitulo3_panorama.cpp`** | Impresión de los extremos de múltiples estructuras (ej. `LinkedDeque front/back`). | Sirve como prueba integradora que instancia y verifica las interfaces de las estructuras básicas y los adaptadores. | Valida la consistencia del Tipado de Datos Abstracto (ADT) comprobando que las interfaces públicas responden correctamente a operaciones equivalentes en distintas implementaciones. |
| **`demo_min_structures.cpp`** | `MinStack min=2 top=7` | Implementa estructuras decoradas que rastrean simultáneamente el mínimo histórico de sus elementos. | Exige una sobrecarga espacial ($O(n)$ extra) para mantener la historia de mínimos, permitiendo así consultar el menor elemento en tiempo $O(1)$ sin búsquedas iterativas. |
| **`demo_xor_list.cpp`** | `XorList: 5 10 20` | Comprime dos punteros (`prev` y `next`) en uno solo mediante operaciones lógicas bit a bit (XOR). | Maximiza el ahorro de memoria en lenguajes de bajo nivel, logrando el comportamiento de una lista doble con el costo espacial de una lista simple. |
| **`demo_linked_adapters.cpp`** | Restricciones de acceso (ej. `pop()` en Pila, `remove()` en Cola). | Enmascara la interfaz completa de las listas para exponer solo los métodos permitidos por el ADT deseado. | Demuestra el principio de encapsulamiento: se restringe deliberadamente el acceso aleatorio ($O(n)$) para garantizar operaciones exclusivamente en tiempo constante $O(1)$. |
| **`demo_contiguous_vs_linked.cpp`** | Comparativa paralela entre `ArrayDeque` y `LinkedDeque`. | Enfrenta en tiempo real una solución de arreglos circulares contra una de nodos enlazados. | Expone el *trade-off* fundamental: los arreglos (`ArrayDeque`) ganan en localidad de memoria y acceso $O(1)$, mientras que los nodos (`LinkedDeque`) ganan en costo de inserción local y evitan redimensionamientos costosos. |

### Evidencias de Compilación y Ejecución

### demo_sllist.cpp

```
$ ./sem3_demo_sllist
size = 3
peek = 5
pop = 5
remove = 10
```

### demo_dllist.cpp

```
$ ./sem3_demo_dllist
DLList: 10 20 30 
```

### demo_selist.cpp

```
$ ./sem3_demo_selist
SEList: 0 10 20 30 40 50 60 70 80 90 
```

### demo_deng_list.cpp

```
$ ./sem3_demo_deng_list.exe
size = 4
front = 5
back = 20
ordenada: 5 10 20 30 

```

### demo_morin_deng_bridge.cpp

```
$ ./sem3_demo_morin_deng_bridge.exe
DLList reforzada con Deng: 1 2 3 4 
Removido = 1
```

### demo_capitulo3_panorama.cpp

```
$ ./sem3_demo_capitulo3_panorama
Semana 3 cargada correctamente
SLList size = 3, peek = 0
DLList: 10 20 30 
SEList: 8 6 7 
LinkedStack top = 200
LinkedQueue front = 11
LinkedDeque front/back = 5/9
ArrayDeque first/last = 4/6
```

### demo_min_structures.cpp

```
$ ./sem3_demo_min_structures
MinStack min=3 top=7
MinQueue min=2 front=4
MinDeque min=1 front=3 back=1
```

### demo_xor_list.cpp

```
$ ./sem3_demo_xor_list
XorList: 5 10 20 
front=5 back=20
```

### demo_linked_adapters.cpp

```
$ ./sem3_demo_linked_adapters
Adaptadores enlazados de Semana 3

LinkedStack
  top() = 30
  pop() = 30
  top() = 20
  size() = 2

LinkedQueue
  front() = 1
  remove() = 1
  front() = 2
  size() = 2

LinkedDeque
  front() = 10, back() = 40
  removeFirst() = 10
  removeLast() = 40
  front() = 20, back() = 30
  size() = 2
```

### demo_contiguous_vs_linked.cpp

```
$ ./sem3_demo_contiguous_vs_linked
Comparacion contiguo vs enlazado (standalone Semana3)

[1] Cola FIFO
  Cola contigua (sobre ArrayDeque)  front/remove: 1 / 1
  Cola enlazada (LinkedQueue)       front/remove: 1 / 1

[2] Deque
  ArrayDeque   first/last: a / d
  LinkedDeque  first/last: a / d

[3] Acceso por indice
  ArrayDeque get(4) = 40
  DLList    get(4) = 40

Observaciones:
- La representacion contigua ofrece mejor localidad de memoria.
- La representacion enlazada facilita inserciones/borrados locales.
- ArrayDeque cubre la comparacion contigua;
  En el repositorio se puede complementar con ArrayQueue y DualArrayDeque.
```

### Análisis de Demos y Observables (Semana 3)

### 1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola?

La secuencia de `push(5)` (comportamiento de pila) seguida de `add(10)` y `add(20)` (comportamiento de cola). Al ejecutar `pop()` y obtener el 5, y luego `remove()` para obtener el 10, se evidencia que la estructura gestiona ambos protocolos de acceso en sus extremos de forma simultánea.

### 2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?

La operación `d.add(1, 20)`. Al insertar el valor 20 entre el 10 (índice 0) y el 30 (índice 1), se demuestra la capacidad de la `DLList` para reorganizar punteros en cualquier punto de la secuencia mediante el uso del nodo centinela.

### 3. En `demo_selist.cpp`, ¿qué observable permite defender el orden lógico frente al trabajo por bloques?

La salida `SEList: 0 10 20 ... 90` tras un ciclo de inserciones por índice. Aunque internamente los datos están fragmentados en bloques (`BDeque`), la interfaz permite recuperarlos secuencialmente, demostrando que la estructura preserva la abstracción de una lista lineal continua para el usuario.

### 4. En `demo_deng_list.cpp`, ¿qué evidencia muestra un ADT de lista más completo?

La presencia del método `lista.sort()` y las funciones `push_front`/`back`. Esto evidencia que `DengList` no solo almacena datos, sino que incorpora capacidades de procesamiento (ordenamiento y búsqueda) que acercan la estructura a un componente de software listo para su uso en aplicaciones finales.

### 5. En `demo_morin_deng_bridge.cpp`, ¿qué justifica la reutilización de algoritmos?

La salida `Removido = 1` tras aplicar `dedup_with_deng(lista)`. Esto prueba que se pueden aplicar algoritmos complejos (como eliminar duplicados) sobre una `DLList` de Morin sin modificar su código original, utilizando el puente como traductor de datos.

### 6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual se observa en `min()`?

Se observa que la estructura no realiza una búsqueda lineal cada vez que se pide el mínimo; en su lugar, utiliza espacio adicional para almacenar el rastro de los mínimos históricos. Es un compromiso donde se sacrifica memoria para obtener un tiempo de respuesta de $O(1)$.

### 7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la reutilización?

El `LinkedStack`. Representa perfectamente la reutilización al emplear una `SLList` completa internamente, pero restringiendo su interfaz para que el usuario solo pueda interactuar con el "tope" de la pila, cumpliendo así con el contrato del ADT Pila.

### 8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa en los accesos?

Se observa que `ArrayDeque` destaca en el acceso por índice y localidad de memoria al usar un bloque contiguo, mientras que `LinkedDeque` sobresale en la inserción local, ya que no requiere desplazar elementos ni redimensionar arreglos, trabajando únicamente con reconexión de enlaces.

---

## Bloque 3 - Pruebas públicas, stress y correctitud

### Material de Revisión:
- `Semana3/pruebas_publicas/README.md`
- `Semana3/pruebas_publicas/test_public_week3.cpp`
- `Semana3/pruebas_publicas/test_public_deng_bridge.cpp`
- `Semana3/pruebas_publicas/test_public_extras.cpp`
- `Semana3/pruebas_publicas/test_public_linked_adapters.cpp`
- `Semana3/pruebas_publicas/test_public_contiguous_vs_linked.cpp`
- `Semana3/pruebas_internas/test_internal_week3.cpp`
- `Semana3/pruebas_internas/test_internal_deng_algorithms.cpp`
- `Semana3/pruebas_internas/test_internal_extras.cpp`
- `Semana3/pruebas_internas/stress_selist_week3.cpp`

### 1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?

Valida las operaciones elementales de los extremos: inserción al inicio (`push`) y al final (`add`), lectura frontal (`peek`), eliminación frontal (`pop`/`remove`), y la consulta del número de elementos (`size`).

### 2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?

Valida el comportamiento de una lista indexada general: inserción en una posición específica (`add(i, x)`), acceso por índice (`get(i)`), eliminación por índice (`remove(i)`) y consulta de la longitud (`size`).

### 3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?

Valida la misma interfaz de lista indexada que la `DLList` (`add`, `get`, `set`, `remove`, `size`), pero aplicada a su arquitectura interna de bloques (asegurando que encuentre los datos correctamente dentro de las sub-colas).

### 4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?

Cubre algoritmos avanzados y específicos: métodos extendidos de las listas como inversión (`reverse`), rotación (`rotate`), búsqueda del penúltimo (`secondLast`), validación de palíndromos, y el correcto funcionamiento de estructuras especializadas (`MinStack`, `MinQueue`, `MinDeque`, `XorList`).

### 5. ¿Qué valida específicamente `test_public_linked_adapters.cpp` sobre `LinkedStack`, `LinkedQueue` y `LinkedDeque`?

Valida la correcta restricción de acceso (políticas del ADT). Asegura que los adaptadores expongan estrictamente operaciones LIFO (`push`/`pop`/`top` para pilas), FIFO (`add`/`remove`/`front` para colas) y operaciones en ambos extremos (`addFirst`/`removeLast`, etc., para deques), utilizando las listas enlazadas subyacentes sin alterar su integridad.

### 6. ¿Qué demuestra `test_public_deng_bridge.cpp` sobre integración y reutilización?

Demuestra la interoperabilidad de la librería. Prueba que las estructuras de Morin (`DLList`, `SEList`) pueden convertirse, ser procesadas por los algoritmos teóricos de Deng (como `sort` o `dedup`) mediante puentes (*bridges*), y ser reasignadas a su forma original sin pérdida de datos.

### 7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?

Estresa los mecanismos internos de equilibrio de bloques de la `SEList` (las operaciones `spread` y `gather`). Al insertar 500 elementos, borrar 250 del frente y luego inyectar 100 en medio, fuerza a la estructura a reacomodar datos entre nodos constantemente, verificando que no se corrompan los punteros y que el tamaño lógico final sea exactamente 350.

### 8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?

Demuestra la correctitud funcional empírica. Confirma que, para un conjunto de entradas predefinidas y controladas, los punteros se actualizan bien, no hay caídas por punteros nulos (*segfaults*), y las salidas coinciden con el comportamiento esperado.

### 9. ¿Qué no demuestra una prueba pública por sí sola?

No demuestra la eficiencia algorítmica real (si la operación toma tiempo $O(1)$ u $O(n)$), ni garantiza la ausencia de fugas de memoria oculta (*memory leaks*), ni prueba la robustez del código ante escenarios límite o volúmenes masivos de datos no controlados.

### 10 . ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?

Porque las pruebas solo verifican el "qué" empírico en casos finitos, pero la explicación teórica provee el "porqué" universal. Solo razonando sobre invariantes y analizando matemáticamente la complejidad se puede garantizar formalmente que la estructura escalará de manera eficiente y segura para cualquier valor de $n$.

---

## Bloque 4 - SLList, DLList y SEList: lectura cercana del código

### Material de Revisión:
- `Semana3/include/SLList.h`
- `Semana3/include/DLList.h`
- `Semana3/include/SEList.h`
- `Parte3-Morin.pdf`
- `Parte3-Deng.pdf`


### 1. En SLList, ¿qué papel cumplen head, tail y n?

`head` es el puntero que mantiene la referencia al primer nodo de la secuencia, `tail` es el puntero que apunta al último nodo, y `n` es la variable entera que contabiliza la cantidad total de elementos almacenados (tamaño lógico).

### 2. En SLList::push, pop, add y remove, ¿qué punteros cambian exactamente?

En `push` (insertar al inicio), el puntero `next` del nuevo nodo se conecta al antiguo `head`, y `head` se reasigna al nuevo nodo. En `pop` o `remove` (eliminar al inicio), `head` avanza hacia el nodo siguiente (`head = head->next`) y el nodo anterior se libera. En `add` (insertar al final), el puntero `next` del nodo `tail` actual se conecta al nuevo nodo, y luego `tail` se reasigna a ese nuevo nodo.

### 3. Expliquen cómo funciona secondLast() y por qué no puede resolverse directamente con solo mirar tail.

`secondLast()` funciona recorriendo toda la secuencia desde el principio (`head`) iterando hasta encontrar el nodo cuyo puntero `next` sea igual a `tail`. No puede resolverse mirando directamente a `tail` porque la lista es unidireccional; los nodos solo conocen a su sucesor, por lo que `tail` no tiene forma de apuntar hacia atrás a su predecesor.

### 4. Expliquen paso a paso cómo funciona reverse() y por qué no necesita estructura auxiliar.

`reverse()` invierte la lista "en su lugar" utilizando tres punteros de apoyo (`prev`, `curr` y `next`). Paso a paso: 
1. Almacena temporalmente el siguiente nodo (`next = curr->next`).
2. Voltea la flecha del nodo actual hacia atrás (`curr->next = prev`).
3. Desplaza `prev` y `curr` un paso hacia la derecha. 
No necesita estructura auxiliar porque no crea datos nuevos; simplemente altera las conexiones físicas (enlaces) de los nodos ya existentes.

### 5. Expliquen qué verifica checkSize() y por qué esta función ayuda a defender correctitud.

Verifica manualmente la integridad de la estructura contando los nodos desde `head` hasta nulo, comprobando que este conteo físico coincida exactamente con la variable teórica `n`. También valida que `tail` apunte de verdad al último elemento recorrido. Ayuda a defender la correctitud porque garantiza que los invariantes estructurales no se corrompieron tras ejecutar operaciones de modificación.

### 6. En DLList, expliquen por qué getNode(i) puede empezar desde el inicio o desde el final.

Puede hacerlo porque es una estructura doblemente enlazada, donde cada nodo posee un enlace previo y uno siguiente. El algoritmo evalúa numéricamente si el índice buscado `i` pertenece a la primera mitad de la lista (`n / 2`); si es así, avanza desde el inicio, y si pertenece a la segunda mitad, retrocede desde el final, reduciendo el recorrido a la mitad.

### 7. En DLList::addBefore, ¿qué enlaces se actualizan y por qué el nodo centinela elimina casos borde?

Al insertar el nuevo nodo `u`, se actualizan cuatro referencias: los dos enlaces del nuevo nodo (`u->next` y `u->prev`), el enlace frontal de su nuevo predecesor (`u->prev->next = u`) y el enlace trasero de su nuevo sucesor (`u->next->prev = u`). El nodo centinela (`dummy`) elimina los casos borde porque proporciona un anillo lógico continuo; asegura que el primer y último elemento real siempre tengan un nodo vecino válido, evitando usar condiciones especiales como "si la lista está vacía".

### 8. Expliquen cómo funciona rotate(r) sin mover los datos elemento por elemento.

En vez de reubicar los datos uno a uno, `rotate(r)` identifica geométricamente el nodo que será la nueva cabecera y el nodo que será la nueva cola. Luego, simplemente desconecta el anillo en ese punto y reconecta las referencias del nodo centinela (`dummy`) a estos nuevos extremos, rotando la estructura entera de forma casi instantánea.

### 9. Expliquen cómo isPalindrome() aprovecha la naturaleza doblemente enlazada de la estructura.

Aprovecha la simetría lanzando dos punteros al mismo tiempo: uno que viaja hacia adelante desde la cabeza y otro que viaja hacia atrás desde la cola. En cada iteración compara ambos valores, deteniéndose en la mitad de la lista, lo cual sería logísticamente ineficiente en una lista simple unidireccional.

### 10. En SEList, expliquen qué representa Location.

`Location` es una estructura de coordenadas (un par). El puntero `u` indica el nodo específico de la lista (el "bloque" contenedor), mientras que el entero `j` señala el índice exacto donde reside el dato dentro del pequeño arreglo interno (`BDeque`) de dicho nodo.

### 11. Expliquen qué hacen spread() y gather() y en qué situaciones aparecen.

Son funciones de mantenimiento que protegen el tamaño límite de los bloques. `spread()` se activa durante las inserciones cuando varios bloques se saturan; este inserta un bloque nuevo y redistribuye equitativamente los elementos sobrantes para hacer espacio. `gather()` ocurre en las eliminaciones cuando hay bloques subutilizados; reúne (colapsa) elementos de varios bloques adyacentes vacíos y elimina un bloque para ahorrar memoria.

### 12. Expliquen cómo el tamaño de bloque b afecta el trade-off entre acceso, actualización y uso de espacio.

El valor `b` regula el balance estructural. Un `b` grande minimiza el uso de espacio (diluye el costo de los punteros) y acelera la búsqueda (permite saltar grandes segmentos), pero encarece temporalmente la actualización local por la contigüidad interna del bloque. Un `b` pequeño recupera la velocidad de inserción/eliminación local de una lista normal, pero penaliza la eficiencia de espacio y hace el acceso iterativo más lento.

---

## Bloque 5 - Adaptadores y estructuras derivadas

### Material de Revisión:
- `Semana3/include/LinkedStack.h`
- `Semana3/include/LinkedQueue.h`
- `Semana3/include/LinkedDeque.h`
- `Semana3/include/MinStack.h`
- `Semana3/include/MinQueue.h`
- `Semana3/include/MinDeque.h`
- `Semana3/demos/demo_linked_adapters.cpp`
- `Semana3/demos/demo_min_structures.cpp`

### Análisis de Adaptadores y Estructuras con Mínimo (Semana 3)

### 1. ¿Cómo reutiliza `LinkedStack` a `SLList`?

Reutiliza la lista mediante el patrón de diseño de composición (adaptador). La clase contiene una instancia privada de `SLList` y restringe su interfaz pública, redirigiendo todas las operaciones típicas de una pila (`push`, `pop`, `top`) hacia los métodos que operan exclusivamente en la cabecera de la lista simple (`push`, `pop`, `peek`).

### 2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?

De forma análoga a la pila, enmascara una `SLList` privada. Para garantizar el comportamiento FIFO (Primero en Entrar, Primero en Salir), asocia la operación de inserción (`add`) de la cola con el método que inserta al final de la lista, y asocia las operaciones de extracción (`remove`, `front`) con los métodos que leen y eliminan en la cabecera de la lista.

### 3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?

Un Deque requiere eficiencia temporal ($O(1)$) tanto para inserciones como para eliminaciones en ambos extremos. Una `SLList` solo permite eliminar eficientemente en la cabecera. La `DLList` (lista doblemente enlazada), al poseer enlaces en ambas direcciones, es la única que permite resolver la extracción desde el final (`removeLast`) sin tener que recorrer toda la estructura de forma iterativa.

### 4. En `MinStack`, ¿por qué cada entrada guarda el valor y el mínimo acumulado?

Almacenar el "mínimo histórico" junto con cada valor ingresado evita tener que recorrer toda la pila buscando el elemento menor. Esto permite que la función `min()` simplemente lea el registro precalculado del elemento superior (el tope actual) y devuelva el resultado de manera instantánea en tiempo $O(1)$.

### 5. En `MinQueue`, ¿por qué usar dos pilas permite mantener semántica FIFO y consulta de mínimo?

Se emplean dos estructuras `MinStack`: una para recibir elementos (`in_`) y otra para extraerlos (`out_`). Cuando `out_` se vacía, los elementos de `in_` se vierten en `out_`, lo cual invierte su orden y logra la secuencia FIFO natural de una cola. Como ambas son pilas de mínimos, el mínimo global de la cola completa se halla comparando únicamente el mínimo de `in_` frente al mínimo de `out_`.

### 6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?

Resuelve el escenario en el que un extremo se queda sin elementos, lo cual impediría realizar operaciones de extracción en ese lado. La función `rebalance()` toma una "fotografía" secuencial de todos los datos actuales y los divide simétricamente entre `front_` y `back_`, garantizando que ambos extremos tengan elementos disponibles para futuras operaciones.

### 7. Comparen "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.

"Implementar" es programar la gestión de memoria y los enlaces de bajo nivel desde cero, como ocurre internamente en `SLList` (creando y conectando punteros `Node`). "Adaptar" es utilizar una estructura que ya funciona y envolverla para cambiar las reglas de cómo el usuario interactúa con ella, como hace `LinkedStack`, que no crea nodos, sino que delega el trabajo a los métodos de la `SLList` que lleva dentro.

### 8. ¿Qué operaciones pueden defender como constantes y cuáles deben defender como amortizadas?

Las operaciones básicas de inserción y extracción puras (`push`, `pop` en `LinkedStack` o `MinStack`) se defienden como de tiempo constante estricto ($O(1)$). Sin embargo, operaciones como `remove()` en `MinQueue` o `removeFirst()`/`removeLast()` en `MinDeque` deben defenderse como de tiempo constante **amortizado** ($O(1)$), debido a que ocasionalmente ejecutan movimientos masivos internos (como el volcado de la pila `in_` o el `rebalance()`), pero este costo se diluye sobre múltiples operaciones rápidas.

---

## Bloque 6 - Deng como refuerzo algorítmico y puente de integración

### Material de Revisión:
- `Semana3/include/CleanList.h`
- `Semana3/include/DengList.h`
- `Semana3/include/MorinDengBridge.h`
- `Semana3/demos/demo_deng_list.cpp`
- `Semana3/demos/demo_morin_deng_bridge.cpp`
- `Semana3/pruebas_publicas/test_public_deng_bridge.cpp`
- `Semana3/pruebas_internas/test_internal_deng_algorithms.cpp`
- `Parte3-Deng.pdf`

### Bloque 4: Integración y Algoritmos (Deng & Morin Bridge)

### 1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?

`DengList` refuerza operaciones algorítmicas avanzadas orientadas al procesamiento y la búsqueda de datos. Estas incluyen el ordenamiento (`sort`), la purga de elementos duplicados (`dedup`, `uniquify`), la inversión de la secuencia (`reverse`) y métodos de consulta específicos (`contains`, `find_index`, `search`).

### 2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?

La principal ventaja es respetar el Principio de Responsabilidad Única mediante el patrón de diseño "Adaptador". Permite que las estructuras base (como las de Morin) se mantengan simples y enfocadas solo en la gestión eficiente de la memoria, mientras que las operaciones teóricas complejas de alto nivel se añaden a través de la cápsula `DengList` sin alterar ni "romper" el código original.

### 3. Expliquen qué hacen `to_deng` y `assign_from_deng`.

Son funciones traductoras. `to_deng` extrae los datos de una lista base (`DLList` o `SEList`) copiándolos secuencialmente para construir una nueva `DengList`. Por el contrario, `assign_from_deng` realiza el camino inverso: vacía la lista base original y la vuelve a llenar con los datos ya procesados provenientes de la `DengList`.

### 4. Expliquen por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento dentro de `DLList` o `SEList`.

No obliga a reimplementarlo porque delega el trabajo utilizando las funciones traductoras (el "puente"). Primero transforma temporalmente la `DLList` o `SEList` en una `DengList`, luego ejecuta el método `sort()` que ya existe en esta última, y finalmente devuelve los datos ya ordenados a su estructura original.

### 5. Expliquen qué hace `dedup_with_deng` y qué relación guarda con `deduplicate()` o `uniquify()` de la teoría.

Esta función elimina los elementos repetidos de las estructuras de Morin apoyándose en el puente hacia `DengList`. Se relaciona con la teoría en que implementa el ADT de Deng: `dedup()` elimina duplicados en listas no ordenadas, mientras que `uniquify()` realiza una purga similar pero mucho más rápida asumiendo que la lista ya está previamente ordenada.

### 6. Expliquen por qué `reverse_with_deng` es un ejemplo de reutilización de algoritmos sobre una interfaz común.

Es un ejemplo de reutilización porque permite aplicar exactamente la misma lógica de inversión a estructuras internas muy distintas (como `DLList` y `SEList`). Al convertir ambas a un formato estándar intermedio (`DengList`), el programador se ahorra tener que escribir un código de inversión a medida para la arquitectura de nodos específica de cada tipo de lista.

### 7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?

La conversión introduce un costo adicional lineal de tiempo ($O(n)$) y espacio extra ($O(n)$), debido a que se deben copiar todos los elementos. Vale la pena aceptarlo cuando el algoritmo principal a aplicar es mucho más complejo que la copia (como un ordenamiento $O(n \log n)$), o cuando se prioriza la **reutilización y legibilidad** del código sobre la optimización extrema de recursos.

---

### Bloque 7: Comparación enlazado vs contiguo, variantes y evidencia experimental

### Material de Revisión:
- `Semana3/include/ArrayDeque.h`
- `Semana3/include/XorList.h`
- `Semana3/demos/demo_contiguous_vs_linked.cpp`
- `Semana3/demos/demo_xor_list.cpp`
- `Semana3/benchmarks/benchmark_semana3.cpp`
- `Parte3-Morin.pdf`

### 1. Comparen `ArrayDeque` y `LinkedDeque`: ¿qué cambia en representación y qué cambia en costo observable?

En cuanto a la **representación**, `ArrayDeque` utiliza un bloque contiguo de memoria (un arreglo circular dinámico), mientras que `LinkedDeque` utiliza nodos dispersos unidos por enlaces o referencias. En cuanto al **costo observable**, `ArrayDeque` ofrece un acceso por índice extremadamente rápido (tiempo constante), pero puede sufrir demoras (costo $O(n)$) si necesita redimensionar el arreglo; por el contrario, `LinkedDeque` hace que el acceso por índice sea lento ($O(n)$), pero garantiza inserciones y eliminaciones en los extremos en tiempo constante estricto sin necesidad de redimensionar.

### 2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?

Significa que los elementos de la estructura se almacenan físicamente uno al lado del otro en la memoria de la computadora. Esta disposición física permite que el procesador los lea secuencialmente a gran velocidad, aprovechando al máximo la **memoria caché**, a diferencia de los nodos enlazados que obligan al procesador a buscar direcciones de memoria dispersas, provocando fallos de caché (*cache misses*).

### 3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?

Favorece de manera destacada a las **operaciones de modificación local** (inserciones y eliminaciones). Una vez que se tiene la referencia del lugar exacto, agregar o quitar un nodo solo requiere reconectar un par de enlaces, evitando por completo el costoso desplazamiento masivo de elementos que sufriría un arreglo.

### 4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?

Para analizar el **acceso aleatorio**, la comparación ideal es enfrentar los tiempos de `random_get_arraydeque` contra `random_get_dllist`, ya que miden la diferencia de velocidad al consultar posiciones dispersas. Para evaluar las **operaciones en los extremos**, la comparación más útil es observar `deque_contiguo_arraydeque` frente a `deque_enlazado_linkeddeque`, las cuales cronometran ciclos masivos de inserción y eliminación pura en la cabeza y la cola.

### 5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?

Porque el rendimiento real está condicionado por el **patrón de operaciones específico** del problema a resolver. Una prueba aislada ignora factores cruciales como el consumo total de memoria, la complejidad de implementación o la facilidad de mantenimiento. Ninguna estructura es universalmente superior; todas representan compromisos de diseño (*trade-offs*).

### 6. ¿Qué idea intenta mostrar `XorList` respecto al ahorro de punteros?

Intenta demostrar que es posible obtener los beneficios de navegación bidireccional de una lista doble ocupando únicamente el espacio en memoria de una lista simple. Logra esto **comprimiendo matemáticamente** los dos punteros clásicos (`prev` y `next`) en una sola variable mediante la operación lógica de bits **XOR**.

### 7. ¿Qué desventaja práctica introduce una estructura como `XorList` aunque sea interesante desde el punto de vista del espacio?

La desventaja principal es la **complejidad operativa**: no se puede acceder al nodo siguiente mirando un nodo aislado, sino que es obligatorio conocer la dirección del nodo anterior para decodificar el enlace. Además, requiere manipular direcciones de memoria crudas (punteros a enteros), lo que dificulta la legibilidad, la depuración y eleva el riesgo de errores fatales.

---
# Bloque 8 - Cierre comparativo y preparación de sustentación

### ¿Qué cambia cuando pasamos de "usar arreglos dinámicos" a "diseñar estructuras enlazadas y adaptadores sobre nodos"?

El paso de arreglos dinámicos a estructuras enlazadas y adaptadores representa una transición de un modelo de **continuidad física** a uno de **conectividad lógica**. Este cambio se resume en los siguientes puntos fundamentales:

*   **Sobre la representación:** Se abandona el bloque único de memoria contigua en favor de una **representación fragmentada**, donde la unidad básica es el **nodo**. El orden de la secuencia ya no lo determina la adyacencia en el hardware, sino la existencia de punteros que vinculan direcciones de memoria dispersas.

*   **Sobre el acceso:** El **acceso por rango** (índice) deja de ser una operación matemática inmediata $O(1)$ para convertirse en una búsqueda iterativa de costo lineal $O(n)$, mientras que el **acceso por posición** (enlace directo) se vuelve la forma natural y más eficiente de interactuar con la estructura.

*   **Sobre las modificaciones locales:** Las **inserciones y eliminaciones locales** se optimizan drásticamente; al poseer la referencia de un nodo, estas operaciones se resuelven mediante una simple reconexión de punteros en tiempo constante estricto $O(1)$, eliminando la necesidad de desplazar elementos o redimensionar arreglos.

*   **Sobre la complejidad:** Se observa una gradación en la sofisticación de los enlaces: la **SLList** ofrece eficiencia mínima en extremos, la **DLList** logra simetría bidireccional permitiendo optimizar búsquedas al centro ($O(1 + \min(i, n-i))$), y la **SEList** introduce un híbrido que amortiza el costo espacial de los punteros mediante bloques.

*   **Sobre la reutilización:** El diseño evoluciona hacia la modularidad mediante **adaptadores** (como `LinkedStack`) y **puentes** (`MorinDengBridge`), permitiendo que una estructura enlazada base asuma múltiples comportamientos (ADT) o sea procesada por algoritmos externos sin alterar su arquitectura interna.

*   **Comparación final:** Mientras que la **representación contigua** prioriza la velocidad de lectura y la localidad de memoria (caché), la **representación enlazada** prioriza la flexibilidad estructural y la eficiencia en la edición constante de la secuencia, sacrificando para ello el acceso aleatorio rápido.

---
