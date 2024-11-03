#include <stdio.h>
#include <omp.h>

/*
Comando para crear el ejecutable:

gcc bad_nested_03.c -o bad_nested_03 -fopenmp

Salida:
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 3
Hola Mundo desde el hilo 1
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 2
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0

*/

int main(){

    #pragma omp parallel num_threads(4)
    {
        printf("Hola Mundo desde el hilo %d\n", omp_get_thread_num());
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo desde el hilo %d\n", omp_get_thread_num());
        }
    }

}