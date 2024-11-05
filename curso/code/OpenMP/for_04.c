#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc for_04.c -fopenmp -o for_04 -Wall

Posible salida:

El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4


*/


int main(){
    
    int n = 5;

    omp_set_num_threads(4);

    #pragma omp parallel default(none) shared(n)
    {
        #pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", omp_get_thread_num(), i);
        }
    }
}