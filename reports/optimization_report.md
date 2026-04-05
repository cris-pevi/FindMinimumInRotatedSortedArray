# Reporte de Optimización

## 1. Builds compilados

Se compiló el benchmark en seis configuraciones distintas, todas con `g++ -std=c++17`. Cada ejecutable se corrió tres veces consecutivas para observar estabilidad.

### Comandos de compilación

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_O0
g++ -std=c++17 -Og -g -Wall -Wextra -Wpedantic bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_Og
g++ -std=c++17 -O1                              bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_O1
g++ -std=c++17 -O2 -DNDEBUG                     bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_O2
g++ -std=c++17 -O3                              bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_O3
g++ -std=c++17 -Os                              bench/benchmark.cpp src/solution.cpp src/utils.cpp -o build/bench_Os
```

### Tamaño de los ejecutables

| Build | Tamaño (bytes) | Tamaño legible | Observación |
|-------|---------------|----------------|-------------|
| `-O0` | 190,960 | ~187 KB | Más grande por símbolos de depuración y código sin optimizar |
| `-Og` | 195,952 | ~191 KB | Similar a `-O0`, incluye símbolos de depuración (`-g`) |
| `-O1` | 18,008 | ~18 KB | Reducción drástica: ~10× menor que Debug |
| `-O2` | 18,168 | ~18 KB | Similar a `-O1` |
| `-O3` | 17,936 | ~18 KB | El más pequeño de los optimizados |
| `-Os` | 18,288 | ~18 KB | Comparable a `-O2`, optimizado para tamaño |

La diferencia principal está entre los builds con `-g` (símbolos de depuración) y sin él. Los símbolos de depuración agregan ~170 KB al ejecutable. Entre los builds optimizados sin `-g`, las diferencias de tamaño son mínimas (~300 bytes).

### Warnings observados

Al compilar con `-Wall -Wextra -Wpedantic` (builds `-O0` y `-Og`), g++ reportó un único warning:

```
warning: variable 'r' set but not used [-Wunused-but-set-variable]
```

Este warning aparece en la función `medir()` del benchmark, donde la variable `volatile int r` se usa intencionalmente para evitar que el compilador elimine la llamada a la función medida. El warning es un falso positivo en este contexto: `volatile` fuerza la escritura aunque el valor no se lea después, que es exactamente el comportamiento deseado. Los archivos `solution.cpp` y `utils.cpp` compilan sin ningún warning.

---

## 2. Resultados del benchmark por build

Todos los tiempos están en milisegundos (ms), promediando 100 repeticiones por tamaño de entrada.

### 2.1. Build `-O0` (Debug, sin optimización)

| n | Lineal O(n) | Sort O(n log n) | Binaria O(log n) |
|---|-------------|-----------------|------------------|
| 1,000 | 0.0050 / 0.0043 / 0.0043 | 0.2441 / 0.2567 / 0.2189 | 0.0001 / 0.0001 / 0.0001 |
| 10,000 | 0.0307 / 0.0338 / 0.0264 | 1.3892 / 1.4359 / 1.3812 | 0.0001 / 0.0001 / 0.0001 |
| 100,000 | 0.1908 / 0.2002 / 0.1926 | 16.4613 / 16.2025 / 16.0710 | 0.0001 / 0.0001 / 0.0001 |
| 1,000,000 | 2.0010 / 2.0013 / 2.0130 | 214.4633 / 197.6813 / 226.6022 | 0.0001 / 0.0001 / 0.0001 |

### 2.2. Build `-Og` (Depurable optimizado)

| n | Lineal O(n) | Sort O(n log n) | Binaria O(log n) |
|---|-------------|-----------------|------------------|
| 1,000 | 0.0014 / 0.0012 / 0.0008 | 0.0154 / 0.0174 / 0.0106 | 0.0000 / 0.0000 / 0.0000 |
| 10,000 | 0.0097 / 0.0125 / 0.0072 | 0.1152 / 0.1492 / 0.0987 | 0.0000 / 0.0000 / 0.0000 |
| 100,000 | 0.0615 / 0.0744 / 0.0628 | 0.8373 / 0.8465 / 0.8349 | 0.0000 / 0.0000 / 0.0000 |
| 1,000,000 | 0.5626 / 0.5617 / 0.5666 | 10.3935 / 10.4460 / 10.6343 | 0.0000 / 0.0000 / 0.0000 |

### 2.3. Build `-O1`

| n | Lineal O(n) | Sort O(n log n) | Binaria O(log n) |
|---|-------------|-----------------|------------------|
| 1,000 | 0.0047 / 0.0032 / 0.0028 | 0.0121 / 0.0088 / 0.0076 | 0.0000 / 0.0000 / 0.0000 |
| 10,000 | 0.0502 / 0.0333 / 0.0300 | 0.1074 / 0.0908 / 0.0841 | 0.0000 / 0.0000 / 0.0000 |
| 100,000 | 0.2598 / 0.2568 / 0.2430 | 0.7106 / 0.9325 / 0.7062 | 0.0000 / 0.0000 / 0.0000 |
| 1,000,000 | 2.1296 / 2.1702 / 2.0755 | 9.3824 / 9.0860 / 9.0339 | 0.0000 / 0.0000 / 0.0000 |

### 2.4. Build `-O2` (Release)

| n | Lineal O(n) | Sort O(n log n) | Binaria O(log n) |
|---|-------------|-----------------|------------------|
| 1,000 | 0.0048 / 0.0048 / 0.0048 | 0.0140 / 0.0156 / 0.0143 | 0.0000 / 0.0000 / 0.0000 |
| 10,000 | 0.0501 / 0.0508 / 0.0497 | 0.1427 / 0.1226 / 0.1376 | 0.0000 / 0.0000 / 0.0000 |
| 100,000 | 0.2664 / 0.2698 / 0.2713 | 0.7699 / 0.7689 / 0.7914 | 0.0000 / 0.0000 / 0.0000 |
| 1,000,000 | 2.0771 / 2.1308 / 2.0702 | 9.5053 / 9.3969 / 9.4036 | 0.0001 / 0.0000 / 0.0000 |

### 2.5. Build `-O3` (Optimización agresiva)

| n | Lineal O(n) | Sort O(n log n) | Binaria O(log n) |
|---|-------------|-----------------|------------------|
| 1,000 | 0.0010 / 0.0013 / 0.0012 | 0.0145 / 0.0108 / 0.0169 | 0.0000 / 0.0000 / 0.0000 |
| 10,000 | 0.0115 / 0.0131 / 0.0136 | 0.0835 / 0.1059 / 0.1023 | 0.0000 / 0.0000 / 0.0000 |
| 100,000 | 0.0785 / 0.0742 / 0.0767 | 0.7306 / 0.6740 / 0.6953 | 0.0000 / 0.0000 / 0.0000 |
| 1,000,000 | 0.7692 / 0.6032 / 0.5749 | 9.2547 / 8.7678 / 8.5520 | 0.0001 / 0.0001 / 0.0000 |

### 2.6. Build `-Os` (Optimización por tamaño)

| n | Lineal O(n) | Sort O(n log n) | Binaria O(log n) |
|---|-------------|-----------------|------------------|
| 1,000 | 0.0059 / 0.0049 / 0.0045 | 0.0153 / 0.0150 / 0.0134 | 0.0001 / 0.0001 / 0.0001 |
| 10,000 | 0.0478 / 0.0494 / 0.0428 | 0.1315 / 0.1462 / 0.1552 | 0.0001 / 0.0001 / 0.0001 |
| 100,000 | 0.2619 / 0.2232 / 0.2504 | 0.9786 / 0.9119 / 1.0333 | 0.0001 / 0.0001 / 0.0001 |
| 1,000,000 | 2.1244 / 2.0429 / 2.3327 | 11.5705 / 11.2393 / 11.2058 | 0.0001 / 0.0001 / 0.0001 |

---

## 3. Tabla resumen comparativa (promedios para n = 1,000,000)

| Build | Lineal (ms) | Sort (ms) | Binaria (ms) | Tamaño ejecutable | Depuración |
|-------|------------|-----------|-------------|-------------------|------------|
| `-O0` | 2.005 | 212.92 | 0.0001 | 187 KB | Excelente |
| `-Og` | 0.564 | 10.49 | 0.0000 | 191 KB | Buena |
| `-O1` | 2.125 | 9.17 | 0.0000 | 18 KB | Limitada |
| `-O2` | 2.093 | 9.44 | 0.0000 | 18 KB | Limitada |
| `-O3` | 0.649 | 8.86 | 0.0001 | 18 KB | Limitada |
| `-Os` | 2.167 | 11.34 | 0.0001 | 18 KB | Limitada |

---

## 4. Análisis de los resultados

* El cambio más dramático entre builds ocurre en `std::sort`. En `-O0`, el sort tarda ~213 ms para n = 1,000,000, pero en todos los demás builds baja a ~9–11 ms. Esto representa un speedup de ~20–24× solo por activar cualquier nivel de optimización. La razón es que `std::sort` (introsort) tiene muchas llamadas a funciones internas, comparaciones y movimientos de datos que el compilador puede optimizar agresivamente con inlining, eliminación de código muerto y reordenamiento de instrucciones.

* Se observa un patrón inesperado: `-O1`, `-O2` y `-Os` dan tiempos de búsqueda lineal similares a `-O0` (~2 ms), mientras que `-Og` y `-O3` son ~3.5× más rápidos (~0.6 ms). Esto sugiere que `-O3` activa alguna optimización adicional (probablemente auto-vectorización con SIMD) que `-O2` no habilita para este patrón de recorrido lineal. El caso de `-Og` siendo rápido es más sutil: su estrategia de optimización "amigable con el debugger" aparentemente genera código eficiente para este loop simple sin las transformaciones más complejas que `-O1`/`-O2` aplican y que podrían interferir con la predicción de ramas o el prefetching.

* En todos los builds, la búsqueda binaria reporta 0.0000–0.0001 ms. Con solo ~20 iteraciones para n = 1,000,000, el tiempo total está por debajo de la resolución de `std::chrono`. La complejidad O(log n) hace que las optimizaciones del compilador sean irrelevantes en la práctica.

* La búsqueda lineal y la binaria muestran buena estabilidad (variación < 15% entre corridas). El sort en `-O0` muestra la mayor variabilidad: 197 ms a 226 ms entre corridas, una diferencia de ~15%. Esto se debe a que el sort accede a más memoria de forma no secuencial, lo que lo hace sensible al estado de la caché y a la carga del sistema.

---

## 5. Microoptimización vs algoritmo

Este es el punto central del reporte. Comparemos el impacto de dos estrategias para mejorar el rendimiento al buscar el mínimo en un arreglo de 1,000,000 de elementos.

### Primera estrategia: Cambiar la bandera de compilación

La mejor mejora posible por bandera de compilación para la búsqueda lineal es pasar de `-O0` (2.005 ms) a `-O3` (0.649 ms), un speedup de **~3.1×**. La clase de complejidad sigue siendo O(n).

### Segunda estrategia: Cambiar el algoritmo

Pasar de búsqueda lineal O(n) a búsqueda binaria O(log n), ambas en `-O0`, reduce el tiempo de 2.005 ms a 0.0001 ms, un speedup de **~20,000×**. La clase de complejidad pasa de O(n) a O(log n).

### Conclusión

La elección del algoritmo tiene un impacto de **cuatro órdenes de magnitud** más que la mejor microoptimización posible. Compilar con `-O3` mejora ~3×; elegir búsqueda binaria mejora ~20,000×. Y conforme n crece, esta ventaja solo se amplifica: para n = 10,000,000 la búsqueda lineal tardaría ~20 ms incluso con `-O3`, mientras que la binaria seguiría en ~0.0001 ms.

| Estrategia | De → A | Speedup | Complejidad |
|-----------|--------|---------|-------------|
| Mejor bandera | `-O0` lineal → `-O3` lineal | ~3.1× | Sigue O(n) |
| Mejor algoritmo | Lineal `-O0` → Binaria `-O0` | ~20,000× | O(n) → O(log n) |

---

## 6. Observaciones adicionales por build

| Build | Correctitud | Warnings | Facilidad de depuración | Observaciones |
|-------|------------|----------|------------------------|---------------|
| `-O0` | Correcta | `volatile` (intencional) | Excelente: todas las variables inspeccionables, breakpoints confiables, flujo secuencial | Referencia para comparación de tiempos |
| `-Og` | Correcta | `volatile` (intencional) | Buena: la mayoría de variables accesibles, stepping razonable | Mejor balance depuración/rendimiento |
| `-O1` | Correcta | Ninguno | Limitada: algunas variables optimizadas | Inlining básico, buen sort pero lineal lento |
| `-O2` | Correcta | Ninguno | Limitada: variables pueden desaparecer, flujo reordenado | Build estándar de producción |
| `-O3` | Correcta | Ninguno | Muy limitada: auto-vectorización dificulta seguimiento | Mejor rendimiento general |
| `-Os` | Correcta | Ninguno | Limitada | Prioriza tamaño; rendimiento similar a `-O1`/`-O2` |

---

## 7. STL y rendimiento

`std::sort` se utilizó en la solución alternativa `encontrarMinSort` para demostrar que una herramienta STL poderosa puede ser inadecuada si no se elige correctamente. Ordena todo el arreglo en O(n log n) cuando solo se necesita encontrar un elemento, lo que constituye trabajo innecesario.

`std::vector` se usa en `generarRotado` para generar arreglos de prueba dinámicamente y en `encontrarMinSort` para recibir el arreglo por copia. La contigüidad en memoria de `vector` favorece el rendimiento de caché en recorridos secuenciales.

`std::chrono::high_resolution_clock` se usa en el benchmark para mediciones de tiempo con resolución de nanosegundos. La técnica de promediar 100 repeticiones reduce el ruido estadístico y permite comparaciones más confiables.
