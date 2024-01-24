

monte_carlo_pi_hpc.exe : monte_carlo_pi.cpp
	module purge
	module load nvhpc
	nvcc -x cu -arch=sm_70 -o monte_carlo_pi_hpc.exe monte_carlo_pi.cpp
	./monte_carlo_pi_hpc.exe

monte_carlo_mpi_pi.exe : monte_carlo_mpi_pi.cpp
	module purge
	module load intel_comp/2018
	module load intel_mpi/2018
	module load cuda
	nvcc -ccbin=mpicxx -x cu -o monte_carlo_mpi_pi.exe monte_carlo_mpi_pi.cpp 
	mpirun -np 1 ./monte_carlo_mpi_pi.exe

monte_carlo_mpi_pi_hcp.exe : monte_carlo_mpi_pi.cpp
	module purge
	module load nvhpc
	nvcc -ccbin=mpicxx -x cu -o monte_carlo_mpi_pi_hpc.exe monte_carlo_mpi_pi.cpp 
	mpirun -np 1 ./monte_carlo_mpi_pi_hpc.exe

clean : 
	rm *.exe

all : monte_calro_pi.exe monte_calro_pi_hpc.exe monte_calo_mpi_pi.exe monte_carlo_mpi_pi_hpc.exe

monte_carlo_pi.exe : monte_carlo_pi.cpp
	module purge
	module load intel_comp/2018
	module load intel_mpi/2018
	module load cuda
	nvcc -x cu -arch=sm_70 -o monte_carlo_pi.exe monte_carlo_pi.cpp
	./monte_carlo_pi.exe

