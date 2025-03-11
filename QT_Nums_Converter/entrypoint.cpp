#include "entrypoint.h"


void doOperation(AppContext* context, Operation operation, Params* params) {
    switch (operation) {
    case FROM_BIN:
        forkBin(context, params);
        break;
    case FROM_OCT:
        forkOct(context, params);
        break;
    case FROM_DEC:
        forkDec(context, params);
        break;
    case SAME_TO_SAME:
        transformSameToSame(context, params);
        break;
    case VALIDATE:
        validateInput(context, params);
        break;
    case SWAP:
        swap(context, params);
        break;
    case PARSE_OPERATION:
        assignOperationType(context, params);
        doOperation(context, params->operation, params);
        break;
    case CLEAR_RESULT:
        clearResult(context);
        break;
    }
}
