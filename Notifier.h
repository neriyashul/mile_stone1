//
// Created by neriya on 1/3/19.
//

#ifndef MILE_STONE1_NOTIFIER_H
#define MILE_STONE1_NOTIFIER_H


#include "Observer.h"
#include <vector>
#include <algorithm>

class Notifier {
    std::vector<Observer*> observers;
public:
    /******************************
     * Observer pattern
     ******************************/

    ~Notifier() = default;

    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o);

    void notifyAll();
};


#endif //MILE_STONE1_NOTIFIER_H
