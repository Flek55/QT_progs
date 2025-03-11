#ifndef MEMORYFUNC_H
#define MEMORYFUNC_H
#include <stdlib.h>
#include "appcontext.h"

char* allocateMemoryForString(int length);
Params* allocateParams();
void freeStringMemory(char * arr);
void freeParams(Params* params);
AppContext* allocateContext();

#endif // MEMORYFUNC_H
