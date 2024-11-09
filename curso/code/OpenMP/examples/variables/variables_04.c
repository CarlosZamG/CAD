#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc variables_04.c -o variables_04 -fopenmp -Wall

Salidas de posibles ejecuciones con ./variables_04 3

1ro. Hilo 0, p[0] = 0
1ro. Hilo 0, p[1] = 0
1ro. Hilo 0, p[2] = 0
1ro. Hilo 2, p[0] = 0
1ro. Hilo 2, p[1] = 2
1ro. Hilo 2, p[2] = 4
1ro. Hilo 1, p[0] = 0
1ro. Hilo 1, p[1] = 1
1ro. Hilo 1, p[2] = 2
1ro. Hilo 3, p[0] = 0
1ro. Hilo 3, p[1] = 3
1ro. Hilo 3, p[2] = 6

2do. Hilo 3, p[0] = 0
2do. Hilo 2, p[0] = 0
2do. Hilo 3, p[1] = 3
2do. Hilo 3, p[2] = 6
2do. Hilo 1, p[0] = 0
2do. Hilo 1, p[1] = 1
2do. Hilo 1, p[2] = 2
2do. Hilo 2, p[1] = 2
2do. Hilo 2, p[2] = 4
2do. Hilo 0, p[0] = 0
2do. Hilo 0, p[1] = 0
2do. Hilo 0, p[2] = 0


1ro. Hilo 0, p[0] = 0
1ro. Hilo 0, p[1] = 0
1ro. Hilo 0, p[2] = 0
1ro. Hilo 3, p[0] = 0
1ro. Hilo 2, p[0] = 0
1ro. Hilo 2, p[1] = 2
1ro. Hilo 2, p[2] = 4
1ro. Hilo 3, p[1] = 3
1ro. Hilo 3, p[2] = 6
1ro. Hilo 1, p[0] = 0
1ro. Hilo 1, p[1] = 1
1ro. Hilo 1, p[2] = 2

2do. Hilo 3, p[0] = 0
2do. Hilo 3, p[1] = 3
2do. Hilo 3, p[2] = 6
2do. Hilo 1, p[0] = 0
2do. Hilo 1, p[1] = 1
2do. Hilo 1, p[2] = 2
2do. Hilo 2, p[0] = 0
2do. Hilo 2, p[1] = 2
2do. Hilo 2, p[2] = 4
2do. Hilo 0, p[0] = 0
2do. Hilo 0, p[1] = 0
2do. Hilo 0, p[2] = 0


*/

int main(int argc, char* argv[]){

    if(argc < 2) return -1;

    int n = atoi(argv[1]);

    #pragma omp parallel num_threads(4)
    {
        int* p = (int*) malloc(sizeof(int) * n);

        int id = omp_get_thread_num();

        for (int i = 0; i < n; i++)
        {
            p[i] = id*i;
            printf("1ro. Hilo %d, p[%d] = %d\n", id, i, p[i]);
        }

        #pragma omp barrier

        #pragma omp single
        printf("\n");

        for (int i = 0; i < n; i++)
        {
            printf("2do. Hilo %d, p[%d] = %d\n", id, i, p[i]);
        }

        free(p);
        p = NULL;
    }

}