#include <stdio.h>

/*
Comando para generar el ejecutable:

gcc pointers_01.c -o pointers_01

(tiene advertencias)

Salida:

La variable a con valor 3 vive en 0x7fff7c850e44
La variable b con valor 10 vive en 0x7fff7c850e48
La variable c con valor 3 vive en 0x7fff7c850e4c
La variable p con valor 10 vive en 0x7fff7c850e50
El resultado de p*a es: 30
sizeof(int): 4
sizeof(float): 4
sizeof(double): 8
sizeof(char): 1
sizeof(int *): 8
sizeof(float *): 8
sizeof(double *): 8
sizeof(char *): 8

*/

int main(){

    int a = 3;
    int b = 10;
    int c = a;
    int *p;
    p = b;

    printf("La variable a con valor %d vive en %p\n", a, &a);
    printf("La variable b con valor %d vive en %p\n", b, &b);
    printf("La variable c con valor %d vive en %p\n", c, &c);
    printf("La variable p con valor %d vive en %p\n", p, &p);
    printf("El resultado de p*a es: %d\n", (int)p*a);
    
    
    printf("sizeof(int): %ld\n",sizeof(int));
    printf("sizeof(float): %ld\n",sizeof(float));
    printf("sizeof(double): %ld\n",sizeof(double));
    printf("sizeof(char): %ld\n",sizeof(char));

    printf("sizeof(int *): %ld\n",sizeof(int *));
    printf("sizeof(float *): %ld\n",sizeof(float *));
    printf("sizeof(double *): %ld\n",sizeof(double *));
    printf("sizeof(char *): %ld\n",sizeof(char *));
    
    return 0;
}