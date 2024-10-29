#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int process_Rank, size_Of_Comm;
    int distro_Array[4] = {39, 72, 129, 42};
    int scattered_Data;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Comm);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    MPI_Scatter(distro_Array,      // Dirección del arreglo que estamos esparciendo
                1,                  // Número de elementos que estamos enviando a cada proceso
                MPI_INT,            // Tipo de dato de MPI del arreglo que estamos recibiendo
                &scattered_Data,    // Dirección donde vamos a guardar los elementos recibidos
                1,                  // Cantidad de elementos que cada proceso va a recibir
                MPI_INT,            // Tipo de dato de MPI del arreglo que va a recibir
                0,                  // ID del proceso que va a enviar los datos
                MPI_COMM_WORLD      //Comunicador de MPI
                );

    printf("Process %d of %d has received: %d \n", process_Rank, size_Of_Comm, scattered_Data);
    //printf("&distro_Array: %p |distro_Array: %p | &distro_Array[0]: %p\n", &distro_Array, distro_Array, &distro_Array[0]);
    

    MPI_Finalize();
    return 0;
}