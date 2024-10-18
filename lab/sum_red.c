#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 1000000

int main()
{
    double arr[SIZE];
    double parallel_sum = 0.0;
    double serial_sum = 0.0;
    double l1 = -2220.0;
    double l2 = 11230.0;


    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = l1 + (l2-l1)*rand()/RAND_MAX;
        //printf("%d %lf\n", i, arr[i]);
    }
    

    #pragma omp parallel for reduction(+ : parallel_sum)
    for (int i = 0; i < SIZE; i++)
    {
        parallel_sum += arr[i];
    }


    printf("Suma de los elementos del arreglo en paralelo: %lf\n", parallel_sum);

    for (int i = 0; i < SIZE; i++)
    {
        serial_sum += arr[i];
    }

    printf("Suma de los elementos del arreglo en serial: %lf\n", serial_sum);

}

