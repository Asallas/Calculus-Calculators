#include "trigFunctions.h"

std::shared_ptr<Function> Trigonometric::getArgument() const{
    return argument;
}

double Sine::evaluate(double x) const{
    double val = std::sin(argument->evaluate(x));
    if(std::abs(val) <= EPSILON){
        return 0.0;
    }
    if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
        return 1.0;
        }

    return val;
}
