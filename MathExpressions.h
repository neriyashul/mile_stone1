
#ifndef MILE_STONE1_MATHEXPRESSIONS_H
#define MILE_STONE1_MATHEXPRESSIONS_H

#include "Expression.h"
#include "BinaryExpression.h"

class AddExp: public BinaryExpression{
public:
    AddExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
    double calculate() override {
        return (left->calculate()+right->calculate());
    }
};

class MinusExp: public BinaryExpression{
public:
    MinusExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
    double calculate() override {
        return (left->calculate()-right->calculate());
    }
};

class MulExp: public BinaryExpression{
public:
    MulExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
    double calculate() override {
        return (left->calculate()*right->calculate());
    }
};

class DivExp: public BinaryExpression{
public:
    DivExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
    double calculate() override {
        if(right->calculate()==0){
            throw "Divid by zero - error!";
        }
        return (left->calculate()/right->calculate());
    }
};

#endif //MILE_STONE1_MATHEXPRESSIONS_H
