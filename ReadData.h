//
// Created by yedaya on 12/25/18.
//

#ifndef UNTITLED1_READCODE_H
#define UNTITLED1_READCODE_H


#include <list>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <thread>

#include "Interpreter.h"





class ReadData {
std::vector<std::thread> threads;
public:
    void readFromFile(std::string fileName);

    void readFromConsole();
};

#endif //UNTITLED1_READCODE_H
