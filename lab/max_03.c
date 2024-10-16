#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10


int main()
{
    int i;
    int max;
    int n_t = 4;

    int a[SIZE];
    int max_t[n_t];

    srand(time(NULL));

    for (i = 0; i < SIZE; i++)
    {
        a[i] = rand();
        printf("%d\n", a[i]);
    }
    
    
    
    max = a[0];

    #pragma omp parallel num_threads(n_t) default(none) shared(max, a, max_t) private(i)
    {
        int tid = omp_get_thread_num();
        max_t[tid] = a[0];

        #pragma omp for
        for (i = 1; i < SIZE; i++)
        {
            printf("Hilo %d haciendo %d\n", omp_get_thread_num(), i);
            if (a[i] > max_t[tid])
            {
                max_t[tid] = a[i];
            }
        }

    }

    for (i = 0; i < n_t; i++)
    {
        if (max_t[i] > max)
        {
            max = max_t[i];
        }
    }

    printf("max = %d\n", max);
}