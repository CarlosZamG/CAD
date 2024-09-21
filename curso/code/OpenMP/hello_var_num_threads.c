#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc hello_var_num_threads.c -o hello_var_num_threads -fopenmp

Salida:

El número de hilos al inicio es: 1
Hola Mundo.
Hola Mundo. El número de hilos dentro de esta región es: 16El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
El número de hilos al final es: 1

*/


int main(){
    
    printf("\nEl número de hilos al inicio es: %d", omp_get_num_threads());

    #pragma omp parallel
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    omp_set_num_threads(7);

    #pragma omp parallel
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    #pragma omp parallel num_threads(4)
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    #pragma omp parallel
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    printf("\nEl número de hilos al final es: %d\n", omp_get_num_threads());
}