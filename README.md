# Simple MPI Program: Compile and Run

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
