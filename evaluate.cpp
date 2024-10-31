#include "Functions.h"

/*
    Base functions
    Function list: Constant, variable
*/

double Constant::evaluate(double x) const{
    return value;
}

double Variable::evaluate(double x) const{
    return x;
}

/*
    Arithmetic functions
    Function list: Sum, Difference, Product, Quotient
*/

double Sum::evaluate(double x) const{
    return left->evaluate(x) + right->evaluate(x);
}

double Difference::evaluate(double x) const{
    return left->evaluate(x) - right->evaluate(x);
}

double Product::evaluate(double x) const {
    return left->evaluate(x) * right->evaluate(x);
}

double Quotient::evaluate(double x) const{
    double denominator = right->evaluate(0.0);
    if(denominator == 0.0){
        throw std::runtime_error("Error divide by 0");
    }
    return left->evaluate(x) / denominator;
}

/*
    Miscellaneous elementary functions
    Function list: Absolute value, Polynomial, Logarithmic, Exponential
*/

double AbsVal::evaluate(double x) const{
    return std::abs(x);
}

double Polynomial::evaluate(double x) const{
    return std::pow(coefficient->evaluate(x), exponent);
}

double Logarithmic::evaluate (double x) const{
    return std::log(argument->evaluate(x)) / std::log(base->evaluate(x));
}

double Exponential::evaluate (double x) const{
    return std::pow(base->evaluate(x), argument->evaluate(x));
}

/*
    Trigonometric functions
    Function list: sin, cos, tan, sec, csc, cot, inverse trig functions, hyperbolic functions
*/

double Sine::evaluate(double x) const{
    double val = std::sin(this->getArgument()->evaluate(x));
    if(std::abs(val) <= EPSILON){
        return 0.0;
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
        return 1.0;
        }

    return val;
}

double Cosine::evaluate (double x) const  {
    double val = std::cos(this->getArgument()->evaluate(x));
    if(std::abs(val) <= EPSILON){
        return 0.0;
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
        return 1.0;
    }
    return val;
}

double Tangent::evaluate (double x) const {
    double val = std::tan(this->getArgument()->evaluate(x));
    if(std::abs(val) <= EPSILON){
        return 0.0;
    }
    if(val > 1 - EPSILON && val < 1 + EPSILON){
        return 1;
    }
    return val;
}

double Secant::evaluate (double x) const {
    double val = std::cos(this->getArgument()->evaluate(x));
    if(val > 0 - EPSILON && val < 0 + EPSILON){
        throw std::runtime_error("Error divide by 0");
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
        return 1.0;
    }
    return 1.0 / val;
}

double Cosecant::evaluate (double x) const {
    double aVal = std::sin(this->getArgument()->evaluate(x));
    if(aVal > 0.0 - EPSILON && aVal < 0.0 + EPSILON){
        throw std::runtime_error("Error divide by 0");
    }
    if(aVal > 1.0 - EPSILON && aVal < 1.0 + EPSILON) return 1.0;
    return 1.0 / aVal;
}

double Cotangent::evaluate (double x) const {
    double aVal = std::tan(this->getArgument()->evaluate(x));
    if(aVal > 0.0 - EPSILON && aVal < 0.0 + EPSILON){
        throw std::runtime_error("Error divide by 0");
    }
    if(aVal > 1.0 - EPSILON && aVal < 1.0 + EPSILON) return 1.0;
    return 1.0 / aVal;
}

/*
    Inverse Trig function evaluations
    Function List: arcsin, arccos, artan, arccot, arcsec, arccsc
*/

double Arcsin::evaluate (double x) const {
    return std::asin(this->getArgument()->evaluate(x));
}

double Arccos::evaluate (double x) const {
    return std::acos(argument->evaluate(x));
}

double Arctan::evaluate (double x) const {
    return std::atan(argument->evaluate(x));
}

double Arccot::evaluate (double x) const {
    double val = argument->evaluate(x);
    if (val == 0.0) {
        throw std::runtime_error("Error divide by 0");
    }
    return std::atan(1.0 / val);
}

double Arcsec::evaluate (double x) const {
    double val = argument->evaluate(x);
    if(val == 0.0){
        throw std::runtime_error("Error divide by 0");
    }
    return std::acos(1.0 / val);
}

double Arccsc::evaluate (double x) const {
    double val = argument->evaluate(x);
    if(val == 0.0){
        throw std::runtime_error("Error divide by 0");
    }
    return std::asin(1.0 / val);
}

/*
    Hyperbolic Functions
    Inverse hyperbolic functions are not currently supported
    Function list: sinh, cosh, tanh, coth, sech, csch
*/

double SineH::evaluate (double x) const {
    return std::sinh(argument->evaluate(x));
}

double CosineH::evaluate (double x) const {
    return std::cosh(argument->evaluate(x));
}

double TangentH::evaluate (double x) const {
    return std::tanh(argument->evaluate(x));
}

double SecantH::evaluate (double x) const {
    double val = std::cosh(argument->evaluate(x));
    if(val > 0.0 - EPSILON && val < 0.0 + EPSILON){
        throw std::runtime_error("Error divide by 0");
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON) return 1.0;
    return 1.0 / val;
}

double CosecantH::evaluate (double x) const {
    double val = std::sinh(argument->evaluate(x));
    if(val > 0.0 - EPSILON && val < 0.0 + EPSILON){
        throw std::runtime_error("Error divide by 0");
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON) return 1.0;
    return 1.0 / val;
}

double CotangentH::evaluate (double x) const {
    double val = std::tanh(argument->evaluate(x));
    if(val > 0.0 - EPSILON && val < 0.0 + EPSILON){
        throw std::runtime_error("Error divide by 0");
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON) return 1.0;
    return 1.0 / val;
}
