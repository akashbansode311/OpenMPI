#!/bin/bash
#SBATCH --job-name=matrix_mult_mpi
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=48
#SBATCH --time=00:05:00
#SBATCH --partition=debug
#SBATCH --output=mpi_%j.out
#SBATCH --error=mpi_%j.err
#SBATCH --mem=64G
#Load the OpenMPI
. /home/apps/spack/share/spack/setup-env.sh
spack load openmpi/n7w3d3y

# Run the program
time mpirun -np 40 ./filename
