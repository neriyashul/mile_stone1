//
// Created by neriya on 1/2/19.
//

#ifndef MILE_STONE1_BINDEXP_H
#define MILE_STONE1_BINDEXP_H


#include <string>
#include "Var.h"

class bindExp : public Expression {
    double* value = nullptr;
public:
    explicit bindExp(double* d) {
        value = d;
    }
    double calculate() override {
        return *value;
    }
    void setValue(double* val) {
        value = val;
    }
};


#endif //MILE_STONE1_PATHEXP_H
