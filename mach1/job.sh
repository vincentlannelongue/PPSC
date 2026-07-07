#!/bin/bash
#
#SBATCH --job-name=PPSC
#SBATCH --output=out.log
#
#SBATCH --nodes 1
#SBATCH --ntasks 64
#SBATCH --ntasks-per-node=64
#SBATCH --ntasks-per-core=1
#SBATCH --partition=CPU
#SBATCH --qos=normal
# SBATCH --exclude='node-101,node-102,node-103,node-104,node-105,node-106,node-120'

# Load module
module load cimlibxx

# Set environment variable for OpenMP
export OMP_PROC_BIND=true
export OMPI_MCA_btl=^openib

make comp

echo "Running mach1..."

for n in 1 1000 1000000 1000000000
do
    for procs in 1 2 4 8 16 32
    do
        echo "Running with n=${n} and np=${procs}..."
        mpirun -n ${procs} ./main ${n}
    done
done