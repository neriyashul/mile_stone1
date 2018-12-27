//
// Created by neriya on 12/26/18.
//

#ifndef MILE_STONE1_ENTERC_H
#define MILE_STONE1_ENTERC_H


#include <Command.h>
#include <iostream>

class Enterc : public Command {
public:
    /**
     * the function wait to any char.
     * @param v  - vector<string>&.
     */
    void doCommand(vector<string>& v) override {
        char c;
        cin >> c;
        // catch "\n"
        getchar();
    }
};


#endif //MILE_STONE1_ENTERC_H
