#include "functionChecks.h"

static bool checkForOne(std::shared_ptr<Function> expr){
    if(auto constant = dynamic_cast<Constant*>(expr.get())){
        return constant->getValue() == 1.0;
    }
    return false;
}

static bool checkForZero(std::shared_ptr<Function> expr){
    if(auto constant = dynamic_cast<Constant*>(expr.get())){
        return constant->getValue() == 0.0;
    }
    return false;
}

static bool checkNegativeFunction(const std::shared_ptr<Function>&expr){
    
    if(auto checkProduct = dynamic_cast<Product*>(expr.get())){
        auto checkConstL = dynamic_cast<Constant*>(checkProduct->getLeft().get());
        auto checkConstR = dynamic_cast<Constant*>(checkProduct->getRight().get());

        return (checkConstL && checkConstL->isEqual(std::make_shared<Constant>(-1.0))) ||
                (checkConstR && checkConstR->isEqual(std::make_shared<Constant>(-1.0)));
    }

    if(auto checkQuotient = dynamic_cast<Quotient*>(expr.get())){
        auto checkTopC = dynamic_cast<Constant*>(checkQuotient->getLeft().get());
        auto checkBotC = dynamic_cast<Constant*>(checkQuotient->getLeft().get());
        if(checkBotC && checkBotC->isEqual(std::make_shared<Constant>(-1.0))){
            return true;
        }
        if(checkTopC && checkTopC->isEqual(std::make_shared<Constant>(-1.0))){
            return true;
        }

        auto checkTopP = dynamic_cast<Product*>(checkQuotient->getLeft().get());
        auto checkBotP = dynamic_cast<Product*>(checkQuotient->getRight().get());

        if(checkTopP) return checkNegativeFunction(checkQuotient->getLeft());
        if(checkBotP) return checkNegativeFunction(checkQuotient->getRight());
        
    }

    return false;
}

static bool tangentChange(std::shared_ptr<Quotient> trigQuot){
    return dynamic_cast<Sine*>(trigQuot->getLeft().get()) && dynamic_cast<Cosine*>(trigQuot->getRight().get());
}
static bool cotangentChange(std::shared_ptr<Quotient> trigQuot){
    return dynamic_cast<Cosine*>(trigQuot->getLeft().get()) && dynamic_cast<Sine*>(trigQuot->getRight().get());
}

std::shared_ptr<Function> trigonometricQuotient(std::shared_ptr<Function> trigExpr){
    if(auto sine = dynamic_cast<Sine*>(trigExpr.get())){
        return std::make_shared<Cosecant>(sine->getArgument());
    }
    if(auto cosine = dynamic_cast<Cosine*>(trigExpr.get())){
        return std::make_shared<Secant>(cosine->getArgument());
    }

    if(auto tangent = dynamic_cast<Tangent*>(trigExpr.get())){
        return std::make_shared<Cotangent>(tangent->getArgument());
    }
    if(auto cotangent = dynamic_cast<Cotangent*>(trigExpr.get())){
        return std::make_shared<Tangent>(cotangent->getArgument());
    }

    if(auto cosecant = dynamic_cast<Cosecant*>(trigExpr.get())){
        return std::make_shared<Sine>(cosecant->getArgument());
    }
    if(auto secant = dynamic_cast<Secant*>(trigExpr.get())){
        return std::make_shared<Cosine>(secant->getArgument());
    }
    return trigExpr;
}



std::shared_ptr<Function> TanSec(std::shared_ptr<Function> trigSum) {
    if (auto checkSum = dynamic_cast<Sum*>(trigSum.get())){
        if(checkForOne(checkSum->getLeft()) || checkForOne(checkSum->getRight())){
            return std::make_shared<Polynomial>(std::make_shared<Secant>(checkSum->getRight()), 2.0);
        }
    }
    return trigSum;
}

std::shared_ptr<Function> SineCosine(std::shared_ptr<Function> trigSum) {
    if(auto checkSum = dynamic_cast<Sum*>(trigSum.get())){
        auto polyCheckL = dynamic_cast<Polynomial*>(checkSum->getLeft().get());
        auto polyCheckR = dynamic_cast<Polynomial*>(checkSum->getRight().get());
        bool checkPowerL = (polyCheckL->getExponent() == 2.0);
        bool checkPowerR = (polyCheckR->getExponent() == 2.0);
        if(((!polyCheckL && checkPowerL) || (!polyCheckR && checkPowerR))){
            return trigSum;
        }
        if(polyCheckL && !polyCheckR){
            auto sineL = dynamic_cast<Sine*>(polyCheckL->getCoefficient().get());
        }
        auto sineL = dynamic_cast<Sine*>(polyCheckL->getCoefficient().get());
        auto cosineR = dynamic_cast<Cosine*>(polyCheckR->getCoefficient().get());

        
        
    }

    return trigSum;
}

static bool negativeArg(std::shared_ptr<Function> argument){
    if(auto product = dynamic_cast<Product*>(argument.get())){
        if(product->getLeft()->isEqual(std::make_shared<Constant>(-1.0)) ||
            product->getRight()->isEqual(std::make_shared<Constant>(-1.0))){
                return true;
        }
    }
    if(auto product = dynamic_cast<Quotient*>(argument.get())){
        if(product->getLeft()->isEqual(std::make_shared<Constant>(-1.0)) ||
            product->getRight()->isEqual(std::make_shared<Constant>(-1.0))){
                return true;
        }
    }
    return false;
}