#include <stdio.h>

/*
Comando para generar el ejecutable:

gcc hello.c -o hello -fopenmp

Salida:

Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo

*/


int main(){

    #pragma omp parallel
    {
        printf("Hola Mundo\n");
    }

}
