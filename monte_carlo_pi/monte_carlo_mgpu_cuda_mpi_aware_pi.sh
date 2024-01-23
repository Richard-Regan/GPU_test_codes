nvcc -ccbin=mpicxx -x cu -arch=sm_70 -o monte_carlo_mgpu_cuda_mpi_cuda_aware exercises/monte_carlo_mgpu_cuda_mpi_cuda_aware.cpp
mpirun -np $NUM_DEVICES ./monte_carlo_mgpu_cuda_mpi_cuda_aware
