#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_02.c -fopenmp -o nested_02 -Wall

Posible salida:

Hola Mundo desde (0, 0)
Hola Mundo desde (2, 0)
Hola Mundo desde (0, 1)
Hola Mundo desde (3, 2)
Hola Mundo desde (2, 1)
Hola Mundo desde (0, 2)
Hola Mundo desde (2, 2)
Hola Mundo desde (2, 3)
Hola Mundo desde (3, 0)
Hola Mundo desde (3, 1)
Hola Mundo desde (3, 3)
Hola Mundo desde (1, 3)
Hola Mundo desde (1, 0)
Hola Mundo desde (1, 1)
Hola Mundo desde (1, 2)
Hola Mundo desde (0, 3)

*/

int main(){

    omp_set_nested(1);

    #pragma omp parallel num_threads(4)
    {
        int tid_p = omp_get_thread_num();

        #pragma omp parallel num_threads(3) shared(tid_p)
        {
            printf("Hola Mundo desde (%d, %d) \n", tid_p, omp_get_thread_num());
        }
    }
}