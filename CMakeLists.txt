cmake_minimum_required(VERSION 3.13)
project(HuaParallel C)

set(CMAKE_C_STANDARD 11)

add_executable(test Entity/fastq.h Helpers/FileHelper.h Helpers/FileHelper.c Serial_Implementation.c Helpers/FastqHelper.c Helpers/FastqHelper.h)