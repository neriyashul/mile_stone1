
#ifndef MILE_STONE1_UNTIEVAR_H
#define MILE_STONE1_UNTIEVAR_H


#include "UpdateableExpression.h"

class UntieVar : public UpdateableExpression {
public:
    double value = 0;
public:
    explicit UntieVar(double d) {
        this->value = d;
    }

    ~UntieVar() override = default;

    void update(double num) override {
        this->value = num;
    }

    double* getIndexOfValue() override {
        return &value;
    }

    double calculate() override {
        return this->value;
    }


};


#endif //MILE_STONE1_UNTIEVAR_H
