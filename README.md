# Compile and Run MPI Program 

## Step 1: Compile

```bash
mpicc hello_mpi.c -o 01.Hello_World.c
```

## Step 2: Run

Run with 4 processes:

```bash
mpirun -np 4 ./01.Hello_World
```

## Expected Output

The order of lines may vary between runs.

```
Hello from process 0 of 4
Hello from process 2 of 4
Hello from process 1 of 4
Hello from process 3 of 4
```
