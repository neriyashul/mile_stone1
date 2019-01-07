
#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include "ExpressionFactory.h"

class ShuntingYard : public ExpressionFactory {
public:
    explicit ShuntingYard(std::unordered_map<std::string,Var*>*
                                   vars) : ExpressionFactory(vars) {}
    ~ShuntingYard() override = default;

    /**
     * The function gets a string and return
     * deque with string acoording to ShuntionYard algorithm.
     *
     * @param vecStr - vector<string> of expression.
     * @return deque<string>.
     */
    std::deque<std::string> shuntingYardAlgorithm(
                   std::vector<std::string>&);


    std::vector<Expression*> expressionFromString(std::vector<std::string>
                                          &expressions) override;
};

#endif // SHUNTINGYARD_H