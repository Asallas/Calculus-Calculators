#include "arithmeticOperands.h"

std::shared_ptr<Function> Sum::getLeft(){
    return left;
}

std::shared_ptr<Function> Sum::getRight(){
    return right;
}

double Sum::evaluate(double x) const{
    return left->evaluate(x) + right->evaluate(x);
}

//Add Trig identity checks
std::shared_ptr<Function> Sum::simplify() const{
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

bool Sum::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherSum = dynamic_cast<Sum*>(other.get());
    if (!otherSum) return false;

    // Compare left and right subtrees recursively
    return left->isEqual(otherSum->left) && right->isEqual(otherSum->right);
}

std::shared_ptr<Function> Difference::getLeft(){
    return left;
}
std::shared_ptr<Function> Difference::getRight(){
    return right;
}

double Difference::evaluate(double x) const{
    return left->evaluate(x) - right->evaluate(x);
}

std::shared_ptr<Function> Difference::simplify() const{
    auto simplifiedLeft = left->simplify();
    auto simplifiedRight = right->simplify();

    auto leftConst = dynamic_cast<Constant*>(simplifiedLeft.get());
    if(leftConst && simplifiedLeft->evaluate(0.0) == 0.0){
        return std::make_shared<Product>(std::make_shared<Constant>(-1.0), simplifiedRight);
    }
    auto rightConst = dynamic_cast<Constant*>(simplifiedRight.get());
    if(rightConst && simplifiedRight->evaluate(0.0) == 0.0){
        return simplifiedLeft;
    }
    if(leftConst && rightConst){
        return std::make_shared<Constant>(simplifiedLeft->evaluate(1.0) - simplifiedRight->evaluate(1.0));
    }

    if(simplifiedLeft->isEqual(simplifiedRight)){
        return std::make_shared<Constant>(0.0);
    }

    return std::make_shared<Difference>(simplifiedLeft, simplifiedRight);
}

bool Difference::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherDiff = dynamic_cast<Difference*>(other.get());
    if (!otherDiff) return false;

    // Compare left and right subtrees recursively
    return left->isEqual(otherDiff->left) && right->isEqual(otherDiff->right);
}

std::string Difference::display() const{
    return left->display() + " - " + right->display();
}

std::shared_ptr<Function> Product::getLeft(){
    return left;
}
std::shared_ptr<Function> Product::getRight(){
    return right;
}

double Product::evaluate(double x) const{
    return left->evaluate(x) * right->evaluate(x);
}

std::shared_ptr<Function> Product::simplify() const{
    auto simplifiedLeft = left->simplify();
    auto simplifiedRight = right->simplify();

    if(checkForZero(simplifiedRight)){
        return std::make_shared<Constant>(0.0);
    }
    if(checkForOne(simplifiedLeft)){
        return simplifiedRight;
    }
    if(checkForZero(simplifiedRight)){
        return std::make_shared<Constant>(0.0);
    }
    if(checkForOne(simplifiedRight)){
        return simplifiedLeft;
    }
    if(simplifiedLeft->isEqual(simplifiedRight)){
        return std::make_shared<Polynomial>(simplifiedLeft, 2.0);
    }
        
    return std::make_shared<Product>(simplifiedLeft, simplifiedRight);
}

bool Product::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherProd = dynamic_cast<Product*>(other.get());
    if(!otherProd) return false;
    return left->isEqual(otherProd->left) && right->isEqual(otherProd->right);
}

std::string Product::display() const{
    return "(" + left->display() + ") * (" + right->display() + ")";
}


std::shared_ptr<Function> Quotient::getLeft(){
    return left;
}
std::shared_ptr<Function> Quotient::getRight(){
    return right;
}

double Quotient::evaluate(double x) const{
    double denominator = right->evaluate(0.0);
    if(denominator == 0.0){
        throw std::runtime_error("Error divide by 0");
    }
    return left->evaluate(x) / denominator;
}

std::shared_ptr<Function> Quotient::simplify() const{
    auto simplifiedTop = right->simplify();
    auto simplifiedBottom = left->simplify();

    if(checkForOne(simplifiedBottom)){
        return simplifiedTop;
    }
    if(checkForZero(simplifiedTop)){
        return std::make_shared<Constant>(0.0);
    }
    if(checkForZero(simplifiedBottom)){
        throw std::runtime_error("Error denominator is 0");
    }

    // Trigonometric identities
    // tan(f(x)) = sin(f(x)) / cos(f(x))
    if(tangentChange(std::make_shared<Quotient>(simplifiedTop, simplifiedBottom))){
        auto sineArg = dynamic_cast<Sine*>(simplifiedTop.get());
        return std::make_shared<Tangent>(sineArg->getArgument());
    }
    // cot(f(x)) = cos(f(x)) / sin(f(x))
    if(cotangentChange(std::make_shared<Quotient>(simplifiedTop, simplifiedBottom))){
        auto cosineArg = dynamic_cast<Cosine*>(simplifiedTop.get());
        return std::make_shared<Cotangent>(cosineArg->getArgument());
    }

    if(checkForOne(simplifiedTop)){
        return trigonometricQuotient(simplifiedBottom);
    }

    return std::make_shared<Quotient>(simplifiedTop, simplifiedBottom);
}
    
bool Quotient::isEqual(const std::shared_ptr<Function>& other) const{
    auto otherQuot = dynamic_cast<Quotient*>(other.get());
    if(!otherQuot) return false;
    return left->isEqual(otherQuot->left) && right->isEqual(otherQuot->right);
}

std::string Quotient::display() const{
    return "(" + left->display() + ") / (" + right->display() + ")";
}