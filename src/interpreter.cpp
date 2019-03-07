#include "interpreter.h"
using namespace std;

Interpreter::Interpreter()
{
    isOpen = 0;
    nSymbols = 0;
    symbol = vector<Symbol>(0);
    nLines = 0;
    lines = vector<string>(0);
}

Interpreter::~Interpreter()
{
    symbol.clear();
    lines.clear();
}

bool Interpreter::getIsOpen() const { return isOpen;}

void Interpreter::open()
{
    cout<<endl;
    cout<<"/ ********************************** /\n";
    cout<<"/          G-MATH INTERPRETER        /\n";
    cout<<"/                                    /\n";
    cout<<"/---------------Commands-------------/\n";
    cout<<"/                                    /\n";
    cout<<"/   - \"q\" or \"quit\": quit.           /\n";
    cout<<"/   - \"print\": display symbol.   /\n";
    cout<<"/   - \"printExp\": display explicit   /\n";
    cout<<"/ symbols.                       /\n";
    cout<<"/   - \"eval\": evaluate quantitatively/\n";
    cout<<"/ the symbol.                    /\n";
    cout<<"/   - \"VARS\": display all present    /\n";
    cout<<"/ variables explicitely.             /\n";
    cout<<"/   - \"save(q)\" file_name: save the  /\n";
    cout<<"/ current session in a notebook      /\n";
    cout<<"/ \"filename\" (and quit).             /\n";
    cout<<"/   - \"simplify\": simplify the       /\n";
    cout<<"/ following symbol.              /\n";
    cout<<"/                                    /\n";
    cout<<"/------Included basis functions------/\n";
    cout<<"/                                    /\n";
    cout<<"/   - cos-sin-cosh-sinh              /\n";
    cout<<"/   - exp-log-sqrt                   /\n";
    cout<<"/                                    /\n";
    cout<<"/--------------Operators-------------/\n";
    cout<<"/                                    /\n";
    cout<<"/ +, *, -, /, ^, =, ==, !=.          /\n";
    cout<<"/                                    /\n";
    cout<<"/ ********************************** /\n";
    cout<<endl;
    isOpen = true;
}

void Interpreter::close() { symbol.clear(); nSymbols = 0; isOpen = false;}

void Interpreter::save(string fileName)
{
    ifstream test(fileName.c_str());
    if (!test.fail())
    {
        cout<<"File \""<<fileName<<"\" already exists ! Do you want to overwrite it ? (y / [n]): ";
        string rep;
        cin>>rep;
        cin.ignore();
        if (!(rep == "y" or rep == "Y" or rep == "yes" or rep == "YES" or rep == "Yes"))
        {
            test.close();
            return;
        }
    }
    test.close();
    ofstream f(fileName.c_str());
    for (int i=0; i<nLines; i++)
        f<<lines[i]<<endl;
    f.close();
}

void Interpreter::addLine(string line)
{
    lines.push_back(line);
    nLines++;
}

int Interpreter::findSymbol(string name)
{
    for (int i=0; i<nSymbols; i++)
        if (name == symbol[i].getName()) return i;
    return -1;
}

void Interpreter::addSymbol(string name)
{
    if (name == "print" or name == "printExp" or name == "q" or name == "quit" or name == "eval" or name == "VARS" or name == "save" or name == "saveq" or name == "simplify")
    {
        cout<<"(gMath) : >> Warning name \""<<name<<"\" is a keyword: replacing it by \"_"<<name<<"\".\n";
        name = "_"+name;
    }
    symbol.push_back(Symbol(name));
    nSymbols++;
}

Symbol Interpreter::evaluateSymbol(vector<string> split, bool minusSign)
{
    Symbol expr;
    if (split.size() > 0)
    {
        if (split.size() == 1)
        {
            if (isNumber(split[0]))
            {
                double foo = stringToDouble(split[0]);
                if (!minusSign) expr = foo;
                else expr = -foo;
                return expr;
            }
            int pos = findSymbol(split[0]);
            if (pos > -1)
            {
                if (!minusSign) return symbol[pos];
                else return -1*symbol[pos];
            }
            addSymbol(split[0]);
            if (!minusSign) return symbol[nSymbols-1];
            else return -1*symbol[nSymbols-1];
        }
        int parenthesis = 0;
        if (split[0] == "(")
        {
            parenthesis = 1;
            for (size_t i=1; i<split.size(); i++)
            {
                if (split[i] == "(") parenthesis ++;
                else if (split[i] == ")") parenthesis--;
                if (i < split.size()-1 and parenthesis == 0) break;
                else if (parenthesis == 0) return evaluateSymbol(subVector(split,1,split.size()-1),minusSign);
            }
        }
        else if (split[0] == "-")
        {
            return evaluateSymbol(subVector(split,1,split.size()),true);
        }
        parenthesis = 0;
        for (size_t i=0; i<split.size(); i++)
        {
            if (split[i] == "(") parenthesis ++;
            else if (split[i] == ")") parenthesis --;
            if (parenthesis == 0)
            {
                if (split[i] == "+")
                {
                    return evaluateSymbol(subVector(split,0,i),minusSign)+evaluateSymbol(subVector(split,i+1,split.size()));
                }
            }
        }
        parenthesis = 0;
        for (size_t i=0; i<split.size(); i++)
        {
            if (split[i] == "(") parenthesis ++;
            else if (split[i] == ")") parenthesis --;
            if (parenthesis == 0)
            {
                if (split[i] == "-")
                {
                    return evaluateSymbol(subVector(split,0,i),minusSign)+evaluateSymbol(subVector(split,i+1,split.size()), true);
                }
            }
        }
        parenthesis = 0;
        for (size_t i=0; i<split.size(); i++)
        {
            if (split[i] == "(") parenthesis ++;
            else if (split[i] == ")") parenthesis --;
            if (parenthesis == 0)
            {
                if (split[i] == "*")
                {
                    return evaluateSymbol(subVector(split,0,i),minusSign)*evaluateSymbol(subVector(split,i+1,split.size()));
                }
            }
        }
        parenthesis = 0;
        for (int i=split.size()-1; i>=0; i--)
        {
            if (split[i] == "(") parenthesis ++;
            else if (split[i] == ")") parenthesis --;
            if (parenthesis == 0)
            {
                if (split[i] == "/")
                {
                    return evaluateSymbol(subVector(split,0,i),minusSign)/evaluateSymbol(subVector(split,i+1,split.size()));
                }
            }
        }

        parenthesis = 0;
        for (int i=split.size()-1; i>=0; i--)
        {
            if (split[i] == "(") parenthesis ++;
            else if (split[i] == ")") parenthesis --;
            if (parenthesis == 0)
            {
                if (split[i] == "^")
                {
                    return pow(-1,minusSign)*pow_(evaluateSymbol(subVector(split,0,i)),evaluateSymbol(subVector(split,i+1,split.size())));
                }
            }
        }
        return readSingleSymbol(split, minusSign);
    }

    return expr;
}

string Interpreter::interpret(string line)
{
    if (line == "quit" or line == "q")
    {
        isOpen = 0;
        return "";
    }

    string answer = "";
    vector<string> split = splitString(line);
    if (split.size() == 0) return "";
    bool verbose = !semiColon(split);
    if (split.size() == 0) return "";

    if (split.size() == 1 and checkVariable(split[0]))
    {
        Symbol foo = evaluateSymbol(split);
        //if (verbose) { cout<<"(gMath) >> "; cout<<foo.evaluateScalar()<<endl;}
        return "";
    }

    int command = 0;
    if (split[0] == "printExp")
    {
        command = 1;
        split.erase(split.begin());
    }
    else if (split[0] == "eval")
    {
        command = 2;
        split.erase(split.begin());
    }
    else if (split[0] == "print")
    {
        command = 0;
        verbose = 1;
        split.erase(split.begin());
    }
    else if (split[0] == "VARS")
    {
        /*cout<<"List of variables: \n";
        for (int i=0; i<nSymbols; i++)
        {
            if (symbol[i].getAbstract()->getType() != 1)
            {
                cout<<symbol[i].getName()<<" = ";
                symbol[i].print();
                cout<<" = "<<symbol[i].evaluateScalar()<<endl;
            }
            else 
            {
                symbol[i].print();
            }

        }
        return;*/ return "";
    }
    else if (split[0] == "simplify")
    {
        /*Symbol expr = evaluateSymbol(subVector(split,1,split.size()));
        if (verbose) expr.print();
        return;*/ return "";
    }
    else if (split[0] == "save")
    {
        /*if (split.size() < 2) cout<<"(gMath) : Please specify a file in which save the notebook !\n";
        save(split[1]);
        return;*/ return "";
    }
    else if (split[0] == "saveq")
    {
        /*if (split.size() < 2) cout<<"(gMath) : Please specify a file in which save the notebook !\n";
        save(split[1]);
        isOpen = 0;
        return;*/ return "";
    }

    int equalSign=-1;
    int comparison = 0;
    for(int i=0; i<(int)split.size(); i++)
    {
        if (split[i] == "=")
        {
            if (equalSign >= 0) comparison = 1;
            else equalSign = i;
        }
        else if (split[i] == "!")
        {
            comparison = -1;
        }
    }
    if (comparison == 0 and equalSign != -1 and equalSign != 1)
    {
        /*cout<<"(gMath) : Warning: wrong placement of \"=\" sign. Ignored.\n";
        return;*/ return "";
    }
    if (equalSign >= 0)
    {
        if (comparison == 1)
        {
            /*cout<<"(gMath) : >> Comparison gives: "<<(evaluateSymbol(subVector(split,0,equalSign))==evaluateSymbol(subVector(split,equalSign+2,split.size())))<<endl;
            return;*/return "";
        }
        else if (comparison == -1)
        {
            /*cout<<"(gMath) : >> Comparison gives: "<<(evaluateSymbol(subVector(split,0,equalSign-1))!=evaluateSymbol(subVector(split,equalSign+1,split.size())))<<endl;
            return;*/ return "";
        }
        if (!checkVariable(split[0]))
        {
            /*cout<<"(gMath) : >> Left-hand side of the equation is not a valid call for a variable.\n";
            return;*/return "";
        }
        int pos = findSymbol(split[0]);
        if (pos == -1)
        {
            pos = nSymbols;
            addSymbol(split[0]);
        }
        vector<string> rhs(0);
        for (int i=2; i<(int)split.size(); i++)
            rhs.push_back(split[i]);
        symbol[pos] = evaluateSymbol(rhs);
        if (verbose)
        {
            //cout<<"(gMath) >> ";
            symbol[pos].print();
            if (command == 0) answer = symbol[pos].printLaTeX();
            else if (command == 1) answer = symbol[pos].printLaTeX();
            else if (command == 2){
                ostringstream flux;
                flux<<symbol[pos].evaluateScalar();
                answer = flux.str();
            }
        }
    }
    else
    {
        if (!checkVariable(split[0]))
        {
            /*cout<<"(gMath) : >> Left-hand side of the equation is not a valid call for a variable.\n";
            return;*/return "";
        }
        if (verbose)
        {
            //cout<<"(gMath) >> ";
            Symbol fooExpr = evaluateSymbol(split);
            if (command == 0) answer = fooExpr.printLaTeX();
            else if (command == 1) answer = fooExpr.printLaTeX();
            else if (command == 2){
                ostringstream flux;
                flux<<fooExpr.evaluateScalar();
                answer = flux.str();
            }
            /*if (command == 0 or command == 1)
                if (fooExpr.getAbstract()->getType() == 1 and fooExpr.getName() == "")
                    cout<<endl;*/
        }
    }
    addLine(line);
    return answer;
}


bool semiColon(vector<string>& line)
{
    if (line[line.size()-1] == ";")
    {
        line.erase(line.end()-1);
        return true;
    }
    return false;
}

vector<string> splitString(string line)
{
    vector<string> splitLine(0);
    int i = -1;
    int nString = 0;
    while (i < (int)line.length()-1)
    {
        i++;
        char c = line[i];
        if (c == ' ') continue;
        nString += 1;
        splitLine.push_back("");
        splitLine[nString-1].push_back(c);
        if (c == '+' or c == '-' or c == '*' or c == '/' or c == '^' or c == '=' or c == '(' or c == ')' or c == ',' or c == ';' or c == '!')
            continue;
        while(i < (int)line.length()-1)
        {
            i++;
            c = line[i];
            if (c == ' ') break;
            if (c == '+' or c == '-' or c == '*' or c == '/' or c == '^' or c == '=' or c == '(' or c == ')' or c == ',' or c == ';' or c == '!')
            {
                nString += 1;
                splitLine.push_back("");
                splitLine[nString-1].push_back(c);
                break;
            }
            splitLine[nString-1].push_back(c);
        }
    }

    return splitLine;
}

bool isNumber(string str)
{
    int nPoints = 0;
    for (int i=0; i<(int)str.length(); i++)
    {
        char c = str[i];
        if (c != '0' and c != '1' and c != '2' and c != '3' and c != '4' and c != '5' and c != '6' and c != '7' and c != '8' and c != '9' and c != '.') return false;
        if (c == '.') nPoints ++;
    }
    if (nPoints > 1) return false;
    return true;
}

double stringToDouble(string str)
{
    istringstream stream(str);
    double foo;
    if (!(stream>>foo)) return 0;

    return foo;
}

vector<string> subVector(vector<string> vec, int initPos, int lastPos)
{
    vector<string> subVec(0);
    for (int i=initPos; i<lastPos; i++)
        if (i >= 0 and i < (int)vec.size())
            subVec.push_back(vec[i]);
    return subVec;
}

int findParenthesis(vector<string> split, int initPos)
{
    int parenthesis = 1;
    for (int i=initPos+1; i<(int)split.size(); i++)
    {
        if (split[i] == "(") parenthesis++;
        else if (split[i] == ")") parenthesis--;
        if (parenthesis == 0) return i;
    }
    return -1;
}

Symbol Interpreter::readSingleSymbol(vector<string>& split, bool minusSign)
{
    Symbol expr;
    if (split[0] == "i")
    {
        split = subVector(split,1,split.size());
        expr = Symbol(i_);
    }
    else if (split[0] == "cos")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr = cos_(evaluateSymbol(subVector(split,2,lastPos)));
        split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "sin")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr = sin_(evaluateSymbol(subVector(split,2,lastPos)));
        split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "cosh")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr = cos_(evaluateSymbol(subVector(split,2,lastPos))); split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "sinh")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr = sin_(evaluateSymbol(subVector(split,2,lastPos)));
        split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "exp")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr = exp_(evaluateSymbol(subVector(split,2,lastPos)));
        split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "log")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr = log_(evaluateSymbol(subVector(split,2,lastPos)));
        split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "sqrt")
    {
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        int lastPos = findParenthesis(split,1);
        if (lastPos == -1)
        {
            cout<<"gMath-Error: expected \")\".\n";
            return expr;
        }
        expr =  exp_(evaluateSymbol(subVector(split,2,lastPos)));
        split = subVector(split,lastPos+1,split.size());
    }
    else if (split[0] == "derive")
    {
        if (split.size() < 6)
        {
            cout<<"gMath-Error: syntax for derivative is \"derive(<function>,<variable>).\n";
            return expr;
        }
        if (split[1] != "(")
        {
            cout<<"gMath-Error: expected \"(\" after \"derive\".\n";
            return expr;
        }
        int pos = findSymbol(split[2]);
        if (pos == -1)
        {
            cout<<"gMath-Error: function argument of derive not defined.\n";
            return expr;
        }
        Symbol function = symbol[pos];
        if (split[3] != ",")
        {
            cout<<"gMath-Error: expected \",\" after function declaration.\n";
            return expr;
        }
        pos = findSymbol(split[4]);
        if (pos == -1) return expr;
        Symbol variable = symbol[pos];
        if (split[5] != ")")
        {
            cout<<"gMath-Error: expected \")\" at the end of derivative declaration.\n";
            return expr;
        }
        expr = function.derive(variable);
        split = subVector(split,6,split.size());
    }
    else
    {
        int pos = findSymbol(split[0]);
        if (pos >= 0) expr = symbol[pos];
        else if (isNumber(split[0]))
        {
           double foo = stringToDouble(split[0]);
           expr = foo;
        }
        else
        {
           addSymbol(split[0]);
           expr = symbol[nSymbols-1];
        }
        split = subVector(split,1,split.size());
    }
    if (minusSign) return -1*expr;
    return expr;
}

bool checkVariable(string name)
{
    if (name == "print" or name == "printExp" or name == "q" or name == "quit" or name == "eval" or name == "VARS") return false;
    for (size_t i=0; i<name.length(); i++)
    {
        char c = name[i];
        if (c=='+' or c=='-' or c=='*' or c=='/' or c=='^' or c=='=') return false;
    }
    return true;
}

bool checkOperator(string name)
{
    if (name == "+" or name == "-" or name == "/" or name == "^" or name == "=") return true;
    return false;
}

bool checkFunction(string name)
{
    if (name == "i" or name == "cos" or name == "sin" or name == "cosh" or name == "sinh" or name == "exp" or name == "log" or name == "sqrt") return true;
    return false;
}
