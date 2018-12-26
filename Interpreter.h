#ifndef MILE_STONE1_INTERPRETER_H
#define MILE_STONE1_INTERPRETER_H


#include <string>
#include <list>
#include <map>
#include <iostream>

#include "VarData.h"
#include "Command.h"
#include "CommandFactory.h"
#include "ExpsCollection.h"
#include "Threads.h"
#include "CommandExpression.h"
#include "LexerParser.h"

class Interpreter {
    map<string, VarData *> symTbl;
    CommandFactory *factory;
    ExpsCollection *expressions;
    map<string, string> codeMap;
    Threads *threads;

public:
    Interpreter();

    ~Interpreter();

    vector<string> lexer(string input);

    void parser(vector<string> input);
};

#endif //MILE_STONE1_INTERPRETER_H
