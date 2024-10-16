#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main()
{
    int i;
    int max;
    int max_t;
    int a[SIZE];

    srand(time(NULL));

    for (i = 0; i < SIZE; i++)
    {
        a[i] = rand();
        printf("%d\n", a[i]);
    }

    max_t = a[0];
    max = a[0];

    #pragma omp parallel num_threads(4) default(none) firstprivate(max_t) shared(max, a) private(i)
    {   
        #pragma omp for
        for (i = 1; i < SIZE; i++)
        {
            printf("Hilo %d haciendo %d\n", omp_get_thread_num(), i);
            if (a[i] > max_t)
            {
                max_t = a[i];
            }
        }

        if (max_t > max)
        {
            #pragma omp critical
            {
                if (max_t > max)
                    max = max_t;
            }
        }
    }
    printf("max = %d\n", max);
}