#include <stdio.h>

int main(){

    #pragma omp parallel
    {
        printf("Hola Mundo\n");
    }

}
