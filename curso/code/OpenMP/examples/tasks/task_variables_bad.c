#include <stdio.h>

/*
Comando para generar el ejecutable:

gcc task_variables_bad.c -o task_variables_bad -Wall -fopenmp

Salida:

task_variables_bad.c: In function ‘main’:
task_variables_bad.c:16:56: error: ‘c’ undeclared (first use in this function)
   16 |         printf("a = %d, b = %d, c = %d, d = %d", a, b, c, d);
      |                                                        ^
task_variables_bad.c:16:56: note: each undeclared identifier is reported only once for each function it appears in
*/

int main()
{
    int a = 2, b = 3;
    #pragma omp parallel default(none) private(a) shared(b)
    {
        int d = 2;
        #pragma omp task
        {
            int c = a + b;
            printf("a = %d, b = %d, c = %d, d = %d", a, b, c, d);
            c = d + b;
            printf("a = %d, b = %d, c = %d, d = %d", a, b, c, d);
        }
        printf("a = %d, b = %d, c = %d, d = %d", a, b, c, d);
    }
}