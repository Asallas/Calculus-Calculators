#pragma once

#include "Functions.h"

// General class to group all derived trigonometric function classes under one class
class Trigonometric : public Function{
    protected:
    std::shared_ptr<Function> argument;

    public:
    explicit Trigonometric(const std::shared_ptr<Function>& expr) : argument(expr){}

    std::shared_ptr<Function> getArgument() const;

    virtual double evaluate(double x) const override = 0;   // Evaluate the function at x
    virtual std::shared_ptr<Function> derivative() const override = 0;  // Return the derivative of the function
    virtual std::shared_ptr<Function> simplify() const override = 0;
    virtual bool isEqual(const std::shared_ptr<Function>& other) const override = 0;
    virtual std::string display() const override = 0;
};

// Class for sine function (sin(f(x)))
class Sine : public Trigonometric{
    public:
    explicit Sine(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}    

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for cosine function (cos(f(x)))
class Cosine : public Trigonometric{
    public:
    explicit Cosine(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}

    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for tangent function (tan(f(x)))
class Tangent : public Trigonometric{
    public:
    explicit Tangent(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}

    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for secant function (sec(f(x)))
class Secant : public Trigonometric{
    public:
    explicit Secant(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other)const override;

    std::string display() const override;
};

// Class for cosecant function (csc(f(x)))
class Cosecant : public Trigonometric{
    public:
    explicit Cosecant(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}
                
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other)const override;

    std::string display() const override;
};

// Class for cotangent function (cot(f(x)))
class Cotangent : public Trigonometric{
    public:
    explicit Cotangent(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for inverse sine function (arcsin(f(x)))
class Arcsin : public Trigonometric{
    public:
    explicit Arcsin(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override{
        auto otherTrig = dynamic_cast<Arcsin*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override;
};

// Class for inverse cosine function (arccos(f(x)))
class Arccos : public Trigonometric{
    public:
    explicit Arccos(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for inverse tangent function (arctan(f(x)))
class Arctan : public Trigonometric{
    public:
    Arctan(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for inverse cotangent function (arccot(f(x)))
class Arccot : public Trigonometric{
    public:
    Arccot(std::shared_ptr<Function> arg) : Trigonometric(arg) {}

    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for inverse secant function (arcsec(f(x)))
class Arcsec : public Trigonometric{
    public:
    Arcsec(std::shared_ptr<Function> arg) : Trigonometric(arg) {}

        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for inverse cosecant function (arccsc(f(X)))
class Arccsc : public Trigonometric{
    public:
    Arccsc(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
      
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

//Hyperbolic Functions

// Class for hyperbolic sine function (sinh(f(x)))
class SineH : public Trigonometric{
    public:
    SineH(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for hyperbolic cosine function (cosh(f(x)))
class CosineH : public Trigonometric{
    public:
    CosineH(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for hyperbolic tangent function (tanh(f(x)))
class TangentH : public Trigonometric{
    public:
    TangentH(std::shared_ptr<Function> arg) : Trigonometric(arg) {}

    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};

// Class for hyperbolic secant function (sech(f(x)))
class SecantH : public Trigonometric{
    public:
    SecantH(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;
    
    std::string display() const override;
};

// Class for hyperbolic cosecant function (csch(f(x)))
class CosecantH : public Trigonometric{
    public:
    CosecantH(std::shared_ptr<Function> arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other)const override;

    std::string display() const override;
};

// Class for hyperbolic cotangent function (coth(f(x)))
class CotangentH : public Trigonometric{
    public:
    CotangentH(std::shared_ptr<Function> arg) : Trigonometric(arg) {}

    double evaluate (double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override;

    bool isEqual(const std::shared_ptr<Function>& other) const override;

    std::string display() const override;
};
