#include "FileHelper.h"

FILE* Get_Input_File(char *filename)
{
    return fopen(filename, "r");

}

FILE* Get_Output_File(char *filename)
{
    return fopen(filename, "w");
}

int Count_File_Lines(FILE * file)
{
    int ch,lines=0;
    while(!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n')
            lines++;
    }
    rewind(file);
    return lines;
}

void Close_Files(FILE * Fin,FILE * Fout){
    fclose(Fin);
    fclose(Fout);
}

char** Get_Lines(FILE * file,int lines,int max_length){
    size_t len =0;
    char ** buffer;
    buffer=(char**)malloc(sizeof(char*)*lines );
    for(int i=0;i<lines;i++){
        buffer[i] = (char*)malloc(sizeof(char)*max_length);
        getline(&buffer[i],&len,file);
    }

    return buffer;
}

void skip_Lines(FILE * file,int lines){
    size_t len =0;
    char ** buffer;
    buffer=(char**)malloc(sizeof(char*)*lines );
    int c=0,i;
    for(i=0;i<lines;i++){
        buffer[i] = (char*)malloc(sizeof(char)*350);
        getline(&buffer[i],&len,file);
        free(buffer[i]);
        c++;
    }
    free(buffer);
}