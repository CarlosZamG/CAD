#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int id = fork();
    printf("Dirección del código: %p\n", main);
    
    int n = 0;
    
    if (id == 0)
    {
        n = 17;
    }else
    {
        n = 23;
    }
    

    printf("Dirección del Stack: %p | Valor de n: %d\n", &n, n);
    printf("Dirección del Heap: %p\n", malloc(1));

        
    if (id != 0)
    {
        sleep(2);
    }
    printf("Valor de n: %d\n", n);
    
    if(id == 0)
    {
        sleep(6);
    }
    printf("Valor de n: %d\n", n);

    if (id != 0)
    {
        wait(0);
    }

    return 0;
}