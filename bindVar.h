//
// Created by neriya on 1/2/19.
//

#ifndef MILE_STONE1_BINDNUMEXP_H
#define MILE_STONE1_BINDNUMEXP_H


#include <string>
#include "Var.h"

class bindVar : public Var {
    std::string expressName;
    double* value = nullptr;
public:
    explicit bindVar(double* d) : Var(this)  {
        value = d;
    }
    double calculate() override {
        return *value;
    }
};


#endif //MILE_STONE1_PATHEXP_H
