#include "operations.h"
#include "indicial.h"
#include "mathFunctions.h"
#include "vector.h"
#include "simplification.h"
using namespace std;

//////////////////////////////////////
//// Class Plus              /////////
//////////////////////////////////////

Plus::Plus(const vector<Expr >& operands, bool explicitPlus): AbstractMultiFunc() {
    nArgs = operands.size();
    argument = operands;
    if (not explicitPlus and nArgs > 0) mergeTerms();
}

Plus::Plus(const Expr& leftOperand, const Expr& rightOperand): AbstractMultiFunc()
{
    if (leftOperand->getType() == PLUS and rightOperand->getType() != PLUS) {
        argument = leftOperand->getVectorArgument();
        nArgs = argument.size();
        insert(rightOperand);
    }
    else if (rightOperand->getType() == PLUS and leftOperand->getType() != PLUS) {
        argument = rightOperand->getVectorArgument();
        nArgs = argument.size();
        insert(leftOperand);
    }
    else {
        nArgs = 2;
        argument = vector<Expr>(2);
        argument[0] = leftOperand;
        argument[1] = rightOperand;
        mergeTerms();
    }
}

Expr Plus::getRealPart()
{
    Expr realPart = ZERO;
    for (int i=0; i<nArgs; i++)
        realPart = plus_(realPart, argument[i]->getRealPart());
    return realPart;
}

Expr Plus::getImaginaryPart() const
{
    Expr imaginaryPart = ZERO;
    for (int i=0; i<nArgs; i++)
        imaginaryPart = plus_(imaginaryPart, argument[i]->getImaginaryPart());
    return imaginaryPart;
}

Expr Plus::getComplexModulus()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
    return pow_(plus_(pow_(real,int_(2)),pow_(im,int_(2))), double_(0.5));
}

Expr Plus::getComplexArgument()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
    return make_shared<Angle>(im,real);
}

vector<Index> Plus::getIndexStructure() const
{
    if (nArgs > 0 and argument[0]->getPrimaryType() == INDICIAL)
        return argument[0]->getIndexStructure();
    return vector<Index>(0);
}

void Plus::insert(const Expr& t_abstract, bool side)
{
    if (nArgs == 0) {
        nArgs++;
        argument.insert(argument.begin(), t_abstract);
        return;
    }
    // If numerical, easy
    if (t_abstract->getPrimaryType() == NUMERICAL) {
        if (argument[0]->getPrimaryType() == NUMERICAL)
            argument[0] = argument[0]->addition_own(t_abstract);
        else {
            argument.insert(argument.begin(), t_abstract);
            ++nArgs;
        }
        if (*argument[0] == ZERO) {
            argument.erase(argument.begin());
            --nArgs;
        }
        return;
    }

    // If not numerical, we search for a similar term
    Expr term = t_abstract->getTerm();
    Expr numericalFact = t_abstract->getNumericalFactor();
    Expr term2;
    for (iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        term2 = (*arg)->getTerm();
        if (*term == term2) {
            *arg = times_((*arg)->getNumericalFactor()->addition_own(numericalFact),term);
            if (**arg == ZERO) {
                arg = argument.erase(arg);
                --nArgs;
            }
            return;
        }
    }
    /*for (int i=0; i<nArgs; i++)
    {
        term2 = argument[i]->getTerm();
        // If we found the right term, it's done
        if (*term == term2)
        {
            argument[i] = make_shared<Plus>(t_abstract->getNumericalFactor()->addition_own(argument[i]->getNumericalFactor()), term);
            return;
        }
    }*/

    // No term corresponds, we order correctly the new term in the sum
    for (const_iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        if (t_abstract < *arg) {
            argument.insert(arg, t_abstract);
            ++nArgs;
            return;
        }
    }

    // no term is more complicated than t_abstract, we put it at the end
    argument.push_back(t_abstract);
    ++nArgs;
}

void Plus::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        cout<<"(";
    for (int i=0; i<nArgs; i++)
    {
        argument[i]->print(1);
        if (i < nArgs-1)
            cout<<" + ";
    }
    if (mode > 1)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Plus::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    for (int i=0; i<nArgs; i++)
    {
        sout<<argument[i]->printLaTeX(1);
        if (i < nArgs-1)
            sout<<"+";
    }
    if (mode > 1)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Plus::evaluateScalar() const
{
    double sum=0;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getDim() > 0) return 0;
        sum += argument[i]->evaluateScalar();
    }
    return sum;
}

Expr Plus::evaluate()
{
    bool number = true;
    double numericalRes = 0;
    Expr result = ZERO;
    Expr foo;
    for (int i=0; i<nArgs; i++)
    {
        foo = argument[i]->evaluate();
        if (foo->getPrimaryType() == NUMERICAL)
            numericalRes += foo->evaluateScalar();
        else
        {
            result = plus_(result, foo);
            number = false;
        }
    }
    if (number) return double_(numericalRes);
    return plus_(double_(numericalRes),result);
}
bool Plus::mergeTerms()
{
    bool simplified = false;
    shared_ptr<Abstract> arg;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getType() == PLUS) // Plus(Plus(.. = Plus( , , ...
        {
            int t_nArgs = argument[i]->getNArgs();
            vector<shared_ptr<Abstract> > t_argument = argument[i]->getVectorArgument();
            for (int j=0; j<nArgs; j++)
                if (i != j)
                    t_argument.push_back(argument[j]);
            i += t_nArgs-1;
            nArgs += t_nArgs-1;
            argument = t_argument;
        }
    }
    nArgs = argument.size();
    bool numericalFactor = (argument[0]->getPrimaryType() == NUMERICAL);
    for (int i=1; i<nArgs; i++)
    {
        if (argument[i]->getPrimaryType() == NUMERICAL)
        {
            if (!numericalFactor)
            {
                shared_ptr<Abstract> foo = argument[i];
                argument.erase(argument.begin()+i);
                argument.insert(argument.begin(),foo);
                numericalFactor = true;
                i--;
            }
            else 
            {
                argument[0] = argument[0]->addition_own(argument[i]);
                argument.erase(argument.begin()+i);
                nArgs--;
                i--;
            }
        }
    }
    if (numericalFactor and argument[0]->evaluateScalar()==0 and nArgs > 1)
    {
        numericalFactor = false;
        argument.erase(argument.begin());
        nArgs--;
    }
    shared_ptr<Abstract> term;
    shared_ptr<Abstract> term2;
    shared_ptr<Abstract> factor;
    for (int i=numericalFactor; i<nArgs-1; i++)
    {
        term = argument[i]->getTerm();
        factor = argument[i]->getNumericalFactor();
        bool matched = false;
        for (int j=i+1; j<nArgs; j++)
        {
            term2 = argument[j]->getTerm();
            if (*term==term2)
            {
                factor = factor->addition_own(argument[j]->getNumericalFactor());
                matched = true;
                argument.erase(argument.begin()+j);
                j--;
                nArgs--;
            }
        }
        if (matched)
        {
            argument[i] = times_(factor, term);
            if (*argument[i] == ZERO)
            {
                argument.erase(argument.begin()+i);
                i--;
                nArgs--;
            }
        }
    }

    orderTerms();
    return simplified;
}
/*bool Plus::mergeTerms()
{
    bool simplified = false;
    Expr arg;
    for (const_iter arg=argument.begin();
                    arg!=argument.end(); ++arg){
        if ((*arg)->getType() == PLUS) { // Plus(Plus(... = Plus(...
            simplified = true;
            for (const_iter arg2=argument.begin();
                            arg2!=argument.end(); ++arg2) 
                if (arg != arg2)
                    (*arg)->insert(*arg2);
        }
    }
    if (simplified) return true;

    nArgs = argument.size();
    bool numericalFactor = (argument[0]->getPrimaryType() == NUMERICAL);
    for (const_iter arg=argument.begin();
                    arg!=argument.end(); ++arg) {
        if ((*arg)->getPrimaryType() == NUMERICAL) {
            if (!numericalFactor) {
                Expr foo = *arg;
                --arg = argument.erase(arg);
                argument.insert(argument.begin(), foo);
            }
            else {
                argument[0] = argument[0]->addition_own(*arg);
                --arg = argument.erase(arg);
                nArgs--;
            }
        }
    }
    if (numericalFactor and argument[0]->evaluateScalar()==0 and nArgs > 1)
    {
        numericalFactor = false;
        argument.erase(argument.begin());
        nArgs--;
    }
    for (iter arg=argument.begin()+numericalFactor;
              arg!=argument.end()-1; ++arg) {
        Expr term = (*arg)->getTerm();
        Expr factor = (*arg)->getNumericalFactor();
        bool matched = false;
        for (const_iter arg2=arg+1; 
                        arg2!=argument.end(); ++arg2) {
            Expr term2 = (*arg2)->getTerm();
            if (*term == term2) {
                factor = factor->addition_own((*arg2)->getNumericalFactor());
                matched = true;
                simplified = true;
                --arg2 = argument.erase(arg2);
                nArgs--;
            }
        }
        if (matched) {
            *arg = times_(factor, term);
            if (*arg == ZERO) {
                --arg = argument.erase(arg);
                nArgs--;
            }
        }
    }

    orderTerms();
    return simplified;
}*/

void Plus::orderTerms()
{
    sort(argument.begin(), argument.end());
    return;
}

Expr Plus::derive(const Expr& t_abstract) const
{
    if (t_abstract == nullptr) return ZERO;
    Expr rep = ZERO;
    for (int i=0; i<nArgs; i++)
        rep = plus_(rep,argument[i]->derive(t_abstract));

    return rep;
}

Expr Plus::factor(bool full)
{
    if (nArgs == 0) return ZERO;
    vector<Expr > arg = argument;
    if (full)
    {
        for (int i=0; i<nArgs; i++)
            arg[i] = arg[i]->factor(full);
    }
    Expr result = plus_(arg);
    int mini = 0;
    int nFactorsMini = arg[0]->getNFactor();
    for (int i=1; i<nArgs; i++)
    {
        if (nFactorsMini > arg[i]->getNFactor())
        {
            mini = i;
            nFactorsMini = arg[i]->getNFactor();
        }
    }
    vector<Expr > factors = arg[mini]->getFactors();
    if (factors.size() == 0) factors = vector<Expr >(1,arg[mini]);
    /*cout<<"FACTORIZING ";print();
    for (int i=0; i<factors.size(); i++)
    {
        cout<<"Factor "<<i+1; factors[i]->print();
    }*/
    for (int i=0; i<nArgs; i++)
    {
        if (i != mini)
        {
            for (size_t j=0; j<factors.size(); j++)
            {
                if (!arg[i]->askTerm(factors[j]))
                {
                    factors.erase(factors.begin()+j);
                    j--;
                }
            }
            if (factors.size() == 0) break;
        }
    }
    if (factors.size() == 0) return result;
    Expr exponent_i;
    Expr exponent_j;
    /*for (int i=0; i<factors.size(); i++)
    {
        cout<<"Factor "<<i+1; factors[i]->print();
    }*/
    for (size_t i=0; i<factors.size(); i++)
    {
        if (factors[i]->getType() == POW)
        {
            exponent_i = factors[i]->getArgument(1);
            if (exponent_i->getPrimaryType() != NUMERICAL) // Checking number exponent
            {
                factors.erase(factors.begin()+i);
                i--;
                break;
            }
            for (size_t j=0; j<factors.size(); j++)
            {
                if (i != j)
                {
                    if (factors[j]->getType() == POW)
                    {
                        exponent_j = factors[j]->getArgument(1);
                        if (exponent_j->getPrimaryType() != NUMERICAL) // Checking number
                        {
                            factors.erase(factors.begin()+j);
                            if (i > j) i--;
                            break;
                        }
                        if (abs(exponent_i->evaluateScalar()) < abs(exponent_j->evaluateScalar()))
                        {
                            factors.erase(factors.begin()+i);
                            i--;
                            break;
                        }
                        factors.erase(factors.begin()+j);
                        if (i > j) i--;
                        break;
                    }
                    else if (*factors[j] == factors[i]->getArgument(0))
                    {
                        if (abs(exponent_i->evaluateScalar()) > 1)
                        {
                            factors.erase(factors.begin()+j);
                            if (i > j) i--;
                            break;
                        }
                        factors.erase(factors.begin()+j);
                        if (i > j) i--;
                        break;
                    }
                }
            }
        }
    }
    /*for (int i=0; i<factors.size(); i++)
    {
        cout<<"Factor "<<i+1; factors[i]->print();
    }*/
    Expr t_abstract;
    Expr newAbstract;
    for (size_t j=0; j<factors.size(); j++)
    {
        t_abstract = factors[j];
        newAbstract = ZERO;
        for (int i=0; i<nArgs; i++)
        {
            if (*arg[i]==t_abstract)
            {
                arg[i] = int_(1);
            }
            else
            {
                int type = arg[i]->getType();
                if (type == TIMES or type == POW)
                {
                    if (arg[i]->askTerm(t_abstract))
                    {
                        arg[i] = arg[i]->suppressTerm(t_abstract);
                    }
                    else return Refresh(this);
                }
                else return Refresh(this);
            }
        }
    }
    return times_(times_(factors),plus_(arg));
}

Expr Plus::factor(const Expr& t_abstract, bool full)
{
    vector<Expr > arg = argument;
    if (full)
    {
        for (int i=0; i<nArgs; i++)
            arg[i] = arg[i]->factor(t_abstract, true);
    }
    Expr newAbstract = ZERO;
    vector<int> toFactor(0);
    for (int i=0; i<nArgs; i++)
    {
        if (*arg[i] == t_abstract)
        {
            toFactor.push_back(i);
        }
        else
        {
            int type = arg[i]->getType();
            if (type == TIMES or type == POW)
            {
                if (arg[i]->askTerm(t_abstract))//, true))
                {
                    toFactor.push_back(i);
                }
                else
                    newAbstract = plus_(newAbstract, arg[i]);
            }
            else
                newAbstract = plus_(newAbstract, arg[i]);
        }
    }
    if (toFactor.size() >= 2)
    {
        Expr factored = ZERO;
        for (size_t i=0; i<toFactor.size(); i++)
            factored = plus_(factored, arg[toFactor[i]]->suppressTerm(t_abstract));
        newAbstract = plus_(newAbstract, times_(t_abstract, factored));
        return newAbstract;
    }
    else return plus_(arg);
    /*if (full) AbstractMultiFunc::factor(t_abstract, true);
    Expr newAbstract = ZERO;
    for (int i=0; i<nArgs; i++)
    {
        if (*argument[i]==t_abstract)
        {
            newAbstract = plus_(newAbstract, int_(1));
        }
        else
        {
            int type = argument[i]->getType();
            if (type == TIMES or type == POW)
            {
                if (argument[i]->askTerm(t_abstract))
                {
                    newAbstract = plus_(newAbstract, argument[i]->suppressTerm(t_abstract));
                }
                else return;
            }
            else return;
        }
    }
    *this=Plus(ZERO, times_(t_abstract,newAbstract));*/
}

int Plus::getParity(const Expr& t_variable) const
{
    int parity = argument[0]->getParity(t_variable);
    if (parity == 0) return 0;

    for (int i=1; i<nArgs; i++)
    {
        if (parity != argument[i]->getParity(t_variable)) return 0;
    }
    return parity;
}

bool Plus::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (nArgs == 1) return *argument[0]==t_abstract;
    if (t_abstract->getType() != PLUS) return false;
    if (nArgs != t_abstract->getNArgs()) return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++) indicesLeft[i] = i;

    for (int i=0; i<nArgs; i++)
    {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++)
        {
            if (*argument[i] == t_abstract->getArgument(indicesLeft[j]))
            {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched) return false;
    }
    return true;
}

Expr plus_(const Expr& leftOperand, const Expr& rightOperand)
{
    if (leftOperand == nullptr or rightOperand == nullptr) return ZERO;
    Expr foo = make_shared<Plus>(leftOperand, rightOperand);
    if (leftOperand->getPrimaryType() == VECTORIAL)
        return leftOperand->addition_own(rightOperand);
    if (rightOperand->getPrimaryType() == VECTORIAL)
        return rightOperand->addition_own(leftOperand);
    if (leftOperand->getType() == POLYNOMIAL)
        return leftOperand->addition_own(rightOperand);
    if (rightOperand->getType() == POLYNOMIAL)
        return rightOperand->addition_own(leftOperand);
    if (foo->getNArgs() == 1)
    {
        Expr foo2 = foo->getArgument();
        return foo2;
    }
    else if (foo->getNArgs() == 0)
    {
        return ZERO;
    }

    return foo;
}

Expr plus_(const vector<Expr >& operands)
{
    Expr foo = make_shared<Plus>(operands);
    if (foo->getNArgs() == 1)
    {
        Expr foo2 = foo->getArgument();
        return foo2;
    }
    else if (foo->getNArgs() == 0)
    {
        return ZERO;
    }

    return foo;
}

Expr minus_(const Expr& leftOperand, const Expr& rightOperand)
{
    return plus_(leftOperand,times_(int_(-1),rightOperand));
}

//////////////////////////////////////
//// Class Times             /////////
//////////////////////////////////////

Times::Times(const vector<Expr >& operands, bool explicitTimes): AbstractMultiFunc()
{
    nArgs = operands.size();
    argument = operands;
    if (not explicitTimes and nArgs > 0) mergeTerms();
    nArgs = argument.size();
}

Times::Times(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes): AbstractMultiFunc()
{
    if (leftOperand->getType() == TIMES and rightOperand->getType() != TIMES) {
        argument = leftOperand->getVectorArgument();
        nArgs = argument.size();
        insert(rightOperand, true); // rightOperand inserted to the right
                                    // of leftOperand
    }
    else if (rightOperand->getType() == TIMES and leftOperand->getType() != TIMES) {
        argument = rightOperand->getVectorArgument();
        nArgs = argument.size();
        insert(leftOperand, false); // leftOperand inserted to the left
                                    // of rightOperand
    }
    else {
        nArgs = 2;
        argument = vector<Expr>(2);
        argument[0] = leftOperand;
        argument[1] = rightOperand;
        if (not explicitTimes) mergeTerms();
    }
}

Expr Times::getNumericalFactor() const
{
    if (argument[0]->getPrimaryType() == NUMERICAL) return argument[0];
    return int_(1);
}

Expr Times::getTerm()
{
    if (argument[0]->getPrimaryType() == NUMERICAL)
    {
        vector<Expr > foo(argument);
        foo.erase(foo.begin());
        return times_(foo);
    }
    return Copy(this);
}

int Times::getNFactor() const
{
    int nFactor = 1;
    for (int i=0; i<nArgs; i++)
        nFactor *= argument[i]->getNFactor();
    return nFactor;
}

vector<Expr > Times::getFactors() const
{
    vector<Expr > foo(0), foo2;
    for (int i=0; i<nArgs; i++)
    {
        foo2 = argument[i]->getFactors();
        if (foo2.size() == 0) foo2 = vector<Expr >(1,argument[i]);
        foo.insert(foo.end(), foo2.begin(), foo2.end());
    }
    return foo;
}

bool Times::askTerm(const Expr& t_abstract, bool exact) const
{
    for (int i=0; i<nArgs; i++)
    {
        if (*argument[i]==t_abstract) return true;
        else if (!exact and argument[i]->getType() == POW) // Pow
            if (argument[i]->askTerm(t_abstract)) return true;
    }
    return false;
}

Expr Times::suppressTerm(const Expr& t_abstract) const
{
    shared_ptr<Abstract> newAbstract = int_(1);
    bool matched = false;
    for (int i=0; i<nArgs; i++) {
        if (not matched) {
            if (argument[i]->getType() == POW) { // Pow 
                if (argument[i]->askTerm(t_abstract)) {
                    newAbstract = times_(newAbstract, argument[i]->suppressTerm(t_abstract));
                    matched = true;
                    continue;
                }
                else newAbstract = times_(newAbstract, argument[i]);
            }
            else if (*argument[i]==t_abstract) {
                matched = true;
                continue;
            }
            else newAbstract = times_(newAbstract, argument[i]);
        }
        else newAbstract = times_(newAbstract, argument[i]);
    }

    return newAbstract;
/*
    Expr newAbstract = Empty(getType());
    bool matched = false;
    for (const auto& arg: argument) {
        if (not matched) {
            if (arg->getType() == POW) { // Pow 
                if (arg->askTerm(t_abstract)) {
                    newAbstract->insert(arg->suppressTerm(t_abstract));
                    matched = true;
                    continue;
                }
                else newAbstract->insert(arg);
            }
            else if (*arg==t_abstract) {
                matched = true;
                continue;
            }
            else newAbstract->insert(arg);
        }
        else newAbstract->insert(arg);
    }
    return newAbstract;*/
}

Expr Times::getRealPart()
{
    Expr realPart = argument[0]->getRealPart();
    Expr imaginaryPart = argument[0]->getImaginaryPart();
    Expr foo;
    for (int i=1; i<nArgs; i++)
    {
        foo = Copy(realPart);
        realPart = plus_(times_(realPart,argument[i]->getRealPart()),times_(int_(-1),times_(imaginaryPart, argument[i]->getImaginaryPart())));
        if (i < nArgs-1)
            imaginaryPart = plus_(times_(foo,argument[i]->getImaginaryPart()),times_(imaginaryPart, argument[i]->getRealPart()));
    }

    return realPart;
}

Expr Times::getImaginaryPart() const
{
    Expr realPart = argument[0]->getRealPart();
    Expr imaginaryPart = argument[0]->getImaginaryPart();
    Expr foo;
    for (int i=1; i<nArgs; i++)
    {
        foo = Copy(realPart);
        if (i < nArgs-1)
            realPart = plus_(times_(realPart,argument[i]->getRealPart()),times_(int_(-1),times_(imaginaryPart, argument[i]->getImaginaryPart())));
        imaginaryPart = plus_(times_(foo,argument[i]->getImaginaryPart()),times_(imaginaryPart, argument[i]->getRealPart()));
    }

    return imaginaryPart;
}

Expr Times::getComplexModulus()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
    return pow_(plus_(pow_(real,int_(2)),pow_(im,int_(2))), double_(0.5));
}

Expr Times::getComplexArgument()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
    return make_shared<Angle>(im,real);
}

void Times::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 2) // Priority lesser than the previous operation: brackets
        cout<<"(";
    vector<int> denominatorIndices(0);
    vector<int> numeratorIndices(0);
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getType() == POW and argument[i]->getArgument(1)->isInteger() and argument[i]->getArgument(1)->evaluateScalar() == -1)
            denominatorIndices.push_back(i);
        else numeratorIndices.push_back(i);
    }
    for (size_t i=0; i<numeratorIndices.size(); i++)
    {
        argument[numeratorIndices[i]]->print(2);
        if (i <numeratorIndices.size() - 1)
            cout<<"*";
    }
    if (denominatorIndices.size() > 0)
    {
        cout<<"/";
        if (denominatorIndices.size() == 1)
            argument[denominatorIndices[0]]->getArgument(0)->print(3);
        else
        {
            cout<<"(";
            for(size_t i=0; i<denominatorIndices.size(); i++)
            {
                argument[denominatorIndices[i]]->getArgument(0)->print(2);
                if (i < denominatorIndices.size()-1)
                    cout<<"*";
            }
            cout<<"(";
        }
    }
    if (mode > 2)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Times::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 2) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    for (int i=0; i<nArgs; i++)
    {
        sout<<argument[i]->printLaTeX(2);
        if (i < nArgs-1)
            if (argument[i+1]->getType() == FRACTION or argument[i+1]->getType() == CFRACTION or (argument[i]->getPrimaryType() < 10 and argument[i+1]->getPrimaryType() >= 10))
                sout<<"\\cdot ";
    }
    if (mode > 2)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

void getExponentStructure(const Expr& argument, Expr& term, Expr& exponent)
    // Search for argument = term^exponent (default argument = argument^1)
    // This function is used assuming that exponent is NUMERICAL
    // Therefore exponent must always be NUMERICAL
{
    if (argument->getType() == POW) {
        exponent = argument->getArgument(1);
        if (exponent->getPrimaryType() != NUMERICAL) {
            exponent = ONE;
            term = argument;
        }
        else term = argument->getArgument(0);
    }
    else {
        term = argument;
        exponent = ONE;
    }
}

// side = 0 insertion to the Left, = 1 to the right.
void Times::insert(const Expr& t_abstract, bool side)
{
    if (nArgs == 0) {
        nArgs++;
        argument.insert(argument.begin(), t_abstract);
        return;
    }
    // If numerical, easy
    if (t_abstract->getPrimaryType() == NUMERICAL) {
        if (argument[0]->getPrimaryType() == NUMERICAL)
            argument[0] = argument[0]->multiplication_own(t_abstract);
        else {
            argument.insert(argument.begin(), t_abstract);
            ++nArgs;
        }
        if (*argument[0] == ZERO) {
            argument.clear();
            nArgs = 0;
        }
        else if (*argument[0] == ONE) {
            argument.erase(argument.begin());
            --nArgs;
        }
        return;
    }

    if (side) rightInsert(t_abstract);
    else      leftInsert (t_abstract);
}
void Times::leftInsert(const Expr& t_abstract)
{
    // If not numerical, we search for a similar term
    bool commut = t_abstract->getCommutable();
    int max = nArgs;
    Expr term, exponent;
    getExponentStructure(t_abstract, term, exponent);
    for (int i=0; i<nArgs; i++) {
        Expr term2, exponent2;
        getExponentStructure(argument[i], term2, exponent2);
        if (commut or argument[i]->getCommutable()) {
            // If we found the right term, it's done
            if (*term == term2) {
                argument[i] = pow_(term, exponent->addition_own(exponent2));
                if (*argument[i] == ONE) {
                    argument.erase(argument.begin()+i);
                    --nArgs;
                }
                return;
            }
        }
        else if (*term == term2) {
            argument[i] = pow_(term, exponent->addition_own(exponent2));
            if (*argument[i] == ONE) {
                argument.erase(argument.begin()+i);
                --nArgs;
            }
            return;
        }
        else {
            // max is the position not reachable because of commutation not trivial
            max = i;
            break;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    for (int i=0; i<max; i++) 
        if (t_abstract < argument[i]) {
            ++nArgs;
            argument.insert(argument.begin()+i, t_abstract);
            return;
        }

    // no term is more complicated than t_abstract, we put it at the end
    argument.insert(argument.begin()+max, t_abstract);
    ++nArgs;
}
void Times::rightInsert(const Expr& t_abstract)
{
    // If not numerical, we search for a similar term
    bool commut = t_abstract->getCommutable();
    int max = -1;
    Expr term, exponent;
    getExponentStructure(t_abstract, term, exponent);
    for (int i=nArgs-1; i>=0; --i) {
        Expr term2, exponent2;
        getExponentStructure(argument[i], term2, exponent2);
        if (commut or argument[i]->getCommutable()) {
            // If we found the right term, it's done
            if (*term == term2) {
                argument[i] = pow_(term, exponent->addition_own(exponent2));
                if (*argument[i] == ONE) {
                    argument.erase(argument.begin()+i);
                    --nArgs;
                }
                return;
            }
        }
        else if (*term == term2) {
            argument[i] = pow_(term, exponent->addition_own(exponent2));
            if (*argument[i] == ONE) {
                argument.erase(argument.begin()+i);
                --nArgs;
            }
            return;
        }
        else {
            // max is the position not reachable because of commutation not trivial
            max = i;
            break;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    for (int i=nArgs-1; i>max; --i)  {
        if (t_abstract > argument[i]) {
            ++nArgs;
            argument.insert(argument.begin()+i+1, t_abstract);
            return;
        }
    }

    // no term is more complicated than t_abstract, we put it at the end
    argument.insert(argument.begin()+max+1, t_abstract);
    ++nArgs;
}


double Times::evaluateScalar() const
{
    double product=1;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getDim() > 0) return 0;
        product *= argument[i]->evaluateScalar();
    }
    return product;
}

Expr Times::evaluate()
{
    bool number = true;
    double numericalRes = 1;
    Expr result = int_(1);
    for (int i=0; i<nArgs; i++) {
        const Expr foo = argument[i]->evaluate();
        if (foo->getPrimaryType() == NUMERICAL)
            numericalRes *= foo->evaluateScalar();
        else {
            result = times_(result, foo);
            number = false;
        }
    }
    if (number) return double_(numericalRes);
    else        return times_(double_(numericalRes),result);
}

bool Times::mergeTerms()
{
    bool simplified = false;
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == TIMES) { // Times(Times(.. = Times( , , ...
            vector<shared_ptr<Abstract> > t_argument = argument[i]->getVectorArgument();
            for (int j=0; j<nArgs; j++)
                if (i != j)
                    t_argument.push_back(argument[j]);
            nArgs += argument[i]->getNArgs()-1;
            i += argument[i]->getNArgs()-1;
            argument = t_argument;
        }
    }
    bool numericalFactor = (argument[0]->getPrimaryType() == NUMERICAL);
    for (int i=1; i<nArgs; i++) {
        if (argument[i]->getPrimaryType() == NUMERICAL) {
            if (!numericalFactor) {
                shared_ptr<Abstract> foo = argument[i];
                argument.erase(argument.begin()+i);
                argument.insert(argument.begin(),foo);
                numericalFactor = true;
                i--;
            }
            else {
                argument[0] = argument[0]->multiplication_own(argument[i]);
                argument.erase(argument.begin()+i);
                nArgs--;
                i--;
            }
        }
    }
    if (numericalFactor and argument[0]->evaluateScalar()==1 and nArgs > 1) {
        argument.erase(argument.begin());
        nArgs--;
    }
    else if (numericalFactor and argument[0]->evaluateScalar()==0) {
        argument = vector<shared_ptr<Abstract>>(1);
        argument[0] = ZERO;
        nArgs = 1;
        return false;
    }
    shared_ptr<Abstract> term, term2;
    shared_ptr<Abstract> factor, factor2;
    bool matched;
    for (int i=numericalFactor; i<nArgs-1; i++) {
        factor = ONE;
        if (argument[i]->getType() == POW) { //Pow 
            term = argument[i]->getArgument(1);
            if (term->getPrimaryType() == NUMERICAL) {
                factor = term;
                term = argument[i]->getArgument();
            }
            else 
                term = argument[i];
        }
        else term = argument[i];
        bool indicial = (argument[i]->getPrimaryType() == INDICIAL);
        if (argument[i]->getCommutable()) {
            if (indicial) {
                for (int j=i+1; j<nArgs; j++) {
                    if (argument[j]->getPrimaryType() == INDICIAL) {
                        argument[i] = make_shared<ITerm>(argument[i], argument[j]);
                        argument.erase(argument.begin()+j);
                        j--;
                        nArgs--;
                    }
                }
            }
            else {
                for (int j=i+1; j<nArgs; j++) {
                    factor2 = ONE;
                    if (argument[j]->getType() == POW) { //Pow
                        term2 = argument[j]->getArgument(1);
                        if (term2->getPrimaryType() == NUMERICAL) {
                            factor2 = term2;
                            term2 = argument[j]->getArgument();
                        }
                        else 
                            term2 = argument[j];
                    }
                    else term2 = argument[j];
                    if (*term==term2) {
                        factor = factor->addition_own(factor2);
                        matched = true;
                        argument.erase(argument.begin()+j);
                        j--;
                        nArgs--;
                    }
                }
            }
        }
        else {
            if (indicial) {
                for (int j=i+1; j<nArgs; j++) {
                    if(!argument[j]->getCommutable() and *argument[i]!=argument[j]) break;
                    if (argument[j]->getPrimaryType() == INDICIAL) {
                        argument[i] = make_shared<ITerm>(argument[i], argument[j]);
                        argument.erase(argument.begin()+j);
                        j--;
                        nArgs--;
                    }
                }
            }
            else {
                for (int j=i+1; j<nArgs; j++) {
                    if(!argument[j]->getCommutable() and *argument[i]!=argument[j]) break;
                    factor2 = ONE;
                    if (argument[j]->getType() == POW) {  //Pow
                        term2 = argument[j]->getArgument(1);
                        if (term2->getPrimaryType() == NUMERICAL) {
                            factor2 = term2;
                            term2 = argument[j]->getArgument();
                        }
                        else 
                            term2 = argument[j];
                    }
                    else term2 = argument[j];
                    if (*term==term2) {
                        factor = factor->addition_own(factor2);
                        matched = true;
                        argument.erase(argument.begin()+j);
                        j--;
                        nArgs--;
                    }
                }
            }
        }
        if (matched) {
            argument[i] = pow_(term, factor);
            simplified = true;
        } 
    }

    orderTerms();
    return simplified;
}
/*bool Times::mergeTerms()
{
    bool simplified = false;
    Expr arg;
    for (iter arg=argument.begin();
                    arg!=argument.end(); ++arg) {
        if ((*arg)->getType() == TIMES) {
            simplified = true;
            for (const_iter arg2=argument.begin();
                                              arg2!=argument.end(); ++arg2) {
                if (arg != arg2) {
                    (*arg)->insert(*arg2);
                }
            }
            argument = (*arg)->getVectorArgument();
            nArgs = argument.size();
            break;
        }
    }
    if (simplified) return true;

    nArgs = argument.size();
    cout<<"Size = "<<nArgs<<" distance = "<<argument.size()<<endl;
    bool numericalFactor = (argument[0]->getPrimaryType() == NUMERICAL);
    if (numericalFactor < nArgs) {
        for (iter arg=argument.begin()+numericalFactor;
                        arg!=argument.end(); ++arg) {
            cout<<"i = "<<distance(argument.begin(),arg)<<endl;
            (*arg)->print();
            if ((*arg)->getPrimaryType() == NUMERICAL) {
                if (not numericalFactor) {
                    Expr foo = *arg;
                    int dist = distance(argument.begin(), arg);
                    argument.erase(arg);
                    argument.insert(argument.begin(),foo);
                    arg = argument.begin()+dist;
                    numericalFactor = true;
                }
                else {
                    argument[0] = argument[0]->multiplication_own(*arg);
                    --arg = argument.erase(arg);
                    nArgs--;
                }
            }
        }
    }
    if (numericalFactor and argument[0]->evaluateScalar()==1 and nArgs > 1)
    {
        argument.erase(argument.begin());
        numericalFactor = false;
        nArgs--;
    }
    else if (numericalFactor and argument[0]->evaluateScalar()==0)
    {
        argument = vector<Expr>(1, ZERO);
        nArgs = 1;
        return false;
    }

    for (iter arg=argument.begin()+numericalFactor;
              arg!=argument.end()-1; ++arg) {
        Expr factor = ONE;
        Expr term1;
        if ((*arg)->getType() == POW) {
            term1 = (*arg)->getTerm();
            if (term1->getPrimaryType() == NUMERICAL) {
                factor = term1;
                term1 = (*arg)->getArgument();
            }
            else 
                term1 = *arg;
        }
        else
            term1 = *arg;
        bool matched = false;
        bool indicial = ((*arg)->getPrimaryType() == INDICIAL);
        if ((*arg)->getCommutable()) {
            if (indicial) {
                for (const_iter arg2=arg+1;
                                arg2!=argument.end(); ++arg2) {
                    if ((*arg2)->getPrimaryType() == INDICIAL) {
                        *arg = make_shared<ITerm>(*arg,*arg2);
                        --arg2 = argument.erase(arg2);
                        nArgs--;
                    }
                }
            }
            else {
                for (const_iter arg2=arg+1;
                                arg2!=argument.end(); ++arg2) {
                    Expr factor2 = ONE;
                    Expr term2;
                    if ((*arg2)->getType() == POW) {
                        term2 = (*arg2)->getArgument(1);
                        if (term2->getPrimaryType() == NUMERICAL) {
                            factor2 = term2;
                            term2 = (*arg2)->getArgument();
                        }
                        else
                            term2 = *arg2;
                    }
                    else
                        term2 = *arg2;
                    if (*term1 == term2) {
                        factor = factor->addition_own(factor2);
                        matched = true;
                        --arg2 = argument.erase(arg2);
                        nArgs--;
                    }
                }
            }
        }
        else {
            if (indicial) {
                for (const_iter arg2=arg+1;
                                arg2!=argument.end(); ++arg2) {
                    if (not (*arg2)->getCommutable() and (**arg) != *arg2)
                        break;
                    if ((*arg2)->getPrimaryType() == INDICIAL) {
                        *arg = make_shared<ITerm>(*arg, *arg2);
                        --arg2 = argument.erase(arg2);
                        nArgs--;
                    }
                }
            }
            else {
                for (const_iter arg2=arg+1;
                                arg2!=argument.end(); ++arg2) {
                    if (not (*arg2)->getCommutable() and (**arg) != *arg2) 
                        break;
                    Expr term2;
                    Expr factor2 = ONE;
                    if ((*arg2)->getType() == POW) {
                        term2 =(*arg2)->getArgument(1);
                        if (term2->getPrimaryType() == NUMERICAL) {
                            factor2 = term2;
                            term2 = (*arg2)->getArgument();
                        }
                        else
                            term2 = *arg2;
                    }
                    else 
                        term2 = *arg2;
                    if (*term1 == term2)
                    {
                        factor = factor->addition_own(factor2);
                        matched = true;
                        --arg2 = argument.erase(arg2);
                        nArgs--;
                    }
                }
            }
        }
        if (matched)
        {
            *arg = pow_(term1, factor);
            simplified = true;
        } 
    }

    orderTerms();
    return simplified;
}*/

void Times::orderTerms() 
{
    if (getCommutable())
    {
        sort(argument.begin(), argument.end());
        return;
    }
    Expr foo;
    for (int i=0; i<nArgs-1; i++)
    {
        int simpler = i;
        bool allCommutable = argument[i]->getCommutable();
        for (int j=i+1; j<nArgs; j++)
        {
            if (not argument[j]->getCommutable())
            {
                if (not allCommutable)
                    break;
                allCommutable = false;
            }
            if (*argument[j] < argument[simpler]) // argument[j] simpler
                simpler = j;
        }
        if (simpler != i)
        {
            foo = argument[i];
            argument[i] = argument[simpler];
            argument[simpler] = foo;
        }
    }
}

Expr Times::derive(const Expr& t_abstract) const
{
    if (t_abstract == nullptr) return ZERO;
    Expr rep = ZERO;
    Expr intermediateResult = nullptr;
    for (int i=0; i<nArgs; i++)
    {
        intermediateResult = int_(1);
        for (int j=0; j<nArgs; j++)
        {
           if (j != i) intermediateResult = times_(intermediateResult, argument[j]);
           else intermediateResult = times_(intermediateResult, argument[j]->derive(t_abstract));
        } 
        rep = plus_(rep,intermediateResult);
    }

    return rep;
}

Expr Times::develop(bool full)
{
    Expr copy = Copy(this);
    if (full)
        for (int i=0; i<nArgs; i++)
            copy->setArgument(argument[i]->develop(true),i);
    vector<Expr > newAbstracts(1);
    newAbstracts[0] = int_(1);
    vector<Expr > foo(0);
    int nArgsBis;
    for (int i=0; i<nArgs; i++)
    {
        if (copy->getArgument(i)->getType() == PLUS) // Plus
        {
            nArgsBis = copy->getArgument(i)->getNArgs();
            for (int j=0; j<nArgsBis; j++)
                for (size_t k=0; k<newAbstracts.size(); k++)
                    foo.push_back(times_(newAbstracts[k],copy->getArgument(i)->getArgument(j)));
            newAbstracts = foo;
            foo.clear();
        }
        else
        {
            for (size_t j=0; j<newAbstracts.size(); j++)
                newAbstracts[j] = times_(newAbstracts[j], copy->getArgument(i));
        }
    }
    return plus_(newAbstracts);
}

int Times::isPolynomial(const Expr& t_abstract) const
{
    bool polynomialTermFound = false;
    bool dependencyFound = false;
    int order = 0;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->dependsOn(t_abstract))
        {
            order = argument[i]->isPolynomial(t_abstract);
            if (order > 0)
                polynomialTermFound = true;
            else 
                dependencyFound = true;
        }
    }
    if (polynomialTermFound and not dependencyFound)
    {
        return order;
    }
    return 0;
}

Expr Times::getPolynomialTerm(const Expr& t_variable, int order)
{
    int argument_order;
    Expr result = Copy(this);
    if (order == 0)
        return result;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->dependsOn(t_variable))
        {
            argument_order = argument[i]->isPolynomial(t_variable);
            if (order == argument_order)
            {
                Expr foo = argument[i]->suppressTerm(pow_(t_variable,int_(order)));
                result->setArgument(foo,i);
                break;
            }
        }
    }
    return result;
}

int Times::getParity(const Expr& t_variable) const
{
    int parity = 1;
    for (int i=0; i<nArgs; i++)
    {
        parity *= argument[i]->getParity(t_variable);
        if (parity == 0) return 0;
    }
    return parity;
}

bool Times::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (nArgs == 1) return *argument[0]==t_abstract;
    if (t_abstract->getType() != TIMES) return false;
    if (nArgs != t_abstract->getNArgs()) return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++) indicesLeft[i] = i;

    Expr foo;
    for (int i=0; i<nArgs; i++)
    {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++)
        {
            foo = t_abstract->getArgument(indicesLeft[j]);
            if (!argument[i]-> getCommutable() and !foo->getCommutable() and *argument[i]!=foo) break;
            if (*argument[i] == foo)
            {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched) return false;
    }
    return true;
}

Expr times_(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes)
{
    if (leftOperand == nullptr or rightOperand == nullptr) return ZERO;
    if (leftOperand->getType() == DERIVATIVE and leftOperand->getArgument() == ZERO)
        return derivative_(rightOperand,leftOperand->getArgument(1), leftOperand->getOrder());
    if (leftOperand->getPrimaryType() == VECTORIAL)
        return leftOperand->multiplication_own(rightOperand);
    if (rightOperand->getPrimaryType() == VECTORIAL)
        return rightOperand->multiplication_own(leftOperand);
    if (leftOperand->getType() == POLYNOMIAL)
    {
        if (rightOperand->getType() == POLYNOMIAL and explicitTimes)
            return make_shared<Times>(leftOperand, rightOperand);
        return leftOperand->multiplication_own(rightOperand);
    }
    if (rightOperand->getType() == POLYNOMIAL)
    {
        if (leftOperand->getType() == POLYNOMIAL and explicitTimes)
            return make_shared<Times>(leftOperand, rightOperand);
        return rightOperand->multiplication_own(leftOperand);
    }
    if (leftOperand->getType() == FRACTION)
    {
        if (rightOperand->getType() == FRACTION)
        {
            return fraction_(times_(leftOperand->getArgument(0),rightOperand->getArgument(0),explicitTimes),times_(leftOperand->getArgument(1),rightOperand->getArgument(1),explicitTimes));
        }
        return fraction_(times_(leftOperand->getArgument(0),rightOperand,explicitTimes),leftOperand->getArgument(1));
    }
    else if (rightOperand->getType() == FRACTION)
    {
        return fraction_(times_(leftOperand,rightOperand->getArgument(0),explicitTimes),rightOperand->getArgument(1));
    }
    Expr foo = make_shared<Times>(leftOperand, rightOperand, explicitTimes);
    if (foo->getNArgs() == 1)
    {
        return foo->getArgument();
    }
    else if (foo->getNArgs() == 0)
    {
        return ZERO;
    }

    return foo;
}

Expr times_(const vector<Expr >& operands, bool explicitTimes)
{
    Expr result = make_shared<Times>(operands, explicitTimes);
    if (result->getNArgs() == 1)
        return result->getArgument();
    if (result->getNArgs() == 0)
        return int_(1);
    return result;
}

//////////////////////////////////////
//// Class Fraction          /////////
//////////////////////////////////////

Fraction::Fraction(const Expr& leftOperand, const Expr& rightOperand): AbstractDuoFunc()
{
    argument[0] = leftOperand;
    argument[1] = rightOperand;
    mergeTerms();
}

int Fraction::getNFactor() const
{
    return (max(1,argument[0]->getNArgs())+max(1,argument[1]->getNArgs()));
}

vector<Expr > Fraction::getFactors() const
{
    vector<Expr > foo = argument[0]->getFactors();
    vector<Expr > foo2 = argument[1]->getFactors();
    for (auto& arg_foo2: foo2)
        arg_foo2 = pow_(arg_foo2,int_(-1));

    foo.insert(foo.end(), foo2.begin(), foo2.end());
    return foo;
}

bool Fraction::askTerm(const Expr& t_abstract, bool exact) const
{
    if (argument[0]->askTerm(t_abstract)) return true;
    if (argument[1]->askTerm(pow_(t_abstract,int_(-1)))) return true;
    return false;
}

Expr Fraction::suppressTerm(const Expr& t_abstract) const
{
    if (argument[0]->askTerm(t_abstract)) return fraction_(argument[0]->suppressTerm(t_abstract),argument[1]);
    if (argument[1]->askTerm(pow_(t_abstract,int_(-1)))) return fraction_(argument[0],argument[1]->suppressTerm(pow_(t_abstract,int_(-1))));
    cout<<"Warning problem with factors in fraction, expression probably wrong...\n";
    return Copy(this);
}

void Fraction::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 3) // Priority lesser than the previous operation: brackets
        cout<<"(";
    argument[0]->print(3);
    cout<<"/";
    argument[1]->print(3);
    if (mode > 3)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Fraction::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 3) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    sout<<"\\frac{";
    sout<<argument[0]->printLaTeX(1);
    sout<<"}{";
    sout<<argument[1]->printLaTeX(1);
    sout<<"}";
    if (mode > 3)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Fraction::evaluateScalar() const
{
    if (argument[0]->getDim() > 0 or argument[1]->getDim() > 0) return 0;
    return argument[0]->evaluateScalar()/argument[1]->evaluateScalar();
}

Expr Fraction::evaluate()
{
    Expr foo1 = argument[0]->evaluate();
    Expr foo2 = argument[1]->evaluate();
    if (foo1->getPrimaryType() == NUMERICAL and foo2->getPrimaryType() == NUMERICAL)
        return double_(fraction_(foo1,foo2)->evaluateScalar());
    foo1 = fraction_(foo1,foo2);
    return foo1->evaluate();
}

bool Fraction::mergeTerms()
{
    bool simplified = false;
    if (argument[0]->getType() == FRACTION)
    {
        if (argument[1]->getType() == FRACTION)
        {
            Expr foo = times_(argument[0]->getArgument(0),argument[1]->getArgument(1));
            argument[1] = times_(argument[0]->getArgument(1),argument[1]->getArgument(0));
            argument[0] = foo;
        }
        else
        {
            argument[1] = times_(argument[0]->getArgument(1),argument[1]);
            argument[0] = argument[0]->getArgument();
        }
    }
    else if (argument[1]->getType() == FRACTION)
    {
        argument[0] = times_(argument[1]->getArgument(1),argument[0]);
        argument[1] = argument[1]->getArgument(0);
    }
    
    return simplified;
}

Expr Fraction::derive(const Expr& t_abstract) const
{
    if (t_abstract == nullptr) return ZERO;
    return fraction_(minus_(times_(argument[0]->derive(t_abstract),argument[1]),times_(argument[0],argument[1]->derive(t_abstract))),pow_(argument[1],int_(2)));
}

int Fraction::isPolynomial(const Expr& t_abstract) const
{
    if (argument[1]->isPolynomial(t_abstract) == 0)
        return argument[0]->isPolynomial(t_abstract);
    return 0;
}

Expr Fraction::getPolynomialTerm(const Expr& t_variable, int order)
{
    return fraction_(argument[0]->getPolynomialTerm(t_variable, order),argument[1]);
}

int Fraction::getParity(const Expr& t_variable) const
{
    int parity = argument[0]->getParity(t_variable);
    if (parity == 0) return 0;
    return parity*argument[1]->getParity(t_variable);
}

bool Fraction::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (t_abstract->getType() != FRACTION) return false;
    if (*argument[0] != t_abstract->getArgument(0) or *argument[1]!=t_abstract->getArgument(1)) return false;
    return true;
}

Expr fraction_(const Expr& leftOperand, const Expr& rightOperand)
{
    if (leftOperand == nullptr or rightOperand == nullptr) return ZERO;
    if (rightOperand->getPrimaryType() == NUMERICAL and rightOperand->evaluateScalar() == 0)
        return INF;
    Expr foo = make_shared<Fraction>(leftOperand, rightOperand);
    Expr arg = foo->getArgument();
    Expr arg2 = foo->getArgument(1);
    if (arg->getPrimaryType() == NUMERICAL and arg2->getPrimaryType() == NUMERICAL)
    {
        if (arg2->getType() == CFRACTION)
            arg2 = _cfraction_(arg2->getDenom(), arg2->getNum());
        else if (arg2->isInteger())
            arg2 = _cfraction_(1, (int)arg2->evaluateScalar());
        else arg2 = double_(1./arg2->evaluateScalar());
        return arg->multiplication_own(arg2);
    }
    if (((arg->getType()==INTEGER or arg->getType() == DOUBLE) and arg->evaluateScalar()==0) or (*arg2==int_(1)))
        return arg;
    if (rightOperand->isInteger())
        return times_(_cfraction_(1,rightOperand->evaluateScalar()),leftOperand);
    if (rightOperand->getType() == CFRACTION)
        return times_(_cfraction_(rightOperand->getDenom(),rightOperand->getNum()),leftOperand);

    if (*arg->getNumericalFactor() != int_(1))
    {
        if (*arg2->getNumericalFactor() != int_(1))
            return times_(fraction_(arg->getNumericalFactor(),arg2->getNumericalFactor()),fraction_(arg->getTerm(), arg2->getTerm()));
        else 
            return times_(arg->getNumericalFactor(),fraction_(arg->getTerm(),arg2));
    }
    else if (*arg2->getNumericalFactor() != int_(1))
    {
        return times_(fraction_(int_(1),arg2->getNumericalFactor()),fraction_(arg,arg2->getTerm()));
    }
    return times_(leftOperand,pow_(rightOperand,int_(-1)));
}

//////////////////////////////////////
//// Class Pow               /////////
//////////////////////////////////////

Pow::Pow(const Expr& leftOperand, const Expr& rightOperand): AbstractDuoFunc()
{
    argument[0] = leftOperand;
    argument[1] = rightOperand;
    mergeTerms();
}

int Pow::getNFactor() const
{
    if (argument[1]->getPrimaryType() != NUMERICAL) return 1;
    return 2*floor(argument[1]->evaluateScalar())+1;
}

vector<Expr > Pow::getFactors() const
{
    //return Abstract::getFactors();
    if (argument[1]->getPrimaryType() != NUMERICAL) return Abstract::getFactors();
    vector<Expr > foo(0);
    if (argument[1]->getType() == INTEGER or argument[1]->getType() == DOUBLE)
    {
        int a = argument[1]->evaluateScalar();
        for (int i=sgn(a); abs(i)<=abs(a); i+=sgn(a))
            foo.push_back(pow_(argument[0],int_(i)));
    }
    else
    {
        int num = argument[1]->getNum();
        int denom = argument[1]->getDenom();
        if (num < 0)
        {
            if (denom < 0)
            {
                num = -num;
                denom = -denom;
            }
        }
        else if (denom < 0)
        {
            num = -num;
            denom = -denom;
        }
        for (int delta_num=0; sgn(num+delta_num)==sgn(num); delta_num-=sgn(num)*denom)
            foo.push_back(pow_(argument[0],_cfraction_(num+delta_num,denom)));
        if (PGCD(num,denom) != 1)
        {
            for (int i=sgn(num); abs(i)<abs(num*1.)/denom; i+=sgn(num))
                foo.push_back(pow_(argument[0], int_(i)));
        }
    }
    return foo;
}

bool Pow::askTerm(const Expr& t_abstract, bool exact) const
{
    if (exact) return ((*this)==t_abstract);
    if (t_abstract->getType() == POW) // Pow also
    {
        Expr a = t_abstract->getArgument(1);
        Expr b = argument[1];
        if (*argument[0] != t_abstract->getArgument(0)) return false;
        if (*a == b) return true;
        if (a->getPrimaryType() != NUMERICAL or b->getPrimaryType() != NUMERICAL) return false;
        if (a->getType() == INTEGER or a->getType() == DOUBLE)
        {
            double a_val = a->evaluateScalar();
            double b_val = b->evaluateScalar();
            return (abs(b_val)>abs(a_val) and sgn(a_val)==sgn(b_val));
        }
        else if (a->getType() == CFRACTION)
        {
            //if (b->getType() == CFRACTION) return false;
            int a_denom = a->getDenom();
            int b_denom = b->getDenom();
            double a_val = a->evaluateScalar();
            double b_val = b->evaluateScalar();
            return (a_denom==b_denom and abs(a_val)<abs(b_val) and sgn(a_val)==sgn(b_val));
        }
        return ((*this)==t_abstract);
    }
    else return (*argument[0]==t_abstract and (argument[1]->isInteger() or argument[1]->getType() == CFRACTION) and argument[1]->evaluateScalar() > 0);
}

Expr Pow::suppressTerm(const Expr& t_abstract) const
{
    // Caution here: we do not re-test if the term corresponds (we do not call askTerm
    // we suppose it has been done before calling this function...)
    if (t_abstract->getType() == POW)
    {
        return pow_(argument[0],minus_(argument[1], t_abstract->getArgument(1)));
    }
    else return pow_(argument[0],minus_(argument[1], int_(1)));
}

void Pow::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 4) // Priority lesser than the previous operation: brackets
        cout<<"(";
    argument[0]->print(4);
    cout<<"^";
    argument[1]->print(4);
    if (mode > 4)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Pow::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 4) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    sout<<argument[0]->printLaTeX(4);
    sout<<"^{";
    sout<<argument[1]->printLaTeX(1);
    sout<<"}";
    if (mode > 4)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Pow::evaluateScalar() const
{
    if (argument[0]->getDim() > 0 or argument[1]->getDim() > 0) return 0;
    return pow(argument[0]->evaluateScalar(), argument[1]->evaluateScalar());
}

Expr Pow::evaluate()
{
    Expr foo1 = argument[0]->evaluate();
    Expr foo2 = argument[1]->evaluate();
    if (foo1->getPrimaryType() == NUMERICAL and foo2->getPrimaryType() == NUMERICAL)
        return double_(pow_(foo1,foo2)->evaluateScalar());
    return pow_(foo1,foo2);
}

bool Pow::mergeTerms()
{
    bool simplified = false;
    Expr arg;
    if (argument[0]->getType() == POW) // Pow(Pow(a,b),c) = Pow(a,Times(b,c))
    {
        argument[1] = times_(argument[0]->getArgument(1),argument[1]);
        argument[0] = argument[0]->getArgument();
    }
    else if ((argument[0]->getType() == DOUBLE or argument[0]->getType() == INTEGER) and (argument[1]->getType() == DOUBLE or argument[1]->getType() == INTEGER))
    {
        argument[0] = auto_number_(pow(argument[0]->evaluateScalar(),argument[1]->evaluateScalar()));
        argument[1] = int_(1);
    }
    else if ((argument[0]->getType() == DOUBLE or argument[0]->getType() == INTEGER) and argument[1]->getType() == CFRACTION and argument[1]->evaluateScalar() == 0.5)
    {
        double value = sqrt(argument[0]->evaluateScalar());
        if (value == round(value))
        {
            argument[0] = int_(value);
            argument[1] = int_(1);
        }
    }
    else if (argument[0]->getType() == FRACTION and (argument[1]->getNumericalFactor() < 0 or (argument[1]->getPrimaryType() == NUMERICAL and argument[1]->evaluateScalar() < 0))) // (a/b)^(-c) = (b/a)^c
    {
        Expr tmp = argument[0]->getArgument(0);
        argument[0]->setArgument(argument[0]->getArgument(1),0);
        argument[0]->setArgument(tmp,1);
        if (argument[1]->getPrimaryType() == NUMERICAL)
            argument[1] = argument[1]->multiplication_own(int_(-1));
        else
            argument[1] = times_(argument[1],int_(-1));
    }
    else if (argument[0]->getType() == TIMES) // (a*b)^c = a^c*b^c
    {
        vector<Expr > newArgument(0);
        for (int i=0; i<argument[0]->getNArgs(); i++)
            newArgument.push_back(pow_(argument[0]->getArgument(i),argument[1]));
        argument[1] = int_(1);
        argument[0] = times_(newArgument);
    }

    return simplified;
}

Expr Pow::derive(const Expr& t_abstract) const
{
    if (t_abstract == nullptr) return ZERO;
    Expr rep = plus_(times_(times_(argument[1]->derive(t_abstract),log_(argument[0])),pow_(argument[0],argument[1])),times_(times_(argument[0]->derive(t_abstract),argument[1]),pow_(argument[0],minus_(argument[1],int_(1)))));

    return rep;
}

Expr Pow::develop(bool full)
{
    if (full)
    {
        Expr foo1 = argument[0]->develop(true);
        Expr foo2 = argument[1]->develop(true);
        if (foo2->isInteger() and foo1->getType() == PLUS)
        {
            double value = argument[1]->evaluateScalar();
            if (value == floor(value))
            {
                int iMax = round(abs(value));
                Expr result = int_(1);
                for (int i=0; i<iMax; i++)
                    result = times_(result, foo1,true);
                result = result->develop(true);
                if (value < 0)
                    pow_(result, int_(-1));
                return result;
            }
        }
        Expr result = pow_(foo1,foo2);
        return result;
    }
    return Refresh(this);
}

Expr Pow::getRealPart()
{
    cout<<"Warning: function \"Pow::getRealPart\" not yet implemented.\n";
    return ZERO;
}

Expr Pow::getImaginaryPart() const
{
    cout<<"Warning: function \"Pow::getImaginaryPart\" not yet implemented.\n";
    return ZERO;
}

Expr Pow::getComplexModulus()
{
    cout<<"Warning: function \"Pow::getComplexModulus\" not yet implemented.\n";
    return ZERO;
}

Expr Pow::getComplexArgument()
{
    cout<<"Warning: function \"Pow::getComplexArgument\" not yet implemented.\n";
    return ZERO;
}

int Pow::isPolynomial(const Expr& t_abstract) const
{
    if (argument[1]->isInteger())
        if (*argument[0]==t_abstract)
                return (int)argument[1]->evaluateScalar();
    return 0;
}

Expr Pow::getPolynomialTerm(const Expr& t_variable, int order)
{
    if (*argument[0] == t_variable and argument[1]->isInteger() and argument[1]->evaluateScalar() == order)
    {
        return int_(1);
    }
    else if (order == 0) return Copy(this);
    else return ZERO;
}

int Pow::getParity(const Expr& t_abstract) const
{
    int parity = argument[0]->getParity(t_abstract);
    int parity2 = argument[1]->getParity(t_abstract);
    if (parity == 1 and parity2 == 1) return 1;
    if (parity == 0 or parity2 == 0) return 0;
    if (not argument[1]->isInteger()) return 0;
    double value = argument[1]->evaluateScalar();
    return -2*((int)value%2)+1;
}

bool Pow::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (t_abstract->getType() != POW) return false;
    if (*argument[0] != t_abstract->getArgument(0) or *argument[1] != t_abstract->getArgument(1))
        return false;
    return true;
}

Expr pow_(const Expr& leftOperand, const Expr& rightOperand)
{
    if (leftOperand == nullptr or rightOperand == nullptr) return ZERO;
    if (*leftOperand == i_ and (rightOperand->getType() == DOUBLE or rightOperand->getType()  == INTEGER))
    {
        double value = rightOperand->evaluateScalar();
        if (value == round(value))
        {
            int n = round(value);
            if (n%2 == 1) return times_(int_(pow(-1,(n/2)%2)),i_);
            return int_(pow(-1,(n/2)%2));
        }
    }
    if (*leftOperand == e_)
        return exp_(rightOperand);

    Expr foo = make_shared<Pow>(leftOperand, rightOperand);
    Expr arg0 = foo->getArgument(0);
    Expr arg1 = foo->getArgument(1);
    if (*arg1==ZERO) return ONE;
    if (*arg0==ZERO) return ZERO;
    if (*arg0==ONE) return ONE;
    if (*arg1==ONE) return arg0;

    return foo;
}

Expr sqrt_(const Expr& operand)
{
    return pow_(operand, _cfraction_(1,2));
}

Polynomial::Polynomial(const Expr& t_abstract, const Expr& t_variable): AbstractMultiFunc()
{
    variable = t_variable;
    Expr t_t_abstract;
    if (t_abstract->getType() == POLYNOMIAL and *t_variable != t_abstract->getVariable())
        t_t_abstract = t_abstract->getRegularExpression();
    else
        t_t_abstract = t_abstract;
    if (t_t_abstract->getType() == PLUS)
    {
        int max_order = 0;
        argument = vector<Expr >(1);
        argument[0] = ZERO;
        Expr foo;
        for (int i=0; i<t_t_abstract->getNArgs(); i++)
        {
            foo = t_t_abstract->getArgument(i);
            int argument_order = foo->isPolynomial(t_variable);
            if (argument_order > max_order)
                for (int i=0; i<argument_order-max_order; i++)
                    argument.push_back(ZERO);
            argument[argument_order] = plus_(argument[argument_order],foo->getPolynomialTerm(t_variable, argument_order));
        }
    }
    else
    {
        int max_order = t_t_abstract->isPolynomial(t_variable);
        argument = vector<Expr >(0);
        for (int i=0; i<max_order+1; i++)
            argument.push_back(ZERO);
        argument[max_order] = t_t_abstract->getPolynomialTerm(t_variable, max_order);
    }
    nArgs = argument.size();
    mergeTerms();
}

Polynomial::Polynomial(const vector<Expr >& terms, const Expr& t_variable): AbstractMultiFunc()
{
    argument = terms;
    variable = t_variable;
    nArgs = argument.size();
    mergeTerms();
}

bool Polynomial::mergeTerms()
{
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == POLYNOMIAL)
            argument[i] = argument[i]->getRegularExpression();
        argument[i] = Refresh(argument[i]);
    }
    for (int i=nArgs-1; i>=1; i--) {
        if (*argument[i] == ZERO) {
            argument.erase(argument.begin()+i);
            nArgs--;
        }
        else 
            break;
    }
    return false;
}

int Polynomial::getOrder() const
{
    return nArgs - 1;
}

Expr Polynomial::getVariable() const
{
    return variable;
}

void Polynomial::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        cout<<"(";
    for (int i=0; i<nArgs; i++)
    {
        if (*argument[i] != ZERO)
        {
            if (i == 0 or *argument[i] != int_(1))
                argument[i]->print(2);
            if (i > 0)
            {
                if (*argument[i] != int_(1))
                    cout<<"*";
                variable->print(4);
                if (i > 1)
                    cout<<"^"<<i;
            }
            if (i < nArgs-1)
            {
                cout<<" + ";
            }
        }
    }
    if (mode > 1)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Polynomial::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    for (int i=0; i<nArgs; i++)
    {
        sout<<argument[i]->printLaTeX(1);
        if (i < nArgs-1)
            sout<<"+";
    }
    if (mode > 1)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Polynomial::evaluateScalar() const
{
    double sum=0;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getDim() > 0) return 0;
        sum += argument[i]->evaluateScalar();
    }
    return sum;
}

Expr Polynomial::evaluate()
{
    Expr result = ZERO;
    Expr foo, foo2;
    for (int i=0; i<nArgs; i++)
    {
        foo = pow_(variable->evaluate(),int_(i));
        foo2 = times_(argument[i]->evaluate(),foo->evaluate());
        result = plus_(result, foo2->evaluate());
        result = result->evaluate();
    }
    return result;
}

Expr Polynomial::derive(const Expr& t_abstract) const
{
    Expr rep;
    vector<Expr > newTerms = argument;
    if (*t_abstract == variable)
    {
        Expr foo = newTerms[0]->derive(t_abstract);
        newTerms.erase(newTerms.begin());
        if (*foo != ZERO)
        {
            if (newTerms.size() > 0)
                newTerms[0] = plus_(newTerms[0], foo);
            else newTerms.insert(newTerms.begin(),foo);
        }
        for(int i=0; i<nArgs; i++)
        {
            newTerms[i] = times_(int_(i+1), newTerms[i]);
        }
        return make_shared<Polynomial>(newTerms, variable);
    }
    for (int i=0; i<nArgs; i++)
    {
        newTerms[i] = newTerms[i]->derive(t_abstract);
    }
    for (int i=newTerms.size()-1; i>= 0; i--)
    {
        if (*newTerms[i] == ZERO)
        {
            newTerms.erase(newTerms.begin()+i);
        }
    }
    return make_shared<Polynomial>(newTerms, variable);
}

int Polynomial::getParity(const Expr& t_variable) const
{
    int parity = 0;
    int newParity;
    if (*variable == t_variable)
    {
        if (*argument[0] != ZERO) parity = argument[0]->getParity(t_variable);
        for (int i=1; i<nArgs; i++)
        {
            if (*argument[i] != ZERO)
            {
                if (parity == 0) parity = -(i%2);
                else
                {
                    newParity = -2*(i%2)+1;
                    if (parity != newParity)
                        return 0;
                }
            }
        }
        if (parity == 0) return 1;
        return parity;
    }
    parity = argument[0]->getParity(t_variable);
    if (parity == 0) return 0;
    for (int i=1; i<nArgs; i++)
    {
        newParity = argument[i]->getParity(t_variable);
        if (newParity != parity) return 0;
    }
    return parity;
}

Expr Polynomial::getRegularExpression() const
{
    Expr result = ZERO;
    for (int i=0; i<nArgs; i++)
        result = plus_(argument[i],pow_(variable,int_(i)));

    return result;
}

Expr Polynomial::addition_own(const Expr& t_abstract) const
{
    Expr foo;
    if (t_abstract->getType() != POLYNOMIAL)
        foo = make_shared<Polynomial>(t_abstract, variable);
    else 
        foo = t_abstract;
    vector<Expr > foo_argument = argument;
    int foo_nArgs = nArgs;
    if (*variable == foo->getVariable())
    {
        for (int i=0; i<foo->getNArgs(); i++)
        {
            if (i >= foo_nArgs)
            {
                foo_nArgs++;
                foo_argument.push_back(ZERO);
            }
            foo_argument[i] = plus_(foo_argument[i], foo->getArgument(i));
        }
        return Refresh(make_shared<Polynomial>(foo_argument, variable));
    }

    return Refresh(plus_(getRegularExpression(),foo->getRegularExpression()));
}

Expr Polynomial::multiplication_own(const Expr& t_abstract) const
{
    Expr foo;
    if (t_abstract->getType() != POLYNOMIAL)
        foo = make_shared<Polynomial>(t_abstract, variable);
    else 
        foo = t_abstract;

    if (*variable == foo->getVariable())
    {
        vector<Expr > foo_argument(nArgs+foo->getNArgs()-1,ZERO);
        for (int i=0; i<foo->getNArgs(); i++)
        {
            for (int j=0; j<nArgs; j++)
            {
                foo_argument[i+j] = plus_(foo_argument[i+j],times_(argument[j],foo->getArgument(i)));
            }
        }
        return Refresh(make_shared<Polynomial>(foo_argument, variable));
    }

    return Refresh(times_(getRegularExpression(),foo->getRegularExpression()));
}

Expr Polynomial::division_own(const Expr& t_abstract) const
{
    Expr foo = Refresh(t_abstract);
    if (foo->getType() != POLYNOMIAL or *foo->getVariable() != variable)
        foo = polynomial_(foo,variable);
    if (foo->getNArgs() > nArgs)
        return Copy(this);
    
    Expr q = polynomial_(ZERO, variable);
    Expr r = polynomial_(argument, variable);
    Expr t;
    int iter = 0;
    int maxiter = 10;
    //cout<<"Division of "; print();
    //cout<<"By "; t_abstract->print();
    while(*r!=ZERO and r->getNArgs()>=foo->getNArgs() and iter < maxiter)
    {
        //cout<<"STEP "<<iter<<": \n";
        //cout<<"DIVIDER = "; q->print();
        //cout<<"RESTE   = "; r->print();
        t = fraction_(r->getArgument(r->getNArgs()-1), foo->getArgument(foo->getNArgs()-1));
        //cout<<"t = "; t->print();
        t = t->develop(true);
        t = times_(t,pow_(variable,int_(r->getNArgs()-foo->getNArgs())));
        //cout<<"t = "; t->print();
        t = t->develop(true);
        //cout<<"t = "; t->print();
        q = plus_(q,t);
        r = plus_(r,times_(times_(int_(-1),t),foo));
        //cout<<"End loop: \n";
        //cout<<"DIVIDER = "; q->print();
        //cout<<"RESTE   = "; r->print();
        r = r->develop(true);
        q = q->develop(true);
        ++iter;
    }
        //cout<<"DIVIDER = "; q->print();
        //cout<<"RESTE   = "; r->print();
    //string gg;
    //cin.ignore();
    //cin>>gg;
    if (*r == ZERO)
        return q;
    return Copy(this);
}

Expr Polynomial::factor(bool full)
{
    if (nArgs == 3)
    {
       Expr delta = plus_(pow_(argument[1],int_(2)),times_(times_(int_(-4),argument[0]),argument[2]));
       Expr mean = times_(int_(-1), argument[1]);
       Expr diff = sqrt_(delta);
       Expr root1 = fraction_(plus_(mean, diff),times_(int_(2),argument[2]));
       Expr root2 = fraction_(plus_(mean, times_(int_(-1),diff)), times_(int_(2),argument[2]));

       Expr pol1 = polynomial_(minus_(variable, root1), variable);
       Expr pol2 = polynomial_(minus_(variable, root2), variable);

       return times_(argument[2],times_(pol1, pol2, true));
    }
    return Copy(this);
}

bool Polynomial::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (nArgs == 1) return *argument[0]==t_abstract;
    if (t_abstract->getType() == POLYNOMIAL)
    {
        Expr t_variable = t_abstract->getVariable();
        if (*variable != t_variable) return false;
        vector<Expr > t_argument = t_abstract->getVectorArgument();
        if (t_argument.size() != argument.size()) return false;
        for (size_t i=0; i<t_argument.size(); i++)
            if (*argument[i] != t_argument[i])
                return false;
        return true;
    }
    if (t_abstract->getType() != PLUS) return false;
    if (nArgs != t_abstract->getNArgs()) return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++) indicesLeft[i] = i;

    for (int i=0; i<nArgs; i++)
    {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++)
        {
            if (*times_(argument[i],pow_(variable,int_(i))) == t_abstract->getArgument(indicesLeft[j]))
            {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched) return false;
    }
    return true;
}

Expr polynomial_(const Expr& t_abstract, const Expr& t_variable)
{
    if (t_abstract->getPrimaryType() == VECTORIAL)
    {
        Expr foo = tensor_(t_abstract->getShape());
        for (int i=0; i<t_abstract->getNArgs(); i++)
            foo->setArgument(polynomial_(t_abstract->getArgument(i),t_variable),i);
        return foo;
    }
    return make_shared<Polynomial>(t_abstract, t_variable);
}

Expr polynomial_(const vector<Expr >& operands, const Expr& t_variable)
{
    return make_shared<Polynomial>(operands, t_variable);
}

int Derivative::getOrder() const { return order;}

void Derivative::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    cout<<"d";
    if (order > 1)
        cout<<"^"<<order<<"(";
    cout<<"(";
    argument[0]->print(1);
    cout<<")";
    cout<<"/d";
    cout<<"(";
    argument[1]->print(1);
    cout<<")";
    if (order > 1)
        cout<<"^"<<order;
    if (mode == 0)
        cout<<endl;
}

string Derivative::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    sout<<"\\dfrac{d^"<<order<<"}{d";
    sout<<argument[1]->printLaTeX(1);
    sout<<"^"<<order<<"}\\left(";
    sout<<argument[1]->printLaTeX(1);
    sout<<"\\right)";

    return sout.str();
}

double Derivative::evaluateScalar() const
{
    if (argument[0]->getDim() > 0 or argument[1]->getDim() > 0) return 0;
    Expr df = argument[0];
    for (int i=0; i<order; i++)
        df = df->derive(argument[1]);

    return df->evaluateScalar();
}

Expr Derivative::evaluate()
{
    Expr df = argument[0];
    for (int i=0; i<order; i++)
        df = df->derive(argument[1]);

    return df;
}

Expr Derivative::derive(const Expr& t_abstract) const
{
    if (t_abstract == nullptr) return ZERO;

    return derivative_(argument[0]->derive(t_abstract), argument[1], order);
}

int Derivative::getParity(const Expr& t_variable) const
{
    int parity = argument[0]->getParity(t_variable);
    if (parity == -1) parity = -2*(order%2)+1;
    if (parity == 0) return 0;
    else return parity*argument[1]->getParity(t_variable);
}

bool Derivative::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (t_abstract->getType() != DERIVATIVE) return false;
    if (*argument[0] != t_abstract->getArgument(0) or *argument[1] != t_abstract->getArgument(1) or order != t_abstract->getOrder())
        return false;
    return true;
}

Expr derivative_(const Expr& leftOperand, const Expr& rightOperand, int order)
{
    if (leftOperand == nullptr or rightOperand == nullptr) return ZERO;

    if (order <= 0) return rightOperand;
    if (*leftOperand == rightOperand) return int_(order == 1);

    return make_shared<Derivative>(leftOperand, rightOperand, order);
}

Expr derivative_(const Expr& variable, int order)
{
    if (order <= 0) return ZERO;
    return make_shared<Derivative>(variable, order);
}

