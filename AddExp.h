//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_ADDEXP_H
#define MILE_STONE1_ADDEXP_H

#include "Expression.h"
#include "BinaryExpression.h"

class AddExp: public BinaryExpression{
public:
    AddExp(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
        double calculate() override {
            return (left->calculate()+right->calculate());
        }
    };

#endif //MILE_STONE1_ADDEXP_H
