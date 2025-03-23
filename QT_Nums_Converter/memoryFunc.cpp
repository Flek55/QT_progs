#include "memoryFunc.h"

char* allocateMemoryForString(int length) {
    return (char*)malloc(sizeof(char) * length);
}

void freeStringMemory(char* arr) {
    free(arr);
}
