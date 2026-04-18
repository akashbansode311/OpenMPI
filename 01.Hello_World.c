#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int rank, size;

    // Get process ID
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get total processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello World from process %d out of %d\n", rank, size);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
