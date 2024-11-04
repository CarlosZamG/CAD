#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc schedule_dynamic.c -fopenmp -o schedule_dynamic -Wall

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
28: 1
29: 1
30: 1
31: 1
32: 1
33: 1
34: 1
35: 0
36: 0
37: 0
38: 0
39: 0
40: 0
41: 0
42: 2
43: 2
44: 2
45: 2
46: 2
47: 2
48: 2
49: 1
50: 1
51: 1
52: 1
53: 1
54: 1
55: 1
56: 3
57: 3
58: 3
59: 3
60: 3
61: 3
62: 3
63: 2
64: 2
65: 2
66: 2
67: 2
68: 2
69: 2
70: 0
71: 0
72: 0
73: 0
74: 0
75: 0
76: 0
77: 2
78: 2
79: 2
80: 2
81: 2
82: 2
83: 2
84: 3
85: 3
86: 3
87: 3
88: 3
89: 3
90: 3
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

        #pragma omp for schedule(dynamic, 7)
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