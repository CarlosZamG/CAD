#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_03.c -fopenmp -o nested_03 -Wall

Posible salida:

Hola Mundo desde (0, 0)
Hola Mundo desde (3, 0)
Hola Mundo desde (1, 0)
Hola Mundo desde (2, 0)

*/

int main(){

    #pragma omp parallel num_threads(4)
    {
        int tid_p = omp_get_thread_num();

        #pragma omp parallel num_threads(3)
        {
            printf("Hola Mundo desde (%d, %d) \n", tid_p, omp_get_thread_num());
        }
    }
}