#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "appcontext.h"
#include "logic.h"
#include "validate.h"

void doOperation(AppContext* context, Operation operation, Params* params);
#endif // ENTRYPOINT_H
