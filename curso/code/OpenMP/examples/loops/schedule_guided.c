#include <stdio.h>
#include <omp.h>

/*
Comando para generar el ejecutable:

gcc schedule_guided.c -fopenmp -o schedule_guided -Wall

Posible salida:


 0: 0
 1: 0
 2: 0
 3: 0
 4: 0
 5: 0
 6: 0
 7: 0
 8: 0
 9: 0
10: 0
11: 0
12: 0
13: 0
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
25: 1
26: 1
27: 1
28: 1
29: 1
30: 1
31: 1
32: 1
33: 1
34: 1
35: 1
36: 1
37: 1
38: 1
39: 1
40: 1
41: 1
42: 1
43: 1
44: 2
45: 2
46: 2
47: 2
48: 2
49: 2
50: 2
51: 2
52: 2
53: 2
54: 2
55: 2
56: 2
57: 2
58: 2
59: 2
60: 2
61: 2
62: 2
63: 2
64: 2
65: 2
66: 2
67: 2
68: 2
69: 0
70: 0
71: 0
72: 0
73: 0
74: 0
75: 0
76: 0
77: 1
78: 1
79: 1
80: 1
81: 1
82: 1
83: 1
84: 0
85: 0
86: 0
87: 0
88: 0
89: 0
90: 0
91: 0
92: 0
93: 0
94: 0
95: 0
96: 0
97: 0
98: 1
99: 1

*/


int main(){
    
    int n = 100;

    int iters[n];

    #pragma omp parallel default(none) shared(n, iters) num_threads(4)
    {
        int tid = omp_get_thread_num();

        #pragma omp for schedule(guided, 7)
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