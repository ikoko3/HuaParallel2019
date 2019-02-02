#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <omp.h>

#include "Helpers/FileHelper.h"
#include "Helpers/FastqHelper.h"

#define WinLen 20
#define WinThres 19

int main(int argc,char **argv)
{

    if(argc!=4){
        printf("the argument count is wrong, format should be <input.fastq> <output.fastq> <threads>\n");
        exit(-1);
    }
    int threads_count = atoi(argv[3]);
    omp_set_num_threads(threads_count);

    FILE * Fin = Get_Input_File(argv[1]);
    FILE * Fout = Get_Output_File(argv[2]);

    int no_of_records = Calculate_No_Of_Records(Count_File_Lines(Fin));
    int records_per_node = no_of_records/(threads_count);
    printf("records in this file :%d\n",no_of_records);

    int *results;
    results = malloc(sizeof(long)*no_of_records);
    memset(results,0,no_of_records*sizeof(int));

    fastq_record *Records = malloc(no_of_records* sizeof(fastq_recordR));
    for(int i=0;i<no_of_records;i++) {
        Records[i] = Parse_Fastq_Record(Create_Next_Fastq_Buffer(Fin));
    }

    #pragma omp parallel
    {
        int thread_no = omp_get_thread_num();
        int from = (thread_no)*records_per_node;
        int to = from + records_per_node;
        if(thread_no==threads_count-1) to += no_of_records%(threads_count);
        
        for (int i = from; i < to; i++) {
            fastq_record record = Records[i];
            if (Check_For_Minimum_Quality(record, WinLen, WinThres))
                Filter_Record(record,WinLen,WinThres);
        }
    }

    //Print and free Records
    for(int i=0;i<no_of_records;i++) {
        fastq_record record = Records[i];
        if(results[i]!=-1){
            fprintf(Fout,"%s\n%s\n+\n%s\n",record->sequence_name,record->sequence,record->sequence_quality);
        }
        free(record);
    }
    free(Records);

    printf("Finished filtering openmp\n");
    Close_Files(Fin,Fout);
    exit(0);
}