#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc for_ordered.c -o for_ordered -Wall -fopenmp

Posible salida:

El hilo 7 está ejecutando la iteración 8 sin orden
El hilo 0 está ejecutando la iteración 1 sin orden
El hilo 0 está ejecutando la iteración 1
El hilo 4 está ejecutando la iteración 5 sin orden
El hilo 1 está ejecutando la iteración 2 sin orden
El hilo 1 está ejecutando la iteración 2
El hilo 3 está ejecutando la iteración 4 sin orden
El hilo 2 está ejecutando la iteración 3 sin orden
El hilo 2 está ejecutando la iteración 3
El hilo 3 está ejecutando la iteración 4
El hilo 4 está ejecutando la iteración 5
El hilo 6 está ejecutando la iteración 7 sin orden
El hilo 5 está ejecutando la iteración 6 sin orden
El hilo 5 está ejecutando la iteración 6
El hilo 6 está ejecutando la iteración 7
El hilo 7 está ejecutando la iteración 8
*/

int main()
{

    #pragma omp parallel for ordered
    for (int i = 1; i <= 8; i++)
    {
        printf("El hilo %d está ejecutando la iteración %d sin orden\n", omp_get_thread_num(), i);
        #pragma omp ordered
        printf("El hilo %d está ejecutando la iteración %d \n", omp_get_thread_num(), i);
    }

    return 0;
}