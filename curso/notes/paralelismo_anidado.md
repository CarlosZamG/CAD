# Paralelismo anidado

Una pregunta muy natural que podemos hacernos al trabajar con OpenMP es **¿Qué sucede al crear una región paralela dentro de otra?**.

Pues intentemos hacerlo en código:

```c
#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo\n");
        }
    }

}
```

El comportamiento que esperaríamos de OpenMP sería que la pantalla nos mostrara el mensaje `Hola Mundo` un total de 16 veces, ya que estamos indicando que se deben de lanzar 4 hilos, y cada uno de esos 4 hilos debe lanzar otros 4 hilos ($4\times 4 = 16$). Sin embargo, la realidad parece ser muy distinta: 


```sh
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
```

Esto debido a que por defecto el paralelismo anidado está deshabilitado en OpenMP, para poder habilitar el paralelismo anidado tenemos que hacer uso de la función `omp_set_nested()` de la siguiente manera:

```c
#include <stdio.h>
#include <omp.h>

int main(){

    omp_set_nested(1);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo desde el hilo: %d\n", omp_get_thread_num());
        }
    }

}


```