#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_04.c -fopenmp -o nested_04 -Wall

Salida:

Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0

*/
int main(){

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo desde el hilo %d\n", omp_get_thread_num());
        }
    }

}