# Simple MPI Program: Compile and Run

## Source file: `hello_mpi.c`

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello from process %d of %d\n", rank, size);

    MPI_Finalize();
    return 0;
}
```

## Step 1: Compile

```bash
mpicc hello_mpi.c -o hello_mpi
```

## Step 2: Run

Run with 4 processes:

```bash
mpirun -np 4 ./hello_mpi
```

## Expected Output

The order of lines may vary between runs.

```
Hello from process 0 of 4
Hello from process 2 of 4
Hello from process 1 of 4
Hello from process 3 of 4
```

## Notes

- If `mpirun` is not available, use `mpiexec -n 4 ./hello_mpi`.
- To run with more processes than available cores (OpenMPI):

  ```bash
  mpirun --oversubscribe -np 8 ./hello_mpi
  ```
