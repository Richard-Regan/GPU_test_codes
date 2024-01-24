module load cuda

nvcc -x cu -arch=sm_70 -o monte_carlo_pi.exe monte_carlo_pi.cpp
