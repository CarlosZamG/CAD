#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc fibonacci.c -o fibonacci -Wall -fopenmp

Posible salida:

Hilo 14 calculando fib(8)
Hilo 5 calculando fib(7)
Hilo 9 calculando fib(6)
Hilo 15 calculando fib(6)
Hilo 13 calculando fib(5)
Hilo 6 calculando fib(5)
Hilo 7 calculando fib(5)
Hilo 0 calculando fib(4)
Hilo 3 calculando fib(3)
Hilo 11 calculando fib(4)
Hilo 11 calculando fib(2)
Hilo 11 calculando fib(0)
Hilo 11 calculando fib(1)
Hilo 11 calculando fib(3)
Hilo 11 calculando fib(1)
Hilo 11 calculando fib(2)
Hilo 11 calculando fib(0)
Hilo 11 calculando fib(1)
Hilo 11 calculando fib(2)
Hilo 11 calculando fib(0)
Hilo 11 calculando fib(1)
Hilo 1 calculando fib(3)
Hilo 11 calculando fib(2)
Hilo 11 calculando fib(0)
Hilo 11 calculando fib(1)
Hilo 10 calculando fib(3)
Hilo 11 calculando fib(2)
Hilo 11 calculando fib(0)
Hilo 11 calculando fib(1)
Hilo 0 calculando fib(2)
Hilo 11 calculando fib(1)
Hilo 1 calculando fib(1)
Hilo 3 calculando fib(1)
Hilo 12 calculando fib(4)
Hilo 10 calculando fib(1)
Hilo 8 calculando fib(4)
Hilo 4 calculando fib(3)
Hilo 0 calculando fib(0)
Hilo 2 calculando fib(4)
Hilo 13 calculando fib(3)
Hilo 13 calculando fib(1)
Hilo 13 calculando fib(2)
Hilo 13 calculando fib(0)
Hilo 13 calculando fib(1)
Hilo 4 calculando fib(1)
Hilo 0 calculando fib(3)
Hilo 13 calculando fib(2)
Hilo 13 calculando fib(0)
Hilo 13 calculando fib(1)
Hilo 10 calculando fib(2)
Hilo 13 calculando fib(1)
Hilo 0 calculando fib(1)
Hilo 2 calculando fib(2)
Hilo 13 calculando fib(1)
Hilo 1 calculando fib(2)
Hilo 1 calculando fib(0)
Hilo 11 calculando fib(3)
Hilo 11 calculando fib(1)
Hilo 11 calculando fib(2)
Hilo 11 calculando fib(0)
Hilo 11 calculando fib(1)
Hilo 10 calculando fib(0)
Hilo 3 calculando fib(2)
Hilo 8 calculando fib(1)
Hilo 13 calculando fib(1)
Hilo 11 calculando fib(0)
Hilo 0 calculando fib(0)
fib(8) =  21

*/


int fib(int n) 
{
    printf("\nHilo %d calculando fib(%d)", omp_get_thread_num(), n);
    int i, j;

    if (n < 2)
        return n;
    else 
    {

        #pragma omp task shared(i)
            i = fib(n - 1);
        #pragma omp task shared(j)
            j = fib(n - 2);
        
        #pragma omp taskwait
        return i+j;
    }
}

int main(int argc, char **argv)
{

    int n = 8;
    int result;

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    printf("\nfib(%d) =  %d\n", n, result);
}