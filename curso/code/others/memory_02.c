#include <stdio.h>
#include <stdlib.h>

/*
Comando para generar el ejecutable:

gcc memory_02.c -o memory_02

Salida:

Valor de n: 21893. Dirección de n: 0x7ffdc16e2eec
Valor de pn: 0x7ffdc16e2ff0. Dirección de pn: 0x7ffdc16e2ef0

Valor de n: 5. Dirección de n: 0x7ffdc16e2eec
Valor de pn: 0x7ffdc16e2eec. Dirección de pn: 0x7ffdc16e2ef0

Valor de n: 12. Dirección de n: 0x7ffdc16e2eec
Valor de pn: 0x55850fb306b0. Dirección de pn: 0x7ffdc16e2ef0


*/


int main(){

    int n;
    int *pn;

    printf("Valor de n: %d. Dirección de n: %p\n", n, &n);
    printf("Valor de pn: %p. Dirección de pn: %p\n\n", pn, &pn);

    n = 5;
    pn = &n;

    printf("Valor de n: %d. Dirección de n: %p\n", n, &n);
    printf("Valor de pn: %p. Dirección de pn: %p\n\n", pn, &pn);

    n = 12;
    pn = (int*) malloc(sizeof(int));

    printf("Valor de n: %d. Dirección de n: %p\n", n, &n);
    printf("Valor de pn: %p. Dirección de pn: %p\n\n", pn, &pn);


}