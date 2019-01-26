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

char** Get_Lines(FILE * file,int lines_count,int lines_length)
{
    size_t len =0;
    int line=0;
    char ** buffer;
    buffer=(char**)malloc(sizeof(char*)*4 );
    for(int i=0;i<lines_count;i++)
        buffer[i]=(char*)malloc(sizeof(char)*lines_length );

    for(line=0;line<lines_count;line++)
        getline(&buffer[line],&len,file);


    return buffer;
}