#include "validate.h"


ValidationStatus validateBin(Params* params) {
    ValidationStatus code = CORRECT;
    int delta = 0;
    const char* tmp = params->value;

    while (tmp[delta] != '\0') {
        if (tmp[delta] < ZERO || tmp[delta] > ONE) {
            code = INCORRECT_INPUT;
            break;
        }
        if (delta > BIN_LEN) {
            code = MAX_LEN_EXCEEDED;
        }
        delta++;
    }
    return code;
}

ValidationStatus validateOct(Params* params) {
    ValidationStatus code = CORRECT;
    int delta = 0;
    const char* tmp = params->value;
    while (tmp[delta] != '\0') {
        if (tmp[delta] < ZERO || tmp[delta] > SEVEN) {
            code = INCORRECT_INPUT;
            break;
        }
        if (delta > OCT_LEN) {
            code = MAX_LEN_EXCEEDED;
        }
        delta++;
    }
    return code;
}

ValidationStatus validateDec(Params* params){
    ValidationStatus code = CORRECT;
    int delta = 0;
    const char* tmp = params->value;
    char* endptr = NULL;
    long long value = strtoll(params->value, &endptr, DEC);

    if (value < DEC_MIN || value > DEC_MAX)
        code = MAX_VALUE_EXCEEDED;
    else {
        while (tmp[delta] != '\0') {
            if ((tmp[delta] < ZERO || tmp[delta] > NINE) && tmp[delta] != MINUS) {
                code = INCORRECT_INPUT;
                break;
            } else if (tmp[delta] == MINUS && delta != 0) {
                code = INCORRECT_INPUT;
                break;
            }
            if (delta > DEC_LEN) {
                code = MAX_LEN_EXCEEDED;
            }
            delta++;
        }
    }
    return code;
}
