#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include <functional>
#include "trigSimplify.h"

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

// Sum expressions f(x) + g(x)
class Sum : public Function {
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Sum(std::shared_ptr<Function> f, std::shared_ptr<Function> g) :
        left(f), right(g) {}

    std::shared_ptr<Function> getLeft(){
        return left;
    }
    std::shared_ptr<Function> getRight(){
        return right;
    }

    double evaluate(double x) const override{
        return left->evaluate(x) + right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Sum>(left->derivative(), right->derivative());
    }
    //Add Trig identity checks
    std::shared_ptr<Function> simplify() const override{
        auto simplifiedLeft = left->simplify();
        auto simplifiedRight = right->simplify();

        auto constLeft = dynamic_cast<Constant*>(simplifiedLeft.get());
        auto constRight = dynamic_cast<Constant*>(simplifiedRight.get());

        if(constLeft && constRight) return std::make_shared<Constant>(simplifiedLeft->evaluate(1) + simplifiedRight->evaluate(1));

        if(constLeft && simplifiedLeft->evaluate(0) == 0.0){
            return simplifiedRight;
        }
        if(constRight && simplifiedRight->evaluate(0) == 0){
            return simplifiedLeft;
        }
        if(simplifiedLeft->isEqual(simplifiedRight)){
            return std::make_shared<Product>(std::make_shared<Constant>(2.0), simplifiedLeft);
        }
        return std::make_shared<Sum>(simplifiedLeft, simplifiedRight);
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherSum = dynamic_cast<Sum*>(other.get());
        if (!otherSum) return false;

        // Compare left and right subtrees recursively
        return left->isEqual(otherSum->left) && right->isEqual(otherSum->right);
    }
};

//Add Trig identity checks
// Difference expression f(x) - g(x)
class Difference : public Function{
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Difference(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : 
        left(f), right(g) {}
    
    std::shared_ptr<Function> getLeft(){
        return left;
    }
    std::shared_ptr<Function> getRight(){
        return right;
    }

    double evaluate(double x) const override{
        return left->evaluate(x) - right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Difference>(left->derivative(), right->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
        auto simplifiedLeft = left->simplify();
        auto simplifiedRight = right->simplify();

        if(dynamic_cast<Constant*>(simplifiedLeft.get()) && simplifiedLeft->evaluate(0) == 0){
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0), simplifiedRight);
        }
        if(dynamic_cast<Constant*>(simplifiedRight.get()) && simplifiedRight->evaluate(0) == 0){
            return simplifiedLeft;
        }
        if(simplifiedLeft->isEqual(simplifiedRight)){
            return std::make_shared<Constant>(0.0);
        }
        return std::make_shared<Difference>(simplifiedLeft, simplifiedRight);
    }

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherDiff = dynamic_cast<Difference*>(other.get());
        if (!otherDiff) return false;

        // Compare left and right subtrees recursively
        return left->isEqual(otherDiff->left) && right->isEqual(otherDiff->right);
    }
};

// Product expressions f(x) * g(x)
class Product : public Function {
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Product(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : 
        left(f), right(g) {}

    std::shared_ptr<Function> getLeft(){
        return left;
    }
    std::shared_ptr<Function> getRight(){
        return right;
    }

    double evaluate(double x) const override{
        return left->evaluate(x) * right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Sum>(
            std::make_shared<Product>(left -> derivative(), right),
            std::make_shared<Product>(left, right->derivative())
        );
    }

    std::shared_ptr<Function> simplify() const override{
        auto simplifiedLeft = left->simplify();
        auto simplifiedRight = right->simplify();

        if(dynamic_cast<Constant*>(simplifiedLeft.get()) && simplifiedLeft->evaluate(0) == 0){
            return std::make_shared<Constant>(0.0);
        }
        if(isOne(simplifiedLeft)){
            return simplifiedRight;
        }
        if(dynamic_cast<Constant*>(simplifiedRight.get()) && simplifiedRight->evaluate(0) == 0){
            return std::make_shared<Constant>(0.0);
        }
        if(dynamic_cast<Constant*>(simplifiedRight.get()) && simplifiedRight->evaluate(0) == 1.0){
            return simplifiedLeft;
        }
        if(simplifiedLeft->isEqual(simplifiedRight)){
            return std::make_shared<Polynomial>(simplifiedLeft, 2.0);
        }
        
        return std::make_shared<Product>(simplifiedLeft, simplifiedRight);
    }

    bool isEqual(const std::shared_ptr<Function>& other){
        auto otherProd = dynamic_cast<Product*>(other.get());
        if(!otherProd) return false;
        return left->isEqual(otherProd->left) && right->isEqual(otherProd->right);
    }
};

// Quotient expressions f(x) / g(x)
// Precondition, g(x) != 0
class Quotient : public Function {
    std::shared_ptr<Function> left;     //Numerator
    std::shared_ptr<Function> right;    //Denominator
    public:
    Quotient(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : left(f), right(g){}

    std::shared_ptr<Function> getLeft(){
        return left;
    }
    std::shared_ptr<Function> getRight(){
        return right;
    }

    double evaluate(double x) const override{
        double denominator = right->evaluate(0);
        if(denominator == 0){
            throw std::runtime_error("Error divide by 0");
        }
        return left->evaluate(x) / denominator;

    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Quotient>(
            std::make_shared<Difference>(std::make_shared<Product>(right->derivative(), left)
            , std::make_shared<Product>(right, left->derivative())),
             std::make_shared<Polynomial>(left, 2.0));
    
    }

    std::shared_ptr<Function> simplify() const override{
        auto simplifiedTop = right->simplify();
        auto simplifiedBottom = left->simplify();


    }
    
    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherQuot = dynamic_cast<Quotient*>(other.get());
        if(!otherQuot) return false;
        return left->isEqual(otherQuot->left) && right->isEqual(otherQuot->right);
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

// Class for sine function (sin(x))
class Sine : public Function {
    std::shared_ptr<Function> argument;
    public:
    Sine(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }

    double evaluate(double x) const override {
        double val = std::sin(argument->evaluate(x));
        if(std::abs(val) <= EPSILON){
            return 0.0;
        }
        if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
            return 1.0;
        }

        return val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Cosine>(argument), argument->derivative());  // sin(f(x)) * f'(x)
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        if(negativeArg(argument)){
            return std::make_shared<Cosine>(argument->simplify());
        }
        return std::make_shared<Sine>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherSine = dynamic_cast<Sine*>(other.get());
        if(!otherSine) return false;
        return argument->isEqual(otherSine->argument);
    }
};

class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
    Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }

    double evaluate (double x) const override {
        double val = std::cos(argument->evaluate(x));
        if(std::abs(val) <= EPSILON){
            return 0.0;
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON){
            return 1;
        }
        return val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(
            std::make_shared<Product>(std::make_shared<Constant>(-1), 
                std::make_shared<Product>(std::make_shared<Sine>(argument), argument->derivative())));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Cosine>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherCosine = dynamic_cast<Cosine*>(other.get());
        if(!otherCosine) return false;
        return argument->isEqual(otherCosine->argument);
    }
};

class Tangent : public Function{
    std::shared_ptr<Function> argument;
    public:
    Tangent(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }

    double evaluate (double x) const override {
        double val = std::tan(argument->evaluate(x));
        if(std::abs(val) <= EPSILON){
            return 0.0;
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON){
            return 1;
        }
        return val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(
            std::make_shared<Polynomial>(std::make_shared<Secant>(argument), 2.0), 
            argument->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Tangent>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTan = dynamic_cast<Tangent*>(other.get());
        if(!otherTan) return false;
        return argument->isEqual(otherTan->argument);
    }
};
//Secant
class Secant : public Function{
    std::shared_ptr<Function> argument;
    public:
    Secant(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::cos(argument->evaluate(x));
        if(val > 0 - EPSILON && val < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON){
            return 1;
        }
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(
            std::make_shared<Product>(std::make_shared<Secant>(argument), std::make_shared<Tangent>(argument))
            ,argument->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Secant>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherSec = dynamic_cast<Secant*>(other.get());
        if(!otherSec) return false;
        return argument->isEqual(otherSec->argument);
    }
};
//cosecant
class Cosecant : public Function{
    std::shared_ptr<Function> argument;
    public:
    Cosecant(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
                
    double evaluate (double x) const override {
        double aVal = std::sin(argument->evaluate(x));
        if(aVal > 0 - EPSILON && aVal < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(aVal > 1 - EPSILON && aVal < 1 + EPSILON) return 1.0;
        return 1.0 / aVal;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0),
        std::make_shared<Product>(
            std::make_shared<Product>(std::make_shared<Cosecant>(argument), std::make_shared<Cotangent>(argument)),
            argument->derivative()));
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Cosecant*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//cotangent
class Cotangent : public Function{
    std::shared_ptr<Function> argument;
    public:
    Cotangent(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double aVal = std::tan(argument->evaluate(x));
        if(aVal > 0 - EPSILON && aVal < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(aVal > 1 - EPSILON && aVal < 1 + EPSILON) return 1.0;
        return 1.0 / aVal;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0), 
        std::make_shared<Polynomial>(std::make_shared<Product>(std::make_shared<Cosecant>, argument->derivative()),2.0));
    }

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Cotangent>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Cotangent*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//arcsin
class Arcsin : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arcsin(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::asin(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(
            std::make_shared<Polynomial>(std::make_shared<Difference>(argument->derivative(), 
            std::make_shared<Polynomial>(argument), 2), (-1.0/2.0)), argument->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Arcsin>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arcsin*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//arccos
class Arccos : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arccos(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::acos(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0), std::make_shared<Arcsin>(argument)->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Arccos>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arccos*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//arctan
class Arctan : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arctan(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::atan(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Quotient>(argument->derivative(),std::make_shared<Sum>(1, std::make_shared<Polynomial>(argument, 2.0)));
    }

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        return std::make_shared<Constant>(this->evaluate(1));
    }
    return std::make_shared<Tangent>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arctan*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//arccot
class Arccot : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arccot(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = argument->evaluate(x);
        if (val == 0.0) {
            throw std::runtime_error("Error divide by 0");
        }
        return std::atan(1.0 / val);
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Quotient>(std::make_shared<Product>(std::make_shared<Constant>(-1.0), argument->derivative()),
        std::make_shared<Sum>(std::make_shared<Constant>(1.0), std::make_shared<Polynomial>(argument, 2.0)));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Arccot>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arccot*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//arcsec
class Arcsec : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arcsec(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = argument->evaluate(x);
        if(val == 0){
            throw std::runtime_error("Error divide by 0");
        }
        return std::acos(1.0 / val);
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Quotient>(argument->derivative(),
        std::make_shared<Product>(std::make_shared<AbsVal>(argument), 
        std::make_shared<Polynomial>(
            std::make_shared<Difference>(std::make_shared<Polynomial>(argument, 2.0), std::make_shared<Constant>(1.0)), 1.0/2.0)));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Arcsec>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arcsec*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
class Arccsc : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arccsc(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = argument->evaluate(x);
        if(val == 0){
            throw std::runtime_error("Error divide by 0");
        }
        return std::asin(1.0 / val);
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Quotient>(std::make_shared<Product>(std::make_shared<Constant>(-1.0), argument->derivative()),
         std::make_shared<Product>(std::make_shared<AbsVal>(argument), 
        std::make_shared<Polynomial>(
            std::make_shared<Difference>(std::make_shared<Polynomial>(argument, 2.0), std::make_shared<Constant>(1.0)), 1.0/2.0)));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<Arccsc>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arccsc*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//sinh
class SineH : public Function{
    std::shared_ptr<Function> argument;
    public:
    SineH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::sinh(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<CosineH>(argument), argument->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<SineH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<SineH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//cosh
class CosineH : public Function{
    std::shared_ptr<Function> argument;
    public:
    CosineH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::cosh(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<SineH>(argument), argument->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<CosineH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<CosineH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//tanh
class TangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
    TangentH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::tanh(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(
            std::make_shared<Polynomial>(std::make_shared<SecantH>(argument),2.0), argument->derivative());
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<TangentH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<TangentH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};

//sech
class SecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
    SecantH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::cosh(argument->evaluate(x));
        if(val > 0 - EPSILON && val < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON) return 1.0;
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0),
        std::make_shared<Product>(argument->derivative(),
        std::make_shared<Product>(std::make_shared<SecantH>(argument), std::make_shared<TangentH>(argument))));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<SecantH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<SecantH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//csch
class CosecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
    CosecantH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::sinh(argument->evaluate(x));
        if(val > 0 - EPSILON && val < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON) return 1.0;
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0),
        std::make_shared<Product>(argument->derivative(),
        std::make_shared<Product>(std::make_shared<CosecantH>(argument), std::make_shared<Cotangent>(argument))));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<CosecantH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<CosecantH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }
};
//coth
class CotangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
    CotangentH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::tanh(argument->evaluate(x));
        if(val > 0 - EPSILON && val < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON) return 1.0;
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(
            std::make_shared<Polynomial>(std::make_shared<CosecantH>(argument),2.0), 
            std::make_shared<Product>(std::make_shared<Constant>(-1.0),argument->derivative()));
    }

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            return std::make_shared<Constant>(this->evaluate(1));
        }
        return std::make_shared<CotangentH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<CotangentH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
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
