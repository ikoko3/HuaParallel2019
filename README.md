# HuaParallel2019

Parallel fastq filtering
C99 

compile Serial Implementation

gcc -o serial Serial_Implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c

compile MPI Implementation

mpicc -o par_mpi mpi_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c