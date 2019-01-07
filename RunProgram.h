
#ifndef MILE_STONE1_RUNPROGRAM_H
#define MILE_STONE1_RUNPROGRAM_H

#include <thread>
#include <vector>
#include "Var.h"
#include "Parser.h"
#include "Lexer.h"

class RunProgram {


/*  create map that every path has the next num after the previous,
    accordingly tp the order in the xml file. */
    std::unordered_map<std::string, int> numsOfPathsNames = {
            {"/instrumentation/airspeed-indicator/indicated-speed-kt", 1},
            {"/instrumentation/altimeter/indicated-altitude-ft", 2},
            {"/instrumentation/altimeter/pressure-alt-ft", 3},
            {"/instrumentation/attitude-indicator/indicated-pitch-deg", 4},
            {"/instrumentation/attitude-indicator/indicated-roll-deg", 5},
            {"/instrumentation/attitude-indicator/internal-pitch-deg", 6},
            {"/instrumentation/attitude-indicator/internal-roll-deg", 7},
            {"/instrumentation/encoder/indicated-altitude-ft", 8},
            {"/instrumentation/encoder/pressure-alt-ft", 9},
            {"/instrumentation/gps/indicated-altitude-ft", 10},
            {"/instrumentation/gps/indicated-ground-speed-kt", 11},
            {"/instrumentation/gps/indicated-vertical-speed", 12},
            {"/instrumentation/heading-indicator/indicated-heading-deg", 13},
            {"/instrumentation/magnetic-compass/indicated-heading-deg", 14},
            {"/instrumentation/slip-skid-ball/indicated-slip-skid", 15},
            {"/instrumentation/turn-indicator/indicated-turn-rate", 16},
            {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 17},
            {"/controls/flight/aileron", 18},
            {"/controls/flight/elevator", 19},
            {"/controls/flight/rudder", 20},
            {"/controls/flight/flaps", 21},
            {"/controls/engines/engine/throttle", 22},
            {"/engines/engine/rpm" ,23}};
/*
 * the map save the value in path from the previous map.
 */
    std::unordered_map<int, double*> valuesOfPaths;
    std::unordered_map<std::string,Var*> variable;
    std::vector<Expression*> expressions;
    std::vector<std::thread> threads;
    Lexer lexer;
    Parser parser;
    std::mutex mtxServer;
    std::mutex mtxClient;
    Notifier notifier;
public:
    RunProgram() : parser(&threads, &numsOfPathsNames,
            &valuesOfPaths, &variable, &mtxServer,
                                &mtxClient, &notifier) {
        initValuesMap();
    }

    void initValuesMap(){
        for (int i = 1; i <= 23; ++i) {
            valuesOfPaths.insert(std::pair
                    <int, double*>(i, new double(0)));
        }
    }
    ~RunProgram();

    void run(std::string& input);

    void addVectorExpression(std::vector<Expression*>& ve);

    bool isContinue(std::string& line);
};


#endif //MILE_STONE1_RUNPROGRAM_H
