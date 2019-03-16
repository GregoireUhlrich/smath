#include "scalarFunc.h"
#include "indicial.h"

using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class AbstractFunc                            //
/*************************************************/
///////////////////////////////////////////////////

bool AbstractFunc::getCommutable() const {
    return (commutable and argument->getCommutable());
}

bool AbstractFunc::isIndexed() const {
    return argument->isIndexed();
}

IndexStructure AbstractFunc::getIndexStructure() const
{
    if (isIndexed())
        return argument->getIndexStructure();
    return IndexStructure();
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

Expr AbstractFunc::factor(const Expr& expr, bool full)
{
    if (full) {
       Expr result = Empty(getType());
       result->setArgument(argument->factor(expr,true));
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

bool AbstractFunc::dependsOn(const Expr& expr) const {
    return ((name != "" and name == expr->getName()) or
            argument->dependsOn(expr));
}

bool AbstractFunc::dependsExplicitelyOn(const Expr& expr) const {
    return ((name != "" and name == expr->getName()) or
            argument->dependsExplicitelyOn(expr));
}

int AbstractFunc::isPolynomial(const Expr& expr) const {
    return (*this==expr);
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

bool AbstractFunc::operator==(const Expr& expr) const 
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;

    return (expr->getType() == this->getType() and 
            *argument == expr->getArgument());
} 

///////////////////////////////////////////////////
/*************************************************/
// AbstractDuoFunc                               //
/*************************************************/
///////////////////////////////////////////////////

bool AbstractDuoFunc::getCommutable() const 
{
    return (commutable and argument[0]->getCommutable() and 
            argument[1]->getCommutable());
}

bool AbstractDuoFunc::isIndexed() const {
    return (argument[0]->isIndexed() or argument[1]->isIndexed());
}

IndexStructure AbstractDuoFunc::getIndexStructure() const
{
    if (isIndexed())
        return (argument[0]->getIndexStructure() 
            + argument[1]->getIndexStructure());
    return IndexStructure();
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

Expr AbstractDuoFunc::factor(const Expr& expr, bool full)
{
    if (full) {
       Expr result = Empty(getType());
       result->setArgument(argument[0]->factor(expr,true),0);
       result->setArgument(argument[1]->factor(expr,true),1);
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

bool AbstractDuoFunc::dependsOn(const Expr& expr) const
{
    return ((name != "" and name == expr->getName()) or
            argument[0]->dependsOn(expr) or
            argument[1]->dependsOn(expr));
}

bool AbstractDuoFunc::dependsExplicitelyOn(const Expr& expr) const
{
    return ((name != "" and name == expr->getName()) or
            argument[0]->dependsExplicitelyOn(expr) or
            argument[1]->dependsExplicitelyOn(expr));
}

int AbstractDuoFunc::isPolynomial(const Expr& expr) const {
    return (this->operator==(expr));
}

///////////////////////////////////////////////////
/*************************************************/
// AbstractMultiFunc                             //
/*************************************************/
///////////////////////////////////////////////////

bool AbstractMultiFunc::getCommutable() const
{
    if (not commutable) 
        return false;

    for (const auto& arg: argument) {
        if (not arg->getCommutable())
            return false;
    }

    return true;
}

bool AbstractMultiFunc::isIndexed() const 
{
    // Indexed terms are in general closer to the end of the 
    // expression because they are considered as complicated.
    // We then go through the arguments in reverse order.
    for (const auto& arg : argument)
        if (arg->isIndexed())
            return true;

    return false;
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

Expr AbstractMultiFunc::factor(const Expr& expr, bool full)
{
    if (full) {
       Expr result = Copy(this);
       for (int i=0; i<nArgs; i++)
           result->setArgument(argument[i]->factor(expr,true),i);
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

bool AbstractMultiFunc::dependsOn(const Expr& expr) const
{
    if (name != "" and name == expr->getName()) 
        return true;

    for (const auto& arg : argument)
        if (arg->dependsOn(expr)) 
            return true;

    return false;
}

bool AbstractMultiFunc::dependsExplicitelyOn(const Expr& expr) const
{
    if (name != "" and name == expr->getName()) 
        return true;

    for (const auto& arg : argument)
        if (arg->dependsExplicitelyOn(expr)) 
            return true;

    return false;
}

int AbstractMultiFunc::isPolynomial(const Expr& expr) const {
    return (this->operator==(expr));
}
