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

class Quotient : public Function {
    std::shared_ptr<Function> top;
    std::shared_ptr<Function> bottom;
    public:
    Quotient(std::shared_ptr<Function> f, std::shared_ptr<Function> g) : top(f), bottom(g){}

    double evaluate(double x) const override{
        if(bottom->evaluate(x) == 0){
            throw std::runtime_error("Error divide by 0");
        }
        return top->evaluate(x) / bottom->evaluate(x);

    }

    std::shared_ptr<Function> derivative() const override{
        return std::make_shared<Quotient>(
            std::make_shared<Difference>(std::make_shared<Product>(top->derivative(), bottom)
            , std::make_shared<Product>(top, bottom->derivative())),
             std::make_shared<Polynomial>(bottom, 2.0));
    
    }
};

class AbsVal : public Function {
    std::shared_ptr<Function> argument;

    public:
    AbsVal(std::shared_ptr<Function> arg) : argument(arg) {}

    double evaluate(double x) const override{
        return std::abs(x);
    }

    std::shared_ptr<Function> derivative(){
        throw std::runtime_error("Absolute value has no derivative");
    }
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

// Class for polynomial functions 
class Polynomial : public Function {
    std::shared_ptr<Function> coefficient;
    double exponent;
public:
    Polynomial(std::shared_ptr<Function> coef, double exp) : coefficient(coef), exponent(exp) {}

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
        return std::make_shared<Product>(std::make_shared<Cosine>(argument), argument->derivative());  // sin(f(x)) * f'(x)
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
            return std::make_shared<Quotient>(1, std::make_shared<Cosine>(argument->evaluate(x)))->evaluate(x);
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
            return std::make_shared<Quotient>(1, std::make_shared<Sine>(argument->evaluate(x)))->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0),
            std::make_shared<Product>(
                std::make_shared<Product>(std::make_shared<Cosecant>(argument), std::make_shared<Cotangent>(argument)),
                argument->derivative()));
        }
};
//cotangent
class Cotangent : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cotangent(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Quotient>(1, std::make_shared<Tangent>(argument->evaluate(x)))->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0), 
            std::make_shared<Polynomial>(std::make_shared<Product>(std::make_shared<Cosecant>, argument->derivative()),2.0));
        }
};
//arcsin
class Arcsin : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arcsin(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::asin(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Polynomial>(std::make_shared<Difference>(argument->derivative(), 
                std::make_shared<Polynomial>(argument), 2), (-1.0/2.0)), argument->derivative());
        }
};
//arccos
class Arccos : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arccos(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::acos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0), std::make_shared<Arcsin>(argument)->derivative());
        }
};
//arctan
class Arctan : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arctan(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::atan(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Quotient>(argument->derivative(),std::make_shared<Sum>(1, std::make_shared<Polynomial>(argument, 2.0)));
        }
};
//arccot
class Arccot : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arccot(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::atan(std::make_shared<Quotient>(std::make_shared<Constant>(1.0), argument->evaluate(x))->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Quotient>(std::make_shared<Product>(std::make_shared<Constant>(-1.0), argument->derivative()),
            std::make_shared<Sum>(std::make_shared<Constant>(1.0), std::make_shared<Polynomial>(argument, 2.0)));
        }
};
//arcsec
class Arcsec : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arcsec(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::acos(std::make_shared<Quotient>(std::make_shared<Constant>(1.0), argument->evaluate(x))->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Quotient>(argument->derivative(),
            std::make_shared<Product>(std::make_shared<AbsVal>(argument), 
            std::make_shared<Polynomial>(
                std::make_shared<Difference>(std::make_shared<Polynomial>(argument, 2.0), std::make_shared<Constant>(1.0)), 1.0/2.0)));
        }
};
class Arccsc : public Function{
    std::shared_ptr<Function> argument;
    public:
        Arccsc(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::asin(std::make_shared<Quotient>(std::make_shared<Constant>(1.0), argument->evaluate(x))->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Quotient>(std::make_shared<Product>(std::make_shared<Constant>(-1.0), argument->derivative()),
             std::make_shared<Product>(std::make_shared<AbsVal>(argument), 
            std::make_shared<Polynomial>(
                std::make_shared<Difference>(std::make_shared<Polynomial>(argument, 2.0), std::make_shared<Constant>(1.0)), 1.0/2.0)));
        }
};
//sinh
class SineH : public Function{
    std::shared_ptr<Function> argument;
    public:
        SineH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::sinh(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<CosineH>(argument), argument->derivative());
        }
};
//cosh
class CosineH : public Function{
    std::shared_ptr<Function> argument;
    public:
        CosineH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cosh(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<SineH>(argument), argument->derivative());
        }
};
//tanh
class TangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
        TangentH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::tanh(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Polynomial>(std::make_shared<SecantH>(argument),2.0), argument->derivative());
        }
};

//sech
class SecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
        SecantH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Quotient>(1, std::make_shared<CosineH>(argument->evaluate(x)))->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0),
            std::make_shared<Product>(argument->derivative(),
            std::make_shared<Product>(std::make_shared<SecantH>(argument), std::make_shared<TangentH>(argument))));
        }
};
//csch
class CosecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
        CosecantH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Quotient>(1, std::make_shared<SineH>(argument->evaluate(x)))->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<Constant>(-1.0),
            std::make_shared<Product>(argument->derivative(),
            std::make_shared<Product>(std::make_shared<CosecantH>(argument), std::make_shared<Cotangent>(argument))));
        }
};
//coth
class CotangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
        CotangentH(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::make_shared<Quotient>(1, std::make_shared<TangentH>(argument->evaluate(x)))->evaluate(x);
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(
                std::make_shared<Polynomial>(std::make_shared<CosecantH>(argument),2.0), 
                std::make_shared<Product>(std::make_shared<Constant>(-1.0),argument->derivative()));
        }
};

class Logarithmic : public Function{
    std::shared_ptr<Function> argument;
    std::shared_ptr<Function> base;
    public:
        Logarithmic(std::shared_ptr<Function> arg, std::shared_ptr<Function> b) : base(b), argument(arg) {}

        double evaluate (double x) const override {
            return std::log(argument->evaluate(x)) / std::log(base->evaluate(x));
        }
        //NOT RIGHT!!!
        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Quotient>(std::make_shared<Logarithmic>(base, std::exp(1.0)), std::make_shared<Logarithmic>(argument, std::exp(1.0)))->derivative();
        }
};

class Exponential : public Function{
    std::shared_ptr<Function> argument;
    std::shared_ptr<Function> base;
    public:
        Exponential(std::shared_ptr<Function> a, std::shared_ptr<Function> arg) : base(a), argument(arg) {}

        double evaluate (double x) const override {
            return std::pow(base->evaluate(x), argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Product>(std::make_shared<Exponential>(base, argument), 
            std::make_shared<Product>(argument,std::make_shared<Logarithmic>(base))->derivative());
        }
};
