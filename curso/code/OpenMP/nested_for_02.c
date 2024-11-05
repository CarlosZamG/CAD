#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc nested_for_02.c -fopenmp -o nested_for_02 -Wall

Posible salida:

Hola desde el hilo 1 en la iteración (2, 0)
Hola desde el hilo 1 en la iteración (2, 1)
Hola desde el hilo 1 en la iteración (2, 2)
Hola desde el hilo 1 en la iteración (2, 3)
Hola desde el hilo 1 en la iteración (2, 4)
Hola desde el hilo 2 en la iteración (3, 0)
Hola desde el hilo 2 en la iteración (3, 1)
Hola desde el hilo 2 en la iteración (3, 2)
Hola desde el hilo 2 en la iteración (3, 3)
Hola desde el hilo 2 en la iteración (3, 4)
Hola desde el hilo 0 en la iteración (0, 0)
Hola desde el hilo 0 en la iteración (0, 1)
Hola desde el hilo 0 en la iteración (0, 2)
Hola desde el hilo 0 en la iteración (0, 3)
Hola desde el hilo 0 en la iteración (0, 4)
Hola desde el hilo 0 en la iteración (1, 0)
Hola desde el hilo 0 en la iteración (1, 1)
Hola desde el hilo 3 en la iteración (4, 0)
Hola desde el hilo 3 en la iteración (4, 1)
Hola desde el hilo 3 en la iteración (4, 2)
Hola desde el hilo 3 en la iteración (4, 3)
Hola desde el hilo 3 en la iteración (4, 4)
Hola desde el hilo 0 en la iteración (1, 2)
Hola desde el hilo 0 en la iteración (1, 3)
Hola desde el hilo 0 en la iteración (1, 4)
for paralelo
    for serial

*/

int main(){

    int n = 5;

    #pragma omp parallel for default(none) num_threads(4) shared(n)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Hola desde el hilo %d en la iteración (%d, %d)\n", omp_get_thread_num(), i, j);
        }
    }
}