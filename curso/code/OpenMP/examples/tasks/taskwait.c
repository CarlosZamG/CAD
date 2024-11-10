#include <stdio.h>
#include <omp.h>
#include <unistd.h>

/*
Comando para generar el ejecuatable:

gcc taskwait.c -o taskwait -Wall -fopenmp

Posible salida:

Hilo 2 haciendo tarea 2
Hilo 2 haciendo tarea 1
Ya esperé
Hilo 2 haciendo tarea 2
Hilo 2 haciendo tarea 1
Ya esperé
Hilo 2 haciendo tarea 1
Hilo 3 haciendo tarea 2
Ya esperé
Hilo 0 haciendo tarea 2
Hilo 1 haciendo tarea 1
Ya esperé
Hilo 2 haciendo tarea 2.1
Hilo 3 haciendo tarea 2.2
Hilo 1 haciendo tarea 2.1
Hilo 0 haciendo tarea 2.2
Hilo 2 haciendo tarea 2.1
Hilo 3 haciendo tarea 2.2
Hilo 0 haciendo tarea 2.2
Hilo 1 haciendo tarea 2.1



*/

int main()
{

    #pragma omp parallel num_threads(4)
    {
        #pragma omp task
        {
            #pragma omp task
            {
                printf("Hilo %d haciendo tarea 1\n", omp_get_thread_num());
            }

            #pragma omp task
            {
                printf("Hilo %d haciendo tarea 2\n", omp_get_thread_num());
                
                #pragma omp task
                {
                    sleep(2);
                    printf("Hilo %d haciendo tarea 2.1\n", omp_get_thread_num());
                }

                #pragma omp task
                {
                    sleep(2);
                    printf("Hilo %d haciendo tarea 2.2\n", omp_get_thread_num());
                }
            }

            #pragma omp taskwait
            printf("Ya esperé\n");
        }
    }

    printf("\n\n");
}
