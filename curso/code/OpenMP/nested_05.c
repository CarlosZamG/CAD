#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_05.c -fopenmp -o nested_05 -Wall

Salida:

Hola Mundo desde el hilo 0 antes de la región anidada
Hola Mundo desde el hilo 0 dentro de de la región anidada
Hola Mundo desde el hilo 0 después de la región anidada
Hola Mundo desde el hilo 3 antes de la región anidada
Hola Mundo desde el hilo 2 antes de la región anidada
Hola Mundo desde el hilo 0 dentro de de la región anidada
Hola Mundo desde el hilo 3 después de la región anidada
Hola Mundo desde el hilo 1 antes de la región anidada
Hola Mundo desde el hilo 0 dentro de de la región anidada
Hola Mundo desde el hilo 2 después de la región anidada
Hola Mundo desde el hilo 0 dentro de de la región anidada
Hola Mundo desde el hilo 1 después de la región anidada

*/
int main(){

    #pragma omp parallel num_threads(4)
    {
        printf("Hola Mundo desde el hilo %d antes de la región anidada\n", omp_get_thread_num());
        #pragma omp parallel num_threads(1)
        {
            printf("Hola Mundo desde el hilo %d dentro de de la región anidada\n", omp_get_thread_num());
        }
        printf("Hola Mundo desde el hilo %d después de la región anidada\n", omp_get_thread_num());
    }

}