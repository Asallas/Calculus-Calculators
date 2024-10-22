#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include <functional>
#include "trigSimplify.h"
#include "arithmeticOperands.h"
#include "trigFunctions.h"

#define EPSILON 1e-12

// Base class for all functions
// Root node
class Function {
public:
    virtual ~Function() = default;
    virtual double evaluate(double x) const = 0;   // Evaluate the function at x
    virtual std::shared_ptr<Function> derivative() const = 0;  // Return the derivative of the function
    virtual std::shared_ptr<Function> simplify() const = 0;
    virtual bool isEqual(const std::shared_ptr<Function>& other) const = 0;
};
// Final child nodes for expressions
// Class for constant functions
class Constant : public Function {
    double value;
public:
    Constant(double val) : value(val) {}

    double getValue(){
        return value;
    }

    double evaluate(double x) const override {
        return value;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Constant>(0);
    }

    std::shared_ptr<Function> simplify() const override{
        return std::make_shared<Constant>(value);
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherConst = dynamic_cast<Constant*>(other.get());
        if(!otherConst){
            return false;
        }
        return value == otherConst->value;
    }
};
//Can be words or characters
class Variable : public Function {
    std::string name;
    public:
    Variable(std::string x) : name(x){}

    std::string getName(){
        return name;
    }

    double evaluate(double x){
        return x;
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Constant>(1.0);
    }

    std::shared_ptr<Function> simplify(){
        return std::make_shared<Variable>(name);
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherVar = dynamic_cast<Variable*>(other.get());
        if(!otherVar) return false;
        return name.compare(otherVar->name);
    }
};


class AbsVal : public Function {
    std::shared_ptr<Function> argument;

    public:
    AbsVal(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }

    double evaluate(double x) const override{
        return std::abs(x);
    }

    std::shared_ptr<Function> derivative(){
        return std::make_shared<Quotient>(std::make_shared<Product>(argument, argument->derivative()), 
            std::make_shared<AbsVal>(argument));
    }

    std::shared_ptr<Function> simplify(){
        return std::make_shared<AbsVal>(argument->simplify());
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherAbs = dynamic_cast<AbsVal*>(other.get());
        if(!otherAbs) return false;

        return argument->isEqual(otherAbs->argument);
    }
};


// Class for polynomial functions 
class Polynomial : public Function {
    std::shared_ptr<Function> coefficient;
    double exponent;
public:
    Polynomial(std::shared_ptr<Function> coef, double exp) : coefficient(coef), exponent(exp) {}

    std::shared_ptr<Function> getCoefficient(){
        return coefficient;
    }
    double getExponent(){
        return exponent;
    }

    double evaluate(double x) const override {
        return std::pow(coefficient->evaluate(x), exponent);
    }
    //Derivative will be of the form f'(x) * A *(f(x))^(A-1)
    std::shared_ptr<Function> derivative() const override {
        if (exponent == 0) return std::make_shared<Constant>(0);  // Derivative of constant
        return std::make_shared<Product>(                                   //Af'(x)f(x)^(A-1)
            std::make_shared<Polynomial>(                                  //Af(x)^(A-1)
            std::make_shared<Product>(                                                                  
                std::make_shared<Product>(coefficient, std::make_shared<Constant>(exponent))), exponent - 1), 
                coefficient->derivative());                                 //f'(x)
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(coefficient.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Polynomial>(coefficient->simplify());
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherPoly = dynamic_cast<Polynomial*>(other.get());
        if(!otherPoly) return false;
        return coefficient->isEqual(otherPoly->coefficient) && exponent == otherPoly->getExponent();
    }
};

class Logarithmic : public Function{
    std::shared_ptr<Function> base;
    std::shared_ptr<Function> argument;
    public:
    Logarithmic(std::shared_ptr<Function> b, std::shared_ptr<Function> arg) : base(b), argument(arg) {}

    std::shared_ptr<Function> getBase(){
        return base;
    }
    std::shared_ptr<Function> getArgument(){
        return argument;
    }

    double evaluate (double x) const override {
        return std::log(argument->evaluate(x)) / std::log(base->evaluate(x));
    }
    
    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Quotient>(
            std::make_shared<Difference>(std::make_shared<Product>(base, argument->derivative()),
            std::make_shared<Product>(
                std::make_shared<Product>(base->derivative(), argument), std::make_shared<Logarithmic>(base, argument))),
                std::make_shared<Product>(std::make_shared<Product>(base, argument), 
                    std::make_shared<Logarithmic>(std::make_shared<Constant>(std::exp(1.0)), base)));
    }

    std::shared_ptr<Function> simplify() const override{
        if(base->isEqual(argument)) return std::make_shared<Constant>(1.0);
        if(argument->isEqual(std::make_shared<Constant>(1.0))) return std::make_shared<Constant>(0.0);
        auto const1 = dynamic_cast<Constant*>(base.get());
        auto const2 = dynamic_cast<Constant*>(argument.get());
        if(const1 && const2){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Logarithmic>(base->simplify(), argument->simplify());
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherLog = dynamic_cast<Logarithmic*>(other.get());
        if(!otherLog) return false;
        return base->isEqual(otherLog->base) && argument->isEqual(otherLog->argument);
    }
};

class Exponential : public Function{
    std::shared_ptr<Function> argument;
    std::shared_ptr<Function> base;
    public:
    Exponential(std::shared_ptr<Function> a, std::shared_ptr<Function> arg) : base(a), argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
    std::shared_ptr<Function> getBase(){
        return base;
    }

    double evaluate (double x) const override {
        return std::pow(base->evaluate(x), argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Exponential>(base, argument), 
        std::make_shared<Product>(argument,std::make_shared<Logarithmic>(base))->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
        auto const1 = dynamic_cast<Constant*>(base.get());
        auto const2 = dynamic_cast<Constant*>(argument.get());
        if(const1 && const2){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Exponential>(base->simplify(), argument->simplify());
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherExp = dynamic_cast<Exponential*>(other.get());
        if(!otherExp) return false;
        return base->isEqual(otherExp->base) && argument->isEqual(otherExp->argument);
    }
};
