#pragma once

#include "Functions.h"


class Trigonometric : public Function{
    protected:
    std::shared_ptr<Function> argument;

    public:
    explicit Trigonometric(const std::shared_ptr<Function>& expr) : argument(expr){}

    std::shared_ptr<Function> getArgument() const;
};

// Class for sine function (sin(x))
class Sine : public Trigonometric{
    public:
    explicit Sine(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}    

    double evaluate(double x) const override;

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        // if(negativeArg(argument)){
        //     return std::make_shared<Cosine>(argument->simplify());
        // }
        return std::make_shared<Sine>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherSine = dynamic_cast<Sine*>(other.get());
        if(!otherSine) return false;
        return argument->isEqual(otherSine->argument);
    }

    std::string display() const override{
        return "sin(" + argument->display() + ")";
    }
};

class Cosine : public Trigonometric{
    public:
    explicit Cosine(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}


    double evaluate (double x) const override {
        double val = std::cos(argument->evaluate(x));
        if(std::abs(val) <= EPSILON){
            return 0.0;
        }
        if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
            return 1.0;
        }
        return val;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<Cosine>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherCosine = dynamic_cast<Cosine*>(other.get());
        if(!otherCosine) return false;
        return argument->isEqual(otherCosine->argument);
    }

    std::string display() const override{
        return "cos(" + argument->display() + ")";
    }
};

class Tangent : public Trigonometric{
    public:
    explicit Tangent(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}

    double evaluate (double x) const override {
        double val = std::tan(argument->evaluate(x));
        if(std::abs(val) <= EPSILON){
            return 0.0;
        }
        if(val > 1 - EPSILON && val < 1 + EPSILON){
            return 1;
        }
        return val;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<Tangent>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTan = dynamic_cast<Tangent*>(other.get());
        if(!otherTan) return false;
        return argument->isEqual(otherTan->argument);
    }

    std::string display() const override{
        return "tan(" + argument->display() + ")";
    }
};
//Secant
class Secant : public Trigonometric{
    public:
    explicit Secant(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}
        
    double evaluate (double x) const override {
        double val = std::cos(argument->evaluate(x));
        if(val > 0 - EPSILON && val < 0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1.0 - EPSILON && val < 1.0 + EPSILON){
            return 1.0;
        }
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Secant>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherSec = dynamic_cast<Secant*>(other.get());
        if(!otherSec) return false;
        return argument->isEqual(otherSec->argument);
    }

    std::string display() const override{
        return "sec(" + argument->display() + ")";
    }
};
//cosecant
class Cosecant : public Trigonometric{
    std::shared_ptr<Function> argument;
    public:
    explicit Cosecant(const std::shared_ptr<Function>& arg) : Trigonometric(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
                
    double evaluate (double x) const override {
        double aVal = std::sin(argument->evaluate(x));
        if(aVal > 0.0 - EPSILON && aVal < 0.0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(aVal > 1.0 - EPSILON && aVal < 1.0 + EPSILON) return 1.0;
        return 1.0 / aVal;
    }

    std::shared_ptr<Function> derivative() const override;

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Cosecant*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "csc(" + argument->display() + ")";
    }
};
//cotangent
class Cotangent : public Function{
    std::shared_ptr<Function> argument;
    public:
    Cotangent(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double aVal = std::tan(argument->evaluate(x));
        if(aVal > 0.0 - EPSILON && aVal < 0.0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(aVal > 1.0 - EPSILON && aVal < 1.0 + EPSILON) return 1.0;
        return 1.0 / aVal;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Cotangent>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Cotangent*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "cot(" + argument->display() + ")";
    }
};
//arcsin
class Arcsin : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arcsin(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::asin(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arcsin>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arcsin*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "arcsin(" + argument->display() + ")";
    }
};
//arccos
class Arccos : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arccos(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::acos(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arccos>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arccos*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "arccos(" + argument->display() + ")";
    }
};
//arctan
class Arctan : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arctan(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::atan(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Tangent>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arctan*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "arctan(" + argument->display() + ")";
    }
};
//arccot
class Arccot : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arccot(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = argument->evaluate(x);
        if (val == 0.0) {
            throw std::runtime_error("Error divide by 0");
        }
        return std::atan(1.0 / val);
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<Arccot>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arccot*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "arccot(" + argument->display() + ")";
    }
};
//arcsec
class Arcsec : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arcsec(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = argument->evaluate(x);
        if(val == 0.0){
            throw std::runtime_error("Error divide by 0");
        }
        return std::acos(1.0 / val);
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<Arcsec>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arcsec*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "arcsec(" + argument->display() + ")";
    }
};
class Arccsc : public Function{
    std::shared_ptr<Function> argument;
    public:
    Arccsc(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = argument->evaluate(x);
        if(val == 0.0){
            throw std::runtime_error("Error divide by 0");
        }
        return std::asin(1.0 / val);
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<Arccsc>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<Arccsc*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "arccsc(" + argument->display() + ")";
    }
};
//sinh
class SineH : public Function{
    std::shared_ptr<Function> argument;
    public:
    SineH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::sinh(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<SineH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<SineH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "sinh(" + argument->display() + ")";
    }
};
//cosh
class CosineH : public Function{
    std::shared_ptr<Function> argument;
    public:
    CosineH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::cosh(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<CosineH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<CosineH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "cosh(" + argument->display() + ")";
    }
};
//tanh
class TangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
    TangentH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        return std::tanh(argument->evaluate(x));
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<TangentH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<TangentH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "tanh(" + argument->display() + ")";
    }
};

//sech
class SecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
    SecantH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::cosh(argument->evaluate(x));
        if(val > 0.0 - EPSILON && val < 0.0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1.0 - EPSILON && val < 1.0 + EPSILON) return 1.0;
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<SecantH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<SecantH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "sech(" + argument->display() + ")";
    }
};
//csch
class CosecantH : public Function{
    std::shared_ptr<Function> argument;
    public:
    CosecantH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::sinh(argument->evaluate(x));
        if(val > 0.0 - EPSILON && val < 0.0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1.0 - EPSILON && val < 1.0 + EPSILON) return 1.0;
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<CosecantH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<CosecantH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "csch(" + argument->display() + ")";
    }
};
//coth
class CotangentH : public Function{
    std::shared_ptr<Function> argument;
    public:
    CotangentH(std::shared_ptr<Function> arg) : argument(arg) {}

    std::shared_ptr<Function> getArgument(){
        return argument;
    }
        
    double evaluate (double x) const override {
        double val = std::tanh(argument->evaluate(x));
        if(val > 0.0 - EPSILON && val < 0.0 + EPSILON){
            throw std::runtime_error("Error divide by 0");
        }
        if(val > 1.0 - EPSILON && val < 1.0 + EPSILON) return 1.0;
        return 1.0 / val;
    }

    std::shared_ptr<Function> derivative() const override;

    std::shared_ptr<Function> simplify() const override{
        if(auto constant = dynamic_cast<Constant*>(argument.get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
                return std::make_shared<Constant>(eval);
            }
        }
        return std::make_shared<CotangentH>(argument->simplify());
    }

    bool isEqual(std::shared_ptr<Function>& other){
        auto otherTrig = dynamic_cast<CotangentH*>(other.get());
        if(!otherTrig) return false;
        return argument->isEqual(otherTrig->argument);
    }

    std::string display() const override{
        return "coth(" + argument->display() + ")";
    }
};
