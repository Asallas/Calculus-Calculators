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


/*
    Parent class of all functions
    Full supported function list: 
        Constant, Variable,
        Absolute Value, Logarithmic, Exponential,
        Sum, Difference, Product, Quotient
        Trigonometric, Inverse Trig, Hyperbolic
*/
class Function {
public:
    virtual ~Function() = default;
    virtual double evaluate(double x) const = 0;   // Evaluate the function at x
    virtual std::shared_ptr<Function> derivative() const = 0;  // Return the derivative of the function
    virtual std::shared_ptr<Function> simplify() const = 0;
    virtual bool isEqual(const std::shared_ptr<Function>& other) const = 0;
    virtual std::string display() const = 0;
};


// Class for constant functions f(x) = C
class Constant : public Function {
    double value;
public:
    Constant(double val) : value(val) {} // Default constructor for Constant

    /**
     * Standard getter to return the value of C
     * 
     * Precondition: None
     * Postcondition: value = value, getValue() = value
     */
    double getValue();

    /**
     * Evaluates the constant function for any given value and returns the value of the constant
     * 
     * Precondition: None
     * Postcondition: value = value evaluate(double) = value
     */
    double evaluate(double x) const override;

    /**
     * Calculates the derivative of the constant f'(x) = 0
     * 
     * Precondition: none
     * Postcondition: value = value, derivative() = constant function with a value of 0
     */
    std::shared_ptr<Function> derivative() const override;

    /**
     * Simplifies the constant function. Since no simplification is possible it just returns the object
     * 
     * Precondition: none
     * Postcondition: value = value, simplify() = this
     */
    std::shared_ptr<Function> simplify() const override;

    /**
     * Compares the object with another object and compares them to see if they are the same tyoe
     * and have the same value
     * 
     * Precondition: none
     * Postcondition: value = value, isEqual() = true if equal else false
     */
    bool isEqual(const std::shared_ptr<Function>& other) const override;

    /**
     * Returns a string representing the function
     * 
     * Precondition: none
     * Postcondition: value = value, display() = "[value]"
     */
    std::string display() const override;
};

// Class for variables f(x) = x
// Can be words or characters
class Variable : public Function {
    std::string name;
    public:
    Variable(std::string x) : name(x){} 

    /**
     * Standard getter to return the name of the variable
     * 
     * Precondition: None
     * Postcondition: name = name, getName() = name
     */
    std::string getName();

    /**
     * Evaluates the variable for any given value and returns the value of the given value
     * 
     * Precondition: None
     * Postcondition: name = name evaluate(double x) = x
     */
    double evaluate(double x) const override;

    /**
     * Calculates the derivative of the variable f'(x) = 1
     * 
     * Precondition: none
     * Postcondition: name = name, derivative() = constant function with a value of 1
     */
    std::shared_ptr<Function> derivative() const override;

    /**
     * Returns the same object since a variable cannot be simplified
     * 
     * Precondition: None
     * Postcondition: value = value, simplify() = this
     */
    std::shared_ptr<Function> simplify()const override;

    /**
     * Compares another function object with this object, and returns true if the name and type are the
     * same but false otherwise
     * 
     * Precondition: none
     * Postcondition: name = name; isEqual = [true if they are the same, false otherwise]
     */
    bool isEqual(const std::shared_ptr<Function>& other) const override;

    /**
     * Returns the object as a string
     * 
     * Precondition: none
     * Postcondition: name = name, display = "name"
     */
    std::string display() const override;
};

// Class for absolute value function |f(x)|
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


// Class for polynomial functions (f(x))^n (n is any real number)
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

// Class for logarithmic functions log_b(f(x)) (b is any function)
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

// Class for exponential functions a^b (a,b are any function)
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