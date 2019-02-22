/*! \file interpreter.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Interpreter. Useful for real-time tests.
 */
#ifndef INTERPRETER_H_INLUDED
#define INTERPRETER_H_INLUDED
#include <vector>
#include "symbol.h"
#include <iostream>
#include <sstream>
#include <fstream>

/*! \class Interpreter
 * \brief Interprets strings as expressions to manipulate them afterwards.
 */
class Interpreter{

    private:

    bool isOpen;
    int nSymbols;
    std::vector<Symbol> symbol;
    int nLines;
    std::vector<std::string> lines;

    public:

    Interpreter();
    ~Interpreter();
 
    bool getIsOpen() const;
    void open();
    void close();
    void save(std::string fileName);

    void addLine(std::string line);
    int findSymbol(std::string name);
    void addSymbol(std::string name);
    Symbol evaluateSymbol(std::vector<std::string> split, bool minusSign=false);
    Symbol readSingleSymbol(std::vector<std::string>& split, bool minusSign=false);

    std::string interpret(std::string line);
};

bool semiColon(std::vector<std::string>& line);
std::vector<std::string> splitString(std::string line);

bool isNumber(std::string str);
double stringToDouble(std::string str);

std::vector<std::string> subVector(std::vector<std::string> vec, int initPos, int lastPos);
int findParenthesis(std::vector<std::string> split, int initPos);

bool checkVariable(std::string name);
bool checkOperator(std::string name);
bool checkFunction(std::string name);

#endif
