#include <stdio.h>

int main(){
    int r = 3;
    int c = 2;
    int M[r][c];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            M[i][j] = i*c + j;
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf(" %d", M[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    for (int i = 0; i < r*c; i++)
    {
        printf(" %d", M[0][i]);
    }
    printf("\n");

    printf("\nM: %p\n\n", M);

    for (int i = 0; i < r; i++)
    {
        printf("M[%d]: %p\n", i, M[i]);
        printf("&M[%d][0]: %p\n\n", i, &M[i][0]);
    }
    
    
}