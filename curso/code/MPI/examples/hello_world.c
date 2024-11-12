#include <mpi.h>
#include <stdio.h>

/*
Comando para generar el ejecutable:

mpicc hello_world.c -o hello_world -Wall

Comando para correrlo:

mpirun ./hello_world

Posible salida:

Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 5 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 6 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 4 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 0 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 1 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 2 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 7 de un total de 8 procesos
Hola mundo desde el proceso DESKTOP-TLLMVTS, ID 3 de un total de 8 procesos

*/

int main(int argc, char** argv) {
    // Inicializamos el entorno de MPI
    MPI_Init(&argc, &argv);

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