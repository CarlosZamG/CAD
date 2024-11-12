# Introducción a MPI

MPI es un estándar utilizado para la programación paralelela mediante el paso de mensajes. El modelo de programación paralela mediante el paso de mensajes se utiliza en computadoras 

Consideremos el siguiente código:
```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Inicializamos el entorno de MPI
    MPI_Init(NULL, NULL);

    // Obtenemos el número de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtenenmos el ID del proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Obtenemos el nombre del proceso
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Cada proceso imprime el mensaje de Hola Mundo correspondiente 
    printf("Hola mundo desde el proceso %s, ID %d de un total de %d procesos\n", processor_name, world_rank, world_size);

    // Finalizamos el entorno de MPI.
    MPI_Finalize();
}
```

Lo primero que debemos hacer para construir un programa utilizando MPI es incluir los archivos de cabecera con `#include <mpi.h>`. Después debemos inicializar el entorno con:

```c
int MPI_Init(int* argc, char*** argv)
```

Con `MPI_Init()`, se inicializa el entorno de ejecución de MPI, es decir, se construyen todas las variables internas y globales de MPI. Por ejemplo, se forma un comunicador en torno a todos los procesos que se generaron y se asignan identificadores únicos a cada proceso. Por ahora, no le pasaremos ningún argumento real a `MPI_Init()`.

Un comunicador es un grupo de procesos al que se asocia un contexto de comunicación. Dicho contexto no es más que el ámbito en el que se envían los mensajes.

Después llamamos dos muy utilizadas en los programas hechos con MPI:

```c
int MPI_Comm_size(MPI_Comm comm, int *size)
```

Esta función nos devuelve el tamaño del comunicador, es decir, cuántos procesos tiene el grupo que forma al comunicador. En nuestro ejemplo utilizamos `MPI_COMM_WORLD`, que es el comunicador por defecto proporcinado por MPI que contiene todos los procesos disponibles para usar.

También usamos la siguiente función:

```c
int MPI_Comm_rank(MPI_Comm comm, int *rank)
```

Esta función nos devuelve el identificador de un proceso en un comunicador. A cada proceso dentro de un comunicador se le asigna un identificador de forma ascendente empezando en 0. Estos identificadores nos serán útiles al momento de enviar y recibir mensajes.

Otra función que es parte de nuestro programa, sin embargo es menos utilizada es:

```c
int MPI_Get_processor_name(char *name, int *resultlen)
```

Se encarga de obtener el nombre del procesador que está ejecuando el proceso.

Por último, tenemos que llamar a la función `MPI_Finalize()`, que se encarga de finalizar el entorno MPI. Una vez que llamamos a esta función, **ninguna otra función de MPI puede ser llamada** salvo algunas excepciones como `MPI_Get_version()`, `MPI_Initialized()` y `MPI_Finalized()`. Todos los procesos deben llamar a esta función antes de terminar, puede ser que los procesos sigan existiendo, pero no pueden realizar llamadas de funciones de MPI. En el momento en que el último proceso llama a `MPI_Finalize()`, todos los envíos pendientes deben coincidir con una recepción, y todas las recepciones pendientes deben coincidir con un envío.

Para compilar nuestro programa podemos usar el comando `mpicc hello_world.c -o hello_world -Wall` y para correrlo podemos usar `mpirun ./hello_world`.

## Paso de mensajes