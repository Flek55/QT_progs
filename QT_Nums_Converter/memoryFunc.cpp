#include "memoryFunc.h"

char* allocateMemoryForString(int length) {
    return (char*)malloc(sizeof(char) * length);
}

void freeStringMemory(char* arr) {
    free(arr);
}

Params* allocateParams() {
    return (Params*)malloc(sizeof (Params));
}

void freeParams(Params* params) {
    free(params);
}

AppContext* allocateContext() {
    return (AppContext*)malloc(sizeof(AppContext));
}
