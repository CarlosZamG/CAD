#include <mpi.h>
#include <stdio.h>

/*
Comando para generar el ejecutable:

mpicc send_recv.c -o send_recv -Wall

Ejecución con mpirun ./send_recv :

Proceso 0 está enviando el número -1 al proceso 1
Proceso 1 recibió el número -1 del proceso 0


Ejecución con mpirun -np 2 ./send_recv :

Proceso 0 está enviando el número -1 al proceso 1
Proceso 1 recibió el número -1 del proceso 0


Ejecución con mpirun -np 1 ./send_recv :

Proceso 0 está enviando el número -1 al proceso 1
[DESKTOP-TLLMVTS:13848] *** An error occurred in MPI_Send
[DESKTOP-TLLMVTS:13848] *** reported by process [1640890369,0]
[DESKTOP-TLLMVTS:13848] *** on communicator MPI_COMM_WORLD
[DESKTOP-TLLMVTS:13848] *** MPI_ERR_RANK: invalid rank
[DESKTOP-TLLMVTS:13848] *** MPI_ERRORS_ARE_FATAL (processes in this communicator will now abort,
[DESKTOP-TLLMVTS:13848] ***    and potentially your MPI job)

(Error de ejecución)

*/

int main(int argc, char** argv) 
{
    // Inicializamos el entorno de MPI
    MPI_Init(&argc, &argv);

    // Obtenemos los identificadores de cada proceso
    int id;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    
    // Obtenemos el tamaño del comunicador
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int number;
    
    //Enviamos y recibimos mensajes según el identificador de cada proceso
    if (id == 0)
    {
        number = -1;
        printf("Proceso 0 está enviando el número %d al proceso 1\n", number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } 
    else if (id == 1) 
    {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso 1 recibió el número %d del proceso 0\n", number);
    }

    MPI_Finalize();
}