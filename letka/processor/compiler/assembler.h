#ifndef assm_h
#define assm_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../instructions.h"

const char* signature = "ROST";
const u_int32_t signatura = 82798384;
const int ass_version  = 2;

struct label_t
{
    char* label_name;
    int   line_number;
};

struct labelArray_t
{
    label_t* array;
    int      used_labels;
};

void MakeMachCode(const char* ProgrammFile, const char* cmdFile, const char* logFile);
void BinWrite(double* cmd_array, const char* BinFileName, u_int32_t nComands);

void labelCtor(labelArray_t* lblarr, int nlabels);
void labelDtor(labelArray_t* lblarr);
void labelDump(labelArray_t* lblarr);


#endif //assm_h