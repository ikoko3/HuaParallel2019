#include "FastqHelper.h"

int Calculate_No_Of_Records(int lines){
    return lines / LINES_PER_RECORD;
}

char** Create_Next_Fastq_Buffer(FILE * file){
    size_t len =0;
    char ** buffer;
    buffer=(char**)malloc(sizeof(char*)*LINES_PER_RECORD );

    buffer[0] = (char*)malloc(sizeof(char)*SEQUENCE_NAME_LENGTH );
    buffer[1] = (char*)malloc(sizeof(char)*SEQUENCE_LENGTH );
    buffer[2] = (char*)malloc(sizeof(char)*PLUS_SYMBOL_LENGTH );
    buffer[3] = (char*)malloc(sizeof(char)*SEQUENCE_LENGTH );

    getline(&buffer[0],&len,file);
    getline(&buffer[1],&len,file);
    getline(&buffer[2],&len,file);
    getline(&buffer[3],&len,file);

    buffer[0][SEQUENCE_NAME_LENGTH-1] = '\0';
    char *pos;
    if ((pos=strchr(buffer[1], '\n')) != NULL)
        *pos = '\0';
    buffer[2][PLUS_SYMBOL_LENGTH-1] = '\0';
    if ((pos=strchr(buffer[3], '\n')) != NULL)
        *pos = '\0';

    return buffer;
}

fastq_record Parse_Fastq_Record(char** buffer){
    fastq_record record = malloc(sizeof(fastq_recordR));

    strcpy(record->sequence_name,buffer[0]);
    strcpy(record->sequence,buffer[1]);
    strcpy(record->sequence_quality,buffer[3]);

    Empty_fastq_buffer(buffer);
    return record;
}

int Filter_Record(fastq_record record,int window_length,int window_threshold){
    // start and end position of the sliding window
    int start=0;
    int end=start+window_length;
    int MaxLen=strlen(record->sequence_quality)-1;
    float Qual=window_threshold+1;

    while ((end<=MaxLen)&&Qual>window_threshold)
    {
        // calculate the mean quality score
        Qual=0;
        for (int k=start;k<end;k++)
            Qual+=record->sequence_quality[k] -33;
        Qual/=window_length;

        //slide the window by one position to the right
        start++;
        end=start+window_length;
    }
    start--;
    Trim_Record_At(record, start);
    return start;
}

//Filter a fastq record at a specific position
void Trim_Record_At(fastq_record record, size_t position){
    strncpy(record->sequence,record->sequence,position);
    record->sequence[position]='\0';
    strncpy(record->sequence_quality,record->sequence_quality,position);
    record->sequence_quality[position]='\0';

}

//returns true if the starting quality is larger than the window threshold
int Check_For_Minimum_Quality(fastq_record record,int window_length,int window_threshold){
    float Qual=0;
    int start=0;
    int end=start+window_length;

    for (int k=start;k<end;k++)
        Qual+=record->sequence_quality[k] -33;
    Qual/=window_length;

    return (Qual > window_threshold);
}

void Empty_fastq_buffer(char **buffer){
    for (int i=0;i<LINES_PER_RECORD;i++)
        free(buffer[i]);
    free(buffer);

}