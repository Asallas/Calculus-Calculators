#ifndef FUNCTIONCHECKS_H
#define FUNCTIONCHECKS_H

#include "Functions.h"


static bool checkForOne(std::shared_ptr<Function> expr);

static bool checkForZero(std::shared_ptr<Function> expr);

static bool checkNegativeFunction(const std::shared_ptr<Function>&expr);

static bool negativeArg(std::shared_ptr<Function> argument);

static bool tangentChange(std::shared_ptr<Quotient> trigQuot);

static bool cotangentChange(std::shared_ptr<Quotient> trigQuot);

std::shared_ptr<Function> trigonometricQuotient(std::shared_ptr<Function> trigExpr);

std::shared_ptr<Function> SineCosine(std::shared_ptr<Function> trigSum);

std::shared_ptr<Function> TanSec(std::shared_ptr<Function> trigSum);



#endif
