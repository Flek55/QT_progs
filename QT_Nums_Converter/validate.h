#ifndef VALIDATE_H
#define VALIDATE_H
#include <stdlib.h>
#include <string.h>
#include "appcontext.h"

enum ASCIIConversion {
    MINUS = 45,
    ZERO = 48,
    ONE = 49,
    SEVEN = 55,
    NINE = 57
};

enum MAXValues {
    DEC_MIN = -2147483646,
    OCT_MAX = 17777777777,
    DEC_MAX = 2147483647,
};

void validateInput(AppContext* context, Params* params);
ValidationStatus validateBin(Params* params);
ValidationStatus validateOct(Params* params);
ValidationStatus validateDec(Params* params);

#endif // VALIDATE_H
