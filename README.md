# Complejidad Temporal

## Tamaño de entrada relevante

Para las tres funciones, el tamaño de entrada relevante es **n**, donde n es el número de elementos del arreglo. Todas las funciones reciben un arreglo de n enteros y devuelven el mínimo.

---

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


# Find Minimum in Rotated Sorted Array

> **Problema:** LeetCode 153 — [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

---

## Alternativa ingenua o menos eficiente

Se implementaron y compararon tres soluciones para encontrar el mínimo en un arreglo rotado:

### Solución 1 — Búsqueda lineal `encontrarMinIngenua` — O(n)

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

### Solución 2 — STL sort `encontrarMinSort` — O(n log n)

Ordena el arreglo completo con `std::sort` y devuelve el primer elemento. Es la solución más ineficiente de las tres porque paga el costo completo de un ordenamiento cuando el problema solo requiere encontrar un elemento.

```cpp
int encontrarMinSort(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr[0];
}
```

Esta solución ilustra el principio central de la práctica: una mejora en la elección del algoritmo tiene más impacto que cualquier microoptimización. El sort hace trabajo completamente innecesario.

### Solución 3 — Búsqueda binaria `encontrarMin` — O(log n) Solución principal

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

Si no aparece ningún mensaje de error de AddressSanitizer o UndefinedBehaviorSanitizer, la ejecución es limpia.
Grupo 10
Angel Jesus Navarro Ruiz
Cristhyan Perez Villegas



