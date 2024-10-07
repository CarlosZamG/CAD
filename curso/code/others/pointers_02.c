#include <stdio.h>

/*
Comando para generar el ejecutable:

gcc pointers_02.c -o pointers_02

Salida:

 ar[0]: -1 | *(ar+0): -1 | ar+0: 0x7ffdd6ff08e0 | &ar[0]: 0x7ffdd6ff08e0
 ar[1]: -2 | *(ar+1): -2 | ar+1: 0x7ffdd6ff08e4 | &ar[1]: 0x7ffdd6ff08e4
 ar[2]: -3 | *(ar+2): -3 | ar+2: 0x7ffdd6ff08e8 | &ar[2]: 0x7ffdd6ff08e8
 ar[3]: -4 | *(ar+3): -4 | ar+3: 0x7ffdd6ff08ec | &ar[3]: 0x7ffdd6ff08ec
 ar[4]: -5 | *(ar+4): -5 | ar+4: 0x7ffdd6ff08f0 | &ar[4]: 0x7ffdd6ff08f0
 ar[5]: -6 | *(ar+5): -6 | ar+5: 0x7ffdd6ff08f4 | &ar[5]: 0x7ffdd6ff08f4
 ar[6]: -7 | *(ar+6): -7 | ar+6: 0x7ffdd6ff08f8 | &ar[6]: 0x7ffdd6ff08f8
 ar[7]: -8 | *(ar+7): -8 | ar+7: 0x7ffdd6ff08fc | &ar[7]: 0x7ffdd6ff08fc
 ar[8]: -9 | *(ar+8): -9 | ar+8: 0x7ffdd6ff0900 | &ar[8]: 0x7ffdd6ff0900
 ar[9]: -10 | *(ar+9): -10 | ar+9: 0x7ffdd6ff0904 | &ar[9]: 0x7ffdd6ff0904

 *((int *)p): -1 | p: 0x7ffdd6ff08e0

*/

int main()
{

    int a;
    int ar[10];
    void *p;
    
    for(int i = 0; i<10; i++)
    {
        ar[i] = -(i+1);
        printf("\n ar[%d]: %d | *(ar+%d): %d | ar+%d: %p | &ar[%d]: %p", i, ar[i], i, *(ar+i), i, ar+i, i, &ar[i]);
    }
    
    p = ar;
    
    printf("\n\n *((int *)p): %d | p: %p\n", *((int *)p), p);
    
    return 0;
}
