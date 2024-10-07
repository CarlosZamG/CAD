#include <stdio.h>

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
