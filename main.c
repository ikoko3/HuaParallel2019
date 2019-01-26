#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Helpers/FileHelper.h"
#include "Entity/fastq.h"

#define WinLen 20
#define WinThres 19


int main(int argc,char **argv)
{
    if(argc!=3){
        printf("the argument count is wrong, format should be <input.fastq> <output.fastq>\n");
        exit(-1);
    }

    FILE * Fin = Get_Input_File(argv[1]);
    FILE * Fout = Get_Output_File(argv[2]);
    int no_of_records;

    no_of_records = Calculate_No_Of_Records(Count_File_Lines(Fin));
    fastq_record Records[no_of_records];
    printf("records in this file :%d\n",no_of_records);

    for(int i=0;i<no_of_records;i++){
        Records[i] = Parse_Next_Fastq_Record(Fin);
        fastq_record record = Records[i];

        //printf("filtering record with id:%d\n",i);
        Filter_Record(record,WinLen,WinThres);

        fprintf(Fout,"%s\n%s\n+\n%s\n",record->sequence_name,record->sequence,record->sequence_quality);
    }
    fclose(Fout);

    exit(0);

}
