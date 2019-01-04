//
// Created by yedaya on 12/17/18.
//

#ifndef MILE_STONE1_NUM_H
#define MILE_STONE1_NUM_H

#include <string>
#include "BinaryExpression.h"

class Num : public Expression {
    double num;
public:
    explicit Num(std::string& str)  {
        num = std::stod(str);
    }

    explicit Num(double val) {
        num = val;
    }

    ~Num() override = default;

    double calculate() override {
        return num;
    }
};
#endif //MILE_STONE1_NUM_H
