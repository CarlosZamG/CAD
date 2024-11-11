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

Con `MPI_Init()`, se inicializa el entorno de ejecución de MPI, es decir, se construyen todas las variables internas y globales de MPI. Por ejemplo, se forma un comunicador en torno a todos los procesos que se generaron y se asignan identificadores únicos a cada proceso. Por ahora, no le pasaremos ningún argumento en realidad a `MPI_Init()`.

Un comunicador es un grupo de procesos al que se asocia un contexto de comunicación. Dicho contexto no es más que el ámbito en el que se envían los mensajes. 