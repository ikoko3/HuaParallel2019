#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Helpers/FileHelper.h"
#include "Helpers/FastqHelper.h"

#include <mpi.h>

#define WinLen 20
#define WinThres 19
#define MaxLength 310

int main(int argc, char **argv){

    int rank, size,source,tag,range;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    FILE * Fin = Get_Input_File(argv[1]);
    FILE * Fout = Get_Output_File(argv[2]);

    int buffer_size = 10000;

    if(rank == 0){ //master
        printf("MPI IMPLEMENTATION: Started filtering file: %s, with %d slave nodes\n",argv[1],size-1);
        if(argc!=3){
            printf("the argument count is wrong, format should be <input.fastq> <output.fastq>\n");
            exit(0);
        }

        int no_of_records = Calculate_No_Of_Records(Count_File_Lines(Fin));
        int records_per_node = no_of_records/(size -1 );

        printf("records in this file :%d\n",no_of_records);
        printf("Records Per Node :%d\n",records_per_node);

        fastq_record *Records = malloc(no_of_records* sizeof(fastq_recordR));
        //Set limits to each node
        for(int i=1;i<size;i++){
            int from = (i-1)*records_per_node ;
            int to = from + records_per_node -1 ;
            if(i==size-1) to += no_of_records%(size -1);
            int data[] = {from,to};

            range = to -from +1;
            //printf("Setting limit to Node %d, filtering from %d to %d,with range %d \n",i,from,to,range);

            MPI_Send(data, 2, MPI_INT, i, 1, MPI_COMM_WORLD);
            for(int j=from;j<=to;j++) {
                Records[j] = Parse_Fastq_Record(Create_Next_Fastq_Buffer(Fin));
            }
        }

        //Collect results from every node, and printing to output
        rewind(Fin);
        int c=0;
        for(int i=1;i<size;i++){
            int from = (i-1)*records_per_node;
            int to = from + records_per_node -1;
            if(i==size-1) to += no_of_records%(size -1);
            range = to -from +1;

            //Master Receives from every node an array with the position to trim the record
            int* results = malloc(range*sizeof(int));
            MPI_Recv(results, range, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            for(int j=0;j<range;j++){
                if(results[j]==-1) //low quality record
                   continue;
                int rId = j + from;

                fastq_record record = Records[rId];
                Trim_Record_At(record,results[j]);
                fprintf(Fout,"%s\n%s\n+\n%s\n",record->sequence_name,record->sequence,record->sequence_quality);
                free(record);
                c++;
            }
            free(results);
        }
        free(Records);
        printf("total records added:%d\n",c);
        printf("MPI IMPLEMENTATION: Ended filtering output file: %s\n",argv[2]);

    }else{ //slave
        int data[2];
        int from,to;

        //Receive limits to filter
        MPI_Recv(data, 2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        from = data[0]-1;
        to = data[1];
        range = to -from;

        long lines_to_skip = (from+1)*4;
        if(rank ==1) lines_to_skip =0;
        //printf("START:Node %d,lines to skip %d, filtering from %d to %d,with range %d \n",rank,lines_to_skip,from,to,range);
        skip_Lines(Fin,lines_to_skip);

        //For Every record in my range save the result in an array
        int* results=malloc(range*sizeof(int));
        for(int i=0;i<range;i++) {
            fastq_record record = Parse_Fastq_Record(Create_Next_Fastq_Buffer(Fin));
            results[i] = -1;

            if(Check_For_Minimum_Quality(record,WinLen,WinThres)){
                results[i] = Filter_Record(record,WinLen,WinThres);
            }
            free(record);
        }
        //printf("FINISH:Node %d, filtered from %d to %d, with range %d\n",rank,from,to,range);
        MPI_Send(results,range , MPI_INT, 0, 1, MPI_COMM_WORLD);
        free(results);
    }
    Close_Files(Fin,Fout);
    MPI_Finalize();

    exit(0);
}
