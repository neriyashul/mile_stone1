
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

class Equal : public BinaryExpression{
public:
    Equal(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    double calculate() override {
        return left->calculate() == right->calculate();
    }


};


class NotEqual : public BinaryExpression {
public:
    NotEqual(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    double calculate() override {
        return left->calculate() > right->calculate();
    }
};


class Greater : public BinaryExpression{
public:
    Greater(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    double calculate() override {
        return left->calculate() > right->calculate();
    }
};


class GreaterEqual : public BinaryExpression{
public:
    GreaterEqual(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    double calculate() override {
        return left->calculate() >= right->calculate();
    }
};


class Smaller : public BinaryExpression{
public:
    Smaller(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    double calculate() override {
        return left->calculate() < right->calculate();
    }
};


class SmallerEqual : public BinaryExpression{
public:
    SmallerEqual(Expression *left, Expression *right) : BinaryExpression(left, right) {}
    double calculate() override {
        return left->calculate() <= right->calculate();
    }
};

class AND : public BinaryExpression{
public:
    AND(Expression *left, Expression *right) : BinaryExpression(left, right) {
    }

    double calculate() override{
        return left->calculate() && right->calculate();
    }
};

class OR : public BinaryExpression{
public:
    OR(Expression *left, Expression *right) : BinaryExpression(left, right){}

    double calculate() override {
        return left->calculate() || right->calculate();
    }
};

#endif //MILE_STONE1_MATHEXPRESSIONS_H
