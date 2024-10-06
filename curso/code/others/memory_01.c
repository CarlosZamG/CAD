#include <stdio.h>
#include <stdlib.h>

/*
Comando para generar el ejecutable:

gcc memory_01.c -o memory_01

Salida:

Dirección del código: 0x5650d8051189
Dirección del Stack: 0x7fffa823df54
Dirección del Heap: 0x5650d95296b0

*/


int main(){

    printf("Dirección del código: %p\n", main);
    int n = 0;
    printf("Dirección del Stack: %p\n", &n);
    printf("Dirección del Heap: %p\n", malloc(1));

    return 0;
}