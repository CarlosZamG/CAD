# Variables en OpenMP

Cuando una región paralela está en ejecución, todos los hilos ejecutan una copia del bloque de instrucciones, pero **¿Cómo se manejan las variables?** OpenMP tiene dos tipos elementales de memoria: *privada* y *compartida*.

- **Variables privadas**: Cada hilo tiene su propia copia de la variable a la que sólo dicho hilo puede acceder, es decir, ningún otro hilo puede interferir, por lo que no hay riesgo de sufrir una *condición de carrera*, ya que un hilo nunca podrá cambiar el valor de la copia de una variable privada perteneciente a otro hilo.

- **Variables compartidas**: Solo existe una instancia de la variable y puede ser leída o modificada por todos los hilos. Debemos tener cuidado al usar estas variables para evitar caer en una *condición de carrera*.

Veamos un ejemplo en código de los distintos tipos de variables en las construcciones de OpenMP.

```c
#include <stdio.h>
#include <omp.h>

int main(){

    int x = 1;
    int y = 1;
    
    int a = 0;

    x = 5;
    y = 5;

    printf("(x, y, a) = (%d, %d, %d)\n", x, y, a);
    
    #pragma omp parallel private(x) firstprivate(y) num_threads(4)
    {
        int id = omp_get_thread_num();
        int n1 = id*x;
        int n2 = id*y;
        //Por reglas de OpenMP, las variables id, n1 y n2 son privadas
        
        x = x+1;
        y = y+1;
        a = a + n2;
        printf("Hilo con ID: %3d | n1: %3d | n2: %3d | (x, y, a) = (%d, %d, %d)\n", id, n1, n2, x, y, a);
    }

    printf("(x, y, a) = (%d, %d, %d)\n", x, y, a);
}
```

Notemos que las variables `x`,`y` y `a` están declaradas afuera de la construcción paralela, pero al momento de escribir la construcción paralela, utilizamos las claúsulas `private()` para la variable `x` y `firstprivate()` para la variable `y`. Así estamos indicando que ambas variables son privadas, por lo que cada hilo tendrá su propia copia de dichas variables. La diferencia entre `private()` y `firstprivate()` es que el valor de las varibles privadas indicadas con `private()` está indefinido dentro de la región paralela, mientras que con `firstprivate()` nos aseguramos que se toma el valor de la variable afuera de la construcción para inicializar cada copia de los hilos en la región paralela.

Por defecto, todas las variables declaradas afuera de la construcción paralela son compartidas, así que la variable `a` es compartida, ya que no estamos utilizando una claúsula para ella.

Al momento de compilar con `gcc variables.c -o variables -fopenmp -Wall`, nos mostrará la siguiente advertencia:

```sh
variables.c: In function ‘main._omp_fn.0’:
variables.c:59:13: warning: ‘x’ is used uninitialized in this function [-Wuninitialized]
   59 |         int n1 = id*x;
      |             ^~
variables.c:46:9: note: ‘x’ was declared here
   46 |     int x = 1;
      |         ^
```

Esto se debe a que el comportamiento de las variables indicadas como privadas usando `private()`  está indefinido, por lo que nos marca una advertencia de que estamos usando una variable sin inicializar.

Veamos lo que sucede al ejecutar un par de veces el programa:

```sh
(x, y, a) = (5, 5, 0)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 10)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 20)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 5)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 20)
(x, y, a) = (5, 5, 20)
```

```sh
(x, y, a) = (5, 5, 0)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 0)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 30)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 20)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 5)
(x, y, a) = (5, 5, 30)
```

```sh
(x, y, a) = (5, 5, 0)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 10)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 5)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 10)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 25)
(x, y, a) = (5, 5, 25)
```

Lo primero que debemos tener en cuenta es que al utilizar la cláusula `num_threads(4)` estamos indicando que se deben lanzar 4 hilos que van a ejecutar las instrucciones generadas por el código de la construcción, cosa que podemos notar al ver que se realizan 4 impresiones a pesar de que estamos llamando a `printf()` una sola vez dentro de la región (cada hilo llama a `printf()` con sus respectivos valores)

Las variables declaradas dentro de la construcción paralela como `id`, `n1` y `n2` son privadas, es decir, cada hilo tiene su propia copia de dichas variables, por lo cuál los valores de estas variables **pueden** ser diferentes para cada copia del hilo. De hecho, como `id` obtiene su valor de `omp_get_thread_num()`, que nos devuelve un número único para cada hilo, cada copia de `id` tendrá un valor diferente para cada hilo, cosa que también afecta a `n2`. Para el caso de `n1` podemos asumir que `x` toma el valor de `0` dentro de la región paralela, cosa que se confirma al momento de sumarle uno y posteriormente imprimir su valor.

Como ya mencionamos, la varible `a` es compartida al estar declarada fuera de la construcción paralela y no utilizar ninguna cláusula para ella. El propósito de esta variable es guardar la suma acumulada de las variables privadas `n2`, sin embargo podemos notar que esto no siempre se logra de manera efectiva, ya que sucede una condición de carrera por lo que se pierde coherencia y el resultado es distinto para diferentes ejecuciones.

