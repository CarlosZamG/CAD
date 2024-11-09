#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_for_04.c -fopenmp -o nested_for_04 -Wall

Salida (error de compilación):

nested_for_04.c: In function ‘main’:
nested_for_04.c:57:21: error: work-sharing region may not be closely nested inside of work-sharing, ‘critical’, ‘ordere’, ‘master’, explicit ‘task’ or ‘taskloop’ region
   57 |             #pragma omp for
      |                     ^~~
*/

int main(){

    int n = 5;

    #pragma omp parallel  default(none) num_threads(4) shared(n)
    {
        #pragma omp for
        for (int i = 0; i < n; i++)
        {   
            #pragma omp for
            for (int j = 0; j < n; j++)
            {
                printf("Hola desde el hilo %d en la iteración (%d, %d)\n", omp_get_thread_num(), i, j);
            }
        }
    }
    
}