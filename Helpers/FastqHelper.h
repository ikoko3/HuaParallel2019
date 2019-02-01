#ifndef HUAPARALLEL_FASTQHELPER_H
#define HUAPARALLEL_FASTQHELPER_H

#endif //HUAPARALLEL_FASTQHELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../Entity/fastq.h"

//Helper Functions

//return the no of the records in a file based on the line count
int Calculate_No_Of_Records(int lines);

//Pare a buffer into fastq struct, and free the buffer
fastq_record Parse_Fastq_Record(char** buffer);

//Reads into a buffer the next lines for a record
char** Create_Next_Fastq_Buffer(FILE * file);

//Frees the buffer
void Empty_fastq_buffer(char **buffer);

//Filters a fastq record, based on its quality
int Filter_Record(fastq_record record,int window_length,int window_threshold);

//Trims a fastq record at a specific position
void Trim_Record_At(fastq_record record, size_t position);

//returns true if the starting quality is larger than the window threshold
int Check_For_Minimum_Quality(fastq_record record,int window_length,int window_threshold);
