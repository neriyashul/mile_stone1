
#ifndef MILE_STONE1_BINDVAR_H
#define MILE_STONE1_BINDVAR_H


#include <string>
#include "Var.h"
#include "UpdateableExpression.h"

class BindVar : public UpdateableExpression {
    double* bindValue = nullptr;
public:
    explicit BindVar(double* d) {
        bindValue = d;
    }

    ~BindVar() override = default;

    void update(double num) override {
        *this->bindValue = num;
    }

    double* getIndexOfValue() override {
        return this->bindValue;
    }

    double calculate() override {
        return *bindValue;
    }
};


#endif //MILE_STONE1_PATHEXP_H
