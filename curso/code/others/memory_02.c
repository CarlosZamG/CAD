#include <stdio.h>
#include <stdlib.h>

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