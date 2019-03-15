#include "variable.h"
#include "operations.h"

using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class AbstractBuildingBlock                   //
/*************************************************/
///////////////////////////////////////////////////

Expr AbstractBuildingBlock::develop(bool full){
    return shared_from_this(); 
}
Expr AbstractBuildingBlock::factor(bool full){
    return shared_from_this(); 
}
Expr AbstractBuildingBlock::factor(const Expr& expr, bool full){
    return shared_from_this(); 
}
Expr AbstractBuildingBlock::getTerm(){
    return shared_from_this(); 
}

Expr AbstractBuildingBlock::getRealPart(){
    return shared_from_this(); 
}
Expr AbstractBuildingBlock::getComplexModulus(){
    return shared_from_this(); 
}
Expr AbstractBuildingBlock::getPolynomialTerm(const Expr& expr, int order){
    if (order == 1 and *this==expr)
        return ONE;
    else if (order == 0)
        return shared_from_this();

    return ZERO;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Double                                  //
/*************************************************/
///////////////////////////////////////////////////

smType::Type Double::getType() const { return smType::Double;}

void Double::setValue(double t_value)
{
    value = t_value;
}

void Double::print(int mode) const
{
    if (mode == 0)
        cout<<value<<endl;
    else if (mode > 0 and value < 0)
        cout<<"("<<value<<")";
    else
        cout<<value;
}

string Double::printLaTeX(int mode) const
{
    ostringstream sout; 
    if (mode == 0) 
        sout<<value<<endl;
    else if (value < 0) 
        sout<<"("<<value<<")";
    else 
        sout<<value;

    return sout.str();
}

double Double::evaluateScalar() const { return value;}

Expr Double::evaluate() { return shared_from_this();}

void Double::operator=(int t_value) {
    value = t_value;
}
void Double::operator=(double t_value) {
    value = t_value;
}

bool Double::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getPrimaryType() != smType::Numerical) 
        return 0;

    return (value==expr->evaluateScalar());
}

Expr Double::multiplication_own(const Expr& expr, bool side) const
{
    if (not expr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    switch(expr->getType()) {
        case smType::Integer:
        return auto_number_(value*expr->evaluateScalar());
        break;

        case smType::Double:
        return auto_number_(value*expr->evaluateScalar());
        break;

        case smType::CFraction:
        if (value == round(value))
            return _cfraction_(value*expr->getNum(),
                               expr->getDenom());
        return double_(value*expr->evaluateScalar());
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Double::division_own(const Expr& expr) const
{
    if (not expr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    switch(expr->getType()) {
        case smType::Integer:
        case smType::Double:
        return auto_number_(value*1/expr->evaluateScalar());
        break;

        case smType::CFraction:
        if (value == round(value))
            return _cfraction_(value*expr->getDenom(),
                               expr->getNum());
        return double_(value*1/expr->evaluateScalar());
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Double::exponentiation_own(const Expr& expr) const
{
    if (not expr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    double value2 = expr->evaluateScalar();
    switch(expr->getType()) {
        case smType::Integer:
        case smType::Double:
        if (value2 > 0)
            return auto_number_(pow(value,expr->evaluateScalar()));
        else
            return _cfraction_(1,pow(value,-value2));
        break;

        case smType::CFraction:
        return make_shared<Pow>(Copy(this),expr);
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Double::addition_own(const Expr& expr) const
{
    if (not expr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    switch(expr->getType()) {
        case smType::Integer:
        return auto_number_(value+expr->evaluateScalar());
        break;

        case smType::Double:
        return auto_number_(value+expr->evaluateScalar());
        break;

        case smType::CFraction:
        if (value == round(value))
            return _cfraction_(value*expr->getDenom()+expr->getNum(),
                               expr->getDenom());
        return double_(value+expr->evaluateScalar());
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Double::derive(const Expr& expr) {
    return ZERO;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Integer                                 //
/*************************************************/
///////////////////////////////////////////////////

smType::Type Integer::getType() const {
    return smType::Integer;
}

void Integer::setValue(double t_value) {
    value = round(t_value);
}

void Integer::print(int mode) const
{
    if (mode == 0) 
        cout<<value<<endl;
    else if (mode > 0 and value < 0) 
        cout<<"("<<value<<")";
    else 
        cout<<value;
}

string Integer::printLaTeX(int mode) const
{
    ostringstream sout; 
    if (mode == 0) 
        sout<<value<<endl;
    else if (value < 0) 
        sout<<"("<<value<<")";
    else 
        sout<<value;

    return sout.str();
}

double Integer::evaluateScalar() const {
    return value;
}

Expr Integer::evaluate() {
    return shared_from_this();
}

void Integer::operator=(int t_value) {
    value = t_value;
}

bool Integer::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())      
        return true;
    if (expr->getPrimaryType() != smType::Numerical) 
        return false;

    return (value==expr->evaluateScalar());
}

Expr Integer::multiplication_own(const Expr& expr, bool side) const
{
    if (expr == nullptr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    switch(expr->getType()) {
        case smType::Integer:
        return auto_number_(value*expr->evaluateScalar());
        break;

        case smType::Double:
        return auto_number_(value*expr->evaluateScalar());
        break;

        case smType::CFraction:
        return _cfraction_(value*expr->getNum(), expr->getDenom());
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Integer::addition_own(const Expr& expr) const
{
    if (expr == nullptr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    switch(expr->getType()) {
        case smType::Integer:
        return auto_number_(value+expr->evaluateScalar());
        break;

        case smType::Double:
        return auto_number_(value+expr->evaluateScalar());
        break;

        case smType::CFraction:
        return _cfraction_(value*expr->getDenom()+expr->getNum(),
                            expr->getDenom());
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Integer::division_own(const Expr& expr) const
{
    if (not expr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    switch(expr->getType()) {
        case smType::Integer:
        case smType::Double:
        return auto_number_(value*1./expr->evaluateScalar());
        break;

        case smType::CFraction:
        if (value == round(value))
            return _cfraction_(value*expr->getDenom(),
                               expr->getNum());
        return double_(value*1./expr->evaluateScalar());
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Integer::exponentiation_own(const Expr& expr) const
{
    if (not expr or expr->getPrimaryType() != smType::Numerical)
        return ZERO;

    double value2 = expr->evaluateScalar();
    switch(expr->getType()) {
        case smType::Integer:
        if (value2 > 0)
            return auto_number_(pow(value,expr->evaluateScalar()));
        else
            return _cfraction_(1,pow(value,-value2));
        break;
        
        case smType::Double:
        if (value2 > 0 or value2 != round(value2))
            return auto_number_(pow(value,expr->evaluateScalar()));
        else
            return _cfraction_(1,pow(value,-value2));
        break;

        case smType::CFraction:
        return make_shared<Pow>(Copy(this),expr);
        break;

        default:
        cout<<"Warning: numerical type \""<<expr->getType();
        cout<<"\" not recognized in number oeprations.\n";
        return ZERO;
    }
}

Expr Integer::derive(const Expr& expr) {
    return ZERO;
}

///////////////////////////////////////////////////
/*************************************************/
// Class CFraction                               //
/*************************************************/
///////////////////////////////////////////////////

CFraction::CFraction(int t_num, int t_denom): AbstractNumerical()
{
    if (t_num < 0) {
        if (t_denom < 0) {
            t_num *= -1;
            t_denom *= -1;
        }
    }
    else if (t_denom < 0) {
        t_num *= -1;
        t_denom *= -1;
    }

    const int pgcd = PGCD(t_num, t_denom);
    if (pgcd != 1) {
        t_num /= pgcd;
        t_denom /= pgcd;
    }
    num = t_num;
    denom = t_denom;
}

smType::Type CFraction::getType() const {
    return smType::CFraction;
}
int CFraction::getNum() const {
    return num;
}
int CFraction::getDenom() const {
    return denom;
}

void CFraction::print(int mode) const
{
    if (mode == 0) 
        cout<<"Fraction: "<<num<<"/"<<denom<<endl;
    else if (mode > 3) 
        cout<<"("<<num<<"/"<<denom<<")";
    else 
        cout<<num<<"/"<<denom;
}

string CFraction::printLaTeX(int mode) const
{
    ostringstream sout; 
    if (mode == 0) 
        sout<<"\\frac{"<<num<<"}{"<<denom<<"}";
    else if (mode > 3) 
        sout<<"\\left("<<"\\frac{"<<num<<"}{"<<denom<<"}\\right)";
    else 
        sout<<"\\frac{"<<num<<"}{"<<denom<<"}";

    return sout.str();
}

double CFraction::evaluateScalar() const {
    return (num*1.)/denom;
}

Expr CFraction::evaluate() {
    return shared_from_this();
}

Expr CFraction::multiplication_own(const Expr& expr, bool side) const
{
    if (expr == nullptr or expr->getPrimaryType() != smType::Numerical) 
        return ZERO;

    double value = expr->evaluateScalar();
    if (expr->isInteger()) // Integer
        return _cfraction_(num*value, denom);
    else if (expr->getType() == smType::Double) 
        return double_(evaluateScalar()*value);

    // Fraction
    int t_num = expr->getNum();
    int t_denom = expr->getDenom();

    return _cfraction_(num*t_num,denom*t_denom);
}

Expr CFraction::addition_own(const Expr& expr) const
{
    if (expr == nullptr or expr->getPrimaryType() != smType::Numerical) 
        return ZERO;
    double value = expr->evaluateScalar();
    if (expr->isInteger())
        return _cfraction_(num+denom*value, denom);
    else if (expr->getType() == smType::Double)
        return double_(evaluateScalar()+value);

    // Fraction
    int t_num = expr->getNum();
    int t_denom = expr->getDenom();

    return _cfraction_(num*t_denom+t_num*denom,denom*t_denom);
}

Expr CFraction::division_own(const Expr& expr) const
{
    if (expr == nullptr or expr->getPrimaryType() != smType::Numerical) 
        return ZERO;

    double value = expr->evaluateScalar();
    if (expr->isInteger()) // Integer
        return _cfraction_(num, denom*value);
    else if (expr->getType() == smType::Double) 
        return double_(evaluateScalar()*1./value);

    // Fraction
    int t_num = expr->getNum();
    int t_denom = expr->getDenom();

    return _cfraction_(num*t_denom,denom*t_num);
}

Expr CFraction::exponentiation_own(const Expr& expr) const
{
    if (expr == nullptr or expr->getPrimaryType() != smType::Numerical) 
        return ZERO;

    double value = expr->evaluateScalar();
    if (expr->isInteger() and value > 0) // Integer
        return _cfraction_(pow(num,(int)value), pow(denom,int(value)));
    else if (expr->isInteger())
        return _cfraction_(pow(denom,(int)(-value)),pow(num,(int)(-value)));
    else if (expr->getType() == smType::Double) 
        return double_(pow(evaluateScalar(),value));

    return make_shared<Pow>(Copy(this), expr);
}

Expr CFraction::derive(const Expr& expr) {
    return ZERO;
}

void CFraction::operator=(int t_value)
{
    num = t_value;
    denom = 1;
}
void CFraction::operator=(double t_value)
{
    num = t_value;
    denom = 1;
}

bool CFraction::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getPrimaryType() == smType::Numerical) 
        return (expr->evaluateScalar()==(num*1./denom));

    return 0;
}

Expr _cfraction_(int num, int denom)
{
    Expr foo = make_shared<CFraction>(num,denom);
    if (foo->getDenom() == 0) 
        return INF;
    if (foo->getNum() == 0) 
        return ZERO;
    if (foo->getDenom() == 1) 
        return auto_number_(foo->getNum());

    return foo;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Constant                                //
/*************************************************/
///////////////////////////////////////////////////

smType::PrimaryType Constant::getPrimaryType() const {
    return smType::Literal;
}
smType::Type Constant::getType() const {
    return smType::Constant;
}
bool Constant::getValued() const {
    return valued;
}

void Constant::setValue(double t_value)
{
    valued = true;
    value = t_value;
}

void Constant::print(int mode) const
{
    if (mode == 0)
        cout<<name<<endl;
    else
        cout<<name;
}

string Constant::printLaTeX(int mode) const
{
    ostringstream sout; 
    if (mode == 0 and valued)
        sout<<name<<" = "<<value<<endl;
    else if (mode == 0)
        sout<<name<<endl;
    else
        sout<<name;

    return sout.str();
}

double Constant::evaluateScalar() const
{
   if (not valued)
       cout<<"Warning variable \""<<name <<"\" not valued, evaluated to 0.\n";

   return value;
}

Expr Constant::evaluate()
{
    if (valued)
        return auto_number_(value);
    else
        return shared_from_this();
}

int Constant::getParity(const Expr& t_variable) const
{
    if (*this == t_variable) 
        return -1;
    else 
        return 1;
}

void Constant::operator=(double t_value) {
    valued = true;
    value = t_value;
}

bool Constant::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getType() != smType::Constant) 
        return 0;

    return name==expr->getName();
}

Expr Constant::derive(const Expr& expr)
{
    return ZERO;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Variable                                //
/*************************************************/
///////////////////////////////////////////////////

smType::PrimaryType Variable::getPrimaryType() const {
    return smType::Literal;
}
smType::Type Variable::getType() const {
    return smType::Variable;
}
bool Variable::getValued() const {
    return valued;
}
double Variable::getValue() const {
    return value;
}

bool Variable::dependsOn(const Expr& expr) const
{
    // Elementary variable: depends only on itself
    if (elementary) 
        return operator==(expr);

    // expr is a number: 0
    if (expr->getPrimaryType() == smType::Numerical)
        return false;

    // All dependencies: the Variable depends on everything by default
    if (allDependencies)
        return true;

    // We check the explicit dependencies of the variable
    for (const auto& dep : dependencies)
        if (operator==(dep))
            return true;

    return false;
}

void Variable::setValue(double t_value)
{
    valued = true;
    value = t_value;
}

void Variable::print(int mode) const
{
    if (mode == 0) 
        cout<<name<<endl;
    else 
        cout<<name;
}

string Variable::printLaTeX(int mode) const
{
    ostringstream sout; 
    if (mode == 0 and valued) 
        sout<<name<<" = "<<value<<endl;
    else if (mode == 0) 
        sout<<name<<endl;
    else 
        sout<<name;

    return sout.str();
}

double Variable::evaluateScalar() const
{
   if (not valued)
       callWarning(smError::NotValued, "Variable::evaluateScalar() const");

   return value;
}

Expr Variable::evaluate()
{
    if (valued)
        return auto_number_(value);
    else
        return shared_from_this();
}

int Variable::getParity(const Expr& t_variable) const
{
    if (*this == t_variable)
        return -1;
    else
        return 1;
}

void Variable::setElementary(bool t_elementary)
{
    elementary = t_elementary;
    if (elementary) 
        allDependencies = false;
    else
        allDependencies = true;
    dependencies.clear();
}

void Variable::setAllDependencies(bool t_allDependencies)
{
    if (allDependencies == t_allDependencies)
        return;
    allDependencies = t_allDependencies;
    //We change of dependance mode
    dependencies.clear();
    if (allDependencies and elementary)
        callError(smError::BadDependency,
                "Variable::setAllDependencies(bool t_allDependencies)",name);
}

void Variable::addDependency(const Expr& expr)
{
    if (elementary)
        callError(smError::BadDependency,
                "Variable::addDependency(const Expr& expr)",name);
    if (not allDependencies)
        dependencies.push_back(expr);
}

void Variable::removeDependency(const Expr& expr)
{
    if (allDependencies) {
        auto pos = find(dependencies.begin(), dependencies.end(), expr);
        if (pos != dependencies.end())
            dependencies.erase(pos);
    }
}

void Variable::operator=(double t_value) {
    valued = true;
    value = t_value;
}

bool Variable::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName() or name==WHATEVER->getName())
        return true;
    if (expr->getType() != smType::Variable)
        return 0;

    return name==expr->getName();
}

Expr Variable::derive(const Expr& expr)
{
    // dx/dx = 1
    if (operator==(expr)) 
        return ONE;
    // If elementary: dx/dy=0
    else if (not elementary and dependsOn(expr))
        return make_shared<Derivative>(shared_from_this(), expr);

    return ZERO;
}

///////////////////////////////////////////////////
/*************************************************/
// Class CFactorial                              //
/*************************************************/
///////////////////////////////////////////////////

void CFactorial::setValue(double t_value)
{
    if (round(value) == value)
        value = t_value;
    else 
        callWarning(smError::FactorialFloat,"CFactorial::setValue(double t_value)");
}

void CFactorial::print(int mode) const
{
    if (mode == 0) 
        cout<<"CFactorial: "<<value<<"!"<<endl;
    else 
        cout<<value<<"!";
}

string CFactorial::printLaTeX(int mode) const
{
    ostringstream sout; 
    if (mode == 0) 
        sout<<value<<"!"<<endl;
    else 
        sout<<value<<"!";

    return sout.str();
}

double CFactorial::evaluateScalar() const
{
    return (double)factorial(value);
}

Expr CFactorial::evaluate(){
    return int_(factorial(value));
}

void CFactorial::operator=(int t_value) {
    value = t_value;
}

bool CFactorial::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getType() != smType::CFactorial) 
        return 0;

    return value==expr->getValue();
}

Expr CFactorial::derive(const Expr& expr)
{
    return ZERO;
}

Expr cfactorial_(int value)
{
    if (value < 0) 
        return times_(pow_(int_(-1),
                           int_(abs(value))),
                      cfactorial_(-value));
    if (value == 0 or value == 1) 
        return int_(1);
    if (value == 2) 
        return int_(2);
    return make_shared<CFactorial>(value);
}

///////////////////////////////////////////////////
/*************************************************/
// Class Imaginary                               //
/*************************************************/
///////////////////////////////////////////////////

Expr Imaginary::getRealPart() {
    return ZERO;
}

Expr Imaginary::getImaginaryPart() const {
    return int_(1);
}

Expr Imaginary::getComplexModulus() {
    return int_(1);
}

Expr Imaginary::getComplexArgument() {
    return fraction_(pi_,int_(2));
}

void Imaginary::print(int mode) const
{
    if (mode == 0) 
        cout<<"i"<<endl;
    else 
        cout<<"i";
}

string Imaginary::printLaTeX(int mode) const {
    return "i";
}

double Imaginary::evaluateScalar() const
{
    cout<<"Warning: evaluating scalar (real)";
    cout<<"of complex expr! replacing i by 0.\n";
    return 0;
}

Expr Imaginary::evaluate() {
    return make_shared<Imaginary>();
}

Expr Imaginary::derive(const Expr& expr) {
    return ZERO;
}

bool Imaginary::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;

    return (expr->getType() == smType::Imaginary);
}

Expr double_(double value)
{
    if (value == round(value))
        return int_(value);
    return make_shared<Double>(value);
}

Expr int_(int value) {
    return make_shared<Integer>(value);
}

Expr auto_number_(double value)
{
    if (value == round(value)) 
        return int_(value);

    return double_(value);
}

Expr constant_(string name) {
    return make_shared<Constant>(name);
}

Expr constant_(string name, double value) {
    return make_shared<Constant>(name, value);
}

Expr var_(string name) {
    return make_shared<Variable>(name);
}

Expr var_(string name, double value) {
    return make_shared<Variable>(name, value);
}
