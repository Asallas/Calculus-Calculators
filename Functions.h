#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include <functional>

// Base class for all functions
class Function {
public:
    virtual double evaluate(double x) const = 0;   // Evaluate the function at x
    virtual std::shared_ptr<Function> derivative() const = 0;  // Return the derivative of the function
    virtual ~Function() = default;
};

class Sum : public Function {
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Sum(std::shared_ptr<Function> f, std::shared_ptr<Function> g) :
        left(f), right(g) {}

    double evaluate(double x) const override{
        return left->evaluate(x) + right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Sum>(left->derivative(), right->derivative());
    }
};

class Difference : public Function{
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Difference(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : 
        left(f), right(g) {}
    
    double evaluate(double x) const override{
        return left->evaluate(x) - right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Difference>(left->derivative(), right->derivative());
    }
};

class Product : public Function {
    std::shared_ptr<Function> left;
    std::shared_ptr<Function> right;

    public:
    Product(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : 
        left(f), right(g) {}

    double evaluate(double x) const override{
        return left->evaluate(x) * right->evaluate(x);
    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Sum>(
            std::make_shared<Product>(left -> derivative(), right),
            std::make_shared<Product>(left, right->derivative())
        );
    }
};

class Quotient: Function {

};

// Class for constant functions
class Constant : public Function {
    double value;
public:
    Constant(double val) : value(val) {}

    double evaluate(double x) const override {
        return value;
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Constant>(0);
    }
};

// Class for polynomial functions (e.g., 5x^3)
class Polynomial : public Function {
    double coefficient;
    double exponent;
public:
    Polynomial(double coef, double exp) : coefficient(coef), exponent(exp) {}

    double evaluate(double x) const override {
        return coefficient * std::pow(x, exponent);
    }

    std::shared_ptr<Function> derivative() const override {
        if (exponent == 0) return std::make_shared<Constant>(0);  // Derivative of constant
        return std::make_shared<Polynomial>(coefficient * exponent, exponent - 1);
    }
};

// Class for sine function (sin(x))
class Sine : public Function {
    std::shared_ptr<Function> argument;
public:
    Sine(std::shared_ptr<Function> arg) : argument(arg) {}

    double evaluate(double x) const override {
        return std::sin(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override {
        return std::make_shared<Product>(std::make_shared<Cosine>(argument), argument->derivative());  // Placeholder, need product rule with argument
    }
};

class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Product>(std::make_shared<Constant>(-1), 
                    std::make_shared<Product>(std::make_shared<Sine>(argument), argument->derivative())));
        }
};

class Tangent : public Function{
    std::shared_ptr<Function> argument;
    public:
        Tangent(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::tan(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Polynomial>(std::make_shared<Secant>(argument), 2.0), 
                argument->derivative());
        }
};
//Secant
class Secant : public Function{
    std::shared_ptr<Function> argument;
    public:
        Secant(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Polynomial>(std::make_shared<Cosine>(argument->evaluate(x)), -1)->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Product>(std::make_shared<Secant>(argument), std::make_shared<Tangent>(argument))
                ,argument->derivative());
        }
};
//cosecant
class Cosecant : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosecant(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Polynomial>(std::make_shared<Sine>(argument->evaluate(x)), -1.0)->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//cotangent
class Cotangent : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cotangent(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Polynomial>(std::make_shared<Tangent>(argument->evaluate(x)), -1.0)->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(std::make_shared<Product>(std::make_shared<Cosecant>, argument->derivative()),2.0);
        }
};
//arcsin
class Arcsin : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arcsin(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Polynomial>(std::make_shared<Difference>(1, 
                std::make_shared<Polynomial>(argument), 2), (-1.0/2.0))),argument->derivative());
        }
};
//arccos
class Arccos : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arccos(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//arctan
class arctan : public Function{
    std::shared_ptr<Function> argument;
    public:
        arctan(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//sinh
class SineH : public Function{
    std::shared_ptr<Function> argument;
    public:
        SineH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//cosh
class CosineH : public Function{
    std::shared_ptr<Function> argument;
    public:
        CosineH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//tanh
class TangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
        TangentH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};

//sech
class SecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
        SecantH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//csch
class CosecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
        CosecantH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//coth
class CotangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
        CotangentH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};

class Logarithmic : public Function{
    std::shared_ptr<Function> argument;
    public:
        Logarithmic(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};

class Exponential : public Function{
    std::shared_ptr<Function> argument;
    public:
        Exponential(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
