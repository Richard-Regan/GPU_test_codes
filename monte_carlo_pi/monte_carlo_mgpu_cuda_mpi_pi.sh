
module purge

module load intel_comp/2018
module load intel_mpi/2018
module load cuda


nvcc -ccbin=mpicxx -x cu -arch=sm_70 -o monte_carlo_mgpu_cuda_mpi.exe monte_carlo_mgpu_cuda_mpi.cpp
mpirun -np $NUM_DEVICES ./monte_carlo_mgpu_cuda_mpi.exe
