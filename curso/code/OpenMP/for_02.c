#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc for_02.c -fopenmp -o for_02 -Wall

Posible salida:

El hilo 2 está haciendo la iteración 13
El hilo 2 está haciendo la iteración 14
El hilo 2 está haciendo la iteración 15
El hilo 2 está haciendo la iteración 16
El hilo 2 está haciendo la iteración 17
El hilo 2 está haciendo la iteración 18
El hilo 1 está haciendo la iteración 7
El hilo 1 está haciendo la iteración 8
El hilo 1 está haciendo la iteración 9
El hilo 1 está haciendo la iteración 10
El hilo 1 está haciendo la iteración 11
El hilo 1 está haciendo la iteración 12
El hilo 3 está haciendo la iteración 19
El hilo 3 está haciendo la iteración 20
El hilo 3 está haciendo la iteración 21
El hilo 3 está haciendo la iteración 22
El hilo 3 está haciendo la iteración 23
El hilo 3 está haciendo la iteración 24
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 5
El hilo 0 está haciendo la iteración 6

*/


int main(){
    
    int n = 25;

    #pragma omp parallel shared(n) num_threads(4)
    {
        int tid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", tid, i);
        }
    }
}