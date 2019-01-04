#include "Notifier.h"

void Notifier::removeObserver(Observer *o)  {
    // Find given element in vector
    auto it = std::find(observers.begin(), observers.end(), o);

    if (it != observers.end())
    {
        int index = (int) distance(observers.begin(), it);
        observers.erase(observers.begin() + index);
    }
}

void Notifier::notifyAll()  {
    for (Observer* o: observers) {
        o->finish();
    }
}

