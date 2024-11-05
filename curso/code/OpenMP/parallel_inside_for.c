#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc parallel_inside_for.c -fopenmp -o parallel_inside_for -Wall

Posible salida:

Hola desde el hilo 2 en la iteración 0
Hola desde el hilo 3 en la iteración 0
Hola desde el hilo 0 en la iteración 0
Hola desde el hilo 1 en la iteración 0
Hola desde el hilo 2 en la iteración 1
Hola desde el hilo 0 en la iteración 1
Hola desde el hilo 1 en la iteración 1
Hola desde el hilo 3 en la iteración 1
Hola desde el hilo 2 en la iteración 2
Hola desde el hilo 3 en la iteración 2
Hola desde el hilo 0 en la iteración 2
Hola desde el hilo 1 en la iteración 2
Hola desde el hilo 3 en la iteración 3
Hola desde el hilo 1 en la iteración 3
Hola desde el hilo 2 en la iteración 3
Hola desde el hilo 0 en la iteración 3
Hola desde el hilo 3 en la iteración 4
Hola desde el hilo 0 en la iteración 4
Hola desde el hilo 1 en la iteración 4
Hola desde el hilo 2 en la iteración 4

*/

int main(){
    
    int n = 5;
    for (int i = 0; i < n; i++)
    {
        #pragma omp parallel default(none) num_threads(4) shared(i)
        {
            printf("Hola desde el hilo %d en la iteración %d\n", omp_get_thread_num(), i);
        }
    }
    
}