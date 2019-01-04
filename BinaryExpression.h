//
// Created by yedaya on 12/17/18.
//

#ifndef MILE_STONE1_BINARYEXPRESSION_H
#define MILE_STONE1_BINARYEXPRESSION_H

#include "Expression.h"
class BinaryExpression: public Expression{
protected:
    Expression *left;
    Expression *right;

public:
    virtual double calculate()=0;
    BinaryExpression(Expression*first, Expression*second): left(first), right(second){};
    ~BinaryExpression() override {
        delete(left);
        delete (right);
    };
};

#endif //MILE_STONE1_BINARYEXPRESSION_H
