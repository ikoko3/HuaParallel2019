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