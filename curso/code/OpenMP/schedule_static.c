#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc schedule_static.c -fopenmp -o schedule_static -Wall

Posible salida:

 0: 0
 1: 0
 2: 0
 3: 0
 4: 0
 5: 0
 6: 0
 7: 1
 8: 1
 9: 1
10: 1
11: 1
12: 1
13: 1
14: 2
15: 2
16: 2
17: 2
18: 2
19: 2
20: 2
21: 3
22: 3
23: 3
24: 3
25: 3
26: 3
27: 3
28: 0
29: 0
30: 0
31: 0
32: 0
33: 0
34: 0
35: 1
36: 1
37: 1
38: 1
39: 1
40: 1
41: 1
42: 2
43: 2
44: 2
45: 2
46: 2
47: 2
48: 2
49: 3
50: 3
51: 3
52: 3
53: 3
54: 3
55: 3
56: 0
57: 0
58: 0
59: 0
60: 0
61: 0
62: 0
63: 1
64: 1
65: 1
66: 1
67: 1
68: 1
69: 1
70: 2
71: 2
72: 2
73: 2
74: 2
75: 2
76: 2
77: 3
78: 3
79: 3
80: 3
81: 3
82: 3
83: 3
84: 0
85: 0
86: 0
87: 0
88: 0
89: 0
90: 0
91: 1
92: 1
93: 1
94: 1
95: 1
96: 1
97: 1
98: 2
99: 2

*/


int main(){
    
    int n = 100;

    int iters[n];

    #pragma omp parallel default(none) shared(n, iters) num_threads(4)
    {
        int tid = omp_get_thread_num();

        #pragma omp for schedule(static, 7)
        for (int i = 0; i < n; i++)
        {
            iters[i] = tid;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("\n%2d: %d", i,iters[i]);
    }
    
    printf("\n");
}