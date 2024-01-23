nvcc -x cu -arch=sm_70 -rdc=true -I $NVSHMEM_HOME/include -L $NVSHMEM_HOME/lib -lnvshmem -lcuda -o nvshmem_pi_step3 exercises/nvshmem_pi_step3.cpp
nvshmrun -np $NUM_DEVICES ./nvshmem_pi_step3
