#include "simplification.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;



bool Double::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return value < expr->evaluateScalar();
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return isInteger();
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison of \"Double\" and \""<<type<<"\" not implemented.\n";
    return false;
}

bool Double::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return value > expr->evaluateScalar();
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return (not isInteger());
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison of \"Double\" and \""<<type<<"\" not implemented.\n";
    return false;
}

bool Integer::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return value < expr->evaluateScalar();
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Integer\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Integer::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return value > expr->evaluateScalar();
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Integer\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Variable::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return (compare(name,expr->getName())==-1);
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Variable\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Variable::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return (compare(name,expr->getName())==1);
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Variable\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Constant::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return (compare(name,expr->getName())==-1);
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Constant\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Constant::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return (compare(name,expr->getName())==1);
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Constant\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFraction::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return (not expr->isInteger());
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        if (SIMPLIFICATION_METHOD == 1) return evaluateScalar() < expr->evaluateScalar();
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFraction\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFraction::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return expr->isInteger();
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        if (SIMPLIFICATION_METHOD == 1) return evaluateScalar() > expr->evaluateScalar();
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFraction\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFactorial::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return value < expr->getValue();
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFactorial\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool CFactorial::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return value > expr->getValue();
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"CFactorial\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Imaginary::operator<(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return true;
        break;

        case smType::Times:
        return true;
        break;

        case smType::Fraction:
        return true;
        break;

        case smType::Pow:
        return true;
        break;

        case smType::Polynomial:
        return true;
        break;

        case smType::Derivative:
        return true;
        break;

        case smType::Angle:
        return true;
        break;

        case smType::ScalarFunction:
        return true;
        break;

        case smType::Vector:
        return true;
        break;

        case smType::Matrix:
        return true;
        break;

        case smType::HighDTensor:
        return true;
        break;

        case smType::ITensor:
        return true;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Imaginary\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Imaginary::operator>(const Expr& expr) const
{
    int type = expr->getType();
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        return false;
        break;

        case smType::Times:
        return false;
        break;

        case smType::Fraction:
        return false;
        break;

        case smType::Pow:
        return false;
        break;

        case smType::Polynomial:
        return false;
        break;

        case smType::Derivative:
        return false;
        break;

        case smType::Angle:
        return false;
        break;

        case smType::ScalarFunction:
        return false;
        break;

        case smType::Vector:
        return false;
        break;

        case smType::Matrix:
        return false;
        break;

        case smType::HighDTensor:
        return false;
        break;

        case smType::ITensor:
        return false;
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"Imaginary\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool Plus::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            t_nArgs = expr->getNArgs();
            nMax = min(nArgs, t_nArgs);
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] < expr->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] > expr->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs < t_nArgs;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) < expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) < expr);
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,expr));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,expr));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,expr));
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Plus::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = min(nArgs, expr->getNArgs());
            t_nArgs = expr->getNArgs();
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] > expr->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] < expr->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs > t_nArgs;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) > expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) > expr);
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,expr));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,expr));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,expr));
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool Times::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = min(nArgs, expr->getNArgs());
            t_nArgs = expr->getNArgs();
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] < expr->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] > expr->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs < t_nArgs;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Times::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            nMax = min(nArgs, expr->getNArgs());
            t_nArgs = expr->getNArgs();
            for (int i=0; i<nMax; i++)
            {
                if (*argument[nArgs-1-i] > expr->getArgument(t_nArgs-1-i))
                    return true;
                else if (*argument[nArgs-1-i] < expr->getArgument(t_nArgs-1-i))
                    return false;
            }
            return nArgs > t_nArgs;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,expr)));
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool Fraction::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::ITensor:
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

bool Fraction::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::ITensor:
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

bool Pow::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            foo = expr->getArgument(0);
            if (*argument[0] != foo)
                return (*argument[0] < expr->getArgument(0));
            return (*argument[1] < expr->getArgument(1));
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(expr,ONE)));
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Pow::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            foo = expr->getArgument(0);
            if (*argument[0] != foo)
                return (*argument[0] > expr->getArgument(0));
            return (*argument[1] > expr->getArgument(1));
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(expr, ONE)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(expr,ONE)));
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool Polynomial::operator<(const Expr& expr) const
{
    return getRegularExpression() < expr;
}

bool Polynomial::operator>(const Expr& expr) const
{
    return getRegularExpression() > expr;
}

bool Derivative::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) < expr);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) < expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this),ONE) < expr);
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[1] != expr->getArgument(1))
                return (*argument[1] < expr->getArgument(1));
            return *argument[0] < expr->getArgument(0);
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative < smType::Angle;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative < expr->getType();
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Derivative::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) > expr);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) > expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this),ONE) > expr);
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[1] != expr->getArgument(1))
                return (*argument[1] > expr->getArgument(1));
            return *argument[0] > expr->getArgument(0);
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative > smType::Angle;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative > expr->getType();
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool Angle::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) < expr);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) < expr);
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle < smType::Derivative;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[0] != expr->getArgument(0))
                return *argument[0] < expr->getArgument(0);
            return *argument[1] < expr->getArgument(1);
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle < expr->getType();
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Angle::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) > expr);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) > expr);
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle > smType::Derivative;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[0] != expr->getArgument(0))
                return *argument[0] > expr->getArgument(0);
            return *argument[1] > expr->getArgument(1);
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle > expr->getType();
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool AbstractFunc::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) < expr);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
           return (*make_shared<Pow>(Copy(this), ONE) < expr);
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() < smType::Derivative;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() < smType::Angle;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            if (getType() == expr->getType())
                return *argument < expr->getArgument();
            return getType() < expr->getType();
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool AbstractFunc::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Plus>(ZERO,Copy(this)) > expr);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > expr);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
           return (*make_shared<Pow>(Copy(this), ONE) > expr);
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() > smType::Derivative;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return getType() > smType::Angle;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            if (getType() == expr->getType())
                return *argument > expr->getArgument();
            return getType() > expr->getType();
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool Vector::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Vector::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool Matrix::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
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

bool Matrix::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool HighDTensor::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool HighDTensor::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
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

bool ITensor::operator<(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return false;
        break;

        case smType::Variable:
        return false;
        break;

        case smType::Constant:
        return false;
        break;

        case smType::CFraction:
        return false;
        break;

        case smType::CFactorial:
        return false;
        break;

        case smType::Imaginary:
        return false;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Polynomial:
        return this->operator<(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ITensor:
        if (SIMPLIFICATION_METHOD == 1) {
            if (index < expr->getIndexStructure())
                return true;
            if (not (index > expr->getIndexStructure()))
                return name < expr->getName();
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"ITensor\" and \""<<type<<"\" not yet implemented.\n";
    return false;
}

bool ITensor::operator>(const Expr& expr) const
{
    int type = expr->getType();
    int nMax, t_nArgs;
    Expr foo;
    if (expr->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return true;
        break;

        case smType::Variable:
        return true;
        break;

        case smType::Constant:
        return true;
        break;

        case smType::CFraction:
        return true;
        break;

        case smType::CFactorial:
        return true;
        break;

        case smType::Imaginary:
        return true;
        break;

        case smType::Plus:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return true;
        }
        break;

        case smType::Vector:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::Matrix:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::HighDTensor:
        if (SIMPLIFICATION_METHOD == 1) {
            return false;
        }
        break;

        case smType::ITensor:
        if (SIMPLIFICATION_METHOD == 1) {
            if (index > expr->getIndexStructure())
                return true;
            if (not (index < expr->getIndexStructure()))
                return name > expr->getName();
            return false;
        }
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
    cout<<"Warning: comparison >,< of \"ITensor\" and \""<<type<<"\" not yet implemented.\n";
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
    int type = expr->getType();
    if (expr->getPrimaryType() == ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = ScalarFunction;
    switch(type)
    {
        case Double:
        break;

        case Integer:
        break;

        case Variable:
        break;

        case Constant:
        break;

        case CFraction:
        break;

        case CFactorial:
        break;

        case Imaginary:
        break;

        case Plus:
        break;

        case Times:
        break;

        case Fraction:
        break;

        case Pow:
        break;

        case Polynomial:
        return this->operator>(expr->getRegularExpression());
        break;

        case Angle:
        break;

        case ScalarFunction:
        break;

        case Vector:
        break;

        case Matrix:
        break;

        case HighDTensor:
        break;

        case ITensor:
        break;

        case ITerm:
        break;

        default:
        cout<<"Warning: type \""<<type<<"\" not recognized in >,< comparisons.\n";
    }
END SWITCH
*/
