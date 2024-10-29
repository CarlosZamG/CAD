#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Obtenemos el número de procesos y verificamos que esten corriendo 4
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Se supone que esta aplicación debe correr con 4 procesos de MPI.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Establecemos el ID del proceso que va a recibir los valores
    int root_rank = 0;

    // Obtenemos el ID para cada proceso
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Creamos los valores para cada proceso
    int my_value = (my_rank + 1) * 100;
    printf("Proceso %d, mi valor = %d.\n", my_rank, my_value);

    if(my_rank == root_rank)
    {
        int buffer[4];
        MPI_Gather(&my_value, 1, MPI_INT, buffer, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
        printf("Valores recolectados en el proceso %d: %d, %d, %d, %d.\n", my_rank, buffer[0], buffer[1], buffer[2], buffer[3]);
    }
    else
    {
        MPI_Gather(&my_value, 1, MPI_INT, NULL, 0, MPI_INT, root_rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}