#include <stdio.h>

int main()
{
    int n = 55;
    int* p = &n;
    double* dp = (double*) &p;

    printf("Dirección: %p | Contenido %d | long: %ld | double %e\n", p, *p,(unsigned long) p, *dp);

    float f = -42.0f;
    unsigned int* pf = (unsigned int*) &f;
    printf("\npf: %u\n", *pf);
    
}