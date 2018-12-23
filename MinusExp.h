//
// Created by yedaya on 12/17/18.
//

#ifndef MILE_STONE1_MINUSEXP_H
#define MILE_STONE1_MINUSEXP_H

#include "BinaryExpression.h"

class MinusExp: public BinaryExpression{
public:
    MinusExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
    double calculate() override {
        return (left->calculate()-right->calculate());
    }
};


#endif //MILE_STONE1_MINUSEXP_H
