# Reporte de Cobertura — Find Minimum in Rotated Sorted Array

## 1. Configuración

Se utilizó `gcov` (parte del toolchain de GCC) para medir la cobertura de líneas y condiciones sobre el conjunto de pruebas. La compilación se realizó con `--coverage -O0` para instrumentar el código sin optimizaciones que pudieran alterar la estructura del flujo.

```bash
# Compilación con cobertura
g++ -std=c++17 --coverage -O0 test/test.cpp src/solution.cpp src/utils.cpp -o test_cov

# Ejecución de los tests
./test_cov

# Generación del reporte
gcov test_cov-solution.gcno test_cov-utils.gcno
```

---

## 2. Resultados de cobertura de líneas

### `solution.cpp` — 57.14% (8 de 14 líneas ejecutadas)

```
        5:    3:int encontrarMin(int arr[], int n) {
        5:    4:    int low = 0, high = n - 1;
       14:    5:    while (low < high) {
        9:    6:        int medio = (low + high) / 2;
        9:    7:        if (arr[medio] > arr[high])
        4:    8:            low = medio + 1;
        5:   10:            high = medio;
        5:   12:    return low;

    #####:   15:int encontrarMinIngenua(int arr[], int n) {
    #####:   16:    int minIndex = 0;
    #####:   17:    for (int i = 1; i < n; i++) {
    #####:   18:        if (arr[i] < arr[minIndex]) {
    #####:   19:            minIndex = i;
    #####:   22:    return minIndex;
```

### `utils.cpp` — 0.00% (0 de 8 líneas ejecutadas)

```
    #####:    4:vector<int> generarRotado(int n, int rotacion) {
    #####:    5:    vector<int> arr(n);
    #####:    6:    for (int i = 0; i < n; i++)
    #####:    7:        arr[i] = (rotacion + i) % n;
    #####:    8:    return arr;

    #####:   11:int encontrarMinSort(vector<int> arr) {
    #####:   12:    sort(arr.begin(), arr.end());
    #####:   13:    return arr[0];
```

### Resumen

| Archivo | Líneas ejecutables | Líneas cubiertas | Cobertura |
|---------|-------------------|-----------------|-----------|
| `solution.cpp` | 14 | 8 | 57.14% |
| `utils.cpp` | 8 | 0 | 0.00% |
| **Total del proyecto** | **22** | **8** | **36.36%** |

---

## 3. Cobertura de condiciones sobre `encontrarMin`

La función `encontrarMin` es la función crítica del proyecto. Analizamos las dos condiciones que controlan su flujo:

### Condición 1: `while (low < high)` (línea 5)

Esta condición se evaluó 14 veces en total a lo largo de los 5 tests:

- **Verdadera (continuar loop):** 9 veces → el algoritmo ejecutó 9 iteraciones en total entre los 5 casos de prueba.
- **Falsa (salir del loop):** 5 veces → una vez por cada test, cuando `low == high` y el mínimo fue encontrado.

Ambas ramas cubiertas.

### Condición 2: `if (arr[medio] > arr[high])` (línea 7)

Esta condición se evaluó 9 veces (una por iteración del while):

- **Verdadera (`low = medio + 1`):** 4 veces → el mínimo estaba en la mitad derecha.
- **Falsa (`high = medio`):** 5 veces → el mínimo estaba en la mitad izquierda o en `medio`.

Ambas ramas cubiertas. Los tests ejercitan tanto el caso donde el punto de rotación está a la derecha del medio como donde está a la izquierda.

### Resumen de condiciones

| Condición | Rama true | Rama false | Cobertura |
|-----------|-----------|------------|-----------|
| `low < high` | 9 ejecuciones | 5 ejecuciones | 100% |
| `arr[medio] > arr[high]` | 4 ejecuciones | 5 ejecuciones | 100% |

La función `encontrarMin` tiene **100% de cobertura de líneas** y **100% de cobertura de condiciones**.

---

## 4. Análisis: ¿qué faltó cubrir?

### `encontrarMinIngenua` — sin cobertura

La función de búsqueda lineal no es llamada por ningún test. Los tests solo validan la solución principal (`encontrarMin`). Esto es una decisión de diseño razonable: los tests verifican la correctitud de la solución que se entrega, no de las alternativas usadas solo para comparación en el benchmark. Sin embargo, si se quisiera cobertura completa, bastaría con agregar un test que llame a `encontrarMinIngenua` y verifique que devuelve el mismo resultado que `encontrarMin`.

### `utils.cpp` — sin cobertura

Las funciones `generarRotado` y `encontrarMinSort` son utilitarias del benchmark, no de la solución. No se invocan desde los tests porque su propósito es generar datos de prueba y medir rendimiento, no resolver el problema. La cobertura de 0% es esperada y no representa un riesgo para la correctitud de la solución.

### ¿Qué casos ejercitan los tests?

| Test | Entrada | Qué ejercita |
|------|---------|-------------|
| Caso normal | `{3, 4, 5, 1, 2}` | Rotación en el medio del arreglo |
| Caso pequeño | `{2, 1}` | Arreglo mínimo con rotación |
| Caso borde 1 | `{1}` | Un solo elemento, `while` no se ejecuta |
| Caso borde 2 | `{1, 2, 3, 4, 5}` | Sin rotación, arreglo ya ordenado |
| Caso propuesto | `{22, 23, 24, 25, 20, 21}` | Rotación cerca del final, valores no consecutivos desde 0 |

Los 5 tests cubren los casos más importantes: arreglo normal rotado, arreglo mínimo, un solo elemento, sin rotación, y un caso con valores arbitrarios. Esto es suficiente para ejercitar todas las ramas de `encontrarMin`.

---

## 5. Conclusión

La función principal `encontrarMin` alcanza **100% de cobertura de líneas y 100% de cobertura de condiciones**, lo cual confirma que el conjunto de tests ejercita todas las ramas del algoritmo de búsqueda binaria. Las funciones no cubiertas (`encontrarMinIngenua`, `generarRotado`, `encontrarMinSort`) son utilitarias del benchmark y no forman parte de la solución entregada, por lo que su falta de cobertura no afecta la validación de correctitud.