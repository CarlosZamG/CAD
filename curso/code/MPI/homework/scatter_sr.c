#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int process_Rank, size_Of_Comm;
    
    // Arreglo que estamos esparciendo
    int distro_Array[4] = {39, 72, 129, 42};    
    // Número de elementos que estamos enviando a cada proceso
    int send_count = 1;
    // Variable donde vamos a guardar los elementos recibidos usando MPI_Send() y MPI_Recv()
    int send_recv_data;
    // Cantidad de elementos que cada proceso va a recibir
    int recv_count = 1;
    // ID del proceso que va a enviar los datos
    int root_process = 0;
    // Etiqueta para MPI_Send() y MPI_Recv()
    int tag = 0;
    // Variable donde vamos a guardar los elementos recibidos usando MPI_Scatter()
    int scattered_Data;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Comm);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    //Hacemos el envío distribuido usando MPI_Send() y MPI_Recv()

    // El proceso con ID igual a root_process envía los datos a los procesos
    if (process_Rank == root_process)
    {
        for (int i = 0; i < size_Of_Comm; i++)
        {
            MPI_Send(distro_Array + i, send_count, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
    }

    // Los procesos reciben los datos correspondientes
    MPI_Recv(&send_recv_data, recv_count, MPI_INT, root_process, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    printf("Proceso %d de %d ha recibido: %d usando Send Recv\n", process_Rank, size_Of_Comm, send_recv_data);

    // Hacemos el envío distribuido usando MPI_Scatter()
    MPI_Scatter(distro_Array, send_count, MPI_INT, &scattered_Data, recv_count, MPI_INT, root_process, MPI_COMM_WORLD);

    printf("Proceso %d de %d ha recibido: %d usando Scatter\n", process_Rank, size_Of_Comm, scattered_Data);
    
    MPI_Finalize();
    return 0;
}