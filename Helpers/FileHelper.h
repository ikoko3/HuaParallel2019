#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef TEST_FILEHELPER_H
#define TEST_FILEHELPER_H

#endif

FILE* Get_Input_File(char *filename);

FILE* Get_Output_File(char *filename);

//returns the total lines of a file
int Count_File_Lines(FILE * file);

//reads n lines from a file
char** Get_Lines(FILE * file,int lines,int max_length);

//Skips n lines in a file
void skip_Lines(FILE * file,int lines);

void Close_Files(FILE * Fin,FILE * Fout);