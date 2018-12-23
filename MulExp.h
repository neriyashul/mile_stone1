//
// Created by yedaya on 12/17/18.
//
#include "BinaryExpression.h"

#ifndef MILE_STONE1__MULEXP_H
#define MILE_STONE1__MULEXP_H
class MulExp: public BinaryExpression{
public:
    MulExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
    double calculate() override {
        return (left->calculate()*right->calculate());
    }



};
#endif //MILE_STONE1_MULEXP_H
