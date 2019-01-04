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
    std::string* path = nullptr;
public:
    Var() = default;

    explicit Var(Expression* e) {
        this->exp = e;
    }

    Var(Expression*e, std::string* newPath) {
        exp = e;
        path = newPath;
    }

    ~Var() override {
        if (exp != nullptr) {
            delete (exp);
        }
        if (path != nullptr) {
            delete (path);
        }
    }



    double calculate() override {
        if (exp == nullptr) {
            throw "var is empty";
        }
        return exp->calculate();
    }

    void setPath(std::string* newPath) {
        if (path != nullptr) {
            delete(path);
        }
        path = newPath;
    }

    std::string* getPath() const {
        return path;
    }

    Expression* getExpression() const {
        return this->exp;
    }

    void setExpression(Expression* e) {
        if (this->exp != nullptr) {
            delete (this->exp);
        }
        this->exp = e;
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
