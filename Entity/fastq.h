
#ifndef FASTQ_H
#define FASTQ_H

#endif

#define SEQUENCE_NAME_LENGTH 19
#define SEQUENCE_LENGTH  300
#define PLUS_SYMBOL_LENGTH 2
#define LINES_PER_RECORD 4


//Define fastq as a struct
struct fastq_recordR{
    char sequence_name[SEQUENCE_NAME_LENGTH];
    char sequence[SEQUENCE_LENGTH];
    char sequence_quality[SEQUENCE_LENGTH];
};

typedef struct fastq_recordR fastq_recordR;

typedef fastq_recordR *fastq_record;



