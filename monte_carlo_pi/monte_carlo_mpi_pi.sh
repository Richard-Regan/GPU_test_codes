
module purge

module load intel_comp/2018
module load intel_mpi/2018
module load cuda


nvcc -ccbin=mpicxx -x cu -arch=sm_70 -o monte_carlo_mpi_pi.exe monte_carlo_mpi_pi.cpp
mpirun -np $NUM_DEVICES ./monte_carlo_mpi_pi.exe
