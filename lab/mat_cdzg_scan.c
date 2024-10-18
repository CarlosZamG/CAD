#include <stdio.h>
#include <stdlib.h>

int main(){

    int*** Ma;
    
    int r = 3;
    int c = 2;
    int d = 4;

    printf("Ingrese el numero de filas");
    scanf("%d", &r);
    printf("Ingrese el numero de columnas");
    scanf("%d", &c);
    printf("Ingrese el numero de profundidad");
    scanf("%d", &d);
    
    Ma = (int***) malloc(r*sizeof(int**));
    
    
    for (int i = 0; i < r; i++)
    {
        Ma[i] = (int**) malloc(c*sizeof(int*));
    }
    
    Ma[0][0] = (int*) malloc(r*c*d*sizeof(int));
    
    
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == 0 && j == 0){
                continue;
            }
            else if (j == 0){
                Ma[i][j] = Ma[i-1][c-1] + d;
            }
            else{
                Ma[i][j] = Ma[i][j-1] + d;
            }
        }
    }

    /*for (int i = 1; i < r; i++)
    {
        Ma[i] = (int**) Ma[i][0];
    }*/
    
    
    for (int i = 0; i < r*c*d; i++)
    {
        Ma[0][0][i] = i;
    }
    
    
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < d; k++)
            {
                printf("\n(%d, %d, %d) %d", i, j, k, Ma[i][j][k]);
            }
            printf("\t");
        }
        printf("\n");
    }


    printf("\nMa: %p\n\n", Ma);

    for (int i = 0; i < r; i++)
    {
        printf("Ma[%d]: %p\n",i, Ma[i]);
        for (int j = 0; j < c; j++)
        {
            printf("Ma[%d][%d]: %p\n", i, j, Ma[i][j]);
            printf("&Ma[%d][%d][0]: %p\n\n", i, j, &Ma[i][j][0]);
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < d; k++)
            {
                printf(" %d", Ma[i][j][k]);
            }
            printf("\t");
        }
        printf("\n");
    }

    printf("\n");
    for (int i = 0; i < r*c*d; i++)
    {
        printf("%d ", Ma[0][0][i]);
    }
    printf("\n");
}
