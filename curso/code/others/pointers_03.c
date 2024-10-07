#include <stdio.h>

/*
Comando para generar el ejecutable:

gcc pointers_03.c -o pointers_03

Salida:

La variable n con valor: 5 vive en 0x7ffe416d7dcc
La variable p con valor: 0x7ffe416d7dcc vive en 0x7ffe416d7dd0 y el contenido de la dirección que guarda es 5
La variable q1 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7dd8 y el contenido de la dirección que guarda es 0x7ffe416d7dcc

La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido (como entero) de la dirección que guarda es 1097694668
La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido (como puntero) de la dirección que guarda es 0x416d7dcc
La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido en la forma ((void *) ((unsigned int) *q2)) de la dirección que guarda es 0x416d7dcc
La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido en la forma ((void *) *q2) de la dirección que guarda es 0x416d7dcc
La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido en la forma ((int *) *q2) de la dirección que guarda es 0x416d7dcc
La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido en la forma *((void **)q2) de la dirección que guarda es 0x7ffe416d7dcc
La variable q2 con valor: 0x7ffe416d7dd0 vive en 0x7ffe416d7de0 y el contenido en la forma *((int **)q2) de la dirección que guarda es 0x7ffe416d7dcc
1097694668 - (1097694668) = 0
*/

int main(){

    int n = 5;
    int *p = &n;
    int **q1 = &p;
    int *q2 = &p;

    printf("La variable n con valor: %d vive en %p\n", n, &n);
    printf("La variable p con valor: %p vive en %p y el contenido de la dirección que guarda es %d\n", p, &p, *p);
    printf("La variable q1 con valor: %p vive en %p y el contenido de la dirección que guarda es %p\n", q1, &q1, *q1);
    printf("\n");

    printf("La variable q2 con valor: %p vive en %p y el contenido (como entero) de la dirección que guarda es %d\n", q2, &q2, *q2);
    
    printf("La variable q2 con valor: %p vive en %p y el contenido (como puntero) de la dirección que guarda es %p\n", q2, &q2, *q2);
    printf("La variable q2 con valor: %p vive en %p y el contenido en la forma ((void *) ((unsigned int) *q2)) de la dirección que guarda es %p\n", q2, &q2, ((void *) ((unsigned int) *q2)));
    
    printf("La variable q2 con valor: %p vive en %p y el contenido en la forma ((void *) *q2) de la dirección que guarda es %p\n", q2, &q2, ((void *) *q2));
    printf("La variable q2 con valor: %p vive en %p y el contenido en la forma ((int *) *q2) de la dirección que guarda es %p\n", q2, &q2, ((int *) *q2));

    printf("La variable q2 con valor: %p vive en %p y el contenido en la forma *((void **)q2) de la dirección que guarda es %p\n", q2, &q2, *((void **)q2));
    printf("La variable q2 con valor: %p vive en %p y el contenido en la forma *((int **)q2) de la dirección que guarda es %p\n", q2, &q2, *((int **)q2));
    
    printf("%d - (%d) = %d\n", *q2, *q2, *q2-*q2);

}