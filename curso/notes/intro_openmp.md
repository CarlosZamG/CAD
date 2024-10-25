# Introducción a OpenMP

**OpenMP** (**Open M**ulti-**P**rocessing) es una **interfaz** de programación de aplicaciones (***API***) que permite convertir programas secuenciales en paralelo utilizando **hilos**, enfocado en **memoria compartida**. El término interfaz nos indica que OpenMP especifica el **qué** es lo que se tiene que hacer, sin embargo pueden haber distintas implementaciones de OpenMP que varien en el **cómo**.

Al usar OpenMP, el **compilador es responsable** de lidiar con los detalles *engorrosos* de la generación, inicialización y finalización de hilos; debido a esto, se dice que al usar OpenMP estamos haciendo paralelismo **implícito**. La desventaja es que se sacrifica el control del programador para darle comodidad.

Hagamos nuestro primer **Hola Mundo en paralelo** con OpenMP:

```c
#include <stdio.h>

int main(){

    #pragma omp parallel
    {
        printf("Hola Mundo\n");
    }

}
```
Notemos que su diferencia de un Hola Mundo convencional es que estamos agregando una línea nueva:

```c
#pragma omp parallel
```

**¿Qué es esto?**

Es una **directiva** pragma, estas directivas son específicas de la máquina o del sistema operativo, y permiten que cada compilador ofrezca características específicas de la máquina o el **S.O** a la vez que mantienen la compatibilidad total con los lenguajes C.

Veamos la salida al compilar con `gcc hello.c -o hello` y ejecutar con `./hello`:

```sh
Hola Mundo
```

Parece un Hola Mundo normal y corriente ¿cierto? Lo que sucede es que para activar el reconocimiento de las directivas tenemos que compilar agregando la opción `-fopenmp` de la siguiente manera: `gcc hello.c -o hello -fopenmp`. Esto nos produce una salida similar a la siguiente:

```sh
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
Hola Mundo
```

Ahora lo que sucede es que la línea `#pragma omp parallel` le indica al compilador que debe lanzar múltiples hilos, y cada uno de esos hilos deberá ejecutar el bloque de instrucciones siguiente.

**¿Por qué el programa no fallaba anteriormente cuando no habíamos incluido la opción `-fopenmp`?**

Esto se debe a que el la directiva pragma es ignorada si el compilador no la reconoce. El hecho de que el compilador no reconozca la directiva de OpenMP puede darse en ciertos casos:

1. El compilador no soporta OpenMP.

2. Se cometió un error de escritura (por ejemplo: se escribió `#pragma openmp parallel`).

3. El archivo fuente no se compiló con la opción correcta para reconocer las directivas.

Así que nuestro código puede compilar sin necesidad de habilitar OpenMP.

Por defecto, OpenMP utilizará tantos hilos como el número de **cores** disponibles en el sistema. La cantidad de hilos puede ser modificada de varias maneras:

1. **Universalmente**: Podemos modificar la variable de entorno `OMP_NUM_THREADS`, lo cuál afectará todos los programas que usen OpenMP.

2. A **nivel de programa** utilizando la función `omp_set_num_threads()`.

3. A **nivel de pragma** con la cláusula `num_threads()`.

Veamos un ejemplo en código:

```c
#include <stdio.h>
#include <omp.h>

int main(){
    
    printf("\nEl número de hilos al inicio es: %d", omp_get_num_threads());

    #pragma omp parallel
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    omp_set_num_threads(7);

    #pragma omp parallel
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    #pragma omp parallel num_threads(4)
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    #pragma omp parallel
    {
        printf("\nHola Mundo. ");
        printf("El número de hilos dentro de esta región es: %d", omp_get_num_threads());
    }

    printf("\nEl número de hilos al final es: %d\n", omp_get_num_threads());
}
```
Notemos dos diferencias importantes de este código con nuestro Hola Mundo paralelo: La primera es que estamos incluyendo el archivo de cabecera `omp.h`. La segunda es que estamos utilizando múltiples veces la función `omp_get_num_threads()`, que nos regresa el número de hilos activos en una región. La salida es la siguiente:

```sh
El número de hilos al inicio es: 1
Hola Mundo.
Hola Mundo. El número de hilos dentro de esta región es: 16El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 16
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 4
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
Hola Mundo. El número de hilos dentro de esta región es: 7
El número de hilos al final es: 1
```

Lo que sucede es que cuando llamamos a `omp_get_num_threads()` dentro de una parte secuencial, nos devuelve el valor de `1`, tal como podemos ver al imprimir el número de hilos al inicio y al final.

La primera región paralela lanza 16 hilos debido a que toma el valor de la varible de entorno `OMP_NUM_THREADS`. Después de ejecutar dicha región, usamos `omp_set_num_threads(7)` para establecer el número de hilos a nivel de programa, lo que afectará a las siguientes regiones paralelas que serán creadas a lo largo del programa. Sin embargo, en la 3ra región estamos utilizando la cláusula `num_threads()` para espeficar que dicha región deberá lanzar 4 hilos.

## Entendiendo la directiva `#pragma omp parallel`

Cuando escribimos 

```c
#pragma omp parallel
{
    // Instrucciones
}
```

Estamos creando una **construcción paralela**: es la combinación de una directiva `pragma` de OpenMP con el bloque de instrucciones que le siguen, mientras que una **región paralela** es la sucesión dinámica de instrucciones producida durante la ejecución de una construcción paralela. El hilo que encuentra la región paralela se llama *hilo maestro* y se encarga de crear los hilos adicionales y está a cargo de la ejecución general. Al conjunto de hilos que están activos dentro de una región paralela se denomina *equipo* de hilos.

Un programa que usa OpenMP siempre empieza ejecutándose en modo serial. El hilo que ejecuta la parte serial de la aplicación es el *hilo maestro* y se mantiene en ejecución a lo largo de todo el tiempo de vida del proceso. En algún punto de la ejecución, se crean hilos **adicionales**. El ***cómo*** y el ***cuándo*** dependen de la implementación, pero se debe garantizar que los hilos estarán disponibles cuando se llegue a una región paralela, entonces el programa se ejecutará en paralelo. Al finalizar la región paralela, el hilo maestro continuará la ejecución por sí solo en serial hasta llegar a la siguiente región paralela. Este modelo es llamado *Bifurcar-Unir* (***Fork-Join*** en inglés).

Consideraciones importantes:

1. El hilo maestro se incluye en el número total de hilos activos en la región paralela.

2. Al final de la región paralela se sincronizan todos los hilos, es decir, la ejecución de las instrucciones restantes solamente continua si todos los hilos han terminado de ejecutar las instrucciones de la región paralela 



## Referencias
1. [Directivas pragma y las palabras clave `__pragma` y `_Pragma`](https://learn.microsoft.com/es-es/cpp/preprocessor/pragma-directives-and-the-pragma-keyword?view=msvc-170)

2. Using OpenMP-The Next Step (Ruud van der Pas, Eric Stotzer, and Christian Terboven).
