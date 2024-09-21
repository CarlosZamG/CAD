#include <stdio.h>

int main(){

    int a = 3;
    int b = 10;
    int c = a;
    int *p;
    p = b;

    printf("El resultado de p*a es: %d\n", (int)p*a);
    printf("La variable a con valor %d vive en %p\n", a, &a);
    printf("La variable b con valor %d vive en %p\n", b, &b);
    printf("La variable c con valor %d vive en %p\n", c, &c);
    printf("La variable p con valor %d vive en %p\n", p, &p);
    
    
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