# Memoria

En algún momento en el uso de la computadoras llegó el momento de realizar **Multiprogramación**: Se tienen múltiples procesos listos para ejecutarse en simultáneo y el sistema operativo debe de intercambiar entre la ejecución de ellos. Hacer esto incrementaba el **uso efectivo** de la CPU. Sin embargo, esta forma de trabajar presenta un problema: Si tenemos varios procesos ejecutándose de forma concurrente, necesitamos **protección**: no queremos que un proceso pueda leer o escribir la memoria de otro proceso.

Para facilitarle la vida a los usuarios se decidió que el sistema operativo crearía una abstracción de la memoria física: el **espacio de direcciones**, y es la visión que tiene un proceso de la memoria del sistema. El espacio de direcciones de un proceso contiene todo el estado de memoria del programa en ejecución. Por ejemplo, el código del programa (las instrucciones) tiene que estar en algún lugar de la memoria, y por lo tanto están en el espacio de direcciones. El programa, mientras se ejecuta, utiliza una pila (***stack*** en inglés) para llevar un control de dónde se encuentra en la cadena de llamadas de función, así como para asignar variables locales y pasar parámetros y valores de retorno a y desde rutinas. Finalmente, el ***heap*** se utiliza para la memoria asignada dinámicamente y administrada por el usuario, como la que puede recibir de una llamada a la función `malloc()` en C o `new` en algunos lenguajes orientados a objetos como C++ o Java. Se guardan más cosas en el espacio de direcciones, pero para simplificar podemos enfocarnos en esos 3 componentes principales: **Código**, **Heap** y **Stack**.

Debido a que el código es estático y por lo tanto es fácil de buscar en memoria, podemos colocarlo al principio en el espacio de direcciones y sabemos que no necesitará más memoria durante la ejecución del programa. Las regiones del *Heap* y *Stack* pueden crecer y encogerse mientras se ejecuta el programa. Se tiene la convención de colocar el *Heap* en la parte superior justo después del código y crece hacia abajo (por ejemplo, cuando se solicita más memoria con `malloc()`), mientras que el *Stack* se coloca en la parte inferior para que pueda crecer hacia arriba (por ejemplo, cuando se llama a una función). De esta forma permitimos el crecimiento de ambas regiones, creciendo en direcciones opuestas. Sin embargo, podemos no seguir la convención y organizar el espacio de direcciones de una forma diferente. De hecho, al momento de trabajar múltiples hilos en un espacio de direcciones, esta forma simple de dividir el espacio de direcciones deja de funcionar.

Una consideración importante es que al describir el espacio de direcciones, estamos describiendo la **abstracción** que el sistema operativo le da al programa. Lo que hace el sistema operativo es **virtualizar** la memoria: cuando un proceso ejecuta una operación en una dirección (**virtual**), el sistema operativo en conjunto con el hardware se encargan de que dicha operación se haga en la dirección física correcta.

Cuando imprimimos un la dirección de un puntero en un programa en C, en realidad estamos imprimiendo la **dirección virtual**. Consideremos el siguiente código:

```c
#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Dirección del código: %p\n", main);
    int n = 0;
    printf("Dirección del Stack: %p\n", &n);
    printf("Dirección del Heap: %p\n", malloc(1));

    return 0;
}
```
Con la siguiente salida:

```sh
Dirección del código: 0x55759a6b5189
Dirección del Stack: 0x7fff4a0df7c4
Dirección del Heap: 0x55759bff16b0
```

Podemos ver que el valor numérico hexadecimal de la dirección del código es menor que el correspondiente a la dirección del *Heap* que a su vez es menor que el correspondiente a la dirección del *Stack*. Sin embargo siempre debemos tener en mente que cualquier dirección vista desde el punto de vista del programador de C son direcciones **virtuales**. Solamente el sistema operativo y el hardware conocen en qué parte de la memoria **física** se encuentran las instrucciones y los datos.  