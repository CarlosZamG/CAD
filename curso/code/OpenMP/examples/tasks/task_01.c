#include <stdio.h>
#include <omp.h>
#include <unistd.h>

/*
Comando para generar el ejecuatable:
gcc task_01.c -o task_01 -Wall -fopenmp

Posible salida:

Hilo 3 haciendo tarea 1
Hilo 1 haciendo tarea 1
Hilo 0 haciendo tarea 1
Hilo 3 haciendo tarea 1


*/

int main()
{

    #pragma omp parallel num_threads(4)
    {
        #pragma omp task
        {
            printf("Hilo %d haciendo tarea 1\n", omp_get_thread_num());
        }
    }

    printf("\n\n");
}
