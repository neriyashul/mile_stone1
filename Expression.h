#ifndef MILE_STONE1_EXPRESSION_H
#define MILE_STONE1_EXPRESSION_H

class Expression{
    public:
    virtual ~Expression() = default;
    virtual double calculate() = 0;
};

#endif //MILE_STONE1_EXPRESSION_H
