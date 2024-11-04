#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc for_01.c -fopenmp -o for_01 -Wall

Posible salida:

El hilo 1 está haciendo la iteración 0
El hilo 1 está haciendo la iteración 1
El hilo 1 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 0
El hilo 3 está haciendo la iteración 0
El hilo 3 está haciendo la iteración 1
El hilo 1 está haciendo la iteración 3
El hilo 3 está haciendo la iteración 2
El hilo 3 está haciendo la iteración 3
El hilo 3 está haciendo la iteración 4
El hilo 3 está haciendo la iteración 5
El hilo 1 está haciendo la iteración 4
El hilo 1 está haciendo la iteración 5
El hilo 2 está haciendo la iteración 0
El hilo 2 está haciendo la iteración 1
El hilo 2 está haciendo la iteración 2
El hilo 2 está haciendo la iteración 3
El hilo 2 está haciendo la iteración 4
El hilo 2 está haciendo la iteración 5
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 5

*/


int main(){
    
    int n = 6;

    #pragma omp parallel shared(n) num_threads(4)
    {
        int tid = omp_get_thread_num();

        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", tid, i);
        }
    }
}