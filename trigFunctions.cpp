#include "trigFunctions.h"

std::shared_ptr<Function> Trigonometric::getArgument() const{
    return argument;
}

std::shared_ptr<Function> Sine::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(this->getArgument().get())){
            if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    // if(negativeArg(argument)){
    //     return std::make_shared<Cosine>(argument->simplify());
    // }
    return std::make_shared<Sine>(this->getArgument()->simplify());
}

bool Sine::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherSine = dynamic_cast<Sine*>(other.get());
    if(!otherSine) return false;
    return this->getArgument()->isEqual(otherSine->getArgument());
}

std::string Sine::display() const{
    return "sin(" + this->getArgument()->display() + ")";
}

std::shared_ptr<Function> Cosine::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(this->getArgument().get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Cosine>(this->getArgument()->simplify());
}

bool Cosine::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherCosine = dynamic_cast<Cosine*>(other.get());
    if(!otherCosine) return false;
    return this->getArgument()->isEqual(otherCosine->getArgument());
}

std::string Cosine::display() const{
    return "cos(" + argument->display() + ")";
}

std::shared_ptr<Function> Tangent::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Tangent>(argument->simplify());
}

bool Tangent::isEqual(const std::shared_ptr<Function>& other) const {
    auto otherTan = dynamic_cast<Tangent*>(other.get());
    if(!otherTan) return false;
    return this->getArgument()->isEqual(otherTan->getArgument());
}

std::string Tangent::display() const{
    return "tan(" + this->getArgument()->display() + ")";
}

std::shared_ptr<Function> Secant::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(this->getArgument().get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Secant>(this->getArgument()->simplify());
}

bool Secant::isEqual(const std::shared_ptr<Function>& other)const {
    auto otherSec = dynamic_cast<Secant*>(other.get());
    if(!otherSec) return false;
    return this->getArgument()->isEqual(otherSec->getArgument());
}

std::string Secant::display() const{
    return "sec(" + this->getArgument()->display() + ")";
}

std::shared_ptr<Function> Cosecant::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(this->getArgument().get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Cotangent>(this->getArgument()->simplify());
}

bool Cosecant::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<Cosecant*>(other.get());
    if(!otherTrig) return false;
    return this->getArgument()->isEqual(otherTrig->getArgument());
}

std::string Cosecant::display() const {
    return "csc(" + this->getArgument()->display() + ")";
}

std::shared_ptr<Function> Cotangent::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(this->getArgument().get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Cotangent>(this->getArgument()->simplify());
}

bool Cotangent::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<Cotangent*>(other.get());
    if(!otherTrig) return false;
    return this->getArgument()->isEqual(otherTrig->getArgument());
}

std::string Cotangent::display() const{
    return "cot(" + this->getArgument()->display() + ")";
}

std::shared_ptr<Function> Arcsin::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(this->getArgument().get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arcsin>(this->getArgument()->simplify());
}

bool Arcsin::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<Arcsin*>(other.get());
    if(!otherTrig) return false;
    return this->getArgument()->isEqual(otherTrig->getArgument());
}

std::string Arcsin::display() const{
    return "arcsin(" + this->getArgument()->display() + ")";
}

std::shared_ptr<Function> Arccos::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arccos>(argument->simplify());
}

bool Arccos::isEqual(const std::shared_ptr<Function>& other) const {
    auto otherTrig = dynamic_cast<Arccos*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string Arccos::display() const {
    return "arccos(" + argument->display() + ")";
}

std::shared_ptr<Function> Arctan::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Tangent>(argument->simplify());
}

bool Arctan::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<Arctan*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string Arctan::display() const {
    return "arctan(" + argument->display() + ")";
}

std::shared_ptr<Function> Arccot::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arccot>(argument->simplify());
}

bool Arccot::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<Arccot*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string Arccot::display() const {
    return "arccot(" + argument->display() + ")";
}

std::shared_ptr<Function> Arcsec::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arcsec>(argument->simplify());
}

bool Arcsec::isEqual(const std::shared_ptr<Function>& other) const {
    auto otherTrig = dynamic_cast<Arcsec*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string Arcsec::display() const{
    return "arcsec(" + argument->display() + ")";
}

std::shared_ptr<Function> Arccsc::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<Arccsc>(argument->simplify());
}

bool Arccsc::isEqual(const std::shared_ptr<Function>& other) const {
    auto otherTrig = dynamic_cast<Arccsc*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string Arccsc::display() const {
    return "arccsc(" + argument->display() + ")";
}

std::shared_ptr<Function> SineH::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<SineH>(argument->simplify());
}

bool SineH::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<SineH*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string SineH::display() const {
    return "sinh(" + argument->display() + ")";
}
//cosh

std::shared_ptr<Function> CosineH::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<CosineH>(argument->simplify());
}

bool CosineH::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<CosineH*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string CosineH::display() const {
    return "cosh(" + argument->display() + ")";
}

//tanh

std::shared_ptr<Function> TangentH::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<TangentH>(argument->simplify());
}

bool TangentH::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<TangentH*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string TangentH::display() const {
    return "tanh(" + argument->display() + ")";
}

//sech

std::shared_ptr<Function> SecantH::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<SecantH>(argument->simplify());
}

bool SecantH::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<SecantH*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string SecantH::display() const {
    return "sech(" + argument->display() + ")";
}

//csch

std::shared_ptr<Function> CosecantH::simplify() const {
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<CosecantH>(argument->simplify());
}

bool CosecantH::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<CosecantH*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string CosecantH::display() const {
    return "csch(" + argument->display() + ")";
}

//coth

std::shared_ptr<Function> CotangentH::simplify() const{
    if(auto constant = dynamic_cast<Constant*>(argument.get())){
        if(double eval = this->evaluate(1.0) == floor(eval)){
            return std::make_shared<Constant>(eval);
        }
    }
    return std::make_shared<CotangentH>(argument->simplify());
}

bool CotangentH::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherTrig = dynamic_cast<CotangentH*>(other.get());
    if(!otherTrig) return false;
    return argument->isEqual(otherTrig->argument);
}

std::string CotangentH::display() const {
    return "coth(" + argument->display() + ")";
}
