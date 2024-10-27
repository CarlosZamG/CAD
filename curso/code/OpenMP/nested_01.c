#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_01.c -fopenmp -o nested_01 -Wall

Posible salida:

Hola Mundo desde el hilo: 2
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 2
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 2
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 2

*/

int main(){

    omp_set_nested(1);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo desde el hilo: %d\n", omp_get_thread_num());
        }
    }

}