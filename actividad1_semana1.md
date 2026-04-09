# Grupo 10

Integrantes:
- Cristhyan Manuel Perez Villegas
- Angel Navarro Ruiz

#### Bloque 1 - Núcleo conceptual de Semana1

Revisen:

* `Semana1/README.md`
* `Semana1/src/bubble_sort.cpp`
* `Semana1/src/power.cpp`
* `Semana1/src/fibonacci.cpp`
* `Semana1/src/count_ones.cpp`
* `Semana1/demos/demo_adt_secuencia.cpp`

Respondan:

1. Expliquen con sus palabras la diferencia entre **problema**, **algoritmo**, **ADT** e **implementación**.

Un problema es lo que se quiere resolver (el objetivo), un algoritmo es el conjunto de pasos lógicos para resolver ese problema, un ADT (tipo de dato abstracto) define cómo se organizan los datos y qué operaciones se pueden hacer sin importar su implementación interna, y la implementación es el código concreto (por ejemplo en C++) que lleva a la práctica ese algoritmo y ese ADT.

2. En `bubble_sort.cpp`, expliquen qué observable conecta correctitud y costo.

El observable que conecta correctitud y costo es el número de inversiones en el arreglo, ya que un arreglo es correcto (está ordenado) cuando no hay inversiones (A[i-1] ≤ A[i]), y el costo del algoritmo depende de cuántas existen, porque cada intercambio elimina al menos una inversión; por eso, mientras más desordenado esté el arreglo, más comparaciones y swaps se requieren.

3. En `power.cpp`, expliquen por qué `power` mejora la idea de una versión ingenua.

Reduce significativamente el numero de multiplicaciones ya que permite buscar la solución utilizando exponiencia binaria, pasando de O(n) a O(log n).

4. En `fibonacci.cpp`, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.

En fibonacci.cpp se ve que una función puede ser correcta y, sin embargo, no ser la mejor opción en la práctica, porque correctitud y eficiencia no es mismo.

Es una función correcta, para una entrada válida, devuelve el resultado esperado según la definición del problema. En este caso, calcular el término n de Fibonacci. Desde el punto de vista conceptual, esta función está bien planteada, porque si se le da un n adecuado, devuelve el Fibonacci correcto.

El problema es que esta versión recursiva hace muchísimo trabajo repetido. Para calcular fib(n), llama a fib(n-1) y fib(n-2), pero dentro de esas llamadas se vuelven a recalcular los mismos valores muchas veces. Por ejemplo, para calcular fib(6):

fib(6) necesita fib(5) y fib(4)
fib(5) necesita fib(4) y fib(3)
fib(4) vuelve a necesitar fib(3) y fib(2)

Entonces, valores como fib(4), fib(3) o fib(2) se calculan repetidamente, aunque ya habían aparecido antes. Es decir, la función es correcta, pero desperdicia tiempo repitiendo subproblemas.

Por eso, su costo temporal crece de manera exponencial, aproximadamente O(2 elevado a la n)
En valores pequeños puede funcionar bien, pero cuando n aumenta, el tiempo de ejecución se dispara y deja de ser razonable. En este caso, la solución puede ser matemáticamente válida, pero computacionalmente ineficiente.

5. En `count_ones.cpp`, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.

En count_ones.cpp, el tamaño de entrada no siempre coincide con el valor numérico porque un número no se mide por cuánto vale en decimal, sino por cuánta información se necesita para representarlo, es decir, por su cantidad de bits. Por ejemplo, 1024 es un número grande, pero en binario se representa como 10000000000, por lo que solo ocupa 11 bits. Esto muestra que un valor numérico alto no necesariamente implica una entrada “grande” en el sentido computacional.

En countOnes1, el número de iteraciones no depende directamente del valor decimal de n, sino de cuántos bits en 1 tiene su representación binaria, ya que en cada paso la operación n &= (n - 1) elimina un bit activado. Por eso, un número grande puede requerir pocas iteraciones si tiene pocos unos. En cambio, countOnes2 trabaja agrupando bits y realiza una cantidad fija de pasos, determinada por el tamaño del tipo unsigned int, no por el valor numérico de n.

En este problema el costo del algoritmo está relacionado con la representación binaria de la entrada y no simplemente con su valor decimal.

6. En `demo_adt_secuencia.cpp`, expliquen por qué la misma interfaz puede convivir con representaciones distintas.

En demo_adt_secuencia.cpp, la misma interfaz puede convivir con representaciones distintas porque el ADT define qué operaciones ofrece una secuencia, pero no obliga a que esas operaciones se implementen de una sola manera. La interfaz "IntSequence" especifica operaciones como size, get, set, add y remove, y cualquier clase que las implemente correctamente puede representar el mismo ADT.

Eso se ve en las clases FixedArraySequence y VectorSequence. Ambas representan una secuencia de enteros y permiten hacer las mismas operaciones desde el punto de vista del usuario, pero internamente usan estructuras diferentes. FixedArraySequence guarda los datos en un arreglo fijo con una capacidad máxima de 16 elementos y controla manualmente el número de elementos. En cambio, VectorSequence usa std::vector<int>, que maneja memoria dinámica y puede crecer automáticamente.

Aunque por dentro son diferentes, para el cliente ambas “se comportan” igual, porque respetan la misma interfaz. La ventaja de esto es que se puede cambiar la implementación interna sin cambiar la forma de usar el ADT. Así, una representación puede ser más simple, otra más flexible o más eficiente en ciertos casos, pero mientras mantengan la misma interfaz y la misma conducta observable, ambas siguen siendo válidas para el mismo tipo abstracto de datos.

#### Bloque 2 - Demos y trazado guiado

Revisen:

* `Semana1/demos/demo_bubblesort.cpp`
* `Semana1/demos/demo_power.cpp`
* `Semana1/demos/demo_fibonacci.cpp`
* `Semana1/demos/demo_countones.cpp`

Construyan una tabla con cuatro columnas:

* archivo,
* salida u observable importante,
* idea algorítmica,
* argumento de costo.

| archivo | salida u observable importante | idea algorítmica | argumento de costo |
|---|---|---|---|
| `demo_bubblesort.cpp` | Muestra el arreglo antes y después, con conteo de comparaciones, intercambios y posición del último swap. | Bubble Sort optimizado: compara vecinos e intercambia si están en desorden, recortando la siguiente pasada al índice del último intercambio. | Peor caso cuadrático, pero la optimización evita revisar el sufijo ya ordenado y puede terminar antes. |
| `demo_power.cpp` | Compara resultados de versiones brutas (`BF`) y optimizadas de potenciación para la misma entrada. | Exponenciación binaria: en vez de multiplicar `n` veces, aprovecha los bits del exponente elevando al cuadrado sucesivamente. | Las versiones `BF` son `O(n)`; las optimizadas reducen iteraciones/llamadas a `O(log n)` desplazando el exponente a la derecha. |
| `demo_fibonacci.cpp` | Muestra que `fibI`, `fib` y `fib(n, prev)` producen el mismo resultado, más los primeros 8 términos desde la clase `Fib`. | Tres estrategias para el mismo problema: iterativa, recursiva ingenua y recursiva con arrastre del término anterior. | `fibI` y `fib(n, prev)` son lineales; `fib(n)` recursiva es exponencial por recomputación de subproblemas. |
| `demo_countones.cpp` | Imprime `x`, su representación binaria y el conteo de bits en 1 con ambos métodos. | `countOnes1` elimina el bit menos significativo en 1 con `n &= (n-1)`; `countOnes2` agrupa y suma bits por bloques. | `countOnes1` cuesta proporcional al número de bits en 1; `countOnes2` hace rondas fijas, así que es `O(1)` para tipos de tamaño fijo. |

Luego respondan:

1. En `demo_bubblesort.cpp`, ¿qué salida sirve para defender costo y no solo resultado?

La salida que sirve para defender costo y no solo resultado es la que imprime las estadísticas: comparaciones, intercambios, ultimo swap; porque esas cantidades muestran cuánto trabajo hizo realmente el algoritmo. Ver solo el arreglo final ordenado prueba el resultado, pero no dice nada sobre el esfuerzo que tomó llegar allí. 

2. En `demo_power.cpp`, ¿qué comparación concreta muestra una mejora algorítmica?

La comparación concreta que muestra una mejora algorítmica es powerBF vs power (potencia por fuerza bruta vs potencia por exponenciación rápida).

"powerBF" se multiplica "a" por sí mismo "n" veces en un bucle lineal, así que su complejidad es O(n). En cambio, power usa la técnica de exponenciación binaria (también llamada square-and-multiply): en cada iteración revisa el bit menos significativo de n, multiplica acumulando solo cuando ese bit es 1, y luego eleva al cuadrado la base mientras desplaza n a la derecha. Como el número de bits de n es log₂(n), la complejidad baja a O(log n).

Por ejemplo, para calcular a^16, powerBF hace 16 multiplicaciones, mientras que power solo necesita alrededor de 4 (los 4 pasos de bits de 16 = 10000₂). A medida que n crece, la diferencia se vuelve enorme: para n = 1 000 000, son un millón de multiplicaciones contra aproximadamente 20.

La mejora se vuelve visible cuando el exponente crece: para exp = 1000, powerBF haría 1000 multiplicaciones y power solo alrededor de 10.

3. En `demo_fibonacci.cpp`, ¿qué crecimiento se vuelve defendible?
El crecimiento que se vuelve defendible es el lineal O(n), tanto en fibI como en fib(n, prev).

fib(n) recursiva recalcula los mismos subproblemas repetidamente: fib(10) llama a fib(9) y fib(8), cada uno de los cuales vuelve a llamar a fib(8) y fib(7), etc. El árbol de llamadas crece exponencialmente → O(2ⁿ).
fib(n, prev) evita eso arrastrando el término anterior como parámetro, convirtiendo la recursión en una cadena lineal sin recomputación → O(n).
fibI hace exactamente lo mismo pero de forma iterativa, también O(n).

Las tres funciones imprimen 55 para n = 10, pero solo fibI y fib(n, prev) escalan bien al aumentar n.

4. En `demo_countones.cpp`, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?

El ejemplo que mejor distingue valor numérico de tamaño en bits es "countOnes1". Su bucle ejecuta "n &= (n - 1)" que apaga el bit menos significativo en cada iteración, así que el número de iteraciones es igual a la cantidad de bits en 1, no al valor de n. Esto se ve claramente comparando dos casos, el número 128 (10000000₂) tiene valor grande pero solo 1 bit encendido, por lo que el bucle itera una sola vez. En cambio, 7 (111₂) tiene valor pequeño pero 3 bits encendidos, y el bucle itera tres veces. Así queda en evidencia que el costo depende del tamaño en bits (cuántos unos hay), no del valor numérico.

La complejidad de 'countOnes1' es 'O(ones)', mientras que 'countOnes2', al usar rondas fijas de ROUND sobre el ancho de palabra de 32 bits, opera en 'O(log w)' constante, independiente tanto del valor como de los bits encendidos.

#### Bloque 3 - Pruebas públicas y preparación de sustentación

Revisen:

* `Semana1/pruebas_publicas/README.md`
* `Semana1/pruebas_publicas/test_public_week1.cpp`
* `Semana1/pruebas_publicas/test_public_week1_extra.cpp`
* `Semana1/sustentacion/preguntas_semana1.md`
* `Semana1/sustentacion/rubrica_semana1.md`

Respondan:

1. ¿Qué funciones o ideas están verificando las pruebas públicas?

Las funciones que están verificando las pruebas públicas son resultados numericos correctos (power, sum) o si un arreglo queda ordenado (Ordenamiento bubbleSortOptimizided).

2. ¿Qué sí demuestra una prueba pública?

Un prueba pública demuestra que las funciones funcionan correctamente ante los casos probados. Es decir evidencia correctitud parcial al verificar comportamientos esperados en entradas definidas.

3. ¿Qué no demuestra una prueba pública?

Una prueba pública no demuestra que un programa sea completamente correcto en todos los casos posibles. Solo verifica un conjunto visible y limitado de ejemplos mínimos esperados. Pasarla indica que el código funciona en esos casos concretos, pero no garantiza que maneje todos los casos borde, ni que sea robusto, ni que su costo esté bien analizado. Tampoco demuestra comprensión conceptual del algoritmo, su correctitud o su complejidad, porque eso se evalúa también en la sustentación.

4. Elijan **una** pregunta de `preguntas_semana1.md` y respóndanla bien.

Mi grupo ha elegido la pregunta 28, la cual es la siguiente:

¿Qué es complejidad temporal?

La complejidad temporal es una medida de cómo crece el número de operaciones de un algoritmo en función del tamaño de la entrada. No mide segundos exactos, sino la tasa de crecimiento del costo. Se expresa normalmente con notación asintótica, como O(n), O(logn), etc. para comparar algoritmos y entender cuáles escalan mejor cuando la entrada se vuelve grande.

5. Usen la rúbrica para autoevaluarse en:

   * comprensión conceptual:        En proceso
   * sustentación de correctitud:   En proceso
   * análisis de eficiencia:        En proceso

#### Bloque 4 - Puente corto con Proyecto0

Revisen:

* `Proyecto0/apps/demo_const_refs.cpp`
* `Proyecto0/bench/bench_vector_growth.cpp`
* `Proyecto0/bench/bench_vector_ops.cpp`
* `Proyecto0/bench/bench_cache_effects.cpp`

Respondan brevemente:

1. ¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?

El demo muestra tres comportamientos distintos sobre el mismo original = {1, 2, 3}. sum_readonly recibe una const& y solo lee: original queda intacto. append_in_place recibe una referencia mutable y modifica el vector directamente, por lo que original pasa a ser {1, 2, 3, 4}. appended_copy devuelve un nuevo vector con el 99 añadido, pero original no cambia. El observable clave es que después de las tres operaciones original sigue siendo {1, 2, 3, 4} y la copia es {1, 2, 3, 4, 99}, dejando claro que leer con const& no cuesta copia, modificar con & afecta al caller, y devolver por valor produce un objeto independiente.

2. En `bench_vector_growth.cpp`, ¿qué cambia con `reserve`?

reserve(n) elimina todas las realocaciones: sin él, el vector crece duplicando capacidad cada vez que se llena, lo que implica copiar todos los elementos a un nuevo bloque de memoria varias veces durante los 300,000 push_back. Con reserve, la memoria se pide una sola vez al inicio y cada push_back solo escribe en el slot siguiente, sin mover nada. El benchmark lo hace visible midiendo el tiempo promedio de ambas versiones: la diferencia refleja exactamente el costo acumulado de esas realocaciones.

3. En `bench_vector_ops.cpp`, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?

push_back al final es O(1) amortizado porque simplemente escribe en la siguiente posición libre. insert(begin()) es O(n) en cada llamada porque antes de insertar debe desplazar todos los elementos existentes una posición hacia la derecha; hacerlo n veces da O(n²) total. insert(middle) también desplaza, pero solo la mitad del vector en cada llamada, así que su constante es menor que insert(begin()), aunque sigue siendo O(n²) en total. Los tres hacen el mismo trabajo observable (llenar el vector con 20,000 elementos), pero el costo de desplazamiento es lo que los separa en el benchmark.

4. En `bench_cache_effects.cpp`, ¿qué intuición deja sobre localidad de memoria?

La intuición es que la localidad de memoria importa tanto como la estructura de datos. El recorrido secuencial del vector es el más rápido porque accede a posiciones contiguas en memoria, permitiendo que el prefetcher de la CPU cargue los datos antes de que se necesiten. El acceso aleatorio al mismo vector es más lento porque cada salto a un índice arbitrario produce un cache miss frecuente. El recorrido de std::list es el más lento de los tres a pesar de ser secuencial en lógica, porque sus nodos están dispersos en el heap y cada next obliga a buscar una dirección distinta en memoria, anulando el beneficio del caché.

#### Bloque 5 - Extensión breve con Ejercicios0

Revisen:

* `Ejercicios0.md`
* `INSTRUCCIONES_Ejercicios0_v4.2.md`
* `stl_optimizacion_demostracion.cpp`
* `resolver_ejercicios0_v4.2.sh`

Respondan:

1. Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?

Ejercicios0.md establece un orden de cuatro pasos. Primero elegir bien el algoritmo, luego verificar que el programa sea correcto, después medir el rendimiento, y finalmente explorar optimizaciones más avanzadas del compilador. El mensaje central es que -O3 no reemplaza a nth_element, a lower_bound, a un buen reserve(), ni a una prueba bien hecha.

2. ¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?

El archivo demuestra que elegir el algoritmo correcto de la STL importa más que el nivel de optimización del compilador. reserve elimina realocaciones evitables en push_back, bajando la constante oculta del costo amortizado. nth_element obtiene la mediana o el k-ésimo elemento en O(n) promedio, evitando el O(n log n) de un sort completo innecesario. partial_sort ordena solo los primeros K elementos para obtener un Top-K, también más barato que ordenar todo. lower_bound convierte una búsqueda lineal O(n) en una búsqueda binaria O(log n) sobre un vector ya ordenado. Cada sección imprime una tabla comparativa de tiempos para que la diferencia sea observable directamente.

3. ¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?

El script genera evidencia empírica y reproducible en forma de archivos dentro de ejercicios0_out/. Produce tablas comparativas de tiempo de ejecución y tamaño de binario para distintos niveles de optimización (experimento 1), salidas del demo STL con tiempos reales (experimento 2), resultados de LTO y PGO con y sin la técnica (experimentos 3 y 4), reportes de ASan, UBSan y TSan detectando errores concretos (experimento 5), porcentajes de cobertura de líneas y condiciones con gcov (experimentos 6 y 7), conteo de warnings por nivel de optimización (experimento 8), y el perfil de funciones calientes con gprof (experimento 9). Todo queda consolidado en reporte_ejercicios0.md.

4. ¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?

El documento advierte tres limitaciones concretas para Windows: ASan, UBSan y TSan pueden no enlazar correctamente; gcov puede requerir ajustes extra según el entorno; y gprof puede fallar o no generar perfiles útiles. Como recomendación, indica usar UCRT64 en MSYS2 para compilación normal, y WSL Ubuntu o Linux nativo para sanitizers, cobertura y profiling. El script mismo detecta estas fallas en tiempo de ejecución y reporta qué log revisar en lugar de abortar silenciosamente.

5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?

Porque el Bloque 5 se enfoca en medir y comparar rendimiento bajo el supuesto de que el código ya es correcto. Los benchmarks y las flags del compilador solo tienen sentido después de garantizar que el programa hace lo que debe: un programa rápido pero incorrecto no sirve. La discusión de correctitud de Semana1 cubre el razonamiento sobre invariantes, precondiciones y postcondiciones de los algoritmos, que es anterior e independiente a cualquier medición. El propio Ejercicios0.md lo dice explícitamente: primero algoritmo correcto, luego medir, luego optimizar.

### Bloque 6 - Cierre comparativo

Respondan esta pregunta final:

**¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?**

La respuesta debe incluir obligatoriamente:

* una afirmación de especificación,
* una afirmación de correctitud,
* una afirmación de costo,
* una afirmación de representación o memoria,
* una advertencia metodológica.

Lo que cambia es el tipo de pregunta que uno está respondiendo. En Semana1 la pregunta era "¿esto funciona bien?"; en el Bloque 5 la pregunta pasa a ser "¿esto funciona mejor que la alternativa, y bajo qué condiciones?". Eso exige un marco distinto.

Afirmación de especificación. Antes de comparar dos implementaciones hay que fijar qué problema resuelven exactamente: nth_element y sort no son intercambiables porque sus contratos son distintos — nth_element solo garantiza que el k-ésimo elemento quede en su posición correcta, no que el resto esté ordenado. Comparar tiempos sin verificar que ambas versiones cumplen la misma especificación es comparar cosas distintas.

Afirmación de correctitud. La evidencia experimental no puede reemplazar al argumento de correctitud: que power(3, 5) devuelva 243 en cinco corridas no prueba que power sea correcta para todo n, solo que no falló en ese caso. La correctitud sigue siendo una propiedad que se defiende con razonamiento sobre el algoritmo, no con observaciones empíricas.

Afirmación de costo. El costo observable en un benchmark es una instancia del costo teórico, no su prueba. Que lower_bound sea más rápido que búsqueda lineal para n = 250000 es consistente con la diferencia entre O(log n) y O(n), pero el argumento de costo se sostiene con el análisis de complejidad, no con el número en pantalla. Los tiempos solo hacen visible lo que el análisis ya predice.
Afirmación de representación o memoria. Cuando bench_cache_effects.cpp muestra que std::list es más lento que vector incluso en recorrido secuencial, lo que se revela no es una diferencia algorítmica sino una diferencia de representación en memoria: los nodos dispersos en el heap rompen la localidad que el caché necesita. Defender una implementación requiere entonces no solo hablar del algoritmo sino de cómo los datos viven en memoria.

Advertencia metodológica. Los benchmarks mienten si no se controlan las variables. El mismo experimento ejecutado con distintos niveles de optimización del compilador, distinto tamaño de entrada o sin repeticiones suficientes puede invertir el resultado. Ejercicios0.md lo resume bien: hay que mantener constantes el input, la máquina, el compilador y el número de repeticiones, y aun así interpretar los tiempos con cuidado, porque medir mal también engaña.
