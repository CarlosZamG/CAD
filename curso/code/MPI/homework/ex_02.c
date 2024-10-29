#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int process_Rank, size_Of_Cluster;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    double start = MPI_Wtime();
    double time;

    for(int i = 0; i < size_Of_Cluster; i++){
        if(i == process_Rank){
            time = MPI_Wtime() - start;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    printf("\nTime %d: %lf ", process_Rank, time);

    MPI_Finalize();
    return 0;
}