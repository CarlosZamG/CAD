#include <stdio.h>
#include <omp.h>

/*
Comando para crear el ejecutable:

gcc bad_nested_01.c -o  bad_nested_01 -fopenmp

Salida:
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo

*/

int main(){

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo\n");
        }
    }

}