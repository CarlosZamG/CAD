#include <stdio.h>

/*
Comando para compilar

gcc hello_bad.c -fopenmp -o hello_bad 

*/


int main(){

    #pragma omp parallel{
        printf("Hola Mundo\n");
    }

}