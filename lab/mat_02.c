#include <stdio.h>

int main(){

    int r = 3;
    int c = 2;
    int d = 4;

    int M[r][c][d];

    for (int i = 0; i < r*c*d; i++)
    {
        M[0][0][i] = i;
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < d; k++)
            {
                printf(" %d", M[i][j][k]);
            }
            printf("\t");
        }
        printf("\n");
    }


    printf("\nM: %p\n\n", M);

    for (int i = 0; i < r; i++)
    {
        printf("M[%d]: %p\n",i, M[i]);
        for (int j = 0; j < c; j++)
        {
            printf("M[%d][%d]: %p\n", i, j, M[i][j]);
            printf("&M[%d][%d][0]: %p\n\n", i, j, &M[i][j][0]);
        }
    }
    
}