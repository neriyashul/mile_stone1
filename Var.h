//
// Created by neriya on 1/1/19.
//

#ifndef MILE_STONE1_VAR_H
#define MILE_STONE1_VAR_H


#include <string>
#include <unordered_map>
#include "Threads.h"
#include "Command.h"
#include "Expression.h"

class Var : public Expression {
    Expression* exp = nullptr;
public:
    explicit Var(Expression* e) {
        this->exp = e;
    }

    //Var() = default;

    virtual double calculate() {
        if (exp == nullptr) {
            throw "var is empty";
        }
        return exp->calculate();
    }


    Expression* getExpression() const {
        return this->exp;
    }

    void setExpression(Expression* e) {
        this->exp = e;
    }
};
std::ostream& operator << (std::ostream& os, const Var& v) {
    os << v.getExpression()->calculate();
    return os;
}


/*****
 * override operator << for printing.
 *
 * @param os - ostream&.
 * @param infNum -const InfInt&.
 */
std::ostream& operator<<(std::ostream& os, Var& var);


#endif //MILE_STONE1_VAR_H
