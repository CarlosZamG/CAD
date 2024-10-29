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
    int my_value = my_rank * 100;
    printf("Proceso %d, mi valor = %d.\n", my_rank, my_value);

    int tag = 0;
    
    // Cada proceso envía su valor usando MPI_Send()
    MPI_Send(&my_value, 1, MPI_INT, root_rank, tag, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        // Recolectamos los valores usando MPI_Recv()
        int buffer_sr[4];
        for (int i = 0; i < size; i++)
        {
            MPI_Recv(buffer_sr + i, 1, MPI_INT, i, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Valores recolectados en el proceso %d usando Send Recv: %d, %d, %d, %d.\n", my_rank, buffer_sr[0], buffer_sr[1], buffer_sr[2], buffer_sr[3]);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}