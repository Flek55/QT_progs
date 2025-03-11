#include "logic.h"
#include <QMainWindow>
#include <QClipboard>
#include <QErrorMessage>
#include <QMessageBox>

void validateInput(AppContext* context, Params* params) {
    enum ValidationStatus result = CORRECT;
    if (strcmp(params->value, "") == 0)
        result = EMPTY_TEXT;
    else {
        switch (context->oldNumSys) {
        case NIL:
            result = EMPTY_START_SYS;
            break;
        case BIN:
            result = validateBin(params);
            break;
        case OCT:
            result = validateOct(params);
            break;
        case DEC:
            result = validateDec(params);
            break;
        }
    }
    if (!context->newNumSys && result != EMPTY_START_SYS)
        result = EMPTY_END_SYS;

    context->validation = result;
}

void assignOperationType(AppContext* context, Params* params) {
    Operation result;

    if (context->oldNumSys == context->newNumSys)
        result = SAME_TO_SAME;
    else if (context->oldNumSys == BIN)
        result = FROM_BIN;
    else if (context->oldNumSys == OCT)
        result = FROM_OCT;
    else
        result = FROM_DEC;

    params->operation = result;
}

void forkBin(AppContext* context, Params* params) {
    transformFromBinToDec(params->value, params);

    if (context->newNumSys == DEC)
        context->result = params->value;
    else if (context->newNumSys == OCT) {
        transformFromDecToOct(params);
        context->result = params->value;
    }

}

void forkOct(AppContext* context, Params* params) {
    transformFromOctToDec(params);

    if (context->newNumSys == DEC)
        context->result = params->value;
    else if (context->newNumSys == BIN) {
        transformFromDecToBin(params);
        context->result = params->value;
    }
}

void forkDec(AppContext* context, Params* params) {
    switch(context->newNumSys) {
    case BIN: {
        transformFromDecToBin(params);
        context->result = params->value;
        break;
    }
    case OCT: {
        transformFromDecToOct(params);
        context->result = params->value;
        break;
    }
    default:
        break;
    }
}

void removeLeadingZeros(char** binValue) {
    char* firstNonZero = *binValue;

    while (*firstNonZero == '0' && *firstNonZero != '\0')
        firstNonZero++;

    char* trimmedValue = strdup(firstNonZero);

    *binValue = trimmedValue;
}

void transformFromDecToBin(Params* params) {
    int decValue = atoi(params->value);
    char* binValue = allocateMemoryForString(BIN_LEN);

    for (size_t i = 0; i < BIN_LEN - 1; i++)
        binValue[i] = '0';

    binValue[BIN_LEN - 1] = '\0';
    int tempDec = abs(decValue);
    binValue[BIN_LEN - 1] = '\0';

    for (int i = BIN_LEN - TWO; i >= 0; i--) {
        binValue[i] = (tempDec % TWO) + '0';
        tempDec /= TWO;
    }

    if (decValue > 0)
        removeLeadingZeros(&binValue);
    if (decValue < 0)
        transformFromNegDecToBin(binValue);

    params->value = strdup(binValue);
}

void transformFromNegDecToBin(char* binValue) {
    for (size_t i = 0; i < BIN_LEN - 1; i++) {
        if (binValue[i] == '0')
            binValue[i] = '1';
        else
            binValue[i] = '0';
    }

    int carry = 1;

    for (size_t i = BIN_LEN - TWO; i >= 0; i--) {
        if (carry == 1 && binValue[i] == '1')
            binValue[i] = '0';
        else if (carry == 1 && binValue[i] == '0') {
            binValue[i] = '1';
            break;
        }
    }
}

void transformSameToSame(AppContext* context, Params* params) {
    context->result = params->value;
}

void transformFromDecToOct(Params* params) {
    int decValue = atoi(params->value);
    char* octValue = allocateMemoryForString(OCT_LEN);


    if (decValue > 0)
        sprintf(octValue, "%o", decValue);
    else {
        char* binValue = allocateMemoryForString(BIN_LEN);
        transformFromDecToBin(params);
        char* decValueStr = allocateMemoryForString(DEC_LEN);
        transformFromBinToDec(binValue, params);
        sprintf(octValue, "%o", atoi(decValueStr));
        freeStringMemory(decValueStr);
        freeStringMemory(binValue);
    }

    params->value = strdup(octValue);
}

void transformFromBinToDec(const char* binValue, Params* params) {
    char* decValue = allocateMemoryForString(DEC_LEN);
    char* endptr = NULL;
    long number = strtoul(binValue, &endptr, BIN);

    if (number > INT_MAX) {
        number -= (1LL << THIRTY_TWO);
    }

    sprintf(decValue, "%ld", number);

    params->value = strdup(decValue);
}

void transformFromOctToDec(Params* params) {
    char* answ = allocateMemoryForString(DEC_LEN);

    char* endptr = NULL;
    long number = strtoul(params->value, &endptr, OCT);

    if (number > INT_MAX) {
        number -= (1LL << THIRTY_TWO);
    }

    sprintf(answ, "%ld", number);
    params->value = strdup(answ);
}

void clearResult(AppContext* context) {
    context->result = NULL;
}

void swap(AppContext* context, Params* params) {
    const char* temp = params->value;
    params->value = context->result;
    context->result = temp;

    int tempS = context->oldNumSys;
    context->oldNumSys = context->newNumSys;
    context->newNumSys = (enum NumberSystems)tempS;
}
