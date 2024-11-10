# Task (Tareas en OpenMP)

Las tareas (o *task* en inglés) de OpenMP son *una instancia específica de código ejecutable y su entorno de datos que una implementación de OpenMP debe preparar para ser ejecutada por hilos*. Algo importante que debemos considerar es que la construcción `parallel` crea un conjunto de tareas **implícitas** y cada una de esas tareas es asignada a cada uno de los diferentes hilos en el equipo.

Podemos usar la construcción `task` para crear tareas **explícitas**. Cuando un hilo encuentra una construcción `task` tiene dos opciones:

- La tarea puede ser ejecutada inmediatamente.

- La tarea puede ser delegada a otro de los hilos del equipo.

Una de las principales ventajas de las tareas es que sosportan el **paralelismo desestructurado**, es decir, nos permiten paralelizar cosas como **bucles sin límites claros** o **funciones recursivas**.

## Fibonacci en paralelo con OpenMP

Consideremos el siguiente código

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
