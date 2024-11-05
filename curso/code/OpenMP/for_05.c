#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc for_05.c -fopenmp -o for_05 -Wall

Posible salida:

El hilo (2, 0)  está haciendo la iteración 0
El hilo (2, 0)  está haciendo la iteración 1
El hilo (2, 3)  está haciendo la iteración 4
El hilo (2, 2)  está haciendo la iteración 3
El hilo (2, 1)  está haciendo la iteración 2
El hilo (1, 2)  está haciendo la iteración 3
El hilo (3, 0)  está haciendo la iteración 0
El hilo (3, 0)  está haciendo la iteración 1
El hilo (1, 1)  está haciendo la iteración 2
El hilo (3, 1)  está haciendo la iteración 2
El hilo (3, 3)  está haciendo la iteración 4
El hilo (3, 2)  está haciendo la iteración 3
El hilo (1, 3)  está haciendo la iteración 4
El hilo (1, 0)  está haciendo la iteración 0
El hilo (1, 0)  está haciendo la iteración 1
El hilo (0, 3)  está haciendo la iteración 4
El hilo (0, 0)  está haciendo la iteración 0
El hilo (0, 0)  está haciendo la iteración 1
El hilo (0, 1)  está haciendo la iteración 2
El hilo (0, 2)  está haciendo la iteración 3


*/


int main(){
    
    int n = 5;

    omp_set_num_threads(4);
    omp_set_nested(1);

    #pragma omp parallel default(none) shared(n)
    {
        int ptid = omp_get_thread_num();

        #pragma omp parallel for default(none) shared(n, ptid)
        for (int i = 0; i < n; i++)
        {
            printf("El hilo (%d, %d)  está haciendo la iteración %d\n", ptid, omp_get_thread_num(), i);
        }
    }
}