#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc task_variables.c -o task_variables -Wall -fopenmp

Salida:

a = 2, b = 3
(Antes) id: 0, a = 21890, b = 3, d = 2
(Después) id: 0, a = 21890, b = 3, d = 2
(Durante) id: 0, a = 21890, b = 3, c = 21893, d = 2
(Durante) id: 0, a = 21890, b = 3, c = 5, d = 2
(Antes) id: 1, a = 0, b = 3, d = 2
(Durante) id: 0, a = 0, b = 4, c = 4, d = 2
(Durante) id: 0, a = 0, b = 4, c = 6, d = 2
(Después) id: 1, a = 0, b = 4, d = 2
a = 2, b = 5

*/

int main()
{
    int a = 2, b = 3;

    printf("a = %d, b = %d\n", a, b);

    #pragma omp parallel default(none) private(a) shared(b) num_threads(2)
    {
        int d = 2;  // d es privada
        
        // b es compartida
        // a es privada con comportamiento indefinido

        printf("(Antes) id: %d, a = %d, b = %d, d = %d\n", omp_get_thread_num(), a, b, d);

        #pragma omp task
        {
            int c = a + b; //c es privada para la tarea
            // d pasa como firstprivate
            // b pasa como compartida
            // a pasa como firstprivate
            printf("(Durante) id: %d, a = %d, b = %d, c = %d, d = %d\n", omp_get_thread_num(), a, b, c, d);
            c = d + b;
            printf("(Durante) id: %d, a = %d, b = %d, c = %d, d = %d\n", omp_get_thread_num(), a, b, c, d);
            b++;
        }
        printf("(Después) id: %d, a = %d, b = %d, d = %d\n", omp_get_thread_num(), a, b, d);
    }

    printf("a = %d, b = %d\n", a, b); // los cambios se notan en b 
}