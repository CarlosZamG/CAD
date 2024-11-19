#include <stdio.h>

/*
Comando para generar el ejecutable:

gcc sizes.c -o sizes -Wall

Salida:

sizeof(char): 1
sizeof(short): 2
sizeof(int): 4
sizeof(long): 8

sizeof(char *): 8
sizeof(short *): 8
sizeof(int *): 8
sizeof(long *): 8

sizeof(mytype): 16

arr[0]:  1 | *(arr + 0):  1 | p2arr[0]:  1 | *(p2arr + 0):  1
arr[1]:  3 | *(arr + 1):  3 | p2arr[1]:  3 | *(p2arr + 1):  3
arr[2]:  5 | *(arr + 2):  5 | p2arr[2]:  5 | *(p2arr + 2):  5
arr[3]:  7 | *(arr + 3):  7 | p2arr[3]:  7 | *(p2arr + 3):  7
arr[4]:  9 | *(arr + 4):  9 | p2arr[4]:  9 | *(p2arr + 4):  9
arr[5]: 11 | *(arr + 5): 11 | p2arr[5]: 11 | *(p2arr + 5): 11
arr[6]: 13 | *(arr + 6): 13 | p2arr[6]: 13 | *(p2arr + 6): 13
arr[7]: 15 | *(arr + 7): 15 | p2arr[7]: 15 | *(p2arr + 7): 15
arr[8]: 17 | *(arr + 8): 17 | p2arr[8]: 17 | *(p2arr + 8): 17
arr[9]: 19 | *(arr + 9): 19 | p2arr[9]: 19 | *(p2arr + 9): 19

&arr[0]: 0x7ffd0d4850a0 | arr + 0: 0x7ffd0d4850a0 | &p2arr[0]: 0x7ffd0d4850a0 | p2arr + 0: 0x7ffd0d4850a0
&arr[1]: 0x7ffd0d4850a4 | arr + 1: 0x7ffd0d4850a4 | &p2arr[1]: 0x7ffd0d4850a4 | p2arr + 1: 0x7ffd0d4850a4
&arr[2]: 0x7ffd0d4850a8 | arr + 2: 0x7ffd0d4850a8 | &p2arr[2]: 0x7ffd0d4850a8 | p2arr + 2: 0x7ffd0d4850a8
&arr[3]: 0x7ffd0d4850ac | arr + 3: 0x7ffd0d4850ac | &p2arr[3]: 0x7ffd0d4850ac | p2arr + 3: 0x7ffd0d4850ac
&arr[4]: 0x7ffd0d4850b0 | arr + 4: 0x7ffd0d4850b0 | &p2arr[4]: 0x7ffd0d4850b0 | p2arr + 4: 0x7ffd0d4850b0
&arr[5]: 0x7ffd0d4850b4 | arr + 5: 0x7ffd0d4850b4 | &p2arr[5]: 0x7ffd0d4850b4 | p2arr + 5: 0x7ffd0d4850b4
&arr[6]: 0x7ffd0d4850b8 | arr + 6: 0x7ffd0d4850b8 | &p2arr[6]: 0x7ffd0d4850b8 | p2arr + 6: 0x7ffd0d4850b8
&arr[7]: 0x7ffd0d4850bc | arr + 7: 0x7ffd0d4850bc | &p2arr[7]: 0x7ffd0d4850bc | p2arr + 7: 0x7ffd0d4850bc
&arr[8]: 0x7ffd0d4850c0 | arr + 8: 0x7ffd0d4850c0 | &p2arr[8]: 0x7ffd0d4850c0 | p2arr + 8: 0x7ffd0d4850c0
&arr[9]: 0x7ffd0d4850c4 | arr + 9: 0x7ffd0d4850c4 | &p2arr[9]: 0x7ffd0d4850c4 | p2arr + 9: 0x7ffd0d4850c4

arr: 0x7ffd0d4850a0 p2arr 0x7ffd0d4850a0

&arr: 0x7ffd0d4850a0 &p2arr 0x7ffd0d485098

sizeof(arr): 40 sizeof(p2arr): 8

sizeof(arr) == sizeof(p2arr) : 0

*/

typedef struct mytype
{
    int x;
    int y;
    int z;
    char c;

} mytype;


int main()
{
    printf("sizeof(char): %ld\n", sizeof(char));
    printf("sizeof(short): %ld\n", sizeof(short));
    printf("sizeof(int): %ld\n", sizeof(int));
    printf("sizeof(long): %ld\n", sizeof(long));
    printf("\n");
    printf("sizeof(char *): %lx\n", sizeof(char *));
    printf("sizeof(short *): %ld\n", sizeof(short *));
    printf("sizeof(int *): %ld\n", sizeof(int *));
    printf("sizeof(long *): %ld\n", sizeof(long *));

    printf("\n");

    printf("sizeof(mytype): %ld\n", sizeof(mytype));

    printf("\n");

    int arr[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int *p2arr = arr;

    for (int i = 0; i < 10; i++)
    {
        printf("arr[%d]: %2d | *(arr + %d): %2d | p2arr[%d]: %2d | *(p2arr + %d): %2d\n", i, arr[i],
                                                                                i, *(arr + i), 
                                                                                i, p2arr[i], 
                                                                                i, *(p2arr + i));
    }

    printf("\n");


    for (int i = 0; i < 10; i++)
    {
        printf("&arr[%d]: %p | arr + %d: %p | &p2arr[%d]: %p | p2arr + %d: %p\n", i, &arr[i],
                                                                        i, arr + i,
                                                                        i, &p2arr[i], 
                                                                        i, p2arr + i);
    }

    printf("\narr: %p p2arr %p\n", arr, p2arr);
    printf("\n&arr: %p &p2arr %p\n", &arr, &p2arr);
    printf("\nsizeof(arr): %ld sizeof(p2arr): %ld\n", sizeof(arr), sizeof(p2arr));
    printf("\nsizeof(arr) == sizeof(p2arr) : %d\n", sizeof(arr) == sizeof(p2arr));

}