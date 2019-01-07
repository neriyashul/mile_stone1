#ifndef MILE_STONE1_UPDATEABLEEXPRESSION_H
#define MILE_STONE1_UPDATEABLEEXPRESSION_H

#include "Expression.h"

class UpdateableExpression : public Expression {
public:
    virtual ~UpdateableExpression() = default;
    virtual void update(double) = 0;
    virtual double* getIndexOfValue()= 0;
};


#endif //MILE_STONE1_UPDATEABLEEXPRESSION_H
