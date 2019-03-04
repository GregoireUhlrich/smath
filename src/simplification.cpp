#include "simplification.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;



bool Double::operator<(const Expr& t_abstract) const
{
    int type = t_abstract->getType();
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return value < t_abstract->evaluateScalar();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return value > t_abstract->evaluateScalar();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return true;
        break;

        case smType::Integer:
        return value < t_abstract->evaluateScalar();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return false;
        break;

        case smType::Integer:
        return value > t_abstract->evaluateScalar();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return (compare(name,t_abstract->getName())==-1);
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return (compare(name,t_abstract->getName())==1);
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return (compare(name,t_abstract->getName())==-1);
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return (compare(name,t_abstract->getName())==1);
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return (not t_abstract->isInteger());
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
        if (SIMPLIFICATION_METHOD == 1) return evaluateScalar() < t_abstract->evaluateScalar();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
        type = smType::ScalarFunction;
    switch(type)
    {
        case smType::Double:
        return t_abstract->isInteger();
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
        if (SIMPLIFICATION_METHOD == 1) return evaluateScalar() > t_abstract->evaluateScalar();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return value < t_abstract->getValue();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return value > t_abstract->getValue();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) < t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) < t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator<(make_shared<Plus>(ZERO,t_abstract));
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) > t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) > t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,t_abstract));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return this->operator>(make_shared<Plus>(ZERO,t_abstract));
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::Times:
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

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::Polynomial:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (this->operator<(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::Times:
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

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::Polynomial:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Times>(ONE,t_abstract)));
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator<(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            foo = t_abstract->getArgument(0);
            if (*argument[0] != foo)
                return (*argument[0] < t_abstract->getArgument(0));
            return (*argument[1] < t_abstract->getArgument(1));
        }
        break;

        case smType::Polynomial:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator<(make_shared<Pow>(t_abstract,ONE)));
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            foo = t_abstract->getArgument(0);
            if (*argument[0] != foo)
                return (*argument[0] > t_abstract->getArgument(0));
            return (*argument[1] > t_abstract->getArgument(1));
        }
        break;

        case smType::Polynomial:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract, ONE)));
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return (this->operator>(make_shared<Pow>(t_abstract,ONE)));
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (*make_shared<Plus>(ZERO,Copy(this)) < t_abstract);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) < t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this),ONE) < t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[1] != t_abstract->getArgument(1))
                return (*argument[1] < t_abstract->getArgument(1));
            return *argument[0] < t_abstract->getArgument(0);
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative < smType::Angle;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative < t_abstract->getType();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (*make_shared<Plus>(ZERO,Copy(this)) > t_abstract);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE, Copy(this)) > t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this),ONE) > t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[1] != t_abstract->getArgument(1))
                return (*argument[1] > t_abstract->getArgument(1));
            return *argument[0] > t_abstract->getArgument(0);
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative > smType::Angle;
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Derivative > t_abstract->getType();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (*make_shared<Plus>(ZERO,Copy(this)) < t_abstract);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) < t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator<(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle < smType::Derivative;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[0] != t_abstract->getArgument(0))
                return *argument[0] < t_abstract->getArgument(0);
            return *argument[1] < t_abstract->getArgument(1);
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle < t_abstract->getType();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (*make_shared<Plus>(ZERO,Copy(this)) > t_abstract);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Pow>(Copy(this), ONE) > t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator>(t_abstract->getRegularExpression());
        break;

        case smType::Derivative:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle > smType::Derivative;
        }
        break;

        case smType::Angle:
        if (SIMPLIFICATION_METHOD == 1) {
            if (*argument[0] != t_abstract->getArgument(0))
                return *argument[0] > t_abstract->getArgument(0);
            return *argument[1] > t_abstract->getArgument(1);
        }
        break;

        case smType::ScalarFunction:
        if (SIMPLIFICATION_METHOD == 1) {
            return smType::Angle > t_abstract->getType();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (*make_shared<Plus>(ZERO,Copy(this)) < t_abstract);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) < t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
           return (*make_shared<Pow>(Copy(this), ONE) < t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator<(t_abstract->getRegularExpression());
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
            if (getType() == t_abstract->getType())
                return *argument < t_abstract->getArgument();
            return getType() < t_abstract->getType();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
            return (*make_shared<Plus>(ZERO,Copy(this)) > t_abstract);
        }
        break;

        case smType::Times:
        if (SIMPLIFICATION_METHOD == 1) {
            return (*make_shared<Times>(ONE,Copy(this)) > t_abstract);
        }
        break;

        case smType::Fraction:
        if (SIMPLIFICATION_METHOD == 1) {
           cout<<"Warning: using method 1 for Simplification but not yet implemented.\n"; 
        }
        break;

        case smType::Pow:
        if (SIMPLIFICATION_METHOD == 1) {
           return (*make_shared<Pow>(Copy(this), ONE) > t_abstract);
        }
        break;

        case smType::Polynomial:
        return this->operator>(t_abstract->getRegularExpression());
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
            if (getType() == t_abstract->getType())
                return *argument > t_abstract->getArgument();
            return getType() > t_abstract->getType();
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator<(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator<(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator<(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator<(t_abstract->getRegularExpression());
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
            return getIndexStructure().size() < t_abstract->getIndexStructure().size();
        }
        break;

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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
            return getIndexStructure().size() > t_abstract->getIndexStructure().size();
        }
        break;

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator<(t_abstract->getRegularExpression());
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
            return false;
        }
        break;

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == smType::ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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

        case smType::ITerm:
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
    if (t_abstract->getPrimaryType() == ScalarFunction) // Danger if type == ScalarFunction, here it is Exp so no problem
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
        return this->operator>(t_abstract->getRegularExpression());
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
