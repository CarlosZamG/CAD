#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc for_03.c -fopenmp -o for_03 -Wall

Posible salida:

a = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
b = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 5
El hilo 0 está haciendo la iteración 6
El hilo 2 está haciendo la iteración 13
El hilo 2 está haciendo la iteración 14
El hilo 2 está haciendo la iteración 15
El hilo 2 está haciendo la iteración 16
El hilo 2 está haciendo la iteración 17
El hilo 2 está haciendo la iteración 18
El hilo 3 está haciendo la iteración 19
El hilo 3 está haciendo la iteración 20
El hilo 3 está haciendo la iteración 21
El hilo 3 está haciendo la iteración 22
El hilo 3 está haciendo la iteración 23
El hilo 3 está haciendo la iteración 24
El hilo 1 está haciendo la iteración 7
El hilo 1 está haciendo la iteración 8
El hilo 1 está haciendo la iteración 9
El hilo 1 está haciendo la iteración 10
El hilo 1 está haciendo la iteración 11
El hilo 1 está haciendo la iteración 12

c = 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48,


*/


int main(){
    
    int n = 25;

    int a[n], b[n], c[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = i;
        b[i] = i;
    }
    
    printf("\na = ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", a[i]);
    }

    printf("\nb = ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", b[i]);
    }

    printf("\n");

    #pragma omp parallel default(none) shared(n, c, a , b) num_threads(4)
    {
        int tid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", tid, i);
            c[i] = a[i] + b[i];
        }
    }

    printf("\nc = ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", c[i]);
    }

    printf("\n");
}