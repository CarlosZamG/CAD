#include <stdio.h>
#include <omp.h>
#include <unistd.h>

/*
Comando para generar el ejecuatable:

Posible salida:


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
