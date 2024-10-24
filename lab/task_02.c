#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{

    #pragma omp parallel num_threads(4)
    {
        #pragma omp task
        {
            printf("Hilo %d haciendo tarea 1\n", omp_get_thread_num());
        }

        #pragma omp task
        {
            printf("Hilo %d haciendo tarea 2\n", omp_get_thread_num());
        }
    }

    printf("\n\n");
}
