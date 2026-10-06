#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
/**
MPI_Allgather collects data from all processes in a given communicator and stores the data collected in the receive buffer of each process. MPI_Allgather is a collective operation; all processes in the communicator must invoke this routine. Other variants of MPI_Allgather are MPI_Gather, MPI_Gatherv and MPI_Allgatherv. Refer to MPI_Iallgather to see the non-blocking counterpart of MPI_Allgather.


int MPI_Allgather(const void* buffer_send,
                  int count_send,
                  MPI_Datatype datatype_send,
                  void* buffer_recv,
                  int count_recv,
                  MPI_Datatype datatype_recv,
                  MPI_Comm communicator);


 * @brief Illustrates how to use an allgather.
 * @details This application is meant to be run with 3 MPI processes. Every MPI
 * process begins with a value, then every MPI process collects the entirety of
 * the data gathered and prints them. It can be visualised as follows:
 *
 * +-----------+  +-----------+  +-----------+
 * | Process 0 |  | Process 1 |  | Process 2 |
 * +-+-------+-+  +-+-------+-+  +-+-------+-+
 *   | Value |      | Value |      | Value |
 *   |   0   |      |  100  |      |  200  |
 *   +-------+      +-------+      +-------+
 *       |________      |      ________|
 *                |     |     | 
 *             +-----+-----+-----+
 *             |  0  | 100 | 200 |
 *             +-----+-----+-----+
 *             |   Each process  |
 *             +-----------------+
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Get number of processes and check that 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 3)
    {
        printf("This application is meant to be run with 3 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    // Define my value
    int my_value = my_rank * 100;
    printf("Process %d, my value = %d.\n", my_rank, my_value);
 
    int buffer[3];
    MPI_Allgather(&my_value, 1, MPI_INT, buffer, 1, MPI_INT, MPI_COMM_WORLD);
    printf("Values collected on process %d: %d, %d, %d.\n", my_rank, buffer[0], buffer[1], buffer[2]);
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
