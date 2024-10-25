#pragma once
#include "Functions.h"


// Sum expressions f(x) + g(x)
class Sum : public Function {
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Sum(std::shared_ptr<Function> f, std::shared_ptr<Function> g) :
        left(f), right(g) {}

    std::shared_ptr<Function> getLeft();
    std::shared_ptr<Function> getRight();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    //Add Trig identity checks
    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override{
        return left->display() + " + " + right->display();
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
    
    std::shared_ptr<Function> getLeft();
    std::shared_ptr<Function> getRight();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Product expressions f(x) * g(x)
class Product : public Function {
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Product(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : 
        left(f), right(g) {}

    std::shared_ptr<Function> getLeft();
    std::shared_ptr<Function> getRight();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Quotient expressions f(x) / g(x)
// Precondition, g(x) != 0
class Quotient : public Function {
    std::shared_ptr<Function> left;     //Numerator
    std::shared_ptr<Function> right;    //Denominator
    public:
    Quotient(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : left(f), right(g){}

    std::shared_ptr<Function> getLeft();
    std::shared_ptr<Function> getRight();

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;
    
    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};