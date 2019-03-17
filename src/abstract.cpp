#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "indicial.h"
#include "simplification.h"
#pragma GCC diagnostic ignored "-Wreturn-type"
using namespace std;

bool Abstract::getCommutable() const {
    return commutable;
}

void Abstract::printExplicit(int mode) const
{
    cout<<"type="<<getType()<<" : ";
    print(1);
    cout<<" ; ";
    if (getNArgs() > 0)
        for (int i=0; i<getNArgs(); i++)
            getArgument(i)->printExplicit(mode);

    cout<<endl;
}

string Abstract::printLaTeX(int mode) const {
    return name;
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

IndexStructure Abstract::getIndexStructure() const
{
    return IndexStructure();
    // Determine if we raise an error or not
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getIndexStructure() const");
}

const IndicialParent* Abstract::getParent() const
{
    print();
    callError(smError::AbstractFuncCalled,
            "const IndicialParent* Abstract::getParent() const");
    return nullptr;
}

bool Abstract::contractIndex(const Index& indexToContract,
                             const Index& newIndex)
{
    print();
    callError(smError::AbstractFuncCalled,
            (string)"Abstract::contractIndex(const Index& indexToContract"
            +"const Index& newIndex)");
}

void Abstract::setIndexStructure(const IndexStructure& index)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::setIndexStructure(const vector<Index>& t_index) const");
}

bool Abstract::checkIndexStructure(const vector<Index>& t_index) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::checkIndexStructure(const vector<Index>& t_index) const");
    return (t_index.size()==0);
}

bool Abstract::checkIndexStructure(const initializer_list<Index>& index) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::checkIndexStructure(initializer_list<Index> index) const");
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

vector<int> Abstract::getShape() const
{
    return vector<int>(1,1);
}

const vector<Expr >& Abstract::getVectorArgument() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getVectorArgument() const");
}

iter Abstract::begin()
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::begin() const");
    return std::vector<Expr>::iterator();
}

iter Abstract::end()
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::begin() const");
    return std::vector<Expr>::iterator();
}

const_iter Abstract::begin() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::begin() const");
    return std::vector<Expr>::iterator();
}

const_iter Abstract::end() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::begin() const");
    return std::vector<Expr>::iterator();
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
    callError(smError::AbstractFuncCalled,
            "Abstract::getArgument(int iArg, int jArg) const");
    return nullptr;
}

Expr Abstract::getArgument(const vector<int>& indices) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::getArgument(const vector<int>& indices) const");
    return nullptr;
}

bool Abstract::isBuildingBlock() const {
    return false;
}

bool Abstract::isIndexed() const {
    return false;
}

bool Abstract::isInteger() const {
    return false;
}

double Abstract::getValue() const 
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getValue() const");
    return 0;
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

bool Abstract::isEmpty() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::isEmpty");
    return false;
}

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

void Abstract::insert(const Expr& expr, bool side)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::insert(const Expr& expr)");
}

bool Abstract::askTerm(const Expr& expr, bool exact) const
{
    return this->operator==(expr);
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
Expr Abstract::derive(const Expr& expr)
{
    return ZERO;
}

Expr Abstract::suppressTerm(const Expr& expr) const
{
    return double_(1);
}

void Abstract::setValue(double value)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::setValue(double value)");
}

void Abstract::setElementary(bool t_elementary)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::setElementary(bool t_elementary)");
}

void Abstract::setAllDependencies(bool t_allDependencies)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::setAllDependencies(bool t_allDependencies)");
}

void Abstract::addDependency(const Expr& expr)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::addDependency(const Expr& expr)");
}

void Abstract::removeDependency(const Expr& expr)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::removeDependency(const Expr& expr)");
}

void Abstract::setArgument(const Expr& expr, int iArg)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::setArgument(const Expr& expr, int iArg)");
}
void Abstract::setArgument(const Expr& expr, const initializer_list<int>& indices)
{
    print();
    callError(smError::AbstractFuncCalled,
           (string)"Abstract::setArgument(const Expr& expr,"
           +"const initializer_list<int>& indices)");
}
void Abstract::setArgument(const Expr& expr, const vector<int>& indices)
{
    print();
    callError(smError::AbstractFuncCalled,
    "Abstract::setArgument(const Expr& expr, const vector<int>& indices)");
}
void Abstract::setVectorArgument(const vector<Expr>& t_argument)
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::setVectorArgument(const vector<Expr>& t_argument)");
}

double Abstract::evaluateScalar() const
{
    print();
    callError(smError::EvalNotValued,"Abstract::evaluateScalar() const");
    return 0;
}

Expr Abstract::addition_own(const Expr& expr) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::addition_own(const Expr& expr) const");
    return ZERO;
}

Expr Abstract::multiplication_own(const Expr& expr, bool side) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::multiplication_own(const Expr& expr) const");
    return ZERO;
}

Expr Abstract::division_own(const Expr& expr) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::division_own(const Expr& expr) const");
    return ZERO;
}

Expr Abstract::exponentiation_own(const Expr& expr) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::exponentiation_own(const Expr& expr) const");
    return ZERO;
}

bool Abstract::dependsOn(const Expr& expr) const
{
    return false;
}

bool Abstract::dependsExplicitelyOn(const Expr& expr) const
{
    return operator==(expr);
}

int Abstract::isPolynomial(const Expr& expr) const
{
    return dependsExplicitelyOn(expr);
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

int Abstract::getParity(const Expr& t_variable) const
{
    return 1;
}

Expr Abstract::getRegularExpression() const
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::getRegularExpression() const");
    return ZERO;
}

void Abstract::operator=(double value)
{
    print();
    callError(smError::AbstractFuncCalled, "Abstract::operator=(double value) const");
}

bool Abstract::operator!=(int t_value) const
{
    return !(this->operator==(t_value));
}

bool Abstract::operator!=(double t_value) const
{
    return !(this->operator==(t_value));
}

bool Abstract::operator!=(const Expr& expr) const
{
    return !(this->operator==(expr));
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

/*bool Abstract::operator==(const Expr& expr) const
{
    return 0;
}*/

Expr Abstract::operator[](int iArg) const
{
    print();
    callError(smError::AbstractFuncCalled,"Abstract::operator[]");
    exit(smError::AbstractFuncCalled); // Not usefull line, only there t
}
Expr& Abstract::operator[](int iArg)
{
    print();
    callError(smError::AbstractFuncCalled,"Abstract::operator[]");
    exit(smError::AbstractFuncCalled); // Not usefull line, only there t
}
/*
bool Abstract::operator>(const Expr& expr) const
{
    cout<<"Warning: operator> of Abstract called. Should not be.\n";
    return false;
}

bool Abstract::operator<(const Expr& expr) const
{
    cout<<"Warning: operator< of Abstract called. Should not be.\n";
    return false;
}
*/

vector<Expr > Abstract::getAlternateForms() const
{
    return vector<Expr >(0);
}

bool Abstract::operator|=(const Expr& expr) const
{
    if (SIMPLIFICATION_METHOD == 1) {
        return (not this->operator<(expr) and
                not this->operator>(expr));
    }
}

bool Abstract::operator&=(const Expr& expr) const
{
    return (not this->operator|=(expr));
}

bool Abstract::operator<=(const Expr& expr) const
{
    return (not this->operator>(expr));
}

bool Abstract::operator>=(const Expr& expr) const
{
    return (not this->operator<(expr));
}

bool Abstract::matchShape(const Expr& expr, bool exact) const
{
    // Return true if we compare to another jcalar or if it is not exact
    // This function assumes that the Object called has dimension 0
    return (not exact or expr->getDim() == 0);
}

Expr Abstract::tensor_dot(const Expr& expr) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::tensor_dot(const Expr& expr) const");
    return nullptr;
}

Expr Abstract::dot(const Expr& expr) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::dot(const Expr& expr) const");
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
    callError(smError::AbstractFuncCalled,
            "Abstract::getVectorialModulus() const");
    return nullptr;
}

Expr Abstract::getSubVectorial(int iExcept) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::getSubVectorial(int iExcept) const");
    return nullptr;
}

Expr Abstract::getSubVectorial(int iExcept, int jExcept) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::getSubVectorial(int iExcept, int jExcept) const");
    return nullptr;
}

Expr Abstract::getSubVectorial(const vector<int>& exceptions) const
{
    print();
    callError(smError::AbstractFuncCalled,
            "Abstract::getSubVectorial(const vector<int>& exceptions) const");
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
    callError(smError::AbstractFuncCalled,
            "Abstract::trace(int axis1, int axis2) const");
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
    // Allows to display the name of a type and not just 
    // an integer.
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
    // Allows to display the name of a primaryType and not just 
    // an integer.
    switch(primaryType) {
        case smType::Numerical:             cout<<"Purely numerical";      break;
        case smType::Literal:               cout<<"Variable Numerical";    break;
        case smType::MultiFunction:         cout<<"Multi Scalar Function"; break;
        case smType::ScalarFunction:        cout<<"Scalar Function";       break;
        case smType::Vectorial:             cout<<"Vectorial";             break;
        case smType::Indicial:              cout<<"Indicial";              break;

        default: cout<<"Primary Type "<<primaryType;
                 cout<< " not known in operator<<(PrimaryType).";
    }
    return fout;
}

///////////////////////////////////////////////////
/*************************************************/
// Arithmetic operators                          //
/*************************************************/
///////////////////////////////////////////////////

Expr operator+(double a, const Expr& b)
{
    return plus_(auto_number_(a), b);
}
Expr operator+(const Expr& a, double b)
{
    return plus_(a, auto_number_(b));
}
Expr operator+(const Expr& a, const Expr& b)
{
    return plus_(a,b);
}

Expr operator-(double a, const Expr& b)
{
    return minus_(auto_number_(a), b);
}
Expr operator-(const Expr& a, double b)
{
    return minus_(a, auto_number_(b));
}
Expr operator-(const Expr& a, const Expr& b)
{
    return minus_(a,b);
}

Expr operator*(double a, const Expr& b)
{
    return times_(auto_number_(a), b);
}
Expr operator*(const Expr& a, double b)
{
    return times_(a, auto_number_(b));
}
Expr operator*(const Expr& a, const Expr& b)
{
    return times_(a,b);
}

Expr operator/(double a, const Expr& b)
{
    return fraction_(auto_number_(a), b);
}
Expr operator/(const Expr& a, double b)
{
    return fraction_(a, auto_number_(b));
}
Expr operator/(const Expr& a, const Expr& b)
{
    return fraction_(a,b);
}

Expr operator^(double a, const Expr& b)
{
    return pow_(auto_number_(a), b);
}
Expr operator^(const Expr& a, double b)
{
    return pow_(a, auto_number_(b));
}
Expr operator^(const Expr& a, const Expr& b)
{
    return pow_(a,b);
}
