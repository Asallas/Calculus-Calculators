#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define EPSILON 1e-12

#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include <functional>
#include "arithmeticOperands.h"
#include "trigFunctions.h"
#include "functionChecks.h"


// Base class for all functions
// Root node
class Function {
public:
    virtual ~Function() = default;
    virtual double evaluate(double x) const = 0;   // Evaluate the function at x
    virtual std::shared_ptr<Function> derivative() const = 0;  // Return the derivative of the function
    virtual std::shared_ptr<Function> simplify() const = 0;
    virtual bool isEqual(const std::shared_ptr<Function>& other) const = 0;
    virtual std::string display() const = 0;
};
// Final child nodes for expressions
// Class for constant functions
class Constant : public Function {
    double value;
public:
    Constant(double val) : value(val) {}

    double getValue();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};
//Can be words or characters
class Variable : public Function {
    std::string name;
    public:
    Variable(std::string x) : name(x){}

    std::string getName();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify()const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};


class AbsVal : public Function {
    std::shared_ptr<Function> argument;

    public:
    AbsVal(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};


// Class for polynomial functions 
class Polynomial : public Function {
    std::shared_ptr<Function> coefficient;
    double exponent;
public:
    Polynomial(std::shared_ptr<Function> coef, double exp) : coefficient(coef), exponent(exp) {}

    std::shared_ptr<Function> getCoefficient();
    double getExponent();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

class Logarithmic : public Function{
    std::shared_ptr<Function> base;
    std::shared_ptr<Function> argument;
    public:
    Logarithmic(std::shared_ptr<Function> b, std::shared_ptr<Function> arg) : base(b), argument(arg) {}

    std::shared_ptr<Function> getBase();
    std::shared_ptr<Function> getArgument();

    double evaluate (double x) const override;
    
    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

class Exponential : public Function{
    std::shared_ptr<Function> argument;
    std::shared_ptr<Function> base;
    public:
    Exponential(std::shared_ptr<Function> a, std::shared_ptr<Function> arg) : base(a), argument(arg) {}

    std::shared_ptr<Function> getArgument();
    std::shared_ptr<Function> getBase();

    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

#endif