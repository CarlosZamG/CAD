# Bucles y Paralelismo (con OpenMP)

Consideremos el siguiente código:

```c
#include <stdio.h>
#include <omp.h>

int main(){
    
    int n = 6;

    #pragma omp parallel shared(n) num_threads(4)
    {
        int tid = omp_get_thread_num();

        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", tid, i);
        }
    }
}
```

Lo que estamos haciendo es lanzar 4 hilos y cada hilo ejecutará un bucle `for` con 6 iteraciones, una posible salida de este código es la siguiente:

```sh
El hilo 1 está haciendo la iteración 0
El hilo 1 está haciendo la iteración 1
El hilo 1 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 0
El hilo 3 está haciendo la iteración 0
El hilo 3 está haciendo la iteración 1
El hilo 1 está haciendo la iteración 3
El hilo 3 está haciendo la iteración 2
El hilo 3 está haciendo la iteración 3
El hilo 3 está haciendo la iteración 4
El hilo 3 está haciendo la iteración 5
El hilo 1 está haciendo la iteración 4
El hilo 1 está haciendo la iteración 5
El hilo 2 está haciendo la iteración 0
El hilo 2 está haciendo la iteración 1
El hilo 2 está haciendo la iteración 2
El hilo 2 está haciendo la iteración 3
El hilo 2 está haciendo la iteración 4
El hilo 2 está haciendo la iteración 5
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 5
```

Podemos observar que se realizan un total de 24 impresiones en consola. Algo importante que debemos considerar es que cada hilo está ejecutando el bucle `for` de forma secuencial, es decir, la iteración `i` para un hilo `k` siempre ocurrirá antes que la iteración `j` de ese mismo hilo `k` para cualquier `j > i` y para cualquier hilo.

**¿Cómo podríamos hacer un bucle de tal forma que los hilos se repartan sus iteraciones**. Es decir, si tenemos que realizar un bucle de 100 iteraciones y tenemos 4 hilos, queremos que cada hilo haga algunas de esas 100 iteraciones. Esto puede ser útil cuando las iteraciones no dependen de los resultados obtenidos en iteraciones anteriores, por ejemplo, al momento de sumar vectores.

Para poder realizar esto, OpenMP nos da la directiva `#pragma omp for`, que se encarga de distribuir (repartir) las iteraciones de un bucle `for` a un equipo de hilos:

```c
#include <stdio.h>
#include <omp.h>

int main(){
    
    int n = 25;

    #pragma omp parallel shared(n) num_threads(4)
    {
        int tid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", tid, i);
        }
    }
}
```

Al ejecutar el código anterior, podemos obtener una salida similar a esta:

```sh
El hilo 2 está haciendo la iteración 13
El hilo 2 está haciendo la iteración 14
El hilo 2 está haciendo la iteración 15
El hilo 2 está haciendo la iteración 16
El hilo 2 está haciendo la iteración 17
El hilo 2 está haciendo la iteración 18
El hilo 1 está haciendo la iteración 7
El hilo 1 está haciendo la iteración 8
El hilo 1 está haciendo la iteración 9
El hilo 1 está haciendo la iteración 10
El hilo 1 está haciendo la iteración 11
El hilo 1 está haciendo la iteración 12
El hilo 3 está haciendo la iteración 19
El hilo 3 está haciendo la iteración 20
El hilo 3 está haciendo la iteración 21
El hilo 3 está haciendo la iteración 22
El hilo 3 está haciendo la iteración 23
El hilo 3 está haciendo la iteración 24
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 5
El hilo 0 está haciendo la iteración 6
```

Aunque por supuesto que el resultado puede cambiar dependiendo de la ejecución debido al no determinismo:

```sh
El hilo 1 está haciendo la iteración 7
El hilo 1 está haciendo la iteración 8
El hilo 1 está haciendo la iteración 9
El hilo 1 está haciendo la iteración 10
El hilo 1 está haciendo la iteración 11
El hilo 1 está haciendo la iteración 12
El hilo 3 está haciendo la iteración 19
El hilo 3 está haciendo la iteración 20
El hilo 3 está haciendo la iteración 21
El hilo 3 está haciendo la iteración 22
El hilo 3 está haciendo la iteración 23
El hilo 3 está haciendo la iteración 24
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 2 está haciendo la iteración 13
El hilo 2 está haciendo la iteración 14
El hilo 2 está haciendo la iteración 15
El hilo 2 está haciendo la iteración 16
El hilo 2 está haciendo la iteración 17
El hilo 2 está haciendo la iteración 18
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 5
El hilo 0 está haciendo la iteración 6
```

En el código anterior estamos ejecutando un bucle `for` con 25 iteraciones, sin embargo dichas iteraciones son repartidas entre los 4 hilos. Podemos ver que en ambas ejecuciones al hilo `0` le tocan las iteraciones `0 - 6`, al hilo `1` le tocan las iteraciones `7 - 12`, al hilo `2` le tocan de la `13 - 18` y al hilo `3` le tocan de la `19 - 24`

OpenMP nos proporciona la directiva `pragma omp parallel for` para reducir las líneas de código. 

Los siguientes códigos son equivalentes: 

```c
#pragma omp parallel for
for(...){

}
```

```c
#pragma omp parallel
#pragma omp for
for(...){

}
```

Algo importante que debemos notar es que cada que utilicemos `#pragma omp parallel for`, al momento de ejecutar el código se tomará como una construcción paralela, por lo que si consideramos el siguiente código:

```c
#include <stdio.h>
#include <omp.h>

int main(){
    
    int n = 5;

    omp_set_num_threads(4);

    #pragma omp parallel default(none) shared(n)
    {
        #pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            printf("El hilo %d está haciendo la iteración %d\n", omp_get_thread_num(), i);
        }
    }
}
```
Es como si estuvieramos trabajando con paralelismo anidado, por lo que tendremos una salida similar a la siguiente:

```
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
El hilo 0 está haciendo la iteración 0
El hilo 0 está haciendo la iteración 1
El hilo 0 está haciendo la iteración 2
El hilo 0 está haciendo la iteración 3
El hilo 0 está haciendo la iteración 4
```

Lo que sucede es que primero estamos lanzando 4 hilos para que ejecuten una región paralela, cada uno de esos 4 hilos se encuentra con una 2da región paralela, por lo que crea su propio equipo para ejecutarla. Dicho equipo lo incluye a sí mismo como el hilo **maestro**, es decir que tiene **ID** igual a 0. Sin embargo, debido a que por defecto el paralelismo anidado está deshabilitado en OpenMP, todos los equipos que crean cada uno de los hilos para esa 2da región paralela constan de un único hilo que se ve así mismo como el hilo **maestro** por esta razón, todas las iteraciones indican que son realizadas por el hilo `0` 

## Schedule

La forma en la que OpenMP asigna las iteraciones que corresponden a cada hilo puede hacerse de diferentes formas, esto debido a que la forma en la que se reparten las iteraciones puede afectar el rendimiento. Para especificar una forma específica de repartir iteraciones ocupamos la cláusula `schedule`. En caso de no especificar dicha cláusula, el compilador elige entre los diferentes tipos de esquemas. Todos los esquemas pueden tener un parámetro llamado `chunk_size`. Tales esquemas son los siguientes:

- `static`: En este esquema se dividen las iteraciones del bucle en grupos del tamaño de `chunk_size` y cada grupo es asignado a los hilos de forma rotatoria según el identificador del hilo.

- `dynamic`: Este esquema imita el funcionamiento de un balanceador de carga dinámico, donde se asignan grupos del tamaño de `chunk_size` a los hilos por orden de llegada. Un hilo ejecuta un grupo, luego solicita otro, y así sucesivamente.

- `guided`: Supongamos que el número de hilos es igual a $p$. El esquema guiado intenta ofrecer flexibilidad mediante el uso de grupos de tamaño variable que se reducen con el tiempo para permitir el equilibrio de carga. El tamaño del grupo que se entrega en cada nueva solicitud es igual a la cantidad de iteraciones sin asignar dividida por $p$. El `chunk_size` especifica un límite inferior para el tamaño de un grupo. Si no se especifica `chunk_size`, el valor predeterminado es 1. Los tamaños de los grupos se pueden determinar mediante la fórmula:

$$\text{tam\_grupo} = \min(\text{iteraciones\_restantes}, \max(\text{chunk\_size}, \lceil{\frac{\text{iteraciones\_restantes}}{p}})) 
$$