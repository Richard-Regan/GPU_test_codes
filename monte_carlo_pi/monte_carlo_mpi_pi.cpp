#include <iostream>
#include <curand_kernel.h>

#include <mpi.h>

#define N 1024*1024

__global__ void calculate_pi(int* hits, int device) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    // Initialize random number state (unique for every thread in the grid)
    int seed = device;
    int offset = 0;
    curandState_t curand_state;
    curand_init(seed, idx, offset, &curand_state);

    // Generate random coordinates within (0.0, 1.0]
    float x = curand_uniform(&curand_state);
    float y = curand_uniform(&curand_state);

    // Increment hits counter if this point is inside the circle
    if (x * x + y * y <= 1.0f) {
        atomicAdd(hits, 1);
    }
}

int get_deviceProp(int deviceId)
{
  cudaDeviceProp props;
  cudaGetDeviceProperties(&props, deviceId);

  /*
   * `props` now contains several properties about the current device.
   */

  int computeCapabilityMajor = props.major;
  int computeCapabilityMinor = props.minor;
  int multiProcessorCount = props.multiProcessorCount;
  int warpSize = props.warpSize;


  printf("\tDevice ID: %d\n\tNumber of SMs: %d\n\tCompute Capability Major: %d\n\tCompute Capability Minor: %d\n\tWarp Size: %d\n\n", deviceId, multiProcessorCount, computeCapabilityMajor, computeCapabilityMinor, warpSize);
  }

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Obtain our rank and the total number of ranks
    // MPI_COMM_WORLD means that we want to include all processes
    // (it is possible in MPI to create "communicators" that only
    // include some of the ranks).

    int rank, num_ranks;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);

    // Ensure that we don't have more ranks than GPUs

    int device_count;
    cudaGetDeviceCount(&device_count);

    if (num_ranks > device_count) {
        std::cout << "Error: more MPI ranks than GPUs" << std::endl;
        return -1;
    }

   
    // Each rank (arbitrarily) chooses the GPU corresponding to its rank
    int dev = rank;
    cudaSetDevice(dev);
    
    get_deviceProp(dev);

    // Allocate host and device values
    int* hits;
    hits = (int*) malloc(sizeof(int));
    
    int* d_hits;
    cudaMalloc((void**) &d_hits, sizeof(int));
    
    // Initialize number of hits and copy to device
    *hits = 0;
    cudaMemcpy(d_hits, hits, sizeof(int), cudaMemcpyHostToDevice);
    
    // Launch kernel to do the calculation
    int threads_per_block = 256;
    int blocks = (N / device_count + threads_per_block - 1) / threads_per_block;
    
    calculate_pi<<<blocks, threads_per_block>>>(d_hits, dev);
    cudaDeviceSynchronize();

    // Copy final result back to the host
    cudaMemcpy(hits, d_hits, sizeof(int), cudaMemcpyDeviceToHost);
    
    // Accumulate the results across all ranks to the result on rank 0
    int* total_hits;
    total_hits = (int*) malloc(sizeof(int));
    
    int root = 0;
    MPI_Reduce(hits, total_hits, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
    
    if (rank == root) {
        // Calculate final value of pi
        float pi_est = (float) *total_hits / (float) (N) * 4.0f;
    
        // Print out result
        std::cout << "Estimated value of pi = " << pi_est << std::endl;
        std::cout << "Error = " << std::abs((M_PI - pi_est) / pi_est) << std::endl;
    }
    
    // Clean up
    free(hits);
    cudaFree(d_hits);
    
    // Finalize MPI
    MPI_Finalize();
    
    return 0;
}

