#include "scalarFunc.h"

using namespace std;


bool AbstractFunc::getCommutable() const {
    return (commutable and argument->getCommutable());
}

int AbstractFunc::getNArgs(int axis) const {
    return 1;
}

Expr AbstractFunc::getArgument(int iArg) const {
    return argument;
}

Expr AbstractFunc::getComplexConjugate()
{
    Expr foo = Empty(getType());
    foo->setArgument(argument->getComplexConjugate());

    return foo;
}

void AbstractFunc::setArgument(const Expr& t_argument, int iArg) {
    argument = t_argument;
}

Expr AbstractFunc::factor(bool full)
{
    if (full) {
       Expr result = Empty(getType());
       result->setArgument(argument->factor(true));
       return Refresh(result);
    }
    return Copy(this);
}

Expr AbstractFunc::factor(const Expr& t_abstract, bool full)
{
    if (full) {
       Expr result = Empty(getType());
       result->setArgument(argument->factor(t_abstract,true));
       return Refresh(result);
    }
    return Copy(this);
}

Expr AbstractFunc::develop(bool full)
{
    if (full) {
        Expr result = Empty(getType());
        result->setArgument(argument->develop(true));
        return Refresh(result);
    }
    return Copy(this);
}

bool AbstractFunc::dependsOn(const Expr& t_abstract) const {
    return ((name != "" and name == t_abstract->getName()) or
            argument->dependsOn(t_abstract));
}

int AbstractFunc::isPolynomial(const Expr& t_abstract) const {
    return (*this==t_abstract);
}

Expr AbstractFunc::evaluate()
{
    Expr evalArg = argument->evaluate();
    Expr result = Empty(getType());

    if (evalArg->getPrimaryType() == smType::Numerical) {
        result->setArgument(evalArg);
        return auto_number_(result->evaluateScalar());
    }
    else {
        result->setArgument(evalArg);
        return result;
    }
}

bool AbstractFunc::operator==(const Expr& t_abstract) const 
{
    if (t_abstract->getName() == WHATEVER->getName()) 
        return true;

    return (t_abstract->getType() == this->getType() and 
            *argument == t_abstract->getArgument());
} 

bool AbstractDuoFunc::getCommutable() const 
{
    return (commutable and argument[0]->getCommutable() and 
            argument[1]->getCommutable());
}

Expr AbstractDuoFunc::getArgument(int iArg) const 
{
    if (iArg != 1 and iArg != 0) {
        print();
        callError(smError::OutOfBounds,
                "AbstractDuoFunc::getArgument(int iArg) const", iArg);
    }

    return argument[iArg];
}

void AbstractDuoFunc::setArgument(const Expr& t_argument, int iArg) 
{
    if (iArg != 1 and iArg != 0) {
        print();
        callError(smError::OutOfBounds,
                "AbstractDuoFunc::getArgument(int iArg) const", iArg);
    }

    argument[iArg] = t_argument;
}

Expr AbstractDuoFunc::factor(bool full) 
{
    if (full) {
       Expr result = Empty(getType());
       result->setArgument(argument[0]->factor(true), 0);
       result->setArgument(argument[1]->factor(true), 1);
       return Refresh(result);
    }

    return Copy(this);
}

Expr AbstractDuoFunc::factor(const Expr& t_abstract, bool full)
{
    if (full) {
       Expr result = Empty(getType());
       result->setArgument(argument[0]->factor(t_abstract,true),0);
       result->setArgument(argument[1]->factor(t_abstract,true),1);
       return Refresh(result);
    }

    return Copy(this);
}

Expr AbstractDuoFunc::develop(bool full)
{
    if (full) {
        Expr result = Empty(getType());
        result->setArgument(argument[0]->develop(true), 0);
        result->setArgument(argument[1]->develop(true), 1);
        return Refresh(result);
    }

    return Copy(this);
}

bool AbstractDuoFunc::dependsOn(const Expr& t_abstract) const
{
    return ((name != "" and name == t_abstract->getName()) or
            argument[0]->dependsOn(t_abstract) or
            argument[1]->dependsOn(t_abstract));
}

int AbstractDuoFunc::isPolynomial(const Expr& t_abstract) const {
    return (this->operator==(t_abstract));
}

bool AbstractMultiFunc::getCommutable() const
{
    if (not commutable) 
        return false;

    for (const auto& arg: argument)
        if (not arg->getCommutable())
            return false;

    return true;
}

const vector<Expr >& AbstractMultiFunc::getVectorArgument() const {
    return argument;
}

Expr AbstractMultiFunc::getArgument(int iArg) const 
{
    if (iArg < 0 or iArg >= nArgs) {
        print();
        callError(smError::OutOfBounds,
                "Expr& AbstractMultiFunc::getArgument(int iArg) const", iArg);
    }

    return argument[iArg];
}

void AbstractMultiFunc::setArgument(const Expr& t_argument, int iArg) 
{
    if (iArg < 0 or iArg >= nArgs) {
        print();
        callError(smError::OutOfBounds,
                "Expr& AbstractMultiFunc::getArgument(int iArg) const", iArg);
    }

    argument[iArg] = t_argument;
}

void AbstractMultiFunc::setVectorArgument(const vector<Expr >& t_argument) 
{
    argument = t_argument;
    nArgs = argument.size();
}

Expr AbstractMultiFunc::factor(bool full)
{
    if (full) {
       Expr result = Copy(this);
       for (int i=0; i<nArgs; i++)
           result->setArgument(argument[i]->factor(true),i);
       return Refresh(result);
    }

    return Copy(this);
}

Expr AbstractMultiFunc::factor(const Expr& t_abstract, bool full)
{
    if (full) {
       Expr result = Copy(this);
       for (int i=0; i<nArgs; i++)
           result->setArgument(argument[i]->factor(t_abstract,true),i);
       return Refresh(result);
    }

    return Copy(this);
}

Expr AbstractMultiFunc::develop(bool full)
{
    if (full) {
        Expr result = Copy(this);
        for (int i=0; i<nArgs; i++)
            result->setArgument(argument[i]->develop(true), i);
        return Refresh(result);
    }

    return Copy(this);
}

bool AbstractMultiFunc::dependsOn(const Expr& t_abstract) const
{
    if (name != "" and name == t_abstract->getName()) 
        return true;

    for (const auto& arg : argument)
        if (arg->dependsOn(t_abstract)) 
            return true;

    return false;
}

int AbstractMultiFunc::isPolynomial(const Expr& t_abstract) const {
    return (this->operator==(t_abstract));
}
