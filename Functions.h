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
    int exponent;
public:
    Polynomial(double coef, int exp) : coefficient(coef), exponent(exp) {}

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
        return std::make_shared<Polynomial>(1, 0);  // Placeholder, need product rule with argument
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
            return std::make_shared<Polynomial>(1,0);
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
            return std::make_shared<Polynomial>(1,0);
        }
};
//Secant
class Secant : public Function{
    std::shared_ptr<Function> argument;
    public:
        Secant(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//cosecant
class Cosecant : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosecant(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
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
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
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
            return std::make_shared<Polynomial>(1,0);
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
class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//tanh
class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};

//sech
class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//csch
class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
//coth
class Cosine : public Function{
    std::shared_ptr<Function> argument;
    public:
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

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
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

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
        Cosine(std::shared_ptr<Function> arg) : argument(arg) {}

        double evaluate (double x) const override {
            return std::cos(argument->evaluate(x));
        }

        std::shared_ptr<Function> derivative() const override {
            return std::make_shared<Polynomial>(1,0);
        }
};
