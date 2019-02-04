# HuaParallel2019

Parallel fastq filtering   C99

			Serial Implementation

Compile
gcc -o serial serial_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c

Excecute
./serial <input.fastq> <output.fastq>

			MPI Implementation

Compile
mpicc -o par_mpi mpi_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c

Excecute
mpirun -np <nodes> -hostfile <hostfile> par_mpi <input.fastq> <output.fastq>


			OpenMP Implementation

Compile
gcc -o par_omp openmp_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c


Excecute
./par_omp <input.fastq> <output.fastq> <threads_count> -fopen
