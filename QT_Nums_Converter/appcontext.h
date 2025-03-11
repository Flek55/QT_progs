#ifndef APPCONTEXT_H
#define APPCONTEXT_H

enum {
    TWO = 2,
    THIRTY_TWO = 32,
};

enum NumberSystems {
    NIL = 0,
    BIN = 2,
    OCT = 8,
    DEC = 10,
};

enum ValidationStatus {
    CORRECT,
    INCORRECT_INPUT,
    MAX_LEN_EXCEEDED,
    EMPTY_START_SYS,
    EMPTY_END_SYS,
    MAX_VALUE_EXCEEDED,
    EMPTY_TEXT
};

enum MaxLenNumerSystems {
    BIN_LEN = 33,
    OCT_LEN = 12,
    DEC_LEN = 11
};

enum NumberSystemInputIndexes {
    DecimalI,
    BinaryI,
    OctalI
};

enum NumberSystemOutputIndexes {
    BinaryO,
    OctalO,
    DecimalO
};

struct AppContext {
    enum NumberSystems oldNumSys;
    enum NumberSystems newNumSys;
    const char* result;
    enum ValidationStatus validation;
};

typedef enum Operation{
    FROM_BIN,
    FROM_OCT,
    FROM_DEC,
    SAME_TO_SAME,
    VALIDATE,
    SWAP,
    PARSE_OPERATION,
    CLEAR_RESULT,
} Operation;

struct Params {
    const char* value;
    enum Operation operation;
};

#endif // APPCONTEXT_H
