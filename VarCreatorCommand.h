#ifndef MILE_STONE1_VARCREATORCOMMAND_H
#define MILE_STONE1_VARCREATORCOMMAND_H


#include <string>
#include <unordered_map>
#include <mutex>
#include "Command.h"
#include "Var.h"
#include "ExpressionFactory.h"
#include "Num.h"
#include "BindVar.h"
#include "CommandExpression.h"


class VarDataCommand : public Command {
    std::unordered_map<std::string, int>* numsOfPathsNames;
    std::unordered_map<int, double*>* valuesOfPaths;
    std::unordered_map<std::string,Var*>* variables;
    std::mutex *mtxServer = nullptr;
    ExpressionFactory* expressFactor;


public:
    VarDataCommand(std::unordered_map<std::string, int>* names,
                   std::unordered_map<int, double*>* values,
                   std::unordered_map<std::string,Var*>* vars,
                   std::mutex* m,
                   ExpressionFactory* expressionFactory);

    ~VarDataCommand() override = default;

    /**
     * the function add new pair of name and Var to variables map.
     * @param name - std::string& name
     * @param v - Vat*.
     */
    void addVarToMap(std::string& name, Var* v) {
        (*variables).insert(std::pair<std::string, Var*>(name, v));
    }


    /**
     * the function create Var which has a path as argument.
     * @param isBind - bool.
     * @param path - string&
     * @return Var*.
     */
    Var* createPathVar(bool isBind, std::string &path);

    /**
     * the function create Var which has a bind Var* as argument.
     * @param name - strin&.
     * @return Var*.
     */
    Var* createBindVarByVarName(std::string& name);

    /**
     * the function create Var which has a Var*
     *    or arithmetic expression as argument.
     * @param expression - vector<string>&
     * @return Var*.
     */
    Var* createArithmeticOrUntieVar(std::
                             vector<std::string> &expression);


    /**
     * the function return new Var*.
     * @param isBind - bool.
     * @param expression - std::vector<std::string>&.
     * @return Var*.
     */
    Var* createVar(bool isBind, std::vector<std::string>& expression);

    std::unordered_map<std::string,Var*>* getVarMap() const {
        return variables;
    }

    void doCommand(std::vector<std::string>& v) override;
};


#endif //MILE_STONE1_VARDATACOMMAND_H
