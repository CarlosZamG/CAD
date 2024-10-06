#include <stdio.h>

int main()
{

    int a;
    int ar[10];
    void *p;
    
    for(int i = 0; i<10; i++)
    {
        ar[i] = -(i+1);
        printf("\n%d %d %p %p", ar[i], *(ar+i), ar+i, &ar[i]);
    }
    
    p = ar;
    
    printf("\n\n%d %p\n", *((int *)p), p);
    
    return 0;
}
