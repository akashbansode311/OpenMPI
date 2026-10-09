#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 8000

/* Multiply 'rows' rows of A with B and store in C.
 * Same triple loop as the OpenMP program (i-j-k order). */
void matmul(double *A, double *B, double *C, int rows) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < N; j++) {
            C[i*N + j] = 0.0;
            for (int k = 0; k < N; k++)
                C[i*N + j] += A[i*N + k] * B[k*N + j];
        }
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* N must divide evenly among the processes */
    if (N % size != 0) {
        if (rank == 0) printf("N must be divisible by number of processes\n");
        MPI_Finalize();
        return 1;
    }
    int rows = N / size;            /* rows handled by each process */

    /* Every process needs B and its own part of A and C */
    double *B       = malloc(N * N * sizeof(double));
    double *local_A = malloc(rows * N * sizeof(double));
    double *local_C = malloc(rows * N * sizeof(double));

    /* Only process 0 holds the full A and C */
    double *A = NULL, *C = NULL;
    if (rank == 0) {
        A = malloc(N * N * sizeof(double));
        C = malloc(N * N * sizeof(double));
        for (int i = 0; i < N * N; i++) {
            A[i] = 1.0;
            B[i] = 1.0;
        }
    }

    /* ---------- MPI run ---------- */
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    /* 1. Send all of B to everyone */
    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* 2. Give each process its rows of A */
    MPI_Scatter(A, rows * N, MPI_DOUBLE,
                local_A, rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* 3. Each process multiplies its rows */
    matmul(local_A, B, local_C, rows);

    /* 4. Collect the rows of C on process 0 */
    MPI_Gather(local_C, rows * N, MPI_DOUBLE,
               C, rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    /* ---------- Results ---------- */
    if (rank == 0) {
        printf("MPI Time:    %f sec (%d processes)\n", end - start, size);
        printf("Check: C[0][0] = %.0f (expected %d)\n", C[0], N);
    }

    free(B);
    free(local_A);
    free(local_C);
    if (rank == 0) {
        free(A);
        free(C);
    }

    MPI_Finalize();
    return 0;
}
