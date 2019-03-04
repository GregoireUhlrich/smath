#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "indicial.h"
#include "simplification.h"
#pragma GCC diagnostic ignored "-Wreturn-type"
using namespace std;

bool Abstract::getProperty(smProperty::OwnBProperty prop)
{
    switch(prop) {
        case smProperty::Commutable:
            return commutable;
            break;
        case smProperty::Valued:
            print();
            callError(smError::AbstractFuncCalled, "Abstract::getProperty(smProperty::Valued) const");
            break;
        default:
            return false;
    };
}

bool Abstract::getProperty(smProperty::DependBProperty prop, const Expr& expression)
{
    switch(prop) {
        default: return (*this==expression);
    };
}

int Abstract::getProperty(smProperty::OwnIProperty prop)
{
    switch(prop) {

        case smProperty::Dim:     return 0; break;
        case smProperty::NFactor: return 1; break;

        case smProperty::Value:
        case smProperty::Numerator:
        case smProperty::Denominator:
            print();
            callError(smError::AbstractFuncCalled,
                    "Abstract::getProperty(smProperty::Value)");
            break;

        case smProperty::Order:
            print();
            callError(smError::AbstractFuncCalled,
                    "Abstract::getProperty(smProperty::Order)");
            break;

        case smProperty::NIndices:
            print();
            callError(smError::AbstractFuncCalled,
                    "Abstract::getProperty(smProperty::NIndices)");
            break;

        default:
            callError(smError::UnknownProperty,
                    "Abstract::getProperty(smProperty::OwnIProperty)",prop);
    };
}

int Abstract::getProperty(smProperty::DependIProperty prop, const Expr& expression)
{
    switch(prop){
        case smProperty::Polynomial:
        case smProperty::Parity:
            return (*this==expression);
        default:
            callError(smError::UnknownProperty,
                    "Abstract::getProperty(smProperty::OwnIProperty, const Expr&)",
                    prop);
    };
}

bool Abstract::getValued() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getValued() const");
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
    callError(smError::AbstractFuncCalled, "Abstract::getNIndices() const");
    return 0;
}

Index Abstract::getIndex(int i) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getIndex(int i) const");
    return Index();
}

vector<Index> Abstract::getIndexStructure() const
{
    return vector<Index>(0);
}

void Abstract::setIndexStructure(const vector<Index>& index)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setIndexStructure(const vector<Index>& t_index) const");
}

bool Abstract::checkIndexStructure(const vector<Index>& t_index) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::checkIndexStructure(const vector<Index>& t_index) const");
    return (t_index.size()==0);
}

bool Abstract::checkIndexStructure(const initializer_list<Index>& index) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::checkIndexStructure(initializer_list<Index> index) const");
    return (index.size()==0);
}

void Abstract::setFullySymmetric()
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setFullySymmetric() const");
}
void Abstract::setFullyAntiSymmetric()
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setFullyAntiSymmetric() const");
}
void Abstract::addSymmetry(int i1, int i2)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::addSymmetry() const");
}
void Abstract::addAntiSymmetry(int i1, int i2)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::addAntiSymmetry() const");
}
int Abstract::getNContractedPairs() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getNContractedPairs() const");
    return 0;
}

int Abstract::permut(int i1, int i2)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::permut(int i1, int i2)");
    return 0;
}
vector<Expr> Abstract::getPermutations() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getPermutations() const");
    return vector<Expr>(0);
}

set<pair<int,int> > Abstract::getContractedPair() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getPair() const");
    return set<pair<int,int> >();
}

void Abstract::contractIndices(int axis1, int axis2)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::contractIndices(int axis1, int axis2)");
}

vector<int> Abstract::getShape() const
{
    return vector<int>(1,1);
}

const vector<Expr >& Abstract::getVectorArgument() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getVectorArgument() const");
}

Expr Abstract::getArgument(int iArg) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getArgument(int iArg) const");
    return nullptr;
}

Expr Abstract::getArgument(const initializer_list<int>& indices) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getArgument(int iArg, int jArg) const");
    return nullptr;
}

Expr Abstract::getArgument(const vector<int>& indices) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getArgument(const vector<int>& indices) const");
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
    callError(smError::AbstractFuncCalled, "Abstract::insert(const Expr& t_abstract)");
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
    callError(smError::AbstractFuncCalled, "Abstract::setArgument(const Expr& t_abstract, int iArg)");
}
void Abstract::setArgument(const Expr& t_abstract, const initializer_list<int>& indices)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setArgument(const Expr& t_abstract, const initializer_list<int>& indices)");
}
void Abstract::setArgument(const Expr& t_abstract, const vector<int>& indices)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setArgument(const Expr& t_abstract, const vector<int>& indices)");
}
void Abstract::setVectorArgument(const vector<Expr>& t_argument)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setVectorArgument(const vector<Expr>& t_argument)");
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
    callError(smError::EvalNotValued,"Abstract::evaluateScalar() const");
    return 0;
}

Expr Abstract::addition_own(const Expr& t_abstract) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::addition_own(const Expr& t_abstract) const");
    return ZERO;
}

Expr Abstract::multiplication_own(const Expr& t_abstract) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::multiplication_own(const Expr& t_abstract) const");
    return ZERO;
}

Expr Abstract::division_own(const Expr& t_abstract) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::division_own(const Expr& t_abstract) const");
    return ZERO;
}

Expr Abstract::exponentiation_own(const Expr& t_abstract) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::exponentiation_own(const Expr& t_abstract) const");
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
    if (getPrimaryType() == smType::Numerical)
        return evaluateScalar() == t_value;
    if (getPrimaryType() == smType::Literal and
            (getType() == smType::Variable or
             getType() == smType::Constant))
        return evaluateScalar() == t_value;
    return false;
}

/*bool Abstract::operator==(const Expr& t_abstract) const
{
    return 0;
}*/

Expr Abstract::operator[](int iArg)
{
    print();
    callError(smError::AbstractFuncCalled,"Abstract::operator[]");
    exit(smError::AbstractFuncCalled); // Not usefull line, only there t
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
    callError(smError::AbstractFuncCalled, "Abstract::tensor_dot(const Expr& t_abstract) const");
    return nullptr;
}

Expr Abstract::dot(const Expr& t_abstract) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::dot(const Expr& t_abstract) const");
    return nullptr;
}

Expr Abstract::getSum() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getSum() const");
    return nullptr;
}

Expr Abstract::getProduct() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getProduct() const");
    return nullptr;
}

Expr Abstract::getVectorialModulus() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getVectorialModulus() const");
    return nullptr;
}

Expr Abstract::getSubVectorial(int iExcept) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getSubVectorial(int iExcept) const");
    return nullptr;
}

Expr Abstract::getSubVectorial(int iExcept, int jExcept) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getSubVectorial(int iExcept, int jExcept) const");
    return nullptr;
}

Expr Abstract::getSubVectorial(const vector<int>& exceptions) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getSubVectorial(const vector<int>& exceptions) const");
    return nullptr;
}

Expr Abstract::determinant() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::determinant() const");
    return nullptr;
}

Expr Abstract::trace() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::trace() const");
    return nullptr;
}

Expr Abstract::trace(int axis1, int axis2) const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::trace(int axis1, int axis2) const");
    return nullptr;
}

Expr Abstract::transpose() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::transpose() const");
    return nullptr;
}

Expr Abstract::symmetrise() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::symmetrise() const");
    return nullptr;
}

Expr Abstract::antisymmetrise() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::antisymmetrise() const");
    return nullptr;
}

Expr Abstract::inverseMatrix() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::inverseMatrix() const");
    return nullptr;
}

bool operator==(const Expr& a, const Expr& b) {
    return (*a==b);
}
bool operator==(const Expr& a, int b) {
    return (*a==b);
}
bool operator!=(const Expr& a, const Expr& b) {
    return (*a!=b);
}
bool operator!=(const Expr& a, int b) {
    return (*a!=b);
}
bool operator!=(const Expr& a, double b) {
    return (*a!=b);
}
bool operator>=(const Expr& a, const Expr& b) {
    return (*a>=b);
}
bool operator<=(const Expr& a, const Expr& b) {
    return (*a<=b);
}
bool operator>(const Expr& a, const Expr& b) {
    return (*a>b);
}
bool operator<(const Expr& a, const Expr& b) {
    return (*a<b);
}
bool operator|=(const Expr& a, const Expr& b) {
    return (*a|=b);
}
bool operator&=(const Expr& a, const Expr& b) {
    return (*a&=b);
}

ostream& operator<<(ostream& fout, smType::Type type)
{
    switch(type) {
        case smType::Integer:     fout<<"Integer";     break;
        case smType::CFraction:   fout<<"CFraction";   break;
        case smType::Double:      fout<<"Double";      break;
        case smType::CFactorial:  fout<<"CFactorial";  break;
        case smType::Imaginary:   fout<<"Imaginary";   break;
        case smType::Constant:    fout<<"Constant";    break;
        case smType::Variable:    fout<<"Variable";    break;
        case smType::Plus:        fout<<"Plus";        break;
        case smType::Polynomial:  fout<<"Polynomial";  break;
        case smType::Times:       fout<<"Times";       break;
        case smType::Fraction:    fout<<"Fraction";    break;
        case smType::Pow:         fout<<"Pow";         break;
        case smType::Exp:         fout<<"Exp";         break;
        case smType::Log:         fout<<"Log";         break;
        case smType::Abs:         fout<<"Abs";         break;
        case smType::Cos:         fout<<"Cos";         break;
        case smType::Sin:         fout<<"Sin";         break;
        case smType::Tan:         fout<<"Tan";         break;
        case smType::Cosh:        fout<<"Cosh";        break;
        case smType::Sinh:        fout<<"Sinh";        break;
        case smType::Tanh:        fout<<"Tanh";        break;
        case smType::Derivative:  fout<<"Derivative";  break;
        case smType::Angle:       fout<<"Angle";       break;
        case smType::Factorial:   fout<<"Factorial";   break;
        case smType::ACos:        fout<<"Acos";        break;
        case smType::ASin:        fout<<"Asin";        break;
        case smType::ATan:        fout<<"Atan";        break;
        case smType::ACosh:       fout<<"Acosh";       break;
        case smType::ASinh:       fout<<"Asinh";       break;
        case smType::ATanh:       fout<<"Atanh";       break;
        case smType::Vector:      fout<<"Vector";      break;
        case smType::Matrix:      fout<<"Matrix";      break;
        case smType::HighDTensor: fout<<"HighDTensor"; break;
        case smType::ITensor:     fout<<"ITensor";     break;
        case smType::ITerm:       fout<<"ITerm";       break;

        default: cout<<"Type "<<type<<" not known in operator<<(Type)."; 
    }
    return fout;
}

ostream& operator<<(ostream& fout, smType::PrimaryType primaryType)
{
    switch(primaryType) {
        case smType::Numerical:             cout<<"Purely numerical";      break;
        case smType::Literal:               cout<<"Variable Numerical";    break;
        case smType::MultiFunction: cout<<"Multi Scalar Function"; break;
        case smType::ScalarFunction:       cout<<"Scalar Function";       break;
        case smType::Vectorial:             cout<<"Vectorial";             break;
        case smType::Indicial:              cout<<"Indicial";              break;

        default: cout<<"Primary Type "<<primaryType<<" not known in operator<<(PrimaryType).";
    }
    return fout;
}
