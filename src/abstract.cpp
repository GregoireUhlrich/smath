#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "indicial.h"
#include "simplification.h"
#pragma GCC diagnostic ignored "-Wreturn-type"
using namespace std;

bool Abstract::getValued() const
{
    print();
    callError(Abstract_func_called, "Abstract::getValued() const");
    return false;
}

int Abstract::getNum() const
{
    return 0;
}

int Abstract::getDenom() const
{
    return 1;
}

int Abstract::getNArgs(int axis) const
{
    //cout<<"Warning: function getNArgs of Abstract called. Should not be.\n";
    return 0;
}

int Abstract::getNIndices() const
{
    print();
    callError(Abstract_func_called, "Abstract::getNIndices() const");
    return 0;
}

Index Abstract::getIndex(int i) const
{
    print();
    callError(Abstract_func_called, "Abstract::getIndex(int i) const");
    return Index();
}

vector<Index> Abstract::getIndexStructure() const
{
    return vector<Index>(0);
}

bool Abstract::checkIndexStructure(const vector<Index>& t_index) const
{
    print();
    callError(Abstract_func_called, "Abstract::checkIndexStructure(const vector<Index>& t_index) const");
    return (t_index.size()==0);
}

bool Abstract::checkIndexStructure(initializer_list<Index> index) const
{
    print();
    callError(Abstract_func_called, "Abstract::checkIndexStructure(initializer_list<Index> index) const");
    return (index.size()==0);
}

int Abstract::getNContractedPairs() const
{
    print();
    callError(Abstract_func_called, "Abstract::getNContractedPairs() const");
    return 0;
}

map<int,int> Abstract::getPair() const
{
    print();
    callError(Abstract_func_called, "Abstract::getPair() const");
    return map<int,int>();
}

void Abstract::contractIndices(int axis1, int axis2)
{
    print();
    callError(Abstract_func_called, "Abstract::contractIndices(int axis1, int axis2)");
}

vector<int> Abstract::getShape() const
{
    return vector<int>(1,1);
}

const vector<Expr >& Abstract::getVectorArgument() const
{
    print();
    callError(Abstract_func_called, "Abstract::getVectorArgument() const");
}

Expr Abstract::getArgument(int iArg) const
{
    print();
    callError(Abstract_func_called, "Abstract::getArgument(int iArg) const");
    return nullptr;
}

Expr Abstract::getArgument(const initializer_list<int>& indices) const
{
    print();
    callError(Abstract_func_called, "Abstract::getArgument(int iArg, int jArg) const");
    return nullptr;
}

Expr Abstract::getArgument(const vector<int>& indices) const
{
    print();
    callError(Abstract_func_called, "Abstract::getArgument(const vector<int>& indices) const");
    return nullptr;
}

Expr Abstract::getNumericalFactor() const
{
    return int_(1);
}

int Abstract::getNFactor() const
{
    return 1;
}

vector<Expr > Abstract::getFactors() const
{
    return vector<Expr >(0);
}

Expr Abstract::getTerm()
{
    return Copy(this);
}

int Abstract::getOrder() const { return 0;}

Expr Abstract::getRealPart()
{
    return Copy(this);
}

Expr Abstract::getImaginaryPart() const
{
    return ZERO;
}

Expr Abstract::getComplexModulus()
{
    return Copy(this);
}

Expr Abstract::getComplexArgument()
{
    return ZERO;
}

Expr Abstract::getComplexConjugate()
{
    Expr fooReal = getRealPart();
    Expr fooImag = getImaginaryPart();
    return plus_(fooReal, times_(times_(double_(-1),i_),fooImag));
}

void Abstract::insert(const Expr& t_abstract, bool side)
{
    print();
    callError(Abstract_func_called, "Abstract::insert(const Expr& t_abstract)");
}

bool Abstract::askTerm(const Expr& t_abstract, bool exact) const
{
    return this->operator==(t_abstract);
}

Expr Abstract::develop(bool full)
{
    return Copy(this);
}
Expr Abstract::factor(bool full)
{
    return Copy(this);
}
Expr Abstract::factor(const Expr& variable, bool full)
{
    return Copy(this);
}
Expr Abstract::derive(const Expr& t_abstract) const
{
    return ZERO;
}

Expr Abstract::suppressTerm(const Expr& t_abstract) const
{
    return double_(1);
}

void Abstract::setArgument(const Expr& t_abstract, int iArg)
{
    print();
    callError(Abstract_func_called, "Abstract::setArgument(const Expr& t_abstract, int iArg)");
}
void Abstract::setArgument(const Expr& t_abstract, const initializer_list<int>& indices)
{
    print();
    callError(Abstract_func_called, "Abstract::setArgument(const Expr& t_abstract, const initializer_list<int>& indices)");
}
void Abstract::setArgument(const Expr& t_abstract, const vector<int>& indices)
{
    print();
    callError(Abstract_func_called, "Abstract::setArgument(const Expr& t_abstract, const vector<int>& indices)");
}
void Abstract::setVectorArgument(const vector<Expr>& t_argument)
{
    print();
    callError(Abstract_func_called, "Abstract::setVectorArgument(const vector<Expr>& t_argument)");
}

void Abstract::printExplicit(int mode) const
{
    cout<<"type="<<getType()<<" : ";
    print(1);
    cout<<" ; ";
    if (getNArgs() > 0)
    {
        for (int i=0; i<getNArgs(); i++)
            getArgument(i)->printExplicit(mode);
    }

    cout<<endl;
}

double Abstract::evaluateScalar() const
{
    print();
    callError(Eval_not_valued,"Abstract::evaluateScalar() const");
    return 0;
}

Expr Abstract::addition_own(const Expr& t_abstract) const
{
    print();
    callError(Abstract_func_called, "Abstract::addition_own(const Expr& t_abstract) const");
    return ZERO;
}

Expr Abstract::multiplication_own(const Expr& t_abstract) const
{
    print();
    callError(Abstract_func_called, "Abstract::multiplication_own(const Expr& t_abstract) const");
    return ZERO;
}

Expr Abstract::division_own(const Expr& t_abstract) const
{
    print();
    callError(Abstract_func_called, "Abstract::division_own(const Expr& t_abstract) const");
    return ZERO;
}

Expr Abstract::exponentiation_own(const Expr& t_abstract) const
{
    print();
    callError(Abstract_func_called, "Abstract::exponentiation_own(const Expr& t_abstract) const");
    return ZERO;
}

bool Abstract::dependsOn(const Expr& t_abstract) const
{
    return (name != "" and t_abstract->getName() == name);
}

int Abstract::isPolynomial(const Expr& t_abstract) const
{
    return dependsOn(t_abstract);
}

Expr Abstract::getVariable() const
{
    return ZERO;
}

Expr Abstract::getPolynomialTerm(const Expr& t_variable, int order)
{
    if (order==1 and *this==t_variable) return int_(1);
    if (order == 0) return Copy(this);
    return ZERO;
}

bool Abstract::isProportionalTo(const Expr& t_abstract) const
{
    return (*this == t_abstract);
}

int Abstract::getParity(const Expr& t_variable) const
{
    return 1;
}

Expr Abstract::getRegularExpression() const
{
    return ZERO;
}

bool Abstract::operator!=(int t_value) const
{
    return !(this->operator==(t_value));
}

bool Abstract::operator!=(double t_value) const
{
    return !(this->operator==(t_value));
}

bool Abstract::operator!=(const Expr& t_abstract) const
{
    return !(this->operator==(t_abstract));
}

bool Abstract::operator==(int t_value) const
{
    return Abstract::operator==((double)t_value);
}

bool Abstract::operator==(double t_value) const
{
    if (getPrimaryType() == NUMERICAL)
        return evaluateScalar() == t_value;
    if (getPrimaryType() == LITERAL and (getType() == VARIABLE
                                     or getType() == CONSTANT))
        return evaluateScalar() == t_value;
    return false;
}

/*bool Abstract::operator==(const Expr& t_abstract) const
{
    return 0;
}*/

Expr& Abstract::operator[](int iArg)
{
    print();
    callError(Abstract_func_called,"Abstract::operator[]");
    exit(Abstract_func_called); // Not usefull line, only there t
}
/*
bool Abstract::operator>(const Expr& t_abstract) const
{
    cout<<"Warning: operator> of Abstract called. Should not be.\n";
    return false;
}

bool Abstract::operator<(const Expr& t_abstract) const
{
    cout<<"Warning: operator< of Abstract called. Should not be.\n";
    return false;
}
*/

vector<Expr > Abstract::getAlternateForms() const
{
    return vector<Expr >(0);
}

bool Abstract::operator|=(const Expr& t_abstract) const
{
    if (SIMPLIFICATION_METHOD == 1) {
        return (not this->operator<(t_abstract) and not this->operator>(t_abstract));
    }
}

bool Abstract::operator&=(const Expr& t_abstract) const
{
    return (not this->operator|=(t_abstract));
}

bool Abstract::operator<=(const Expr& t_abstract) const
{
    return (not this->operator>(t_abstract));
}

bool Abstract::operator>=(const Expr& t_abstract) const
{
    return (not this->operator<(t_abstract));
}

bool Abstract::matchShape(const Expr& t_abstract, bool exact) const
{
    // Return true if we compare to another jcalar or if it is not exact
    // This function assumes that the Object called has dimension 0
    return (not exact or t_abstract->getDim() == 0);
}

Expr Abstract::tensor_dot(const Expr& t_abstract) const
{
    print();
    callError(Abstract_func_called, "Abstract::tensor_dot(const Expr& t_abstract) const");
    return nullptr;
}

Expr Abstract::dot(const Expr& t_abstract) const
{
    print();
    callError(Abstract_func_called, "Abstract::dot(const Expr& t_abstract) const");
    return nullptr;
}

Expr Abstract::getSum() const
{
    print();
    callError(Abstract_func_called, "Abstract::getSum() const");
    return nullptr;
}

Expr Abstract::getProduct() const
{
    print();
    callError(Abstract_func_called, "Abstract::getProduct() const");
    return nullptr;
}

Expr Abstract::getVectorialModulus() const
{
    print();
    callError(Abstract_func_called, "Abstract::getVectorialModulus() const");
    return nullptr;
}

Expr Abstract::getSubVectorial(int iExcept) const
{
    print();
    callError(Abstract_func_called, "Abstract::getSubVectorial(int iExcept) const");
    return nullptr;
}

Expr Abstract::getSubVectorial(int iExcept, int jExcept) const
{
    print();
    callError(Abstract_func_called, "Abstract::getSubVectorial(int iExcept, int jExcept) const");
    return nullptr;
}

Expr Abstract::getSubVectorial(const vector<int>& exceptions) const
{
    print();
    callError(Abstract_func_called, "Abstract::getSubVectorial(const vector<int>& exceptions) const");
    return nullptr;
}

Expr Abstract::determinant() const
{
    print();
    callError(Abstract_func_called, "Abstract::determinant() const");
    return nullptr;
}

Expr Abstract::trace() const
{
    print();
    callError(Abstract_func_called, "Abstract::trace() const");
    return nullptr;
}

Expr Abstract::trace(int axis1, int axis2) const
{
    print();
    callError(Abstract_func_called, "Abstract::trace(int axis1, int axis2) const");
    return nullptr;
}

Expr Abstract::transpose() const
{
    print();
    callError(Abstract_func_called, "Abstract::transpose() const");
    return nullptr;
}

Expr Abstract::symmetrise() const
{
    print();
    callError(Abstract_func_called, "Abstract::symmetrise() const");
    return nullptr;
}

Expr Abstract::antisymmetrise() const
{
    print();
    callError(Abstract_func_called, "Abstract::antisymmetrise() const");
    return nullptr;
}

Expr Abstract::inverseMatrix() const
{
    print();
    callError(Abstract_func_called, "Abstract::inverseMatrix() const");
    return nullptr;
}

bool operator==(const Expr& a, const Expr& b)
{
    return (*a==b);
}

bool operator==(const Expr& a, int b)
{
    return (*a==b);
}

bool operator==(const Expr& a, double b)
{
    return (*a==b);
}

bool operator!=(const Expr& a, const Expr& b)
{
    return (*a!=b);
}

bool operator!=(const Expr& a, int b)
{
    return (*a!=b);
}

bool operator!=(const Expr& a, double b)
{
    return (*a!=b);
}

bool operator>=(const Expr& a, const Expr& b)
{
    return (*a>=b);
}

bool operator<=(const Expr& a, const Expr& b)
{
    return (*a<=b);
}

bool operator>(const Expr& a, const Expr& b)
{
    return (*a>b);
}

bool operator<(const Expr& a, const Expr& b)
{
    return (*a<b);
}

bool operator|=(const Expr& a, const Expr& b)
{
    return (*a|=b);
}

bool operator&=(const Expr& a, const Expr& b)
{
    return (*a&=b);
}

ostream& operator<<(ostream& fout, Type type)
{
    switch(type)
    {
        case INTEGER:     fout<<"Integer";     break;
        case CFRACTION:   fout<<"CFraction";   break;
        case DOUBLE:      fout<<"Double";      break;
        case CFACTORIAL:  fout<<"CFactorial";  break;
        case IMAGINARY:   fout<<"Imaginary";   break;
        case CONSTANT:    fout<<"Constant";    break;
        case VARIABLE:    fout<<"Variable";    break;
        case PLUS:        fout<<"Plus";        break;
        case POLYNOMIAL:  fout<<"Polynomial";  break;
        case TIMES:       fout<<"Times";       break;
        case FRACTION:    fout<<"Fraction";    break;
        case POW:         fout<<"Pow";         break;
        case EXP:         fout<<"Exp";         break;
        case LOG:         fout<<"Log";         break;
        case ABS:         fout<<"Abs";         break;
        case COS:         fout<<"Cos";         break;
        case SIN:         fout<<"Sin";         break;
        case TAN:         fout<<"Tan";         break;
        case COSH:        fout<<"Cosh";        break;
        case SINH:        fout<<"Sinh";        break;
        case TANH:        fout<<"Tanh";        break;
        case DERIVATIVE:  fout<<"Derivative";  break;
        case ANGLE:       fout<<"Angle";       break;
        case FACTORIAL:   fout<<"Factorial";   break;
        case ACOS:        fout<<"Acos";        break;
        case ASIN:        fout<<"Asin";        break;
        case ATAN:        fout<<"Atan";        break;
        case ACOSH:       fout<<"Acosh";       break;
        case ASINH:       fout<<"Asinh";       break;
        case ATANH:       fout<<"Atanh";       break;
        case VECTOR:      fout<<"Vector";      break;
        case MATRIX:      fout<<"Matrix";      break;
        case HIGHDTENSOR: fout<<"HighDTensor"; break;
        case ITENSOR:     fout<<"ITensor";     break;
        case ITERM:       fout<<"ITerm";       break;

        default: cout<<"Type "<<type<<" not known in operator<<(Type)."; 
    }
    return fout;
}

ostream& operator<<(ostream& fout, PrimaryType primaryType)
{
    switch(primaryType)
    {
        case NUMERICAL:      cout<<"Purely numerical";      break;
        case LITERAL:    cout<<"Variable Numerical";    break;
        case MULTI_SCALAR_FUNCTION: cout<<"Multi Scalar Function"; break;
        case SCALAR_FUNCTION:       cout<<"Scalar Function";       break;
        case VECTORIAL:             cout<<"Vectorial";             break;
        case INDICIAL:              cout<<"Indicial";              break;

        default: cout<<"Primary Type "<<primaryType<<" not known in operator<<(PrimaryType).";
    }
    return fout;
}
