#include <mpi.h>
#include <stdio.h>

/*
Comando para generar el ejecutable:

mpicc send_recv.c -o send_recv -Wall

Ejecución con mpirun ./send_recv :

Proceso 1 está esperando recibir un número del proceso 0
^C

Se bloquea porque no recibe ningún mensaje

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
    
    //Estamos esperando recibir un mensaje que nunca se envía
    if (id == 0)
    {
        number = -1;
        //printf("Proceso 0 está enviando el número %d al proceso 1\n", number);
        //MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } 
    else if (id == 1) 
    {   
        printf("Proceso 1 está esperando recibir un número del proceso 0\n");
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso 1 recibió el número %d del proceso 0\n", number);
    }

    MPI_Finalize();
}