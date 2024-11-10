# Task (Tareas en OpenMP)

Las tareas (o *task* en inglés) de OpenMP son *una instancia específica de código ejecutable y su entorno de datos que una implementación de OpenMP debe preparar para ser ejecutada por hilos*. Algo importante que debemos considerar es que la construcción `parallel` crea un conjunto de tareas **implícitas** y cada una de esas tareas es asignada a cada uno de los diferentes hilos en el equipo.

Podemos usar la construcción `task` para crear tareas **explícitas**. Cuando un hilo encuentra una construcción `task` tiene dos opciones:

- La tarea puede ser ejecutada inmediatamente.

- La tarea puede ser delegada a otro de los hilos del equipo.

Veamos ejemplos usando tareas explícitas:

```c
#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{

    #pragma omp parallel num_threads(4)
    {
        #pragma omp task
        {
            printf("Hilo %d haciendo tarea 1\n", omp_get_thread_num());
        }
    }

    printf("\n\n");
}
```
Debido a que estamos creando un equipo de 4 hilos y cada hilo encuentra una construcción `#pragma omp task`, se lanzan 4 tareas que serán ejecutadas por el equipo de hilos, sin embargo, no necesariamente se asignará una tarea a cada uno de los hilos, puede ser que un hilo se encargue de realizar dos o más tareas, tal como podemos ver en la siguiente ejecución:

```sh
Hilo 3 haciendo tarea 1
Hilo 1 haciendo tarea 1
Hilo 0 haciendo tarea 1
Hilo 3 haciendo tarea 1


```


Una de las principales ventajas de las tareas es que soportan el **paralelismo desestructurado**, es decir, nos permiten paralelizar cosas como **bucles sin límites claros** o **funciones recursivas**.

## Fibonacci en paralelo con OpenMP

Consideremos el siguiente código:

```c
#include <stdio.h>
#include <omp.h>

int fib(int n) 
{
    printf("\nHilo %d calculando fib(%d)", omp_get_thread_num(), n);
    int i, j;
    
    if (n < 2)
        return n;
    else 
    {

        #pragma omp task shared(i)
            i = fib(n - 1);
        #pragma omp task shared(j)
            j = fib(n - 2);
        
        #pragma omp taskwait
        return i+j;
    }
}

int main(int argc, char **argv)
{

    int n = 8;
    int result;

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    printf("\nfib(%d) =  %d\n", n, result);
}
```

Una posible salida es la siguiente:

```sh

Hilo 11 calculando fib(8)
Hilo 4 calculando fib(6)
Hilo 8 calculando fib(7)
Hilo 12 calculando fib(5)
Hilo 10 calculando fib(4)
Hilo 14 calculando fib(6)
Hilo 15 calculando fib(5)
Hilo 0 calculando fib(4)
Hilo 0 calculando fib(2)
Hilo 0 calculando fib(0)
Hilo 0 calculando fib(1)
Hilo 3 calculando fib(2)
Hilo 7 calculando fib(5)
Hilo 6 calculando fib(4)
Hilo 7 calculando fib(3)
Hilo 6 calculando fib(2)
Hilo 6 calculando fib(0)
Hilo 6 calculando fib(1)
Hilo 1 calculando fib(3)
Hilo 2 calculando fib(3)
Hilo 3 calculando fib(0)
Hilo 2 calculando fib(1)
Hilo 13 calculando fib(3)
Hilo 2 calculando fib(2)
Hilo 13 calculando fib(1)
Hilo 13 calculando fib(2)
Hilo 13 calculando fib(0)
Hilo 13 calculando fib(1)
Hilo 13 calculando fib(4)
Hilo 13 calculando fib(2)
Hilo 13 calculando fib(0)
Hilo 13 calculando fib(1)
Hilo 13 calculando fib(3)
Hilo 13 calculando fib(1)
Hilo 13 calculando fib(2)
Hilo 13 calculando fib(0)
Hilo 13 calculando fib(1)
Hilo 5 calculando fib(4)
Hilo 2 calculando fib(0)
Hilo 2 calculando fib(1)
Hilo 2 calculando fib(2)
Hilo 2 calculando fib(0)
Hilo 2 calculando fib(1)
Hilo 2 calculando fib(3)
Hilo 2 calculando fib(1)
Hilo 2 calculando fib(2)
Hilo 2 calculando fib(0)
Hilo 2 calculando fib(1)
Hilo 1 calculando fib(1)
Hilo 3 calculando fib(1)
Hilo 7 calculando fib(1)
Hilo 13 calculando fib(2)
Hilo 2 calculando fib(1)
Hilo 5 calculando fib(2)
Hilo 3 calculando fib(1)
Hilo 6 calculando fib(3)
Hilo 1 calculando fib(2)
Hilo 1 calculando fib(0)
Hilo 1 calculando fib(1)
Hilo 10 calculando fib(0)
Hilo 9 calculando fib(3)
Hilo 2 calculando fib(0)
Hilo 3 calculando fib(1)
Hilo 7 calculando fib(2)
Hilo 3 calculando fib(1)
Hilo 10 calculando fib(0)
Hilo 13 calculando fib(1)
fib(8) =  21
```

Podemos notar que a pesar de que un único dentro de la región paralela realiza la llamada de `fib(n)` con `n == 8`, `fib()` es una función recursiva que hemos paralelizado con el uso de tareas, así las diferentes llamadas de esta función pueden ser realizadas por diferentes hilos.

Sabemos que una llamada a la función recursiva del problema de *Fibonacci* que se encarga de calcular el término `fib(k)` requiere haber calculado previamente `fib(k - 1)` y `fib(k - 2)`, por esta razón en el ejemplo usamos la directiva `# pragma omp taskwait` que espera a que termine la ejecución de las tareas que son hijas **directas** de la tarea actual:

```c
#pragma omp parallel
#pragma omp single
{
    #pragma omp task
    {
        //Digamos que esta es la tarea A

        #pragma omp task
        {
            //Digamos que esta es la tarea B
        }

        #pragma omp task
        {
            //Digamos que esta es la tarea C
            
            #pragma omp task
            {
                //Digamos que esta es la tarea C.1
            }

            #pragma omp task
            {
                //Digamos que esta es la tarea C.1
            }
        }

        #pragma omp taskwait
        // Este taskwait espera a que finalicen las tareas B y C, pero NO espera a C.1 ni C.2
    }
}
```

Veamos un ejemplo en código:

```c
#include <stdio.h>
#include <omp.h>
#include <unistd.h>


int main()
{

    #pragma omp parallel num_threads(4)
    {
        #pragma omp task
        {
            #pragma omp task
            {
                printf("Hilo %d haciendo tarea 1\n", omp_get_thread_num());
            }

            #pragma omp task
            {
                printf("Hilo %d haciendo tarea 2\n", omp_get_thread_num());
                
                #pragma omp task
                {
                    sleep(2);
                    printf("Hilo %d haciendo tarea 2.1\n", omp_get_thread_num());
                }

                #pragma omp task
                {
                    sleep(2);
                    printf("Hilo %d haciendo tarea 2.2\n", omp_get_thread_num());
                }
            }

            #pragma omp taskwait
            printf("Ya esperé\n");
        }
    }

    printf("\n\n");
}
```

La salida puede ser similar a la siguiente:

```sh
Hilo 2 haciendo tarea 2
Hilo 2 haciendo tarea 1
Ya esperé
Hilo 2 haciendo tarea 2
Hilo 2 haciendo tarea 1
Ya esperé
Hilo 2 haciendo tarea 1
Hilo 3 haciendo tarea 2
Ya esperé
Hilo 0 haciendo tarea 2
Hilo 1 haciendo tarea 1
Ya esperé
Hilo 2 haciendo tarea 2.1
Hilo 3 haciendo tarea 2.2
Hilo 1 haciendo tarea 2.1
Hilo 0 haciendo tarea 2.2
Hilo 2 haciendo tarea 2.1
Hilo 3 haciendo tarea 2.2
Hilo 0 haciendo tarea 2.2
Hilo 1 haciendo tarea 2.1


```
Podemos notar que el mensaje `Ya esperé` sale después de que se realizan las tareas `1` y `2` debido a que son las tareas hijas directas de la tarea actual, sin embargo, no espera a las tareas `2.1` ni `2.2`.

### Entorno de datos al trabajar con tareas

Al momento de trabajar con tareas, las variables pueden ser compartidas, privadas o `firstprivate` respecto a una tarea, muy parecido al manejo de variables en otras construcciones de OpenMP. Aquí una lista de las diferencias que tiene respecto al manejo de variables con hilos:

- El entorno de datos corresponde a la tarea, **no** al hilo que encuentra a la tarea.

- Si una variable es compartida dentro de una construcción `task`, las referencia a ella son al mismo espacio de direcciones de esta variable compartida cuando la tarea fue encontrada.

- Si una variable aparece en la cláusula `private` de una construcción `task`, las referencias a ella dentro de la construcción son a un almacenamiento nuevo y sin inicializar que se crea cuando se encuentra a la tarea.

- Si una variable aparece en la cláusula `firstprivate` de una construcción `task`, las referencias a ella dentro de la construcción son a un almacenamiento nuevo que se inicializa con el valor que tenía la variable al momento de encontyrar la tarea.

Los comportamientos por defecto son los siguientes:

- Las variables que son privadas cuando se encuentra una construcción `task` se manejan como `firstprivate` por defecto.

- Las variables que son compartidas cuando se encuentra una construcción `task` se manejan como compartidas por defecto.

Por esta razón debemos indicar que las variables `i` y `j` son compartidas para sus respectivas tareas en nuestra función recursiva que usa tareas, ya que por defecto serán privadas, entonces el valor calculado al momento de hacer las tareas se perderá al momento de hacer el retorno.