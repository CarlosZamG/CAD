#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

/*
El siguiente código reduce el número de ejecuciones de regiones críticas para encontrar
el máximo de  un arreglo utilizando una variable privada donde cada hilo guardará el 
valor máximo que encuentre en sus iteraciones y después de ejecutar el for, cada hilo 
comparará su variable privada con una varible compartida que guarda el máximo global
y actualizará el valor en caso de ser necesario. De esta forma se reduce el número 
de ejecuciones de regiones críticas de a lo más tantas como el número de hilos.
*/

int main()
{
    // Arreglo de números enteros
    int a[SIZE];
    // Varible para guardar el máximo global del arreglo    
    int max;    
    // Varible privada para que cada hilo guarde el máximo de sus iteraciones 
    int max_t;  
    
    // Inicializamos los valores el arreglo de forma aleatoria
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 1000000;
    }

    // Inicializamos el máximo global y el máximo privado de cada hilo con el primer
    // valor del arreglo
    max_t = a[0];
    max = a[0];

    #pragma omp parallel num_threads(4) default(none) firstprivate(max_t) shared(max, a)
    {
        // Se realiza un for paralelo y las iteraciones se reparten entre los hilos
        #pragma omp for
        for (int i = 1; i < SIZE; i++)
        {
            // Cada hilo va guardando el máximo de sus iteraciones correspondientes en
            // su variable privada
            if (a[i] > max_t)
            {
                max_t = a[i];
            }
        }

        // Después del for paralelo cada hilo compara el máximo de su varible privada con
        // el máximo global de la varible compartida y actualiza la varible compartida de
        // ser necesario.
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