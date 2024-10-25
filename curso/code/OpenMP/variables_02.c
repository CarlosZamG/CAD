#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc variables_02.c -o variables_02 -fopenmp -Wall

Salidas de múltiples ejecuciones:

*/

int main(int argc, char* argv[]){

    if(argc < 2) return -1;

    int n = atoi(argv[1]);

    int* p = (int*) malloc(sizeof(int) * n);

    #pragma omp parallel num_threads(4)
    {

        int id = omp_get_thread_num();

        if (id == 3)
        {
            //sleep(10);
        }
        

        for (int i = 0; i < n; i++)
        {
            p[i] = id*i;
        }
        
        for (int i = 0; i < n; i++)
        {
            printf("%d * %d = %d\n", id, i, p[i]);
        }

    }

    free(p);
    p = NULL;

}