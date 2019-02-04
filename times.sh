#!/bin/bash

echo serial 100 Records 
time ./serial 100.fastq 100-output-serial.fastq > temp
echo serial 10k Records 
time ./serial 10K.fastq 10k-output-serial.fastq > temp
echo serial 100k Records 
time ./serial 100K.fastq 100k-output-serial.fastq > temp

c=9


echo MPI 100 Records Nodes $c
time mpirun -np 9 -hostfile ~/hostfiles par_mpi 100.fastq 100-output-mpi.fastq >temp
echo MPI 10K Records Nodes $c
time mpirun -np 9 -hostfile ~/hostfiles par_mpi 10K.fastq 10K-output-mpi.fastq >temp
echo MPI 100K Records Nodes $c
time mpirun -np 9 -hostfile ~/hostfiles par_mpi 100K.fastq 100K-output-mpi.fastq >temp

c=5
echo OPENMP 100 Records Threads $c
time  ./par_omp 100.fastq 100-output-omp.fastq 5 > temp
echo OPENMP 10K Records Threads $c
time ./par_omp 10K.fastq 10K-output-omp.fastq 5 > temp
echo OPENMP 100K Records Threads $c
time ./par_omp 100K.fastq 100K-output-omp.fastq 10 > temp

rm temp
