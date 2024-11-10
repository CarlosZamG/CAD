# Task (Tareas en OpenMP)

Las tareas (o *task* en inglés) de OpenMP son *una instancia específica de código ejecutable y su entorno de datos que una implementación de OpenMP debe preparar para ser ejecutada por hilos*. Algo importante que debemos considerar es que la construcción `parallel` crea un conjunto de tareas **implícitas** y cada una de esas tareas es asignada a cada uno de los diferentes hilos en el equipo.

Podemos usar la construcción `task` para crear tareas **explícitas**. Cuando un hilo encuentra una construcción `task` tiene dos opciones:

- La tarea puede ser ejecutada inmediatamente.

- La tarea puede ser delegada a otro de los hilos del equipo.

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