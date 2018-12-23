//
// Created by yedaya on 12/17/18.
//

#ifndef MILE_STONE1_DIVEXP_H
#define MILE_STONE1_DIVEXP_H

#include "Expression.h"
#include "BinaryExpression.h"

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

#endif //MILE_STONE1_DIVEXP_H
