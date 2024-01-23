nvcc -ccbin=mpicxx -x cu -arch=sm_70 -o monte_carlo_mgpu_cuda_mpi exercises/monte_carlo_mgpu_cuda_mpi.cpp
mpirun -np $NUM_DEVICES ./monte_carlo_mgpu_cuda_mpi
