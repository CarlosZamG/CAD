#include <stdio.h>
#include <stdlib.h>

int main(){

    int** Ma;
    
    int r = 3;
    int c = 2;

    Ma = (int**) malloc(r*sizeof(int*));
    
    Ma[0] = (int*) malloc(r*c*sizeof(int));
    
    for (int i = 1; i < r; i++)
    {
        Ma[i] = Ma[i-1] + c;
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            Ma[i][j] = i*c + j;
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf(" %d", Ma[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    for (int i = 0; i < r*c; i++)
    {
        printf(" %d", Ma[0][i]);
    }
    printf("\n");

    printf("\nMa: %p\n\n", Ma);

    for (int i = 0; i < r; i++)
    {
        printf("Ma[%d]: %p\n", i, Ma[i]);
        printf("&Ma[%d][0]: %p\n\n", i, &Ma[i][0]);
    }
    
}
