#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

/*
El siguiente código reduce el número de ejecuciones de regiones críticas para encontrar
el máximo de  un arreglo utilizando un arreglo donde cada hilo guardará el valor máximo
que encuentre en sus iteraciones y después de ejecutar el for, se comparará el valor 
guardado en el arreglo con el máximo global y actualizará el valor del máximo global en
caso de ser necesario. De esta forma se eliminan las regiones críticas.
*/

int main()
{
    // Arreglo de números enteros
    int a[SIZE];
    // Variable para guardar el máximo del arreglo de números enteros
    int max;
    // Variable para guardar el número máximo de hilos que pueden usarse en una región
    // paralela
    int n_t = omp_get_max_threads();
    // Arreglo para que cada hilo guarde el máximo de sus iteraciones  
    int max_t[n_t];

    // Inicializamos los valores el arreglo de forma aleatoria
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 1000000;
    }
    
    // Inicializamos el máximo global
    max = a[0];
    // Inicializamos los valores del arreglo para que cada hilo guarde su máximo
    for (int i = 0; i < n_t; i++)
    {
        max_t[i] = a[0];
    }
    
    #pragma omp parallel default(none) shared(a, max_t)
    {
        // Variable privada para guardar el identificador del hilo
        int tid = omp_get_thread_num();
        
        // Se realiza un for paralelo y las iteraciones se reparten entre los hilos
        #pragma omp for
        for (int i = 1; i < SIZE; i++)
        {
            // Cada hilo va guardando el máximo de sus iteraciones correspondientes en
            // en el arreglo (la posición corresponde el identificador)
            if (a[i] > max_t[tid])
            {
                max_t[tid] = a[i];
            }
        }
    }

    // Después de la región paralela, se comparan los máximos de cada hilo guardados en
    // el arreglo con el máximo global y se actualiza en caso de ser necesario
    for (int i = 0; i < n_t; i++)
    {
        if (max_t[i] > max)
        {
            max = max_t[i];
        }
    }

    printf("max = %d\n", max);
}