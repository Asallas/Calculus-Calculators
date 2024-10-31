#include "Functions.h"
#include "trigFunctions.h"
#include "arithmeticOperands.h"

// Derivatives of arithmetic operations

// (f(x) + g(x))' = f'(x) + g'(x)
std::shared_ptr<Function> Sum::derivative() const{
    return std::make_shared<Sum>(left->derivative(), right->derivative());
}

// (f(x) - g(x))' = f'(x) - g'(x)
std::shared_ptr<Function> Difference::derivative() const{
    return std::make_shared<Difference>(left->derivative(), right->derivative());
}

// (f(x)*g(x))' = f'(x)*g(x) + f(x)*g'(x)
std::shared_ptr<Function> Product::derivative() const{
    return std::make_shared<Sum>(
        std::make_shared<Product>(left -> derivative(), right),
        std::make_shared<Product>(left, right->derivative()));
}

// (f(x) / g(x))' = f'(x) * g(x) - f(x) * g'(x) /
//                            (g(x)^2)
std::shared_ptr<Function> Quotient::derivative() const{
    return std::make_shared<Quotient>(
        std::make_shared<Difference>(std::make_shared<Product>(right->derivative(), left), 
                std::make_shared<Product>(right, left->derivative())),
        std::make_shared<Polynomial>(left, 2.0));
}

// Base derivatives

// (C)' = 0
std::shared_ptr<Function> Constant::derivative() const {
    return std::make_shared<Constant>(0.0);
}

// x' = 1
std::shared_ptr<Function> Variable::derivative() const{
    return std::make_shared<Constant>(1.0);
}

// Elementary function derivatives

// (|f(x)|)' = (f(x) * f'(x)) / |f(x)|
std::shared_ptr<Function> AbsVal::derivative() const{
    return std::make_shared<Quotient>(std::make_shared<Product>(argument, argument->derivative()), 
        std::make_shared<AbsVal>(argument));
}

// A * f'(x) * f(x)^(A-1)
std::shared_ptr<Function> Polynomial::derivative() const{
    if (exponent == 0) return std::make_shared<Constant>(0);  // Derivative of constant
    return std::make_shared<Product>(                                   //Af'(x)f(x)^(A-1)
        std::make_shared<Polynomial>(                                  //Af(x)^(A-1)
        std::make_shared<Product>(                                                                  
            std::make_shared<Product>(coefficient, std::make_shared<Constant>(exponent))), exponent - 1), 
            coefficient->derivative());                                 //f'(x)
}


// (log_g(x)(f(x)))' = (g(x) * f'(x) - g'(x) * f(x) * log_g(x)(f(X))) / 
//                            (g(x) * f(x) * ln(g(x)))
std::shared_ptr<Function> Logarithmic::derivative() const{
    return std::make_shared<Quotient>(
        std::make_shared<Difference>(std::make_shared<Product>(base, argument->derivative()),
        std::make_shared<Product>(
            std::make_shared<Product>(base->derivative(), argument), std::make_shared<Logarithmic>(base, argument))),
            std::make_shared<Product>(std::make_shared<Product>(base, argument), 
                std::make_shared<Logarithmic>(std::make_shared<Constant>(std::exp(1.0)), base)));
}

// (g(x)^f(X))' = g(x)^f(x) * (f(x)ln(g(x)))'
std::shared_ptr<Function> Exponential::derivative() const{
    return std::make_shared<Product>(std::make_shared<Exponential>(base, argument), 
        std::make_shared<Product>(argument,
            std::make_shared<Logarithmic>(std::make_shared<Constant>(std::exp(1.0)), base))->derivative());
}

// Trigonometric derivatives

// sin(f(X))' = cos(f(x)) * f'(x)
std::shared_ptr<Function> Sine::derivative() const{
    return std::make_shared<Product>(std::make_shared<Cosine>(this->getArgument()), this->getArgument()->derivative());
}

// cos(f(x))' = -sin(f(x)) * f'(x)
std::shared_ptr<Function> Cosine::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Product>(std::make_shared<Constant>(-1.0), 
            std::make_shared<Product>(std::make_shared<Sine>(argument), argument->derivative())));
}

// tan(f(x))' = sec^2(f(x)) * f'(x)
std::shared_ptr<Function> Tangent::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Polynomial>(std::make_shared<Secant>(argument), 2.0), 
        argument->derivative());
}

// sec(f(x))' = sec(f(x)) * tan(f(x)) * f'(x)
std::shared_ptr<Function> Secant::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Product>(std::make_shared<Secant>(argument), std::make_shared<Tangent>(argument)), 
        argument->derivative());
}

// csc(f(x))' = -csc(f(x)) * cot(f(x)) * f'(x)
std::shared_ptr<Function> Cosecant::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Constant>(-1.0),
        std::make_shared<Product>(
            std::make_shared<Product>(std::make_shared<Cosecant>(argument), std::make_shared<Cotangent>(argument)),
            argument->derivative()));
}

// cot(f(x))' = -csc(f(x))^2 * f'(x)
std::shared_ptr<Function> Cotangent::derivative() const{
        return std::make_shared<Product>(
            std::make_shared<Constant>(-1.0), 
            std::make_shared<Product>(
                std::make_shared<Polynomial>(std::make_shared<Cosecant>(argument), 2.0),
                argument->derivative()));
    }

// Inverse trig derivatives

// sin^-1(f(x))' = arcsin(f(x))' = f'(x)(1-f(x)^2)^(-1/2) = f'(x)/sqrt(1-f(x)^2)
std::shared_ptr<Function> Arcsin::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Polynomial>(
            std::make_shared<Difference>(std::make_shared<Constant>(1.0), 
                std::make_shared<Polynomial>(argument), 2.0), 
            (-1.0/2.0)), 
        argument->derivative());
}

// cos^-1(f(x))' = arccos(f(x))' = -f'(x)(1-f(x)^2)^(-1/2) = -f'(x)/sqrt(1-f(x)^2) = -arcsin'(f(x))
std::shared_ptr<Function> Arccos::derivative() const{
    return std::make_shared<Product>(std::make_shared<Constant>(-1.0), 
        std::make_shared<Arcsin>(argument)->derivative());
}

// arctan(x)' = f'(x)/(1 + f(x)^2)
std::shared_ptr<Function> Arctan::derivative() const{
    return std::make_shared<Quotient>(argument->derivative(),
        std::make_shared<Sum>(std::make_shared<Constant>(1.0), std::make_shared<Polynomial>(argument, 2.0)));
}

// arccot(f(x))' = -arctan(f(x))' = -f'(x)/(1 + f(x)^2) 
std::shared_ptr<Function> Arccot::derivative() const{
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0), 
        std::make_shared<Arctan>(argument)->derivative());
}

// arcsec(f(x))' = f'(x) / (|f(x)|sqrt(f(x)^2 - 1))
std::shared_ptr<Function> Arcsec::derivative() const{
    return std::make_shared<Quotient>(argument->derivative(),
    std::make_shared<Product>(std::make_shared<AbsVal>(argument), 
    std::make_shared<Polynomial>(
        std::make_shared<Difference>(std::make_shared<Polynomial>(argument, 2.0), std::make_shared<Constant>(1.0)), 1.0/2.0)));
}

// arccsc(f(x))' = -arcsec(f(x))' = -f'(x) / (|f(x)|sqrt(f(x)^2 - 1))
std::shared_ptr<Function> Arccsc::derivative() const{
    return std::make_shared<Product>(std::make_shared<Constant>(-1.0), 
        std::make_shared<Arcsec>(argument)->derivative());
}

// Hyperbolic derivatives

// sinh(f(x))' = cosh(f(x)) * f'(x)
std::shared_ptr<Function> SineH::derivative() const{
    return std::make_shared<Product>(std::make_shared<CosineH>(argument), argument->derivative());
}

// cosh(f(x))' = sinh(f(x)) * f'(x)
std::shared_ptr<Function> CosineH::derivative() const{
     return std::make_shared<Product>(std::make_shared<SineH>(argument), argument->derivative());
}

// tanh(f(x))' = sech(f(x))^2 * f'(x)
std::shared_ptr<Function> TangentH::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Polynomial>(std::make_shared<SecantH>(argument),2.0), argument->derivative());
}

// sech(f(x))' = -sech(f(x)) * tanh(f(x)) * f'(x)
std::shared_ptr<Function> SecantH::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Constant>(-1.0),
        std::make_shared<Product>(
            argument->derivative(),
            std::make_shared<Product>(
                std::make_shared<SecantH>(argument), 
                std::make_shared<TangentH>(argument))));
}

// csch(f(x))' = -csch(f(x)) * coth(f(x)) * f'(x) 
std::shared_ptr<Function> CosecantH::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Constant>(-1.0),
        std::make_shared<Product>(
            argument->derivative(),
            std::make_shared<Product>(
                std::make_shared<CosecantH>(argument), 
                std::make_shared<Cotangent>(argument))));
}

// coth(f(x))' =  -csch(f(x))^2 * f'(x)
std::shared_ptr<Function> CotangentH::derivative() const{
    return std::make_shared<Product>(
        std::make_shared<Polynomial>(std::make_shared<Constant>(-1.0), 
        std::make_shared<Product>(
            std::make_shared<CosecantH>(argument),2.0),
            argument->derivative()));
}