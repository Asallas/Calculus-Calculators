#include "Functions.h"

//Constant

double Constant::getValue(){
    return value;
}


std::shared_ptr<Function> Constant::simplify() const{
    return std::make_shared<Constant>(value);
}

bool Constant::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherConst = dynamic_cast<Constant*>(other.get());
    if(!otherConst){
        return false;
    }
    return value == otherConst->value;
}

std::string Constant::display() const{
    return std::to_string(value);
}

// Variable

std::string Variable::getName(){
    return name;
}

std::shared_ptr<Function> Variable::simplify() const{
    return std::make_shared<Variable>(name);
}

bool Variable::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherVar = dynamic_cast<Variable*>(other.get());
    if(!otherVar) return false;
    return name.compare(otherVar->name);
}

std::string Variable::display() const{
    return name;
}

// Absolute Value

std::shared_ptr<Function> AbsVal::getArgument(){
    return argument;
}

std::shared_ptr<Function> AbsVal::simplify() const{
    return std::make_shared<AbsVal>(argument->simplify());
}

bool AbsVal::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherAbs = dynamic_cast<AbsVal*>(other.get());
    if(!otherAbs) return false;
    return argument->isEqual(otherAbs->argument);
}

std::string AbsVal::display() const{
    return "| " + argument->display() + " |";
}

// Polynomial

std::shared_ptr<Function> Polynomial::getCoefficient(){
    return coefficient;
}
double Polynomial::getExponent(){
    return exponent;
}
    
std::shared_ptr<Function> Polynomial::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(coefficient.get())){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Polynomial>(coefficient->simplify());
}

bool Polynomial::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherPoly = dynamic_cast<Polynomial*>(other.get());
    if(!otherPoly) return false;
    return coefficient->isEqual(otherPoly->coefficient) && exponent == otherPoly->getExponent();
}

std::string Polynomial::display() const{
    if(auto var = dynamic_cast<Variable*>(coefficient.get())){
        return coefficient->display() + "^" + std::to_string(exponent);
    }
}

// Logarithmic

std::shared_ptr<Function> Logarithmic::getBase(){
    return base;
}
std::shared_ptr<Function> Logarithmic::getArgument(){
    return argument;
}    

std::shared_ptr<Function> Logarithmic::simplify() const{
    if(base->isEqual(argument)) return std::make_shared<Constant>(1.0);

    if(argument->isEqual(std::make_shared<Constant>(1.0))) return std::make_shared<Constant>(0.0);

    auto const1 = dynamic_cast<Constant*>(base.get());
    auto const2 = dynamic_cast<Constant*>(argument.get());
    if(const1 && const2){
        double eval = this->evaluate(1.0);
        if(eval == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Logarithmic>(base->simplify(), argument->simplify());
}

bool Logarithmic::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherLog = dynamic_cast<Logarithmic*>(other.get());
    if(!otherLog) return false;
    return base->isEqual(otherLog->base) && argument->isEqual(otherLog->argument);
}

std::string Logarithmic::display() const{
    if(base->isEqual(std::make_shared<Constant>(std::exp(1.0)))){
        return "ln(" + argument->display() + ")";
    }
    else {
        return "log_" + base->display() + "(" + argument->display() + ")";
    }
}

// Exponential

std::shared_ptr<Function> Exponential::getArgument(){
    return argument;
}
std::shared_ptr<Function> Exponential::getBase(){
    return base;
}

std::shared_ptr<Function> Exponential::simplify() const {
    auto const1 = dynamic_cast<Constant*>(base.get());
    auto const2 = dynamic_cast<Constant*>(argument.get());
    if(const1 && const2){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Exponential>(base->simplify(), argument->simplify());
}

bool Exponential::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherExp = dynamic_cast<Exponential*>(other.get());
    if(!otherExp) return false;
    return base->isEqual(otherExp->base) && argument->isEqual(otherExp->argument);
}

std::string Exponential::display() const {
    if(base->isEqual(std::make_shared<Constant>(std::exp(1.0)))){
        return "e^" + argument->display();
    }
    else return base->display() + "^" + argument->display();
}