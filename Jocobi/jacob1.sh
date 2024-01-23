#Build and run Jacob code with nvshmem

!nvcc -x cu -arch=sm_70 -rdc=true -I $NVSHMEM_HOME/include -L $NVSHMEM_HOME/lib -lnvshmem -lcuda -o jacobi_step1 exercises/jacobi_step1.cpp
!nvshmrun -np $NUM_DEVICES ./jacobi_step1
