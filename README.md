# Grupo 10

Integrantes:
- Cristhyan Manuel Perez Villegas
- Angel Navarro Ruiz

# Find Minimum in Rotated Sorted Array

> **Problema:** LeetCode 153 — [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, 
the array nums = [0,1,2,4,5,6,7] might become:

- [4,5,6,7,0,1,2] if it was rotated 4 times.
- [0,1,2,4,5,6,7] if it was rotated 7 times.

Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
Given the sorted rotated array nums of unique elements, return the minimum element of this array.
You must write an algorithm that runs in O(log n) time.

Example 1:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
Example 2:

Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
Example 3:

Constraints:

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.

## Entrada y salida

Entrada: Un arreglo de enteros arr de tamaño n, originalmente ordenado de forma estrictamente ascendente y rotado un número desconocido de posiciones. Por ejemplo: [3, 4, 5, 1, 2].

Salida: El valor mínimo del arreglo (o su índice, según la implementación).

## Tamaño de entrada relevante

El parámetro relevante es n, la cantidad de elementos del arreglo. A medida que n crece, el costo de encontrar el mínimo depende directamente del enfoque utilizado. Para entradas pequeñas cualquier estrategia es viable, pero conforme n escala, la diferencia entre un recorrido completo y una búsqueda que descarta porciones del arreglo se vuelve significativa.

## Descripción de la solución

El problema admite varios enfoques. El más directo consiste en recorrer todos los elementos y llevar registro del menor encontrado. Sin embargo, dado que el arreglo tiene una estructura particular —es un arreglo ordenado con un punto de quiebre— es posible aprovechar esa propiedad para reducir el espacio de búsqueda en cada paso y encontrar el mínimo sin necesidad de examinar todos los elementos. También existe la alternativa de reordenar el arreglo con herramientas estándar y acceder directamente al primer elemento.

# Soluciones

Se implementaron y compararon tres soluciones para encontrar el mínimo en un arreglo rotado:

### Solución 1 — Búsqueda binaria `encontrarMin` — O(log n) Solución principal

Aprovecha la propiedad estructural del arreglo rotado: en cada paso compara `arr[medio]` con `arr[high]` para determinar en cuál mitad se encuentra el punto de quiebre y descarta la otra mitad. Cada iteración reduce el rango a la mitad.

```cpp
int encontrarMin(int arr[], int n) {
    int low = 0, high = n - 1;
    while (low < high) {
        int medio = (low + high) / 2;
        if (arr[medio] > arr[high])
            low = medio + 1;
        else
            high = medio;
    }
    return low;
}
```

### Solución 2 — Búsqueda lineal `encontrarMinIngenua` — O(n)

Recorre el arreglo completo de izquierda a derecha, comparando cada elemento con el mínimo encontrado hasta ese momento. No aprovecha ninguna propiedad estructural del arreglo rotado.

```cpp
int encontrarMinIngenua(int arr[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex])
            minIndex = i;
    }
    return minIndex;
}
```

Es la solución más intuitiva pero también la más costosa: siempre realiza n − 1 comparaciones independientemente de la entrada.

### Solución 3 — STL sort `encontrarMinSort` — O(n log n)

Ordena el arreglo completo con `std::sort` y devuelve el primer elemento. Es la solución más ineficiente de las tres porque paga el costo completo de un ordenamiento cuando el problema solo requiere encontrar un elemento.

```cpp
int encontrarMinSort(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr[0];
}
```

Esta solución ilustra el principio central de la práctica: una mejora en la elección del algoritmo tiene más impacto que cualquier microoptimización. El sort hace trabajo completamente innecesario.



# Análisis de Soluciones

### 1. Solución Óptima — Búsqueda Binaria

**Justificación de determinismo y factibilidad**  
Dado un arreglo de enteros con rotación, el algoritmo siempre produce el mismo índice del mínimo para la misma entrada. No existe aleatoriedad ni decisiones ambiguas: cada comparación depende únicamente de los valores del arreglo, por lo que el resultado es completamente predecible y reproducible.

**Argumento de finitud**  
En cada iteración el espacio de búsqueda `[low, high]` se reduce estrictamente: si se toma la rama `low = medio + 1` el intervalo se achica por la izquierda; si se toma `high = medio` se achica por la derecha. Como `medio` siempre es estrictamente menor que `high` (división entera con `low < high`), el intervalo nunca permanece igual. Al ser finito y decrecer en cada paso, el ciclo termina en a lo sumo `⌈log₂(n)⌉` iteraciones.

**Argumento de correctitud**  
El algoritmo mantiene la propiedad de que el índice del mínimo siempre se encuentra dentro de `[low, high]`. Al terminar, `low == high`, por lo que ese único índice es necesariamente el mínimo global.

**Invariante**  
> Al inicio de cada iteración, el índice del mínimo global se encuentra en `arr[low..high]`.

- *Base:* con `low = 0` y `high = n - 1`, el intervalo contiene todo el arreglo.  
- *Paso:* si `arr[medio] > arr[high]`, el mínimo no puede estar en `[low, medio]` pues ese segmento es creciente y mayor que `arr[high]`, así que se actualiza `low = medio + 1`. En caso contrario, el mínimo está en `[low, medio]` y se actualiza `high = medio`. La invariante se preserva en ambos casos.

**Monotonicidad**  
La cantidad `high - low` es estrictamente decreciente en cada iteración, actuando como función de ranking que converge a 0 y garantiza la terminación.

---

### 2. Solución Ingenua — Recorrido Lineal

**Justificación de determinismo y factibilidad**  
El algoritmo recorre el arreglo de izquierda a derecha de forma secuencial. Para cualquier entrada fija siempre retorna el mismo índice, sin depender de factores externos ni decisiones no deterministas.

**Argumento de finitud**  
El índice `i` se incrementa en 1 en cada iteración, comenzando en 1 y terminando en `n - 1`. El bucle ejecuta exactamente `n - 1` iteraciones, por lo que termina en tiempo finito y estrictamente acotado por el tamaño de la entrada.

**Argumento de correctitud**  
`minIndex` siempre guarda el índice del menor elemento visto hasta la iteración `i`. Al finalizar el recorrido completo, todos los elementos han sido comparados, por lo que `minIndex` contiene el índice del mínimo global.

**Invariante**  
> Al inicio de la iteración `i`, `minIndex` es el índice del mínimo en `arr[0..i-1]`.

- *Base:* con `i = 1`, `minIndex = 0`, que es trivialmente el mínimo de `arr[0..0]`.  
- *Paso:* si `arr[i] < arr[minIndex]` se actualiza `minIndex = i`; en caso contrario se conserva. En ambos casos la invariante se mantiene para `arr[0..i]`.

**Monotonicidad**  
No aplica en el sentido de partición del espacio de búsqueda. La función de progreso es el contador `i`, que crece de forma lineal y acotada hasta `n - 1`.

---

### 3. Solución STL — `sort` + acceso directo

**Justificación de determinismo y factibilidad**  
`std::sort` es un algoritmo determinista. Para la misma entrada siempre produce el mismo arreglo ordenado, y el mínimo queda ubicado en la posición 0, accesible directamente.

**Argumento de finitud**  
`std::sort` tiene complejidad garantizada de `O(n log n)` en el peor caso. Al ser un algoritmo estándar con terminación formalmente probada, la función concluye en un número finito de operaciones proporcional a `n log n`.

**Argumento de correctitud**  
Por definición de ordenamiento ascendente, al aplicar `std::sort` el elemento en la posición 0 es el mínimo global del arreglo. El acceso `arr[0]` retorna ese valor de forma directa y correcta.

**Invariante**  
No aplica a nivel de uso externo del STL. Las invariantes de partición son internas al algoritmo subyacente (introsort) y quedan encapsuladas en la librería estándar.

**Monotonicidad**  
No aplica a nivel de esta solución. La monotonicidad es interna al algoritmo de ordenamiento subyacente.



# Complejidad Temporal

## 1. Búsqueda binaria — `encontrarMin` → O(log n)

En cada iteración del while, el rango de búsqueda `[low, high]` se reduce a la mitad. Si el arreglo tiene n elementos, después de k iteraciones el rango tiene tamaño n / 2^k. El algoritmo termina cuando el rango tiene tamaño 1, es decir cuando:

$$\frac{n}{2^k} = 1 \implies k = \log_2 n$$

Por lo tanto el algoritmo realiza a lo sumo ⌈log₂ n⌉ iteraciones.

### Análisis por caso

| Caso | Situación | Complejidad |
|------|-----------|-------------|
| Mejor caso | El mínimo se encuentra en la primera comparación (arreglo de 1 elemento) | Ω(1) |
| Peor caso | El arreglo tiene n elementos y se divide log₂ n veces hasta llegar al mínimo | O(log n) |
| Caso promedio | En promedio también se divide el rango logarítmicamente | Θ(log n) |

### Notación asintótica

$$T(n) = O(\log n)$$

Cada iteración realiza una cantidad constante de operaciones (calcular `medio`, una comparación, mover `low` o `high`). El costo por iteración es O(1), y hay O(log n) iteraciones, entonces:

$$T(n) = O(1) \cdot O(\log n) = O(\log n)$$

### Complejidad espacial

No usa estructuras adicionales. Solo tres variables enteras (`low`, `high`, `medio`).

$$S(n) = O(1)$$

---

## 2. Búsqueda lineal — `encontrarMinIngenua` → O(n)

El algoritmo recorre el arreglo completo de izquierda a derecha una sola vez, comparando cada elemento con el mínimo actual. Para un arreglo de n elementos, realiza exactamente n − 1 comparaciones sin importar la entrada.

### Análisis por caso

| Caso | Situación | Complejidad |
|------|-----------|-------------|
| Mejor caso | El mínimo está en el índice 0, pero igual recorre todo el arreglo | Ω(n) |
| Peor caso | Mismo recorrido completo | O(n) |
| Caso promedio | Siempre recorre los n elementos | Θ(n) |

A diferencia de búsqueda lineal en arreglos no ordenados, aquí **no hay terminación temprana**: el algoritmo siempre recorre todo el arreglo porque no sabe de antemano dónde está el mínimo.

### Notación asintótica

$$T(n) = \Theta(n)$$

La notación Θ (y no solo O) se justifica porque el número de operaciones es exactamente n − 1 en todos los casos, no solo en el peor.

### Complejidad espacial

Solo usa una variable entera `minIndex`.

$$S(n) = O(1)$$

---

## 3. Solución con STL sort — `encontrarMinSort` → O(n log n)

Esta solución ordena el arreglo completo con `std::sort` y luego toma el primer elemento. `std::sort` en C++ usa una variante de introsort (combinación de quicksort, heapsort e insertion sort), cuya complejidad es O(n log n) en todos los casos.

### Análisis por caso

| Caso | Situación | Complejidad |
|------|-----------|-------------|
| Mejor caso | std::sort con introsort garantiza O(n log n) incluso en el mejor caso | Ω(n log n) |
| Peor caso | Mismo costo garantizado por introsort | O(n log n) |
| Caso promedio | Θ(n log n) |

### Notación asintótica

$$T(n) = \Theta(n \log n)$$

### Observación importante

Esta solución hace **trabajo innecesario**: reorganiza completamente el arreglo cuando el problema solo requiere encontrar un elemento. Paga un costo O(n log n) para obtener información que puede conseguirse en O(log n).

### Complejidad espacial

`std::sort` usa O(log n) de espacio en la pila por las llamadas recursivas internas.

$$S(n) = O(\log n)$$

---

## Comparación resumida

| Función | Mejor caso | Peor caso | Caso promedio | Espacio |
|---------|-----------|-----------|---------------|---------|
| `encontrarMin` (binaria) | Ω(1) | O(log n) | Θ(log n) | O(1) |
| `encontrarMinIngenua` (lineal) | Ω(n) | O(n) | Θ(n) | O(1) |
| `encontrarMinSort` (STL sort) | Ω(n log n) | O(n log n) | Θ(n log n) | O(log n) |

## Jerarquía de crecimiento

Ubicando las tres soluciones en la jerarquía del curso:

$$O(1) \subset O(\log n) \subset O(n) \subset O(n \log n) \subset O(n^2) \subset O(2^n)$$

La búsqueda binaria se ubica en **O(log n)**, el segundo nivel más eficiente posible. La búsqueda lineal en **O(n)** y la solución con sort en **O(n log n)**. La diferencia se vuelve dramática conforme n crece: para n = 1,000,000, log₂(n) ≈ 20 operaciones versus 1,000,000 operaciones de la búsqueda lineal.



---



### Tabla comparativa

| Solución | Complejidad temporal | Complejidad espacial | Observación |
|----------|---------------------|---------------------|-------------|
| Búsqueda lineal | Θ(n) | O(1) | No aprovecha la estructura del arreglo |
| STL sort | Θ(n log n) | O(log n) | Hace trabajo innecesario |
| Búsqueda binaria | O(log n) | O(1) | Aprovecha el orden parcial del arreglo rotado |

---

## Discusión de robustez, degeneración y reutilización

### Robustez

La solución maneja correctamente los siguientes casos borde:

**Arreglo de un solo elemento**: cuando `n = 1`, el while no se ejecuta porque `low == high` desde el inicio. Se retorna `low = 0` directamente, que es el único índice válido.

**Arreglo sin rotación**: cuando el arreglo está en su orden original como `{1, 2, 3, 4, 5}`, `arr[medio]` siempre será menor que `arr[high]`, por lo que `high` se mueve hacia la izquierda hasta converger en el índice 0, que es correcto.

**Arreglo rotado al máximo**: cuando el arreglo tiene una sola rotación como `{2, 3, 4, 5, 1}`, el algoritmo identifica correctamente el punto de quiebre en el último elemento.

**Arreglo de dos elementos**: `{2, 1}` funciona correctamente: `medio = 0`, `arr[0] > arr[1]` es verdadero, entonces `low = 1` y el loop termina con el mínimo en el índice 1.

### Degeneración

El peor comportamiento del algoritmo ocurre cuando el arreglo está completamente ordenado sin rotación. En ese caso el algoritmo ejecuta el máximo de iteraciones posibles, ⌈log₂ n⌉, porque `high` se mueve de a un paso en cada iteración. Sin embargo esto sigue siendo O(log n), no hay degeneración real que cambie la clase de complejidad.

Un riesgo a considerar: si se pasa `n = 0` (arreglo vacío), el algoritmo inicializa `high = -1`, lo que produce comportamiento indefinido. La solución actual asume que la entrada siempre tiene al menos un elemento, que es la garantía del problema de LeetCode.

### Reutilización

El código está organizado en tres capas separadas que permiten reutilización independiente:

`solution.hpp` declara la interfaz pública de las funciones. Cualquier archivo que incluya este header puede usar `encontrarMin` sin conocer su implementación.

`solution.cpp` contiene únicamente la implementación. Si se quisiera cambiar el algoritmo internamente, ningún otro archivo necesitaría modificarse.

`main.cpp`, `tests/test.cpp` y `bench/benchmark.cpp` consumen las funciones a través del header, sin duplicar código. La función `encontrarMin` se escribe una sola vez y se usa en tres contextos distintos.

---

## Instrucciones para compilar

### Requisitos previos

- g++ con soporte C++17
- CMake 3.20 o superior
- Sistema Linux o WSL

### Compilación con CMake (recomendado)

Desde la raíz del proyecto:

```bash
# Configura el proyecto y genera los archivos de compilación
cmake -B build

# Compila todos los ejecutables
cmake --build build
```

Esto genera tres ejecutables dentro de `build/`:
- `build/programa` — ejecutable principal
- `build/ejecutable_tests` — suite de pruebas
- `build/benchmark` — experimento de rendimiento

### Builds alternativos con flags específicos

Para el build de depuración:

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic src/main.cpp src/solution.cpp -o build/prog_O0
```

Para el build release optimizado:

```bash
g++ -std=c++17 -O2 -DNDEBUG src/main.cpp src/solution.cpp -o build/prog_O2
```

Para el build con sanitizers:

```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined src/main.cpp src/solution.cpp -o build/prog_san
```

Para el build con profiling:

```bash
g++ -std=c++17 -O2 -pg src/main.cpp src/solution.cpp -o build/prog_prof
```

---

## Instrucciones para ejecutar

### Ejecutable principal

```bash
./build/programa
```

Salida esperada:

```
El mínimo es: 10
Rotaciones: 4
Arreglo original: [10, 11, 12, 13, 14, 15]
```

### Correr los tests

Con CTest (recomendado):

```bash
ctest --test-dir build
```

Directamente:

```bash
./build/ejecutable_tests
```

Salida esperada si todos los casos pasan:

```
Caso normal pasó
Caso pequeño pasó
Caso borde 1 pasó
Caso borde 2 pasó
Caso propuesto pasó
Todos los test pasaron
```

### Correr el benchmark

```bash
./build/benchmark
```

Salida esperada:

```
Tamaño      Lineal O(n)       Sort O(nlogn)         Binaria O(logn)
----------------------------------------------------------------------
1000        0.0012            0.0089                0.0001
10000       0.0120            0.1100                0.0001
100000      0.1200            1.3000                0.0001
1000000     1.2000            15.000                0.0002
```

### Correr con sanitizers

```bash
./build/prog_san
```

## Benchmark realizado
 
Se implementó un benchmark en `bench/benchmark.cpp` que compara las tres soluciones (búsqueda lineal, `std::sort` y búsqueda binaria) para tamaños de entrada de 1,000 a 1,000,000 elementos. Cada medición promedia 100 repeticiones usando `std::chrono::high_resolution_clock`. Se usa una variable `volatile` para evitar que el compilador elimine la llamada al algoritmo por optimización. Los arreglos de prueba se generan con `generarRotado(n, n/3)`, que crea un arreglo rotado de tamaño n.
 
---
 
## Tabla resumida de builds y resultados
 
Se compiló el benchmark con seis configuraciones distintas de `g++ -std=c++17`. Los tiempos corresponden al promedio de 3 corridas para n = 1,000,000.
 
| Build | Flags | Lineal (ms) | Sort (ms) | Binaria (ms) | Tamaño ejecutable |
|-------|-------|------------|-----------|-------------|-------------------|
| Debug | `-O0 -g -Wall -Wextra -Wpedantic` | 2.005 | 212.92 | 0.0001 | 187 KB |
| Depurable optimizado | `-Og -g -Wall -Wextra -Wpedantic` | 0.564 | 10.49 | 0.0000 | 191 KB |
| Optimización básica | `-O1` | 2.125 | 9.17 | 0.0000 | 18 KB |
| Release | `-O2 -DNDEBUG` | 2.093 | 9.44 | 0.0000 | 18 KB |
| Optimización agresiva | `-O3` | 0.649 | 8.86 | 0.0001 | 18 KB |
| Compacto | `-Os` | 2.167 | 11.34 | 0.0001 | 18 KB |
 
El cambio más notable es el de `-O0` a cualquier nivel de optimización en `std::sort`: pasa de ~213 ms a ~9 ms (~24× más rápido). Los builds con `-g` (símbolos de depuración) son ~170 KB más grandes que los optimizados sin él.
 
---
 
## Observaciones de sanitizers
 
Se compiló y ejecutó la solución con AddressSanitizer y UndefinedBehaviorSanitizer:
 
```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined src/main.cpp src/solution.cpp src/utils.cpp -o build/prog_san
./build/prog_san
```
 
**Resultado:** ejecución limpia, sin errores detectados. ASan no reportó accesos fuera de límites, uso de memoria liberada ni leaks. UBSan no reportó desbordamientos de enteros, divisiones por cero ni comportamiento indefinido.
 
En un programa mal escrito, esta configuración habría detectado errores como: acceso fuera de los límites del arreglo (buffer overflow), uso de variables no inicializadas, desbordamiento de enteros con signo y acceso a memoria ya liberada (use-after-free).
 
---
 
## Resumen de cobertura
 
Se midió la cobertura con `gcov` compilando con `--coverage -O0`.
 
| Archivo | Líneas ejecutables | Líneas cubiertas | Cobertura |
|---------|-------------------|-----------------|-----------|
| `solution.cpp` | 14 | 8 | 57.14% |
| `utils.cpp` | 8 | 0 | 0.00% |
 
La función principal `encontrarMin` tiene **100% de cobertura de líneas y 100% de cobertura de condiciones**: ambas ramas del `if (arr[medio] > arr[high])` fueron ejercitadas (4 veces true, 5 veces false) y el `while` se ejecutó tanto en su rama verdadera (9 iteraciones) como falsa (5 salidas). Las funciones no cubiertas (`encontrarMinIngenua`, `generarRotado`, `encontrarMinSort`) son utilitarias del benchmark y no forman parte de la solución entregada.
 
---
 
## Resumen de profiling
 
Se perfiló el benchmark con `gprof` compilando con `-O2 -pg`.
 
| Función | % del tiempo | Segundos | Llamadas |
|---------|-------------|----------|----------|
| `encontrarMinIngenua` | 89.57% | 1.03 s | 1,200 |
| `encontrarMinSort` | 10.43% | 0.12 s | 400 |
| `encontrarMin` | 0.00% | 0.00 s | 400 |
| `generarRotado` | 0.00% | 0.00 s | 4 |
 
El resultado coincide con el análisis teórico: la búsqueda lineal O(n) domina el tiempo de ejecución, el sort O(n log n) es significativo, y la búsqueda binaria O(log n) es tan rápida que gprof no puede medir su contribución. Al perfilar el programa principal (que solo usa `encontrarMin` con un arreglo de 6 elementos), gprof reportó "no time accumulated", confirmando la eficiencia de O(log n).
 
---
 
## Microoptimización vs algoritmo
 
Para n = 1,000,000, comparando las dos estrategias de mejora:
 
| Estrategia | Cambio | Speedup | Complejidad |
|-----------|--------|---------|-------------|
| Mejor bandera de compilación | Lineal `-O0` → Lineal `-O3` | ~3.1× | Sigue en O(n) |
| Mejor algoritmo | Lineal `-O0` → Binaria `-O0` | ~20,000× | O(n) → O(log n) |
 
La elección del algoritmo correcto (búsqueda binaria vs lineal) tiene un impacto de **cuatro órdenes de magnitud** más que la mejor optimización del compilador. Cambiar de `-O0` a `-O3` mejora ~3×; cambiar de búsqueda lineal a búsqueda binaria mejora ~20,000×. Esta diferencia solo se amplifica conforme n crece.
 
---

