#include "symbol.h"
#include "simplification.h"

using namespace std;

//////////////////////////////////////
//// Class member functions  /////////
//////////////////////////////////////

Symbol::Symbol()
{
    name = "";
    abstract = ZERO;
}

Symbol::Symbol(std::string t_name)
{
    abstract = var_(t_name);
    name = t_name;
}

Symbol::Symbol(int value)
{
    name = "";
    abstract = int_(value);
}

Symbol::Symbol(double value)
{
    name = "";
    abstract = auto_number_(value);
}

Symbol::Symbol(const Expr& t_abstract)
{
    if (t_abstract) name = t_abstract->getName();
    else cout<<"Warning: initializing a symbol with an invalid abstract.\n";
    abstract = t_abstract;
}

Symbol::Symbol(const Symbol& t_symbol)
{
    name = t_symbol.name;
    abstract = t_symbol.abstract;
}

Symbol::~Symbol()
{
}

void Symbol::clear()
{
    abstract = var_(name);
}

string Symbol::getName() const 
{
    return name;
}

int Symbol::getDim() const
{
    return abstract->getDim();
}

smType::Type Symbol::getType() const
{
    return abstract->getType();
}

smType::PrimaryType Symbol::getPrimaryType() const
{
    return abstract->getPrimaryType();
}

bool Symbol::getCommutable() const
{
    return abstract->getCommutable();
}

Expr Symbol::getAbstract() const 
{
    return abstract;
}

void Symbol::setArgument(const Symbol& t_symbol, int iArg)
{
    abstract->setArgument(t_symbol.getAbstract(), iArg);
}

void Symbol::setArgument(const Symbol& t_symbol, int iArg, int jArg)
{
    abstract->setArgument(t_symbol.getAbstract(), {iArg, jArg});
}

void Symbol::setArgument(const Symbol& t_symbol, int iArg, int jArg, int kArg)
{
    abstract->setArgument(t_symbol.getAbstract(), {iArg, jArg, kArg});
}

void Symbol::setArgument(const Symbol& t_symbol, vector<int> indices)
{
    abstract->setArgument(t_symbol.getAbstract(), indices);
}

Symbol Symbol::getRealPart() const
{
    return Symbol(abstract->getRealPart());
}

Symbol Symbol::getImaginaryPart() const
{
    return Symbol(abstract->getImaginaryPart());
}

Symbol Symbol::getComplexModulus() const
{
    return Symbol(abstract->getComplexModulus());
}

Symbol Symbol::getComplexArgument() const
{
    return Symbol(abstract->getComplexArgument());
}

void Symbol::setName(string t_name)
{
    name = t_name;
    if (abstract and abstract->getName() == "")
        abstract->setName(name);
}

void Symbol::setCommutable(bool t_commutable)
{
    abstract->setCommutable(t_commutable);
}

void Symbol::setAbstract(const Expr& t_abstract)
{
    abstract = t_abstract;
}

void Symbol::print() const
{
    if (abstract) abstract->print();
    else cout<<"INVALID AbsTRACT! \n";
}

void Symbol::printExplicit() const
{
    if (abstract) abstract->printExplicit();
    else cout<<"INVALID AbsTRACT! \n";
}

string Symbol::printLaTeX() const
{
    if (abstract) return abstract->printLaTeX();
    cout<<"INVALID AbsTRACT! \n";
    return "";
}

double Symbol::evaluateScalar()
{
    if (abstract->getDim() == 0)
        return abstract->evaluateScalar();
    return 0;
}

Symbol Symbol::evaluate()
{
    return Symbol(abstract->evaluate());
}

Symbol Symbol::derive(Symbol t_symbol) const
{
    Expr foo = abstract->derive(t_symbol.getAbstract()); 
    return Symbol(foo);
}

Symbol Symbol::factor() const
{
    return Symbol(abstract->factor());
}

Symbol Symbol::full_factor() const
{
    return Symbol(abstract->factor(true));
}

Symbol Symbol::factor(const Symbol& t_factor) const
{
    return Symbol(abstract->factor(t_factor.getAbstract()));
}

Symbol Symbol::full_factor(const Symbol& t_factor) const
{
    return Symbol(abstract->factor(t_factor.getAbstract(), true));
}

Symbol Symbol::develop() const
{
    return Symbol(abstract->develop());
}

Symbol Symbol::full_develop() const
{
    return Symbol(abstract->develop(true));
}

Symbol Symbol::replace(const Symbol& old_symbol, const Symbol& new_symbol) const
{
   return Symbol(Replace(abstract, old_symbol.getAbstract(), new_symbol.getAbstract()));
}

Symbol Symbol::polynomialDivision(const Symbol& t_symbol) const
{
    if (abstract->getType() == smType::Polynomial)
        return Symbol(abstract->division_own(t_symbol.getAbstract()));
    return *this;
}

Symbol Symbol::sum() const
{
    return Symbol(abstract->getSum());
}

Symbol Symbol::product() const
{
    return Symbol(abstract->getProduct());
}

Symbol Symbol::determinant() const
{
    return Symbol(abstract->determinant());
}

Symbol Symbol::trace() const
{
    return Symbol(abstract->trace());
}

Symbol Symbol::trace(int axis1, int axis2) const
{
    return Symbol(abstract->trace(axis1,axis2));
}

Symbol Symbol::transpose() const
{
    return Symbol(abstract->transpose());
}
Symbol Symbol::symmetrise() const
{
    return Symbol(abstract->symmetrise());
}
Symbol Symbol::antisymmetrise() const
{
    return Symbol(abstract->antisymmetrise());
}

bool Symbol::checkIndexStructure(const vector<Index>& t_index) const
{
    return abstract->checkIndexStructure(t_index);
}

bool Symbol::checkIndexStructure(initializer_list<Index> t_index) const
{
    return abstract->checkIndexStructure(t_index);
}

Symbol Symbol::inverseMatrix() const
{
    return Symbol(abstract->inverseMatrix());
}

//////////////////////////////////////
//// Functions and operators /////////
//////////////////////////////////////

Symbol Copy(const Symbol& t_symbol)
{
    Symbol result(t_symbol.getName());
    result.setAbstract(Copy(t_symbol.getAbstract()));
    return result;
}
Symbol DeepCopy(const Symbol& t_symbol)
{
    Symbol result(t_symbol.getName());
    result.setAbstract(DeepCopy(t_symbol.getAbstract()));
    return result;
}
Symbol Refresh(const Symbol& t_symbol)
{
    Symbol result(t_symbol.getName());
    result.setAbstract(Refresh(t_symbol.getAbstract()));
    return result;
}
Symbol DeepRefresh(const Symbol& t_symbol)
{
    Symbol result(t_symbol.getName());
    result.setAbstract(DeepRefresh(t_symbol.getAbstract()));
    return result;
}
Symbol Simplify(const Symbol& t_symbol, int recursion)
{
    return Symbol(Simplify(t_symbol.getAbstract(), recursion));
}

int Symbol::getParity(const Symbol& t_symbol)
{
    return abstract->getParity(t_symbol.getAbstract());
}

bool Symbol::operator==(const Symbol& t_symbol)
{
    return *abstract==t_symbol.getAbstract();
}
bool Symbol::operator!=(const Symbol& t_symbol)
{
    return !(*this==t_symbol);
}

Symbol& Symbol::operator=(const Symbol& t_symbol)
{
    abstract = t_symbol.getAbstract();

    return *this;
}

Symbol& Symbol::operator=(double t_value)
{
    if (abstract->getType() <= 10) abstract->setValue(t_value);
    else abstract = auto_number_(t_value);

    return *this;
}

Symbol& Symbol::operator=(int t_value)
{
    if (abstract->getType() <= 10) abstract->setValue((double)t_value);
    else abstract = int_(t_value);
    
    return *this;
}

Symbol Symbol::operator[](int iArg) const
{
    if (iArg == -1)
        cout<<"Warning: using -1 in operator[] of Symbol will not give the expected result in a chain (ex: Symbol[-1][1]..).\n";

    return Symbol(abstract->getArgument(iArg));
}

Symbol Symbol::operator[](const vector<int>& indices) const
{
    return Symbol(abstract->getArgument(indices));
}

bool Symbol::operator|=(const Symbol& t_symbol) const
{
    return abstract->operator|=(t_symbol.getAbstract());
}

bool Symbol::operator&=(const Symbol& t_symbol) const
{
    return abstract->operator&=(t_symbol.getAbstract());
}

bool Symbol::operator>(const Symbol& t_symbol) const
{
    return abstract->operator>(t_symbol.getAbstract());
}

bool Symbol::operator<(const Symbol& t_symbol) const
{
    return abstract->operator<(t_symbol.getAbstract());
}

bool Symbol::operator>=(const Symbol& t_symbol) const
{
    return abstract->operator>=(t_symbol.getAbstract());
}

bool Symbol::operator<=(const Symbol& t_symbol) const
{
    return abstract->operator<=(t_symbol.getAbstract());
}

Symbol cfraction_(int value1, int value2)
{
    if (value2 == 0) return Symbol(INF);
    Expr foo = _cfraction_(value1, value2);
    return Symbol(foo);
}

Symbol fraction_(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr foo = fraction_(t_symbol1.getAbstract(),t_symbol2.getAbstract());
    return Symbol(foo);
}

Symbol factorial_(const Symbol& t_symbol1)
{
    Expr foo = make_shared<Factorial>(t_symbol1.getAbstract());
    return Symbol(foo);
}

Symbol pow_(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr foo = pow_(t_symbol1.getAbstract(), t_symbol2.getAbstract());
    return Symbol(foo);
}

Symbol sqrt_(const Symbol& t_symbol)
{
    Expr foo = sqrt_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol exp_(const Symbol& t_symbol)
{
    Expr foo = exp_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol log_(const Symbol& t_symbol)
{
    Expr foo = log_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol cos_(const Symbol& t_symbol)
{
    Expr foo = cos_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol sin_(const Symbol& t_symbol)
{
    Expr foo = sin_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol tan_(const Symbol& t_symbol)
{
    Expr foo = tan_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol acos_(const Symbol& t_symbol)
{
    Expr foo = acos_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol asin_(const Symbol& t_symbol)
{
    Expr foo = asin_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol atan_(const Symbol& t_symbol)
{
    Expr foo = atan_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol cosh_(const Symbol& t_symbol)
{
    Expr foo = cosh_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol sinh_(const Symbol& t_symbol)
{
    Expr foo = sinh_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol tanh_(const Symbol& t_symbol)
{
    Expr foo = tanh_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol acosh_(const Symbol& t_symbol)
{
    Expr foo = acosh_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol asinh_(const Symbol& t_symbol)
{
    Expr foo = asinh_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol atanh_(const Symbol& t_symbol)
{
    Expr foo = atanh_(t_symbol.getAbstract());
    return Symbol(foo);
}

Symbol derivative_(const Symbol& t_variable, int order)
{
    return Symbol(derivative_(t_variable.getAbstract(), order));
}

Symbol derivative_(const Symbol& t_symbol, const Symbol& t_variable, int order)
{
    return Symbol(derivative_(t_symbol.getAbstract(), t_variable.getAbstract(), order));
}

Symbol polynomial_(const Symbol& t_symbol, const Symbol& t_variable)
{
    return Symbol(polynomial_(t_symbol.getAbstract(), t_variable.getAbstract()));
}

Symbol vector_(int t_nElements)
{
    return Symbol(_vector_(t_nElements));
}

Symbol vector_(int t_nElements, const Symbol& t_symbol, const Symbol& index)
{
    return vector_(t_nElements, t_symbol.getAbstract(), index.getAbstract());
}

Symbol vector_(const vector<Symbol>& t_argument)
{
    vector<Expr > foo(t_argument.size());
    for (size_t i=0; i<foo.size(); i++)
        foo[i] = t_argument[i].getAbstract();
    return Symbol(vector_(foo));
}

Symbol matrix_(int t_nArgs)
{
    return Symbol(_matrix_(t_nArgs));
}

Symbol matrix_(int t_x_nArgs, int t_y_nArgs)
{
    return Symbol(_matrix_(t_x_nArgs, t_y_nArgs));
}

Symbol matrix_(int t_x_nArgs, int t_y_nArgs, const Symbol& t_symbol, const Symbol& index_x, const Symbol& index_y)
{
    return Symbol(matrix_(t_x_nArgs, t_y_nArgs, t_symbol.getAbstract(), index_x.getAbstract(), index_y.getAbstract()));
}

Symbol matrix_(const vector<vector<Symbol> >& t_argument)
{
    Expr foo = make_shared<Vector>(t_argument.size());
    vector<Expr > fooVec;
    vector<Expr > result(0);
    for (size_t i=0; i<t_argument.size(); i++)
    {
        fooVec.clear();
        for (size_t j=0; j<t_argument[i].size(); j++)
            fooVec.push_back(t_argument[i][j].getAbstract());
        result.push_back(make_shared<Vector>(fooVec));
    }
    return Symbol(make_shared<Matrix>(result));
}

Symbol itensor_(std::string name, Index index)
{
    return Symbol(_itensor_(name, index));
}

Symbol itensor_(std::string name, initializer_list<Index> t_indices)
{
    return Symbol(_itensor_(name, t_indices));
}

Symbol tensor_dot(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    return Symbol(t_symbol1.getAbstract()->tensor_dot(t_symbol2.getAbstract()));
}

Symbol Symbol::polynomialFactorization() const
{
    return Symbol(abstract->factor());
}

Symbol scalarDot(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    if (t_symbol1.getType() != smType::Vector or t_symbol2.getType() != smType::Vector)
    {
        cout<<"Warning: taking scalarDot for non-vectors.\n";
        return 0;
    }
    return Symbol(t_symbol1.getAbstract()->dot(t_symbol2.getAbstract()));
}

Symbol dot(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    smType::PrimaryType type1 = t_symbol1.getPrimaryType();
    if (t_symbol1.getDim() == 0 or t_symbol2.getDim() == 0)
        return t_symbol1*t_symbol2;
    if (type1 == smType::Vectorial)
        return Symbol(t_symbol1.getAbstract()->dot(t_symbol2.getAbstract()));
    else 
        return Symbol(t_symbol2.getAbstract()->dot(t_symbol1.getAbstract()));
}

Symbol Taylor(const Symbol& t_symbol, const Symbol& t_variable, unsigned int max_order)
{
    Symbol Taylor = Copy(t_symbol);
    Taylor = Taylor.replace(t_variable, ZERO);
    Symbol derivative = Copy(t_symbol);
    Symbol foo;
    for (size_t order=1; order<=max_order; order++) 
    {
        derivative = derivative.derive(t_variable);
        foo = Copy(derivative);
        foo = foo.replace(t_variable,ZERO);
        Taylor = Taylor + (fraction_(pow_(t_variable,(int)order),Symbol(cfactorial_(order)))*foo);
    }
    return Refresh(Taylor);
}

Symbol operator+(const Symbol& t_symbol, int t_value)
{
    Expr new_object = plus_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator+(int t_value, const Symbol& t_symbol)
{
    Expr new_object = plus_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator+(const Symbol& t_symbol, double t_value)
{
    Expr new_object = plus_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator+(double t_value, const Symbol& t_symbol)
{
    Expr new_object = plus_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator+(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr new_object = plus_(t_symbol1.getAbstract(),t_symbol2.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}

Symbol operator-(const Symbol& t_symbol, int t_value)
{
    Expr new_object = minus_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator-(int t_value, const Symbol& t_symbol)
{
    Expr new_object = minus_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator-(const Symbol& t_symbol, double t_value)
{
    Expr new_object = minus_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator-(double t_value, const Symbol& t_symbol)
{
    Expr new_object = minus_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator-(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr new_object = minus_(t_symbol1.getAbstract(),t_symbol2.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}

Symbol operator-(const Symbol& t_symbol)
{
    return Symbol(minus_(ZERO,t_symbol.getAbstract()));
}

Symbol operator*(const Symbol& t_symbol, int t_value)
{
    Expr new_object = times_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator*(int t_value, const Symbol& t_symbol)
{
    Expr new_object = times_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator*(const Symbol& t_symbol, double t_value)
{
    Expr new_object = times_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator*(double t_value, const Symbol& t_symbol)
{
    Expr new_object = times_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator*(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr new_object = times_(t_symbol1.getAbstract(),t_symbol2.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}

Symbol operator/(const Symbol& t_symbol, int t_value)
{
    Expr new_object = fraction_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator/(int t_value, const Symbol& t_symbol)
{
    Expr new_object = fraction_(int_(t_value),t_symbol.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator/(const Symbol& t_symbol, double t_value)
{
    Expr new_object = fraction_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator/(double t_value, const Symbol& t_symbol)
{
    Expr new_object = fraction_(auto_number_(t_value),t_symbol.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator/(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr new_object = fraction_(t_symbol1.getAbstract(),t_symbol2.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}

Symbol operator^(const Symbol& t_symbol, int t_value)
{
    Expr new_object = pow_(t_symbol.getAbstract(), int_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator^(int t_value, const Symbol& t_symbol)
{
    Expr new_object = pow_(int_(t_value),t_symbol.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator^(const Symbol& t_symbol, double t_value)
{
    Expr new_object = pow_(t_symbol.getAbstract(), auto_number_(t_value));
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator^(double t_value, const Symbol& t_symbol)
{
    Expr new_object = pow_(auto_number_(t_value),t_symbol.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}
Symbol operator^(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    Expr new_object = pow_(t_symbol1.getAbstract(),t_symbol2.getAbstract());
    Symbol new_symbol(new_object);
    return new_symbol;
}

std::ostream& operator<<(std::ostream& fout, const Symbol& t_symbol)
{
    t_symbol.getAbstract()->print();
    return fout;
}

Expr Copy(const Abstract* t_abstract)
{    
    if (t_abstract == nullptr) return ZERO;
    int type = t_abstract->getType();
    Expr newAbstract;
    bool commutable = t_abstract->getCommutable();
    switch(type)
    {
        case smType::Double:
        newAbstract = double_(t_abstract->evaluateScalar());
        break;

        case smType::Integer:
        newAbstract = int_(t_abstract->evaluateScalar());
        break;

        case smType::Variable:
        newAbstract = var_(t_abstract->getName(), t_abstract->getValue());
        break;

        case smType::CFraction:
        newAbstract = _cfraction_(t_abstract->getNum(), t_abstract->getDenom());
        break;

        case smType::CFactorial:
        newAbstract = make_shared<CFactorial>(t_abstract->getValue());
        break;

        case smType::Imaginary:
        newAbstract = make_shared<Imaginary>();
        break;

        case smType::Plus:
        newAbstract = make_shared<Plus>(t_abstract->getVectorArgument(), true);
        break;
    
        case smType::Times:
        newAbstract = make_shared<Times>(t_abstract->getVectorArgument(), true);
        break;
    
        case smType::Fraction:
        newAbstract = make_shared<Fraction>(t_abstract->getArgument(0), t_abstract->getArgument(1));
        break;
    
        case smType::Pow:
        newAbstract = make_shared<Pow>(t_abstract->getArgument(0), t_abstract->getArgument(1));
        break;

        case smType::Polynomial:
        newAbstract = polynomial_(t_abstract->getVectorArgument(), t_abstract->getVariable());
        break;
    
        case smType::Exp:
        newAbstract = make_shared<Exp>(t_abstract->getArgument());
        break;
    
        case smType::Log:
        newAbstract = make_shared<Log>(t_abstract->getArgument());
        break;
    
        case smType::Cos:
        newAbstract = make_shared<Cos>(t_abstract->getArgument());
        break;
    
        case smType::Sin:
        newAbstract = make_shared<Sin>(t_abstract->getArgument());
        break;

        case smType::Tan:
        newAbstract = make_shared<Tan>(t_abstract->getArgument());
        break;

        case smType::ACos:
        newAbstract = make_shared<ACos>(t_abstract->getArgument());
        break;
    
        case smType::ASin:
        newAbstract = make_shared<ASin>(t_abstract->getArgument());
        break;

        case smType::ATan:
        newAbstract = make_shared<ATan>(t_abstract->getArgument());
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(t_abstract->getArgument(0),t_abstract->getArgument(1));
        break;

        case smType::Abs:
        newAbstract = make_shared<Abs>(t_abstract->getArgument());
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(t_abstract->getArgument(0), t_abstract->getArgument(1), t_abstract->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(t_abstract->getArgument());
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(t_abstract->getArgument());
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(t_abstract->getArgument());
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(t_abstract->getArgument());
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(t_abstract->getArgument());
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(t_abstract->getArgument());
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(t_abstract->getArgument());
        break;

        case smType::Vector:
        newAbstract = make_shared<Vector>(t_abstract->getVectorArgument());
        break;

        case smType::Matrix:
        newAbstract = make_shared<Matrix>(t_abstract->getVectorArgument());
        break;

        case smType::HighDTensor:
        newAbstract = make_shared<HighDTensor>(t_abstract->getVectorArgument());
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(t_abstract->getName(), t_abstract->getIndexStructure());
        break;
        
        case smType::ITerm:
        newAbstract = make_shared<ITerm>(t_abstract->getVectorArgument());
        break;
    
        default:
        cout<<"Warning: type "<<type<<" not recognize in copy function.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);
    return newAbstract;
}

Expr Copy(const Expr& t_abstract)
{
    return Copy(t_abstract.get());
}

Expr DeepCopy(const Abstract* t_abstract)
{
    //////
    ////// copy of commutable to add in this function
    //////
    if (t_abstract == nullptr) return ZERO;
    int type = t_abstract->getType();
    vector<Expr > foo(0), foo2(0);
    switch(type)
    {
        case smType::Double:
        return double_(t_abstract->evaluateScalar());
        break;

        case smType::Integer:
        return int_(t_abstract->evaluateScalar());
        break;

        case smType::Variable:
        return var_(t_abstract->getName(), t_abstract->getValue());
        break;

        case smType::CFraction:
        return _cfraction_(t_abstract->getNum(), t_abstract->getDenom());
        break;

        case smType::CFactorial:
        return make_shared<CFactorial>(t_abstract->getValue());
        break;

        case smType::Imaginary:
        return make_shared<Imaginary>();
        break;

        case smType::Plus:
        foo = t_abstract->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<Plus>(foo2, true);
        break;

        case smType::Times:
        foo = t_abstract->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<Times>(foo2,true);
        break;

        case smType::Fraction:
        return make_shared<Fraction>(DeepCopy(t_abstract->getArgument(0)), DeepCopy(t_abstract->getArgument(1)));
        break;

        case smType::Pow:
        return make_shared<Pow>(DeepCopy(t_abstract->getArgument(0)), DeepCopy(t_abstract->getArgument(1)));
        break;

        case smType::Polynomial:
        for (int i=0; i<t_abstract->getNArgs(); i++)
            foo.push_back(DeepCopy(t_abstract->getArgument(i)));
        return polynomial_(foo, DeepCopy(t_abstract->getVariable()));
        break;

        case smType::Exp:
        return make_shared<Exp>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Log:
        return make_shared<Log>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Cos:
        return make_shared<Cos>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Sin:
        return make_shared<Sin>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Tan:
        return make_shared<Tan>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::ACos:
        return make_shared<ACos>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::ASin:
        return make_shared<ASin>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::ATan:
        return make_shared<ATan>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Angle:
        return make_shared<Angle>(DeepCopy(t_abstract->getArgument(0)),DeepCopy(t_abstract->getArgument(1)));
        break;

        case smType::Abs:
        return make_shared<Abs>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Derivative:
        return make_shared<Derivative>(DeepCopy(t_abstract->getArgument(0)), DeepCopy(t_abstract->getArgument(1)), t_abstract->getOrder());
        break;
    
        case smType::Cosh:
        return make_shared<Cosh>(DeepCopy(t_abstract->getArgument()));
        break;
    
        case smType::Sinh:
        return make_shared<Sinh>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Tanh:
        return make_shared<Tanh>(DeepCopy(t_abstract->getArgument()));
        break;
    
        case smType::ACosh:
        return make_shared<ACosh>(DeepCopy(t_abstract->getArgument()));
        break;
    
        case smType::ASinh:
        return make_shared<ASinh>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::ATanh:
        return make_shared<ATanh>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Factorial:
        return make_shared<Factorial>(DeepCopy(t_abstract->getArgument()));
        break;

        case smType::Vector:
        foo = t_abstract->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<Vector>(foo2);
        break;

        case smType::Matrix:
        foo = t_abstract->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<Matrix>(foo2);
        break;

        case smType::HighDTensor:
        foo = t_abstract->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<HighDTensor>(foo2);
        break;

        case smType::ITensor:
        return make_shared<ITensor>(t_abstract->getName(), t_abstract->getIndexStructure());
        break;
        
        case smType::ITerm:
        foo = t_abstract->getVectorArgument();
        for (Expr i_abstract: foo)
            i_abstract = DeepCopy(i_abstract);
        return make_shared<ITerm>(foo);
        break;

        default: 
        cout<<"Warning: type "<<type<<" not recognized in DeepCopy function.\n";
        return ZERO;
    }
}
Expr DeepCopy(const Expr& t_abstract)
{
    return DeepCopy(t_abstract.get());
}

Expr Refresh(const Abstract* t_abstract)
{
    if (!t_abstract) return ZERO;
    int type = t_abstract->getType();
    Expr newAbstract = nullptr;
    vector<Expr > foo;
    Expr foo2;
    bool commutable = t_abstract->getCommutable();
    vector<Expr > newArgument(0);
    switch(type)
    {
        case smType::Double:
        newAbstract = double_(t_abstract->evaluateScalar());
        break;

        case smType::Integer:
        newAbstract = int_(t_abstract->evaluateScalar());
        break;

        case smType::Variable:
        newAbstract = var_(t_abstract->getName(), t_abstract->getValue());
        break;

        case smType::Constant:
        newAbstract = make_shared<Constant>(t_abstract->getName(), t_abstract->getValue());
        break;

        case smType::CFraction:
        newAbstract = _cfraction_(t_abstract->getNum(), t_abstract->getDenom());
        if (newAbstract->getNum() == 0 and newAbstract->getDenom() != 0) newAbstract = ZERO;
        else if (newAbstract->getDenom() == 1) newAbstract = int_(newAbstract->getNum());
        break;

        case smType::CFactorial:
        newAbstract = cfactorial_(t_abstract->getValue());
        newAbstract->setName(t_abstract->getName());
        break;

        case smType::Imaginary:
        newAbstract = make_shared<Imaginary>();
        break;

        case smType::Plus:
        newAbstract = plus_(t_abstract->getVectorArgument());
        break;

        case smType::Times:
        newAbstract = times_(t_abstract->getVectorArgument());
        break;

        case smType::Fraction:
        newAbstract = fraction_(t_abstract->getArgument(0), t_abstract->getArgument(1));
        break;

        case smType::Pow:
        newAbstract = pow_(t_abstract->getArgument(0),t_abstract->getArgument(1));
        break;

        case smType::Polynomial:
        foo = t_abstract->getVectorArgument();
        foo2 = t_abstract->getVariable();
        newAbstract = polynomial_(foo, foo2);
        break;

        case smType::Exp:
        newAbstract = exp_(t_abstract->getArgument());
        break;

        case smType::Log:
        newAbstract = log_(t_abstract->getArgument());
        break;

        case smType::Cos:
        newAbstract = cos_(t_abstract->getArgument());
        break;

        case smType::Sin:
        newAbstract = sin_(t_abstract->getArgument());
        break;

        case smType::Tan:
        newAbstract = tan_(t_abstract->getArgument());
        break;

        case smType::ACos:
        newAbstract = acos_(t_abstract->getArgument());
        break;

        case smType::ASin:
        newAbstract = asin_(t_abstract->getArgument());
        break;

        case smType::ATan:
        newAbstract = atan_(t_abstract->getArgument());
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(t_abstract->getArgument(0),t_abstract->getArgument(1));
        break;

        case smType::Abs:
        newAbstract = abs_(t_abstract->getArgument());
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(t_abstract->getArgument(0), t_abstract->getArgument(1), t_abstract->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(t_abstract->getArgument());
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(t_abstract->getArgument());
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(t_abstract->getArgument());
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(t_abstract->getArgument());
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(t_abstract->getArgument());
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(t_abstract->getArgument());
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(t_abstract->getArgument());
        break;

        case smType::Vector:
        foo = t_abstract->getVectorArgument();
        newAbstract = vector_(foo);
        break;

        case smType::Matrix:
        foo = t_abstract->getVectorArgument();
        newAbstract = matrix_(foo);
        break;

        case smType::HighDTensor:
        foo = t_abstract->getVectorArgument();
        newAbstract = highDTensor_(foo);
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(t_abstract->getName(), t_abstract->getIndexStructure());
        break;
        
        case smType::ITerm:
        newAbstract = make_shared<ITerm>(t_abstract->getVectorArgument());
        break;

        default:
        cout<<"Warning type "<<type<<" not known by Refresh function in symbol.cpp.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);

    return newAbstract;
}

Expr Refresh(const Expr& t_abstract)
{
    if (!t_abstract) return ZERO;
    int type = t_abstract->getType();
    Expr newAbstract = nullptr;
    vector<Expr > foo;
    Expr foo2;
    bool commutable = t_abstract->getCommutable();
    vector<Expr > newArgument(0);
    switch(type)
    {
        case smType::Double:
        case smType::Integer:
        case smType::Variable:
        case smType::Constant:
        case smType::CFactorial:
        case smType::Imaginary:
        newAbstract = t_abstract;
        break;

        case smType::CFraction:
        newAbstract = _cfraction_(t_abstract->getNum(), t_abstract->getDenom());
        if (newAbstract->getNum() == 0 and newAbstract->getDenom() != 0) newAbstract = ZERO;
        else if (newAbstract->getDenom() == 1) newAbstract = int_(newAbstract->getNum());
        break;

        case smType::Plus:
        newAbstract = plus_(t_abstract->getVectorArgument());
        break;

        case smType::Times:
        newAbstract = times_(t_abstract->getVectorArgument());
        break;

        case smType::Fraction:
        newAbstract = fraction_(t_abstract->getArgument(0), t_abstract->getArgument(1));
        break;

        case smType::Pow:
        newAbstract = pow_(t_abstract->getArgument(0),t_abstract->getArgument(1));
        break;

        case smType::Polynomial:
        foo = t_abstract->getVectorArgument();
        foo2 = t_abstract->getVariable();
        newAbstract = polynomial_(foo, foo2);
        break;

        case smType::Exp:
        newAbstract = exp_(t_abstract->getArgument());
        break;

        case smType::Log:
        newAbstract = log_(t_abstract->getArgument());
        break;

        case smType::Cos:
        newAbstract = cos_(t_abstract->getArgument());
        break;

        case smType::Sin:
        newAbstract = sin_(t_abstract->getArgument());
        break;

        case smType::Tan:
        newAbstract = tan_(t_abstract->getArgument());
        break;

        case smType::ACos:
        newAbstract = acos_(t_abstract->getArgument());
        break;

        case smType::ASin:
        newAbstract = asin_(t_abstract->getArgument());
        break;

        case smType::ATan:
        newAbstract = atan_(t_abstract->getArgument());
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(t_abstract->getArgument(0),t_abstract->getArgument(1));
        break;

        case smType::Abs:
        newAbstract = abs_(t_abstract->getArgument());
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(t_abstract->getArgument(0), t_abstract->getArgument(1), t_abstract->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(t_abstract->getArgument());
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(t_abstract->getArgument());
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(t_abstract->getArgument());
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(t_abstract->getArgument());
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(t_abstract->getArgument());
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(t_abstract->getArgument());
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(t_abstract->getArgument());
        break;

        case smType::Vector:
        foo = t_abstract->getVectorArgument();
        newAbstract = vector_(foo);
        break;

        case smType::Matrix:
        foo = t_abstract->getVectorArgument();
        newAbstract = matrix_(foo);
        break;

        case smType::HighDTensor:
        foo = t_abstract->getVectorArgument();
        newAbstract = highDTensor_(foo);
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(t_abstract->getName(), t_abstract->getIndexStructure());
        break;
        
        case smType::ITerm:
        cout<<"Warning: Type ITerm not correctly implemented in Refresh.\n";
        newAbstract = make_shared<ITerm>(t_abstract->getVectorArgument());
        break;

        default:
        cout<<"Warning type "<<type<<" not known by Refresh function in symbol.cpp.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);

    return newAbstract;
}

Expr DeepRefresh(const Expr& t_abstract)
{
    if (!t_abstract) return ZERO;
    int type = t_abstract->getType();
    Expr newAbstract = nullptr;
    vector<Expr > foo;
    Expr foo2;
    int nArgs;
    bool commutable = t_abstract->getCommutable();
    vector<Expr > newArgument(0);
    switch(type)
    {
        case smType::Double:
        newAbstract = double_(t_abstract->evaluateScalar());
        break;

        case smType::Integer:
        newAbstract = int_(t_abstract->evaluateScalar());
        break;

        case smType::Variable:
        newAbstract = var_(t_abstract->getName(), t_abstract->getValue());
        break;

        case smType::Constant:
        newAbstract = make_shared<Constant>(t_abstract->getName(), t_abstract->getValue());
        break;

        case smType::CFraction:
        newAbstract = _cfraction_(t_abstract->getNum(), t_abstract->getDenom());
        if (newAbstract->getNum() == 0 and newAbstract->getDenom() != 0) newAbstract = ZERO;
        else if (newAbstract->getDenom() == 1) newAbstract = int_(newAbstract->getNum());
        break;

        case smType::CFactorial:
        newAbstract = cfactorial_(t_abstract->getValue());
        newAbstract->setName(t_abstract->getName());
        break;

        case smType::Imaginary:
        newAbstract = make_shared<Imaginary>();
        break;

        case smType::Plus:
        nArgs = t_abstract->getNArgs();
        newArgument = vector<Expr >(nArgs);
        for (int i=0; i<nArgs; i++)
            newArgument[i] = DeepRefresh(t_abstract->getArgument(i));
        newAbstract = plus_(newArgument);
        break;

        case smType::Times:
        nArgs = t_abstract->getNArgs();
        newArgument = vector<Expr >(nArgs);
        for (int i=0; i<nArgs; i++)
            newArgument[i] = DeepRefresh(t_abstract->getArgument(i));
        newAbstract = times_(newArgument);
        break;

        case smType::Fraction:
        newAbstract = fraction_(DeepRefresh(t_abstract->getArgument(0)),DeepRefresh(t_abstract->getArgument(1)));
        break;

        case smType::Pow:
        newAbstract = pow_(DeepRefresh(t_abstract->getArgument(0)),DeepRefresh(t_abstract->getArgument(1)));
        break;

        case smType::Polynomial:
        foo = t_abstract->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo[i] = DeepRefresh(foo[i]);
        foo2 = t_abstract->getVariable();
        newAbstract = polynomial_(foo, foo2);
        break;

        case smType::Exp:
        newAbstract = exp_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Log:
        newAbstract = log_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Cos:
        newAbstract = cos_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Sin:
        newAbstract = sin_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Tan:
        newAbstract = tan_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::ACos:
        newAbstract = acos_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::ASin:
        newAbstract = asin_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::ATan:
        newAbstract = atan_(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(DeepRefresh(t_abstract->getArgument(0)),DeepRefresh(t_abstract->getArgument(1)));
        break;

        case smType::Abs:
        newAbstract = abs_(DeepRefresh(DeepRefresh(t_abstract->getArgument())));
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(DeepRefresh(t_abstract->getArgument(0)), DeepRefresh(t_abstract->getArgument(1)), t_abstract->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(DeepRefresh(t_abstract->getArgument()));
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(DeepRefresh(t_abstract->getArgument()));
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(DeepRefresh(t_abstract->getArgument()));
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(DeepRefresh(t_abstract->getArgument()));
        break;

        case smType::Vector:
        nArgs = t_abstract->getNArgs();
        newAbstract = ZERO;
        foo = t_abstract->getVectorArgument();
        for (int i=0; i<nArgs; i++)
            foo[i] = DeepRefresh(foo[i]);
        newAbstract = vector_(foo);
        break;

        case smType::Matrix:
        nArgs = t_abstract->getNArgs();
        newAbstract = ZERO;
        foo = t_abstract->getVectorArgument();
        for (int i=0; i<nArgs; i++)
            foo[i] = DeepRefresh(foo[i]);
        newAbstract = matrix_(foo);
        break;

        case smType::HighDTensor:
        nArgs = t_abstract->getNArgs();
        newAbstract = ZERO;
        foo = t_abstract->getVectorArgument();
        for (int i=0; i<nArgs; i++)
            foo[i] = DeepRefresh(foo[i]);
        newAbstract = highDTensor_(foo);
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(t_abstract->getName(), t_abstract->getIndexStructure());
        break;
        
        case smType::ITerm:
        cout<<"Warning: Type ITerm not correctly implemented in Refresh.\n";
        nArgs = t_abstract->getNArgs();
        newAbstract = ZERO;
        foo = t_abstract->getVectorArgument();
        for (int i=0; i<nArgs; i++)
            foo[i] = DeepRefresh(foo[i]);
        newAbstract = make_shared<ITerm>(foo);
        break;

        default:
        cout<<"Warning type "<<type<<" not known by Refresh function in symbol.cpp.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);

    return newAbstract;
}

Expr Replace(const Expr& t_abstract, const Expr& old_abstract, const Expr& new_abstract)
{
    /*cout<<"Replacing ";
    old_abstract->print();
    cout<<"by ";
    new_abstract->print();
    cout<<"in ";
    t_abstract->print();
    cout<<"first cond = "<<(*t_abstract==old_abstract)<<endl;
    cout<<"primaryType = "<<t_abstract->getPrimaryType();*/
    if (*t_abstract==old_abstract) return new_abstract;
    int type = t_abstract->getPrimaryType();
    if (type < 10) return t_abstract;
    if (type < 50 and type >= 20)
    {
        Expr foo = Copy(t_abstract);
        foo->setArgument(Replace(t_abstract->getArgument(), old_abstract, new_abstract),0);
        foo = Refresh(foo);
        return foo;
    }
    if (type < 100)
    {
        Expr foo = Copy(t_abstract);
        if (t_abstract->getType() == smType::Polynomial and *old_abstract == t_abstract->getVariable())
            foo = foo->getRegularExpression();
        for (int i=0; i<foo->getNArgs(); i++)
            foo->setArgument(Replace(t_abstract->getArgument(i), old_abstract, new_abstract),i);
        foo = Refresh(foo);
        return foo;
    }
    cout<<"Warning: type "<<type<<" not taken into account in \"Replace\".\n";

    return t_abstract;
}

Expr Empty(smType::Type type)
{
    switch(type)
    {
        case smType::Integer:     return make_shared<Integer>();     break;
        case smType::CFraction:   return make_shared<CFraction>();   break;
        case smType::Double:      return make_shared<Double>();      break;
        case smType::CFactorial:  return make_shared<CFactorial>();  break;
        case smType::Imaginary:   return make_shared<Imaginary>();   break;
        case smType::Constant:    return make_shared<Constant>();    break;
        case smType::Variable:    return make_shared<Variable>();    break;
        case smType::Plus:        return make_shared<Plus>();        break;
        case smType::Polynomial:  return make_shared<Polynomial>();  break;
        case smType::Times:       return make_shared<Times>();       break;
        case smType::Fraction:    return make_shared<Fraction>();    break;
        case smType::Pow:         return make_shared<Pow>();         break;
        case smType::Exp:         return make_shared<Exp>();         break;
        case smType::Log:         return make_shared<Log>();         break;
        case smType::Abs:         return make_shared<Abs>();         break;
        case smType::Cos:         return make_shared<Cos>();         break;
        case smType::Sin:         return make_shared<Sin>();         break;
        case smType::Tan:         return make_shared<Tan>();         break;
        case smType::Cosh:        return make_shared<Cosh>();        break;
        case smType::Sinh:        return make_shared<Sinh>();        break;
        case smType::Tanh:        return make_shared<Tanh>();        break;
        case smType::Derivative:  return make_shared<Derivative>();  break;
        case smType::Angle:       return make_shared<Angle>();       break;
        case smType::Factorial:   return make_shared<Factorial>();   break;
        case smType::ACos:        return make_shared<ACos>();        break;
        case smType::ASin:        return make_shared<ASin>();        break;
        case smType::ATan:        return make_shared<ATan>();        break;
        case smType::ACosh:       return make_shared<ACosh>();       break;
        case smType::ASinh:       return make_shared<ASinh>();       break;
        case smType::ATanh:       return make_shared<ATanh>();       break;
        case smType::Vector:      return make_shared<Vector>();      break;
        case smType::Matrix:      return make_shared<Matrix>();      break;
        case smType::HighDTensor: return make_shared<HighDTensor>(); break;
        case smType::ITensor:     return make_shared<ITensor>();     break;
        case smType::ITerm:       return make_shared<ITerm>();       break;

        default: callWarning<smType::Type>(smError::UnknownType, "Empty(Type)", type); return ZERO;
    }
}
