#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef TEST_FILEHELPER_H
#define TEST_FILEHELPER_H

#endif

FILE* Get_Input_File(char *filename);

FILE* Get_Output_File(char *filename);

int Count_File_Lines(FILE * file);

void Close_Files(FILE * Fin,FILE * Fout);