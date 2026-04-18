#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int data;
    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc, &argv);  // Start MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get process ID

    if (rank == 0)
    {
        data = 100;

        // Non-blocking send
        MPI_Isend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);

        printf("Process 0 started sending data: %d\n", data);

        // Wait until send is complete
        MPI_Wait(&request, &status);

        printf("Process 0 finished sending\n");
    }
    else if (rank == 1)
    {
        // Non-blocking receive
        MPI_Irecv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

        printf("Process 1 is doing some work while waiting...\n");

        // Wait until receive is complete
        MPI_Wait(&request, &status);

        printf("Process 1 received data: %d\n", data);
    }

    MPI_Finalize();  // End MPI
    return 0;
}
