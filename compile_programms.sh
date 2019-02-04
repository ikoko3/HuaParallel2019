#!/bin/bash

gcc -o serial serial_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c
mpicc -o par_mpi mpi_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c
gcc -o par_omp openmp_implementation.c Entity/fastq.h Helpers/FastqHelper.h Helpers/FastqHelper.c Helpers/FileHelper.h Helpers/FileHelper.c -fopenmp
