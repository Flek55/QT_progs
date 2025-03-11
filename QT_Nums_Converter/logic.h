#ifndef LOGIC_H
#define LOGIC_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "appcontext.h"
#include "validate.h"
#include "memoryFunc.h"

void assignOperationType(AppContext* context, Params* params);
void clearResult(AppContext* context);

void forkBin(AppContext* context, Params* params);
void forkOct(AppContext* context, Params* params);
void forkDec(AppContext* context, Params* params);

void transformFromDecToBin(Params* params);
void transformSameToSame(AppContext* context, Params* params);
void removeLeadingZeros(char** binValue, Params* params);
void transformFromNegDecToBin(char* binValue);
void transformFromDecToOct(Params* params);
void transformFromBinToDec(const char* binValue, Params* params);
void transformFromOctToDec(Params* params);
void swap(AppContext* context, Params* params);

#endif // LOGIC_H
