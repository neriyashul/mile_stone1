#include "Var.h"

double Var::calculate()  {
    if (exp == nullptr) {
        throw "var is empty";
    }
    return *exp->getIndexOfValue();
}

void Var::setExpression(UpdateableExpression *e)  {
    if (this->exp != nullptr) {
        delete (this->exp);
    }
    this->exp = e;
}


void Var::setExpression(Expression *e)  {
    if (this->exp != nullptr) {
        delete (this->exp);
    }
    this->exp = new UntieVar(e->calculate());
    delete(e);
}

void Var::setPath(std::string& newPath)  {
    path = newPath;
}


