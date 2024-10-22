#pragma once

#include "Functions.h"

std::shared_ptr<Function> SineCosine(std::shared_ptr<Function> trigSum) {
    if(auto checkSum = dynamic_cast<Sum*>(trigSum.get())){
        if(isSinSquared(checkSum->getLeft()) && isCosSquared(checkSum->getRight())){
            return std::make_shared<Constant>(1.0);
        }
        if(isSinSquared(checkSum->getLeft()) && isCosSquared(checkSum->getRight())){
            return std::make_shared<Constant>(1.0);
        }
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

static bool isOne(const std::shared_ptr<Function>& expr){
        if(auto constant = dynamic_cast<Constant*>(expr.get())){
            return constant->getValue() == 1;
        }
        return false;
}

static bool isSinSquared(const std::shared_ptr<Function>& expr){
    // Check if the expression is of the form sin^2(x)
    if (auto poly = dynamic_cast<Polynomial*>(expr.get())) {
        return dynamic_cast<Sine*>(poly->getCoefficient().get()) && poly->getExponent() == 2;
    }
    return false;
}
static bool isCosSquared(const std::shared_ptr<Function>& expr){
    // Check if the expression is of the form sin^2(x)
    if (auto poly = dynamic_cast<Polynomial*>(expr.get())) {
        return dynamic_cast<Sine*>(poly->getCoefficient().get()) && poly->getExponent() == 2;
    }
    return false;
}
static bool isTanSquared(const std::shared_ptr<Function>& expr){
    // Check if the expression is of the form sin^2(x)
    if (auto poly = dynamic_cast<Polynomial*>(expr.get())) {
        return dynamic_cast<Sine*>(poly->getCoefficient().get()) && poly->getExponent() == 2;
    }
    return false;
}
static bool isSecSquared(const std::shared_ptr<Function>& expr){
    // Check if the expression is of the form sin^2(x)
    if (auto poly = dynamic_cast<Polynomial*>(expr.get())) {
        return dynamic_cast<Sine*>(poly->getCoefficient().get()) && poly->getExponent() == 2;
    }
    return false;
}
static bool isCscSquared(const std::shared_ptr<Function>& expr){
    // Check if the expression is of the form sin^2(x)
    if (auto poly = dynamic_cast<Polynomial*>(expr.get())) {
        return dynamic_cast<Sine*>(poly->getCoefficient().get()) && poly->getExponent() == 2;
    }
    return false;
}
static bool isCotSquared(const std::shared_ptr<Function>& expr){
    // Check if the expression is of the form sin^2(x)
    if (auto poly = dynamic_cast<Polynomial*>(expr.get())) {
        return dynamic_cast<Sine*>(poly->getCoefficient().get()) && poly->getExponent() == 2;
    }
    return false;
}