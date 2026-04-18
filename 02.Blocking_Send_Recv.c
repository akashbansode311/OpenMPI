#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int data;

    MPI_Init(&argc, &argv);  // Start MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get process ID

    if (rank == 0)
    {
        // Process 0 sends data
        data = 100;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data: %d\n", data);
    }
    else if (rank == 1)
    {
        // Process 1 receives data
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: %d\n", data);
    }

    MPI_Finalize();  // End MPI
    return 0;
}
