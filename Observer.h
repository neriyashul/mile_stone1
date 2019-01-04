//
// Created by neriya on 1/3/19.
//

#ifndef MILE_STONE1_OBSERVER_H
#define MILE_STONE1_OBSERVER_H


class Observer {
public:
    virtual ~Observer() = default;

    virtual void finish() = 0;
};


#endif //MILE_STONE1_OBSERVER_H
