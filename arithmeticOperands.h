#pragma once
#include "Functions.h"

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

    std::shared_ptr<Function> derivative() const override;

    //Add Trig identity checks
    std::shared_ptr<Function> simplify() const override{
        auto simplifiedLeft = left->simplify();
        auto simplifiedRight = right->simplify();

        auto constLeft = dynamic_cast<Constant*>(simplifiedLeft.get());
        auto constRight = dynamic_cast<Constant*>(simplifiedRight.get());

        if(constLeft && constRight) return std::make_shared<Constant>(simplifiedLeft->evaluate(1.0) + simplifiedRight->evaluate(1.0));

        if(constLeft && simplifiedLeft->evaluate(0.0) == 0.0){
            return simplifiedRight;
        }
        if(constRight && simplifiedRight->evaluate(0.0) == 0.0){
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
    
    std::shared_ptr<Function> getLeft(){
        return left;
    }
    std::shared_ptr<Function> getRight(){
        return right;
    }

    double evaluate(double x) const override{
        return left->evaluate(x) - right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        auto simplifiedLeft = left->simplify();
        auto simplifiedRight = right->simplify();

        if(dynamic_cast<Constant*>(simplifiedLeft.get()) && simplifiedLeft->evaluate(0.0) == 0.0){
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0), simplifiedRight);
        }
        if(dynamic_cast<Constant*>(simplifiedRight.get()) && simplifiedRight->evaluate(0.0) == 0.0){
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

    std::string display() const override{
        return left->display() + " - " + right->display();
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

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        auto simplifiedLeft = left->simplify();
        auto simplifiedRight = right->simplify();

        if(dynamic_cast<Constant*>(simplifiedLeft.get()) && simplifiedLeft->evaluate(0.0) == 0.0){
            return std::make_shared<Constant>(0.0);
        }
        if(isOne(simplifiedLeft)){
            return simplifiedRight;
        }
        if(dynamic_cast<Constant*>(simplifiedRight.get()) && simplifiedRight->evaluate(0.0) == 0.0){
            return std::make_shared<Constant>(0.0);
        }
        if(dynamic_cast<Constant*>(simplifiedRight.get()) && simplifiedRight->evaluate(0.0) == 1.0){
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

    std::string display() const override{
        return "(" + left->display() + ") * (" + right->display() + ")";
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
        double denominator = right->evaluate(0.0);
        if(denominator == 0.0){
            throw std::runtime_error("Error divide by 0");
        }
        return left->evaluate(x) / denominator;

    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        auto simplifiedTop = right->simplify();
        auto simplifiedBottom = left->simplify();


    }
    
    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherQuot = dynamic_cast<Quotient*>(other.get());
        if(!otherQuot) return false;
        return left->isEqual(otherQuot->left) && right->isEqual(otherQuot->right);
    }

    std::string display() const override{
        return "(" + left->display() + ") / (" + right->display() + ")";
    }    
};