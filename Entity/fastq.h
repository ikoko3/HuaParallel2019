
#ifndef TEST_FASTQ_H
#define TEST_FASTQ_H

#endif

#define SEQUENCE_NAME_LENGTH 19
#define SEQUENCE_LENGTH  300
#define LINES_PER_RECORD 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//Define fastq as a struct
struct fastq_record{
    char sequence_name[SEQUENCE_NAME_LENGTH];
    char sequence[SEQUENCE_LENGTH];
    char sequence_quality[SEQUENCE_LENGTH];
};

typedef struct fastq_record *fastq_record;


//Helper Functions

//return the no of the records in a file based on the line count
int Calculate_No_Of_Records(int lines);

fastq_record Parse_Next_Fastq_Record(FILE * file);

char** Create_Fastq_Buffer();

void Filter_Record(fastq_record record,int window_length,int window_threshold);

void Filter_Record_At(fastq_record record,int position);


//System Variables
int fastq_record_size;