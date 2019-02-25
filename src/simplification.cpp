#include "simplification.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;



bool Double::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return value < t_abstract->evaluateScalar();
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return isInteger();
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison of \"Double\" and \""<<type<<"\" not implemented.\n";
    return false;
}

bool Double::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return value > t_abstract->evaluateScalar();
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return (not isInteger());
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison of \"Double\" and \""<<type<<"\" not implemented.\n";
    return false;
}

bool Integer::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return value < t_abstract->evaluateScalar();
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Integer\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Integer::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return value > t_abstract->evaluateScalar();
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Integer\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Variable::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return (compare(name,t_abstract->getName())==-1);
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Variable\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Variable::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return (compare(name,t_abstract->getName())==1);
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Variable\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Constant::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return (compare(name,t_abstract->getName())==-1);
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Constant\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Constant::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return (compare(name,t_abstract->getName())==1);
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Constant\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFraction::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return (not t_abstract->isInteger());
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        if (SIMPLIFICATION_METHOD == 1) return evaluateScalar() < t_abstract->evaluateScalar();
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFraction\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFraction::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return t_abstract->isInteger();
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        if (SIMPLIFICATION_METHOD == 1) return evaluateScalar() > t_abstract->evaluateScalar();
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFraction\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFactorial::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return value < t_abstract->getValue();
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFactorial\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFactorial::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return value > t_abstract->getValue();
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFactorial\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Imaginary::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return true;
        break;

        case TIMES:
        return true;
        break;

        case FRACTION:
        return true;
        break;

        case POW:
        return true;
        break;

        case POLYNOMIAL:
        return true;
        break;

        case DERIVATIVE:
        return true;
        break;

        case ANGLE:
        return true;
        break;

        case SCALAR_FUNCTION:
        return true;
        break;

        case VECTOR:
        return true;
        break;

        case MATRIX:
        return true;
        break;

        case HIGHDTENSOR:
        return true;
        break;

        case ITENSOR:
        return true;
        break;

        case ITERM:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Imaginary\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Imaginary::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        return false;
        break;

        case TIMES:
        return false;
        break;

        case FRACTION:
        return false;
        break;

        case POW:
        return false;
        break;

        case POLYNOMIAL:
        return false;
        break;

        case DERIVATIVE:
        return false;
        break;

        case ANGLE:
        return false;
        break;

        case SCALAR_FUNCTION:
        return false;
        break;

        case VECTOR:
        return false;
        break;

        case MATRIX:
        return false;
        break;

        case HIGHDTENSOR:
        return false;
        break;

        case ITENSOR:
        return false;
        break;

        case ITERM:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Imaginary\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Plus::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            t_nArgs = t_abstract->getNArgs();
            nMax = min(nArgs, t_nArgs);
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] < t_abstract->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] > t_abstract->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs < t_nArgs;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) < t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) < t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Plus\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Plus::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = min(nArgs, t_abstract->getNArgs());
            t_nArgs = t_abstract->getNArgs();
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] > t_abstract->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] < t_abstract->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs > t_nArgs;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) > t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) > t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Plus\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Times::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = min(nArgs, t_abstract->getNArgs());
            t_nArgs = t_abstract->getNArgs();
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] < t_abstract->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] > t_abstract->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs < t_nArgs;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Times\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Times::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = min(nArgs, t_abstract->getNArgs());
            t_nArgs = t_abstract->getNArgs();
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] > t_abstract->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] < t_abstract->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs > t_nArgs;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Times\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Fraction::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Fraction\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Fraction::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Fraction\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Pow::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            foo = t_abstract->getArgument(0);
            if (*argument[0] != foo)
                return (*argument[0] < t_abstract->getArgument(0));
            return (*argument[1] < t_abstract->getArgument(1));
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract,ONE)));
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Pow\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Pow::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            foo = t_abstract->getArgument(0);
            if (*argument[0] != foo)
                return (*argument[0] > t_abstract->getArgument(0));
            return (*argument[1] > t_abstract->getArgument(1));
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract,ONE)));
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Pow\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Polynomial::operator<(const Expr& t_abstract) const
{
    return getRegularExpression() < t_abstract;
}

bool Polynomial::operator>(const Expr& t_abstract) const
{
    return getRegularExpression() > t_abstract;
}

bool Derivative::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) < t_abstract);
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) < t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this),ONE) < t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[1] != t_abstract->getArgument(1))
                return (*argument[1] < t_abstract->getArgument(1));
            return *argument[0] < t_abstract->getArgument(0);
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return DERIVATIVE < ANGLE;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return DERIVATIVE < t_abstract->getType();
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Derivative\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Derivative::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) > t_abstract);
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) > t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this),ONE) > t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[1] != t_abstract->getArgument(1))
                return (*argument[1] > t_abstract->getArgument(1));
            return *argument[0] > t_abstract->getArgument(0);
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return DERIVATIVE > ANGLE;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return DERIVATIVE > t_abstract->getType();
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Derivative\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Angle::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) < t_abstract);
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) < t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return ANGLE < DERIVATIVE;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[0] != t_abstract->getArgument(0))
                return *argument[0] < t_abstract->getArgument(0);
            return *argument[1] < t_abstract->getArgument(1);
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return ANGLE < t_abstract->getType();
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Angle\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Angle::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) > t_abstract);
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) > t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return ANGLE > DERIVATIVE;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[0] != t_abstract->getArgument(0))
                return *argument[0] > t_abstract->getArgument(0);
            return *argument[1] > t_abstract->getArgument(1);
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return ANGLE > t_abstract->getType();
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Angle\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool AbstractFunc::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) < t_abstract);
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
           return (*make_shared<Pow>(Copy(this), ONE) < t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() < DERIVATIVE;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() < ANGLE;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            if (getType() == t_abstract->getType())
                return *argument < t_abstract->getArgument();
            return getType() < t_abstract->getType();
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"AbstractFunc\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool AbstractFunc::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) > t_abstract);
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > t_abstract);
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
           return (*make_shared<Pow>(Copy(this), ONE) > t_abstract);
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() > DERIVATIVE;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() > ANGLE;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            if (getType() == t_abstract->getType())
                return *argument > t_abstract->getArgument();
            return getType() > t_abstract->getType();
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"AbstractFunc\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Vector::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Vector\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Vector::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Vector\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Matrix::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Matrix\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Matrix::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Matrix\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool HighDTensor::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"HighDTensor\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool HighDTensor::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"HighDTensor\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool ITensor::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return getIndexStructure().size() < t_abstract->getIndexStructure().size();
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"ITensor\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool ITensor::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return getIndexStructure().size() > t_abstract->getIndexStructure().size();
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"ITensor\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool ITerm::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return false;
        break;

        case INTEGER:
        return false;
        break;

        case VARIABLE:
        return false;
        break;

        case CONSTANT:
        return false;
        break;

        case CFRACTION:
        return false;
        break;

        case CFACTORIAL:
        return false;
        break;

        case IMAGINARY:
        return false;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case POLYNOMIAL:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = getIndexStructure().size();
            t_nArgs = t_abstract->getIndexStructure().size();
            if (nMax != t_nArgs)
                return nMax < t_nArgs;
            nMax = min(nArgs, t_abstract->getNArgs());
            t_nArgs = t_abstract->getNArgs();
            for (int i=0; i<nMax; i++)
                if (*argument[nArgs-1-i] < t_abstract->getArgument(t_nArgs-1-i))
                    return true;
            return nArgs < t_nArgs;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"ITerm\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool ITerm::operator>(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        return true;
        break;

        case INTEGER:
        return true;
        break;

        case VARIABLE:
        return true;
        break;

        case CONSTANT:
        return true;
        break;

        case CFRACTION:
        return true;
        break;

        case CFACTORIAL:
        return true;
        break;

        case IMAGINARY:
        return true;
        break;

        case PLUS:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case TIMES:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case FRACTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POW:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case DERIVATIVE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ANGLE:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case SCALAR_FUNCTION:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case VECTOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case MATRIX:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case HIGHDTENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case ITENSOR:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case ITERM:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = getIndexStructure().size();
            t_nArgs = t_abstract->getIndexStructure().size();
            if (nMax != t_nArgs)
                return nMax > t_nArgs;
            nMax = min(nArgs, t_abstract->getNArgs());
            t_nArgs = t_abstract->getNArgs();
            for (int i=0; i<nMax; i++)
                if (*argument[nArgs-1-i] > t_abstract->getArgument(t_nArgs-1-i))
                    return true;
            return nArgs > t_nArgs;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"ITerm\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

/* TypeS IN COMPARISON
Double
Integer
Variable
Constant
CFraction
CFactorial
Imaginary
Plus
Times
Fraction
Pow
Polynomial
Derivative
Angle
AbstractScalarFunc
Vector
Matrix
HighDTensor
ITensor
ITerm
END TypeS
*/

/* SWITCH STATEMENT
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == SCALAR_FUNCTION) // Danger if type == SCALAR_FUNCTION, here it is EXP so no problem
        type = SCALAR_FUNCTION;
    switch(type)
    {
        case DOUBLE:
        break;

        case INTEGER:
        break;

        case VARIABLE:
        break;

        case CONSTANT:
        break;

        case CFRACTION:
        break;

        case CFACTORIAL:
        break;

        case IMAGINARY:
        break;

        case PLUS:
        break;

        case TIMES:
        break;

        case FRACTION:
        break;

        case POW:
        break;

        case POLYNOMIAL:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case ANGLE:
        break;

        case SCALAR_FUNCTION:
        break;

        case VECTOR:
        break;

        case MATRIX:
        break;

        case HIGHDTENSOR:
        break;

        case ITENSOR:
        break;

        case ITERM:
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
END SWITCH
*/
