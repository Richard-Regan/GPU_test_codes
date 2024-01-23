module load cuda

nvcc -x cu -arch=sm_70 -o monte_carlo monte_carlo_pi.cpp
