#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Dirección del código: %p\n", main);
    int n = 0;
    printf("Dirección del Stack: %p\n", &n);
    printf("Dirección del Heap: %p\n", malloc(1));

    return 0;
}