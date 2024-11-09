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
Hagamos unas modificaciones al código:

```c
#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel num_threads(4)
    {
        #pragma omp parallel num_threads(4)
        {
            printf("Hola Mundo desde el hilo %d\n", omp_get_thread_num());
        }
    }

}
```
El código tiene la siguiente salida:

```sh
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0
Hola Mundo desde el hilo 0
```



Esto debido a que por defecto el paralelismo anidado está deshabilitado en OpenMP. Entonces tenemos que cada hilo está ejecutando la impresión en consola y como tenemos 4 hilos, la impresión se realiza 4 veces. Ahora una cuestión importante es **¿Por qué todos los hilos nos muestran un ID igual a 0?**. La interfaz de OpenMP nos dice lo siguiente: *Cuando cualquier hilo encuentra una construcción paralela, el hilo crea un equipo de sí mismo y cero o más hilos adicionales y se convierte en el **maestro** del nuevo equipo.* Además también podemos leer lo siguiente: *El hilo maestro es el hilo que encuentra una construcción paralela, crea un equipo y ejecuta el código de esa región como hilo número 0.*

Es decir, al momento de que hilo inicial encuentra la construcción paralela exterior, se crea un equipo con ese hilo (es el hilo maestro) y 3 hilos adicionales para entrar a una región paralela. Entonces cada hilo se encuentra con una región paralela y crea un equipo (que lo incluye a sí mismo como el hilo maestro) para entrar a ejecutar la región paralela interior. Sin embargo, al tener deshabilitado el paralelismo anidado, cada uno de esos equipos consta de un único hilo.

Para poder habilitar el paralelismo anidado tenemos que hacer uso de la función `omp_set_nested()` de la siguiente manera:

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

Al generar el ejecutable con `gcc nested_01.c -fopenmp -o nested_01 -Wall` podemos obtener la siguiente salida:

```sh
Hola Mundo desde el hilo: 2
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 2
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 2
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 3
Hola Mundo desde el hilo: 0
Hola Mundo desde el hilo: 1
Hola Mundo desde el hilo: 2
```

Notemos que ahora la impresión en pantalla se muestra un total de 16 veces, y cada identificador `i = 0, 1, 2, 3` aparece un total de 4 veces.

Ahora hagamos un código que nos muestre cuál es el identificador del hilo padre:

```c
#include <stdio.h>
#include <omp.h>

int main(){

    omp_set_nested(1);

    #pragma omp parallel num_threads(4)
    {
        int tid_p = omp_get_thread_num();

        #pragma omp parallel num_threads(3) shared(tid_p)
        {
            printf("Hola Mundo desde (%d, %d) \n", tid_p, omp_get_thread_num());
        }
    }
}
```

Al crear el ejecutable con `gcc nested_02.c -fopenmp -o nested_02 -Wall` podemos ver que una de las posibles salidas es:

```
Hola Mundo desde (3, 2)
Hola Mundo desde (1, 0)
Hola Mundo desde (3, 0)
Hola Mundo desde (3, 1)
Hola Mundo desde (2, 1)
Hola Mundo desde (0, 0)
Hola Mundo desde (0, 2)
Hola Mundo desde (2, 2)
Hola Mundo desde (2, 0)
Hola Mundo desde (1, 2)
Hola Mundo desde (1, 1)
Hola Mundo desde (0, 1)
```
Notemos que esto es posible debido a que habilitamos el paralelismo anidado con `omp_set_nested(1)`, ya que al quitar esa llamada obtenemos el siguiente resultado:

```
Hola Mundo desde (0, 0)
Hola Mundo desde (3, 0)
Hola Mundo desde (1, 0)
Hola Mundo desde (2, 0)
```

Esto debido a que al llamar a la función `omp_get_thread_num()` dentro de la construcción paralela anidada, cada hilo se ve así mismo como el hilo maestro. 
