//
// Created by yedaya on 12/25/18.
//

#include "Interpreter.h"



vector<string> Interpreter::lexer(string input) {
    Lexer lexer;
    return lexer.lexer(input);
}

void Interpreter::parse(vector<string> code) {
    Parser p;
    // create expressions
    p.parse(code);//, this->expressions, this->factory, this->codeMap);
    // execute expressions
    this->expressions->executeAll();
}

Interpreter::Interpreter() {
    // supported commands
    this->codeMap["var"] = "command";
    this->codeMap["openDataServer"] = "command";
    this->codeMap["connect"] = "command";
    this->codeMap["print"] = "command";
    this->codeMap["sleep"] = "command";
    this->codeMap["while"] = "condition";
    this->codeMap["if"] = "condition";
    this->codeMap["="] = "command";
    this->codeMap["sleep"] = "command";
    this->codeMap["entrc"] = "command";

    // init members
    this->expressions = new ExpsCollection();
    this->threads = new Threads();
    this->factory = new CommandFactory(&this->symTbl, this->codeMap, this->threads);
}

Interpreter::~Interpreter() {
    delete this->factory;
    delete this->expressions;
    delete this->threads;

    // free all VarDataCommand
    for (auto &it : this->symTbl)
        delete it.second;
}