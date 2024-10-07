#include <stdio.h>

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