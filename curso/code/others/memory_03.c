#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Comando para generar el ejecutable:

gcc memory_03.c -o memory_03

Salida:

Dirección del código: 0x55a2142471e9
Dirección del Stack: 0x7ffcb80b97c0 | Valor de n: 23
Dirección del Heap: 0x55a21596d6b0
Dirección del código: 0x55a2142471e9
Dirección del Stack: 0x7ffcb80b97c0 | Valor de n: 17
Dirección del Heap: 0x55a21596d6b0
Valor de n: 17
Valor de n: 23
Valor de n: 23
Valor de n: 17

*/


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