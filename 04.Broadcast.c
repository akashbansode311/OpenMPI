#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**Definition-
 *
 * broadcasts a message from a process to all other processes in the same communicator. This is a collective operation; it must be called by all processes in the communicator.
 *
 * Syntax-
 * int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int emitter_rank, MPI_Comm communicator);
 *
 *
 * @brief Illustrates how to broadcast a message.
 * @details This code picks a process as the broadcast root, and makes it
 * broadcast a specific value. Other processes participate to the broadcast as
 * receivers. These processes then print the value they received via the 
 * broadcast.
 *
 * ## Parameters
 *
 * **buffer**
 *
 * The buffer from which load the data to broadcast if the calling MPI process is the emitter, or the buffer in which store the data broadcasted is the calling MPI process is a receiver.
 *
 * **count**
 *
 * The number of elements in the buffer broadcasted.
 *
 * **datatype**
 *
 * The type of an element in the buffer broadcasted.
 *
 * **emitter_rank**
 *
 * The rank of the MPI process that broadcasts the data, all other processes receive the data broadcasted.
 *
 * **communicator**
 *
 * The communicator in which the broadcast takes place.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get my rank in the communicator
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Determine the rank of the broadcast emitter process
    int broadcast_root = 0;

    int buffer;
    if(my_rank == broadcast_root)
    {
        buffer = 12345;
        printf("[MPI process %d] I am the broadcast root, and send value %d.\n", my_rank, buffer);
    }
    MPI_Bcast(&buffer, 1, MPI_INT, broadcast_root, MPI_COMM_WORLD);
    if(my_rank != broadcast_root)
    {
        printf("[MPI process %d] I am a broadcast receiver, and obtained value %d.\n", my_rank, buffer);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}


