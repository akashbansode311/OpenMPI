#!/bin/sh
#SBATCH -N 2                                    # specify number of nodes
#SBATCH --job-name=mpi_hello                    # specify job name
#SBATCH --ntasks-per-node=20                    # specify number of cores per node
#SBATCH --time=01:00:00                         # specify maximum duration of run in hours:minutes:seconds format
#SBATCH --error=job.%J.err                      # specify error file name
#SBATCH --output=job.%J.out             # specify output file name
#SBATCH --partition=cpu             # specify type of resource such as  CPU/GPU/High memory etc.
#SBATCH --reservation=cdac-app

### Load the default MPI module

ulimit -s unlimited

source /home/apps/spack/share/spack/setup-env.sh

spack load openmpi/gtwaa24

### Run the mpi program with mpirun
mpirun -np 2 ./01.Hello_World
