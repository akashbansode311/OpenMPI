#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*Definition-
 * MPI_Scatter dispatches data from a process across all processes in the same communicator. As a blocking operation, the buffer passed can be safely reused as soon as the routine returns. Also, MPI_Scatter is a collective operation; all processes in the communicator must invoke this routine. Other variants of MPI_Scatter are MPI_Scatterv, MPI_Iscatter and MPI_Iscatterv. Refer to MPI_Iscatter to see the non-blocking counterpart of MPI_Scatter.
 *
 *
 *Syntax-
int MPI_Scatter(const void* buffer_send,int count_send,MPI_Datatype datatype_send,void* buffer_recv,int count_recv,MPI_Datatype datatype_recv,int root,MPI_Comm communicator);


 * @brief Illustrates how to use a scatter.
 * @details This application is meant to be run with 4 processes. Process 0 is
 * designed as root and begins with a buffer containing all values, and prints
 * them. It then dispatches these values to all the processes in the same
 * communicator. Other processes just receive the dispatched value meant for
 * them. Finally, everybody prints the value received.
 *
 *                +-----------------------+
 *                |       Process 0       |
 *                +-----+-----+-----+-----+
 *                |  0  | 100 | 200 | 300 |
 *                +-----+-----+-----+-----+
 *                 /      |       |      \
 *                /       |       |       \
 *               /        |       |        \
 *              /         |       |         \
 *             /          |       |          \
 *            /           |       |           \
 * +-----------+ +-----------+ +-----------+ +-----------+
 * | Process 0 | | Process 1 | | Process 2 | | Process 3 |
 * +-+-------+-+ +-+-------+-+ +-+-------+-+ +-+-------+-+
 *   | Value |     | Value |     | Value |     | Value |
 *   |   0   |     |  100  |     |  200  |     |  300  |
 *   +-------+     +-------+     +-------+     +-------+
 *
 *
 ***Parameters**

**buffer_send**

The buffer containing the data to disptach from the root process. For non-root processes, the send parameters like this one are ignored.

**count_send**

The number of elements to send to each process, not the total number of elements in the send buffer. For non-root processes, the send parameters like this one are ignored.

**datatype_send**

The type of one send buffer element. For non-root processes, the send parameters like this one are ignored.

**buffer_recv**

The buffer in which store the data dispatched.

**count_recv**

The number of elements in the receive buffer.

**datatype_recv**

The type of one receive buffer element.

**root**

The rank of the root process, which will dispatch the data to scatter.

**communicator**

The communicator in which the scatter takes place.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get number of processes and check that 4 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("This application is meant to be run with 4 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Determine root's rank
    int root_rank = 0;

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Define my value
    int my_value;

    if(my_rank == root_rank)
    {
        int buffer[4] = {0, 100, 200, 300};
        printf("Values to scatter from process %d: %d, %d, %d, %d.\n", my_rank, buffer[0], buffer[1], buffer[2], buffer[3]);
        MPI_Scatter(buffer, 1, MPI_INT, &my_value, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(NULL, 1, MPI_INT, &my_value, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    }

    printf("Process %d received value = %d.\n", my_rank, my_value);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
