#include "fastq.h"

int Calculate_No_Of_Records(int lines){
    return lines / LINES_PER_RECORD;
}


int fastq_record_size = 2*sizeof(char)*SEQUENCE_LENGTH + sizeof(char)*SEQUENCE_NAME_LENGTH;

void Get_Next_Lines(FILE * file,char** buffer){
    size_t len =0;
    char *t = (char*)malloc(sizeof(char)*15);

    getline(&buffer[0],&len,file);
    getline(&buffer[1],&len,file);
    getline(&t,&len,file);
    getline(&buffer[3],&len,file);

    buffer[0][SEQUENCE_NAME_LENGTH-1] = '\0';
    char *pos;
    if ((pos=strchr(buffer[1], '\n')) != NULL)
        *pos = '\0';
    if ((pos=strchr(buffer[3], '\n')) != NULL)
        *pos = '\0';

}

fastq_record Parse_Next_Fastq_Record(FILE * file){
    size_t len =0;
    fastq_record record = malloc(fastq_record_size);

    char *id,*seq, *qual, *plus;

    id = (char*)malloc(sizeof(char)*SEQUENCE_NAME_LENGTH );
    seq = (char*)malloc(sizeof(char)*SEQUENCE_LENGTH);
    plus = (char*)malloc(sizeof(char)*10);
    qual = (char*)malloc(sizeof(char)*SEQUENCE_LENGTH);

    getline(&id,&len,file);
    getline(&seq,&len,file);
    getline(&qual,&len,file);
    getline(&plus,&len,file);

    strcpy(record->sequence_name,id);
    strcpy(record->sequence,seq);
    strcpy(record->sequence_quality,qual);

    //Fix the values
    record->sequence_name[SEQUENCE_NAME_LENGTH-1] = '\0';
    char *pos;
    if ((pos=strchr(record->sequence, '\n')) != NULL)
        *pos = '\0';
    if ((pos=strchr(record->sequence_quality, '\n')) != NULL)
        *pos = '\0';

    free(id);
    free(seq);
    //free(plus);
    //free(qual);


    return record;
}

char** Create_Fastq_Buffer(){
    char ** buffer;
    buffer=(char**)malloc(sizeof(char*)*3 );

    buffer[0] = (char*)malloc(sizeof(char)*SEQUENCE_NAME_LENGTH );
    buffer[1] = (char*)malloc(sizeof(char)*SEQUENCE_LENGTH );
    buffer[2] = (char*)malloc(sizeof(char)*20 );
    buffer[3] = (char*)malloc(sizeof(char)*SEQUENCE_LENGTH );

    return buffer;
}

void Filter_Record(fastq_record record,int window_length,int window_threshold){
    float Qual=0;

    // start and end position of the sliding window
    int start=0;
    int end=start+window_length;
    int MaxLen=strlen(record->sequence_quality)-1;

    Qual=window_threshold+1;

    while ((end<=MaxLen)&&Qual>window_threshold)
    {
        // calculate the mean quality score
        Qual=0;
        for (int k=start;k<end;k++)
            Qual+=record->sequence_quality[k] -33;
        //printf("Accumulated Qual=%f \t Mean Qual=%f \n",Qual,Qual/window_length);
        Qual/=window_length;

        //slide the window by one position to the right
        start++;
        end=start+window_length;
    }
    start--;
    //printf("Nucelotides after position %d have mean window quality under %d\n",start,window_threshold);
    if(start>0)
        Filter_Record_At(record,start);

}

void Filter_Record_At(fastq_record record,int position){

    strncpy(record->sequence,record->sequence,position);
    record->sequence[position]='\0';
    strncpy(record->sequence_quality,record->sequence_quality,position);
    record->sequence_quality[position]='\0';

}

int Check_Minimum_Quality(fastq_record record){

}