#include <stdio.h>
#include <omp.h>

int fib(int n) {
    
    printf("\nHilo %d calculando fib(%d)", omp_get_thread_num(), n);
    
    int i = 8, j = 8;
    
    if (n<2)
        return n;
    else {
        #pragma omp task shared(i)
        {
            //printf("\nHilo %d calculando fib(%d)", omp_get_thread_num(), n - 1);
            i = fib(n-1);
        }
        
        #pragma omp task shared(j)
        {
            //printf("\nHilo %d calculando fib(%d)", omp_get_thread_num(), n - 2);
            j = fib(n-2);
        }
        
        #pragma omp taskwait
        return i+j;
    }

}

int main()
{
    int n = 5;

    #pragma omp parallel num_threads(4)
    {
        #pragma omp task
        printf ("\nid: %d fib(%d) = %d\n", omp_get_thread_num(), n, fib(n));
    }
}
