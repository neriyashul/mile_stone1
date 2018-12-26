#ifndef MILE_STONE1_READDATA_H
#define MILE_STONE1_READDATA_H


#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

#include "Interpreter.h"

using namespace std;

class ReadData {

public:
    void read_Data_From_File(string fileName);

    void read_From_Console();
};


#endif //MILE_STONE1_READDATA_H
