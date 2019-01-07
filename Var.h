//
// Created by neriya on 1/1/19.
//

#ifndef MILE_STONE1_VAR_H
#define MILE_STONE1_VAR_H


#include <string>
#include <unordered_map>
#include <ostream>
#include <iostream>
#include "Command.h"
#include "Expression.h"
#include "UntieVar.h"

class Var : public Expression {
    UpdateableExpression* exp = nullptr;
    std::string path;
public:
    /**
     * constructors:
     */
    Var() = default;

    explicit Var(UpdateableExpression* e) {
        this->exp = e;
    }

    Var(UpdateableExpression*e, std::string& newPath) {
        exp = e;
        path = newPath;
    }

    ~Var() override {
        delete (exp);
    }

    /**
     * the function update the value in exp.
     * @param d double.
     */
    void update(double d) {
        this->exp->update(d);
    }


    double calculate() override;

    void setExpression(UpdateableExpression* e);

    void setExpression(Expression* e);

    void setPath(std::string& newPath);

    std::string& getPath() {
        return path;
    }

    UpdateableExpression* getExpression() const {
        return this->exp;
    }
};

/*****
 * override operator << for printing.
 *
 * @param os - ostream&.
 * @param v - const Var&.
 */
inline std::ostream& operator << (std::ostream& os, Var& v) {
    os << std::to_string(v.getExpression()->calculate());
    return os;
}


#endif //MILE_STONE1_VAR_H
