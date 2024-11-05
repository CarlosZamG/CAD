#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc schedule_dynamic.c -fopenmp -o schedule_dynamic -Wall

Posible salida:

 0: 1
 1: 1
 2: 1
 3: 1
 4: 1
 5: 1
 6: 1
 7: 2
 8: 2
 9: 2
10: 2
11: 2
12: 2
13: 2
14: 0
15: 0
16: 0
17: 0
18: 0
19: 0
20: 0
21: 0
22: 0
23: 0
24: 0
25: 0
26: 0
27: 0
28: 1
29: 1
30: 1
31: 1
32: 1
33: 1
34: 1
35: 2
36: 2
37: 2
38: 2
39: 2
40: 2
41: 2
42: 0
43: 0
44: 0
45: 0
46: 0
47: 0
48: 0
49: 1
50: 1
51: 1
52: 1
53: 1
54: 1
55: 1
56: 2
57: 2
58: 2
59: 2
60: 2
61: 2
62: 2
63: 0
64: 0
65: 0
66: 0
67: 0
68: 0
69: 0
70: 1
71: 1
72: 1
73: 1
74: 1
75: 1
76: 1
77: 2
78: 2
79: 2
80: 2
81: 2
82: 2
83: 2
84: 0
85: 0
86: 0
87: 0
88: 0
89: 0
90: 0
91: 2
92: 2
93: 2
94: 2
95: 2
96: 2
97: 2
98: 3
99: 3

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