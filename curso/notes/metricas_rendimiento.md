# Métricas de Rendimineto

### Granularidad:

Se define como:

$$Gr = \frac{t_{comm}}{t_{comp}}$$

Dónde:
- $t_{comm}$ es el tiempo que las unidades de procesamiento se comunican.

- $t_{comp}$ es el tiempo que las unidades de procesamiento realizan cálculos.

- $Gr$ es la granularidad de la tarea:

    - Si $Gr$ es grande, la tarea es de grano grueso: Conviene usar **MPI**.

    - Si $Gr$ es cercano a $1$, la tarea es de grano medio. Conviene usar **OpenMP**.

    - Si $Gr$ es pequeño, la tarea es de grano fino. Conviene usar **CUDA**.

### Factor de velocidad (*Speedup* en inglés):

Se define como:

$$S(n) = \frac{t_s}{t_p}$$

Dónde:
- $n$ es el número de unidades de procesamiento. Se suele decir que el la cantidad de procesadores, pero no necesariamente es así: Pueden ser cores, tarjetas de video o nodos de un cluster.

- $t_s$ es el tiempo de ejecución que se toma el programa al utilizar una **única** unidad de procesamiento, es decir, depende de la unidad de medida. Es la base con la que vamos a comparar y **nosotros** la elegimos.

- $t_p$ es el tiempo paralelo: es el tiempo de ejecución que se toma el programa que utiliza múltipes unidades de procesamiento para resolver esa misma instancia del problema.

- $S(n)$: La mejora en el tiempo de ejecución al utilizar un programa con múltiples unidades de procesamiento respecto a uno con una sola unidad de procesamiento.

El *Speedup* ideal sería que $S(n) = n$, es decir, el factor de velocidad es proporcional al número de unidades de procesamiento.

### Ley de Amdahl

En 1967, Gene Amdahl formuló una ley para describir los beneficios en rendimineto obtenidos con un programa paralelo. Amdahl hizo las siguientes suposiciones:

- Tenemos una aplicación que requiere un tiempo $t_s$ para ejecutarse con una sola unidad de procesamiento.

- La aplicación tiene una parte $0\leq f\leq 1$ que debe realizarse de forma serial, mientras que el resto de la tarea puede paralelizarse. Por ejemplo, si $f = 0.1$, significa que el $10\%$ de la tarea debe hacerse serial.

- La parte paralela $(1-f)$ puede dividirse uniformente entre cualquier cantidad $n$ de unidades de procesamiento.

Con estas suposiciones tenemos que $t_p = f\cdot t_s + \frac{(1-f)}{n}\cdot t_s$

Entonces el *Speedup* obtenido al usar $n$ unidades de procesmiento está dado por:

$$S(n) = \frac{t_s}{t_p} = \frac{t_s}{f\cdot t_s + \frac{(1-f)}{n}\cdot t_s} = \frac{1}{f + \frac{(1-f)}{n}} =  \frac{n}{n\cdot f + (1-f)} = \frac{n}{1+(n-1)f} $$

Notemos que $$\lim_{n\rightarrow \infty} S(n) = \frac{1}{f}$$

Lo que nos daría la cota del factor de velocidad. Informalmente lo podemos ver como el factor de velocidad que obtendríamos al usar *infinitas* unidades de procesamiento.

Para el caso en el que $f=0.1$ tenemos que $\lim_{n\rightarrow \infty} S(n) = 1 / 0.1 = 10$. Esto quiere decir que si tenemos infinitas unidades de procesamiento para paralelizar una tarea con una parte del $10\%$ que obligatoriamente debe ser serial, la mejora en el rendimiento respecto a una sola unidad de procesamiento es únicamente de $10$, lo cuál es un número muy bajo considerando una infinidad de unidades.

### Ley de Gustafson

Dos décadas después de que Amdahl publicara su ley, Gustafson y Barsis decidieron abordar el problema de una forma diferente: Un programa en paralelo hace más que acelerar la ejecución de un programa secuencial, puede solucionar instancias **más grandes** del problema. Así que en vez de comparar lo que un programa paralelo puede hacer respecto a uno secuencial, podemos estudiar como se comporta el programa secuencial si se le pide resolver el mismo problema que un programa paralelo puede resolver. Por lo tanto se hicieron las siguientes suposiciones:

- Tenemos una aplicación paralela que se ejecuta en tiempo $t_p$ en $n$ unidades de procesamiento.

- La aplicación ocupa $0 \leq p \leq 1$ del tiempo ejecutándose en todas las máquinas, mientras que el resto del tiempo $s = 1 - p$ se ejecuta de forma serial.

Entonces resolver todo el problema de forma serial requeriría el siguiente tiempo:

$t_s = s\cdot t_p + p \cdot t_p \cdot n$

debido a que la parte en paralelo requeriría ser hecha de forma serial.

Así tenemos el *Speedup* de la siguiente forma:

$$S(n) = \frac{t_s}{t_p} = \frac{s\cdot t_p + p \cdot t_p \cdot n}{t_p}= s+p\cdot n = s+(1-s)\cdot n = s\cdot (1-n) + n$$

Supongamos que tenemos 20 unidades de procesamiento para realizar una tarea con una fracción serial de $0.05$, entonces el *Speedup* considerando la **Ley de Amdahl** tendría un valor:

$$S(20) = \frac{20}{1+(19)\cdot 0.05} = 10.25641$$


Mientras que usando la **Ley de Gustafson** tenemos:

$$S(20) = 20 + (-19)\cdot 0.05 = 19.05$$

Es decir, las suposiciones de la Ley de Gustafson nos permiten tener una visión más optimista de la mejora en el rendimiento respecto a la Ley de Amdahl.

### Eficiencia (%)

Es una métrica que nos indica qué tanto se ocuparon las unidades de procesamiento y se calcula de la siguiente forma:

$$E = \frac{S(n)}{n}\times 100\%$$

### Costo

Es una métrica que nos indica cuánto se está gastando y se calcula de la forma:

$$\text{Costo} = \frac{t_s}{E} = \frac{t_s\cdot n}{S(n)}$$