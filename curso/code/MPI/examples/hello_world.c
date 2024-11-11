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