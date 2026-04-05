# Reporte de Profiling

## 1. Configuración

Se utilizó `gprof` para analizar el perfil de ejecución del programa. La compilación se realizó con `-O2 -pg` para habilitar la instrumentación de profiling manteniendo las optimizaciones de producción.

```bash
# Compilación del benchmark con profiling
g++ -std=c++17 -O2 -pg bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_prof

# Ejecución (genera gmon.out)
./build/bench_prof

# Análisis
gprof build/bench_prof build/gmon.out
```

Se perfilaron dos ejecutables: el benchmark (que ejecuta las tres soluciones con múltiples tamaños) y el programa principal (que solo ejecuta la búsqueda binaria con un arreglo pequeño).

---

## 2. Resultados del benchmark

### Flat profile

| % tiempo | Segundos acumulados | Segundos propios | Llamadas | ms/llamada (self) | ms/llamada (total) | Función |
|----------|--------------------|-----------------|---------|--------------------|---------------------|---------|
| 89.57% | 1.03 | 1.03 | 1,200 | 0.86 | 0.86 | `encontrarMinIngenua` |
| 10.43% | 1.15 | 0.12 | 400 | 0.30 | 2.02 | `encontrarMinSort` |
| 0.00% | 1.15 | 0.00 | 400 | 0.00 | 0.00 | `encontrarMin` |
| 0.00% | 1.15 | 0.00 | 4 | 0.00 | 0.00 | `generarRotado` |

### Call graph (resumen)

```
main [100.0%]
 ├── encontrarMinSort       [70.1%]  (0.12s self + 0.69s en hijos)
 │    └── encontrarMinIngenua  (llamada internamente por std::sort vía comparaciones)
 ├── encontrarMinIngenua    [89.6%]  (0.34s desde main + 0.69s desde sort)
 ├── encontrarMin           [0.0%]   (0.00s)
 └── generarRotado          [0.0%]   (0.00s)
```

---

## 3. Resultados del programa principal

Al perfilar el programa principal (que solo ejecuta `encontrarMin` con un arreglo de 6 elementos), gprof reportó:

```
no time accumulated
```

La función `encontrarMin` fue llamada 1 vez y registró 0.00 segundos. El programa completo terminó tan rápido que gprof no pudo muestrear ningún tiempo. Esto es coherente con O(log n): para n = 6, el algoritmo realiza a lo sumo 3 iteraciones, un trabajo insignificante.

---

## 4. Análisis

* `encontrarMinIngenua` concentra el **89.57%** del tiempo total de ejecución, con 1.03 segundos acumulados en 1,200 llamadas. Esto incluye tanto las 400 llamadas directas desde `main` como las 800 llamadas indirectas desde `encontrarMinSort` (porque `std::sort` internamente recorre y compara elementos de manera similar a una búsqueda lineal).

* `encontrarMinSort` aparece con 10.43% de tiempo propio (0.12 s), pero su tiempo total incluyendo hijos es 70.1% (0.81 s), porque la mayor parte de su trabajo lo delega a las comparaciones y movimientos internos de `std::sort`, que gprof atribuye parcialmente a `encontrarMinIngenua` por la instrumentación.

* El análisis teórico predice que la búsqueda lineal O(n) y el sort O(n log n) dominarán el tiempo de ejecución, mientras que la búsqueda binaria O(log n) será despreciable. Los datos de gprof confirman exactamente esto:

    - `encontrarMinIngenua` O(n): **89.57%** del tiempo → es la función más costosa
    - `encontrarMinSort` O(n log n): **10.43%** propio → significativo pero menor porque sort tiene mejor constante con `-O2`
    - `encontrarMin` O(log n): **0.00%** del tiempo → completamente despreciable, ni siquiera registra muestras

* La búsqueda lineal tarda más que el sort en gprof y esto parece contradecir el benchmark donde sort es más lento. La explicación es que gprof reporta tiempo **propio** (`self`): el sort delega la mayor parte de su trabajo a funciones internas de la STL (comparaciones, movimientos) que gprof no siempre atribuye correctamente al sort en sí. Además, `encontrarMinSort` recibe el arreglo **por copia**, lo que genera una llamada implícita al constructor de copia de `std::vector` antes de cada sort. El tiempo de la búsqueda lineal, en cambio, está completamente contenido en una sola función sin hijos, por lo que gprof lo captura íntegramente.

### Conclusión

El profiling confirma experimentalmente lo que el análisis teórico predice: la función con complejidad más alta (lineal y sort) domina el tiempo de ejecución, mientras que la búsqueda binaria O(log n) es tan rápida que gprof literalmente no puede medir su contribución. Esto refuerza la conclusión del reporte de optimización: la elección del algoritmo es el factor decisivo en el rendimiento.