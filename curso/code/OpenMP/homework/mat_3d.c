#include <stdio.h>
#include <stdlib.h>

int main(){

    //El puntero para guardar nuestra matriz de forma dinámica 
    int*** Ma;
    
    // Las 3 dimensiones de nuestra matriz
    int r = 3;
    int c = 2;
    int d = 2;
    
    // Construimos nuestra matriz de 3 dimesiones con memoria continua 
    Ma = (int***) malloc(r*sizeof(int**));
    
    Ma[0] = (int**) malloc(r*c*sizeof(int*));
    
    for (int i = 1; i < r; i++)
    {
        Ma[i] = Ma[i-1] + c;
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

    // Asignamos valores a nuestra matriz con un único bucle 
    for (int i = 0; i < r*c*d; i++)
    {
        Ma[0][0][i] = 2 * (i + 1);
    }
    
    // Imprimimos los valores con 3 bucles anidados
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < d; k++)
            {
                printf("\nM[%d][%d][%d] = %d", i, j, k, Ma[i][j][k]);
            }
        }
        printf("\n");
    }
    
    printf("\n");
    
    // Imprimimos los valores con un único bucle
    for (int i = 0; i < r*c*d; i++)
    {
        printf("\nMa[0][0][%d]: %d ", i, Ma[0][0][i]);
    }
    printf("\n");
    
}
