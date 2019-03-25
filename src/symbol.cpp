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

Symbol::Symbol(std::string t_name, const Symbol& symbol)
{
    name = t_name;
    abstract = symbol.getAbstract();
    if (abstract->getName() == "")
        abstract->setName(name);
}

Symbol::Symbol(std::string t_name, bool constant)
{
    if (constant)
        abstract = constant_(t_name);
    else
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

Symbol::Symbol(const Expr& expr)
{
    if (expr) name = expr->getName();
    else cout<<"Warning: initializing a symbol with an invalid abstract.\n";
    abstract = expr;
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

void Symbol::setAbstract(const Expr& expr)
{
    abstract = expr;
    if (abstract->getName() == "")
        abstract->setName(name);
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

Symbol Symbol::derive(Symbol t_symbol)
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

void Symbol::setElementary(bool t_elementary)
{
    abstract->setElementary(t_elementary);
}

void Symbol::setAllDependencies(bool t_allDependencies)
{
    abstract->setAllDependencies(t_allDependencies);
}

void Symbol::addDependency(const Symbol& symbol)
{
    abstract->addDependency(symbol.getAbstract());
}

void Symbol::removeDependency(const Symbol& symbol)
{
    abstract->removeDependency(symbol.getAbstract());
}

Symbol Symbol::getVectorialModulus() const
{
    return Symbol(abstract->getVectorialModulus());
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

bool Symbol::checkIndexStructure(const vector<Idx>& t_index) const
{
    return abstract->checkIndexStructure(t_index);
}

bool Symbol::checkIndexStructure(initializer_list<Idx> t_index) const
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
    if (abstract->getName() == "")
        abstract->setName(name);

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

Symbol Symbol::operator()(const initializer_list<Idx>& indices) const
{
    Expr newAbstract = Copy(abstract);
    IndexStructure freeStructure = abstract->getFreeIndexStructure();
    if (indices.size() != freeStructure.getNIndices())
        callError(smError::InvalidITensor,
                "Symbol::operator()(const initializer_list<Idx>&) const");
    for (auto i=indices.begin(); i!=indices.end(); ++i)
        newAbstract->replaceIndex(freeStructure[distance(indices.begin(),i)],*i);

    return Symbol(newAbstract);
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

Symbol derivative_(const Symbol& t_symbol, const Symbol& t_variable, int order, bool empty)
{
    return Symbol(derivative_(t_symbol.getAbstract(), t_variable.getAbstract(), order, empty));
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
    return Symbol(vector_(t_nElements, t_symbol.getAbstract(), index.getAbstract()));
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

Symbol Id_(int dim)
{
    Symbol M = matrix_(dim);
    for (int i=0; i<dim; ++i)
        M.setArgument(1,i,i);
    return M;
}

Symbol tensor_dot(const Symbol& t_symbol1, const Symbol& t_symbol2)
{
    return Symbol(t_symbol1.getAbstract()->tensor_dot(t_symbol2.getAbstract()));
}

Symbol Symbol::polynomialFactorization() const
{
    return Symbol(abstract->factor());
}

Symbol Symbol::getRegularExpression() const
{
    return Symbol(abstract->getRegularExpression());
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
    Taylor = Taylor.replace(t_variable, Symbol(ZERO));
    Symbol derivative = Copy(t_symbol);
    Symbol foo;
    for (size_t order=1; order<=max_order; order++) 
    {
        derivative = derivative.derive(t_variable);
        foo = Copy(derivative);
        foo = foo.replace(t_variable,Symbol(ZERO));
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
    Expr new_object = minus_(int_(t_value),t_symbol.getAbstract());
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
    Expr new_object = minus_(auto_number_(t_value), t_symbol.getAbstract());
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

Expr Copy(const Abstract* expr)
{    
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        callWarning(smError::CopyingBuildingBlock,
                "Copy(const Abstract* expr)", expr->printLaTeX(1));
    int type = expr->getType();
    Expr newAbstract;
    bool commutable = expr->getCommutable();
    switch(type)
    {
        case smType::Plus:
        newAbstract = make_shared<Plus>();
        newAbstract->setVectorArgument(expr->getVectorArgument());
        break;
    
        case smType::Times:
        newAbstract = make_shared<Times>();
        newAbstract->setVectorArgument(expr->getVectorArgument());
        break;
    
        case smType::Fraction:
        newAbstract = make_shared<Fraction>(expr->getArgument(0), expr->getArgument(1));
        break;
    
        case smType::Pow:
        newAbstract = make_shared<Pow>(expr->getArgument(0), expr->getArgument(1));
        break;

        case smType::Polynomial:
        newAbstract = make_shared<Polynomial>(ZERO,expr->getVariable());
        newAbstract->setVectorArgument(expr->getVectorArgument());
        break;
    
        case smType::Exp:
        newAbstract = make_shared<Exp>(expr->getArgument());
        break;
    
        case smType::Log:
        newAbstract = make_shared<Log>(expr->getArgument());
        break;
    
        case smType::Cos:
        newAbstract = make_shared<Cos>(expr->getArgument());
        break;
    
        case smType::Sin:
        newAbstract = make_shared<Sin>(expr->getArgument());
        break;

        case smType::Tan:
        newAbstract = make_shared<Tan>(expr->getArgument());
        break;

        case smType::ACos:
        newAbstract = make_shared<ACos>(expr->getArgument());
        break;
    
        case smType::ASin:
        newAbstract = make_shared<ASin>(expr->getArgument());
        break;

        case smType::ATan:
        newAbstract = make_shared<ATan>(expr->getArgument());
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(expr->getArgument(0),expr->getArgument(1));
        break;

        case smType::Abs:
        newAbstract = make_shared<Abs>(expr->getArgument());
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(expr->getArgument(0), expr->getArgument(1), expr->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(expr->getArgument());
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(expr->getArgument());
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(expr->getArgument());
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(expr->getArgument());
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(expr->getArgument());
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(expr->getArgument());
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(expr->getArgument());
        break;

        case smType::Vector:
        newAbstract = make_shared<Vector>(expr->getVectorArgument());
        break;

        case smType::Matrix:
        newAbstract = make_shared<Matrix>(expr->getVectorArgument());
        break;

        case smType::HighDTensor:
        newAbstract = make_shared<HighDTensor>(expr->getVectorArgument());
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(expr);
        break;
        
        default:
        cout<<"Warning: type "<<type<<" not recognize in copy function.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);
    return newAbstract;
}

Expr Copy(const Expr& expr)
{
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        // If building block we do not copy
        return expr;
    return Copy(expr.get());
}

Expr DeepCopy(const Abstract* expr)
{
    //////
    ////// copy of commutable to add in this function
    //////
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        callWarning(smError::CopyingBuildingBlock,
                "DeepCopy(const Abstract* expr)", expr->printLaTeX(1));
    int type = expr->getType();
    vector<Expr > foo(0), foo2(0);
    Expr fooExpr;
    switch(type)
    {
        case smType::Plus:
        foo = expr->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        fooExpr = make_shared<Plus>();
        fooExpr->setVectorArgument(foo2);
        return fooExpr;
        break;

        case smType::Times:
        foo = expr->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        fooExpr = make_shared<Times>();
        fooExpr->setVectorArgument(foo2);
        return fooExpr;
        break;

        case smType::Fraction:
        return make_shared<Fraction>(DeepCopy(expr->getArgument(0)), DeepCopy(expr->getArgument(1)));
        break;

        case smType::Pow:
        return make_shared<Pow>(DeepCopy(expr->getArgument(0)), DeepCopy(expr->getArgument(1)));
        break;

        case smType::Polynomial:
        for (int i=0; i<expr->getNArgs(); i++)
            foo.push_back(DeepCopy(expr->getArgument(i)));
        fooExpr = make_shared<Polynomial>(ZERO,DeepCopy(expr->getVariable()));
        fooExpr->setVectorArgument(foo);
        return fooExpr;
        break;

        case smType::Exp:
        return make_shared<Exp>(DeepCopy(expr->getArgument()));
        break;

        case smType::Log:
        return make_shared<Log>(DeepCopy(expr->getArgument()));
        break;

        case smType::Cos:
        return make_shared<Cos>(DeepCopy(expr->getArgument()));
        break;

        case smType::Sin:
        return make_shared<Sin>(DeepCopy(expr->getArgument()));
        break;

        case smType::Tan:
        return make_shared<Tan>(DeepCopy(expr->getArgument()));
        break;

        case smType::ACos:
        return make_shared<ACos>(DeepCopy(expr->getArgument()));
        break;

        case smType::ASin:
        return make_shared<ASin>(DeepCopy(expr->getArgument()));
        break;

        case smType::ATan:
        return make_shared<ATan>(DeepCopy(expr->getArgument()));
        break;

        case smType::Angle:
        return make_shared<Angle>(DeepCopy(expr->getArgument(0)),DeepCopy(expr->getArgument(1)));
        break;

        case smType::Abs:
        return make_shared<Abs>(DeepCopy(expr->getArgument()));
        break;

        case smType::Derivative:
        return make_shared<Derivative>(DeepCopy(expr->getArgument(0)), DeepCopy(expr->getArgument(1)), expr->getOrder());
        break;
    
        case smType::Cosh:
        return make_shared<Cosh>(DeepCopy(expr->getArgument()));
        break;
    
        case smType::Sinh:
        return make_shared<Sinh>(DeepCopy(expr->getArgument()));
        break;

        case smType::Tanh:
        return make_shared<Tanh>(DeepCopy(expr->getArgument()));
        break;
    
        case smType::ACosh:
        return make_shared<ACosh>(DeepCopy(expr->getArgument()));
        break;
    
        case smType::ASinh:
        return make_shared<ASinh>(DeepCopy(expr->getArgument()));
        break;

        case smType::ATanh:
        return make_shared<ATanh>(DeepCopy(expr->getArgument()));
        break;

        case smType::Factorial:
        return make_shared<Factorial>(DeepCopy(expr->getArgument()));
        break;

        case smType::Vector:
        foo = expr->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<Vector>(foo2);
        break;

        case smType::Matrix:
        foo = expr->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<Matrix>(foo2);
        break;

        case smType::HighDTensor:
        foo = expr->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo2.push_back(DeepCopy(foo[i]));
        return make_shared<HighDTensor>(foo2);
        break;

        case smType::ITensor:
        return make_shared<ITensor>(expr);
        break;
        
        default: 
        cout<<"Warning: type "<<type<<" not recognized in DeepCopy function.\n";
        return ZERO;
    }
}
Expr DeepCopy(const Expr& expr)
{
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        //If building block we do not copy
        return expr;
    return DeepCopy(expr.get());
}

Expr Refresh(const Abstract* expr)
{
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        callWarning(smError::CopyingBuildingBlock,
                "Refresh(const Abstract* expr)", expr->printLaTeX(1));
    int type = expr->getType();
    Expr newAbstract = nullptr;
    vector<Expr > foo;
    Expr foo2;
    bool commutable = expr->getCommutable();
    vector<Expr > newArgument(0);
    switch(type)
    {
        case smType::Plus:
        newAbstract = plus_(expr->getVectorArgument());
        break;

        case smType::Times:
        newAbstract = times_(expr->getVectorArgument());
        break;

        case smType::Fraction:
        newAbstract = fraction_(expr->getArgument(0), expr->getArgument(1));
        break;

        case smType::Pow:
        newAbstract = pow_(expr->getArgument(0),expr->getArgument(1));
        break;

        case smType::Polynomial:
        foo = expr->getVectorArgument();
        foo2 = expr->getVariable();
        newAbstract = polynomial_(foo, foo2);
        break;

        case smType::Exp:
        newAbstract = exp_(expr->getArgument());
        break;

        case smType::Log:
        newAbstract = log_(expr->getArgument());
        break;

        case smType::Cos:
        newAbstract = cos_(expr->getArgument());
        break;

        case smType::Sin:
        newAbstract = sin_(expr->getArgument());
        break;

        case smType::Tan:
        newAbstract = tan_(expr->getArgument());
        break;

        case smType::ACos:
        newAbstract = acos_(expr->getArgument());
        break;

        case smType::ASin:
        newAbstract = asin_(expr->getArgument());
        break;

        case smType::ATan:
        newAbstract = atan_(expr->getArgument());
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(expr->getArgument(0),expr->getArgument(1));
        break;

        case smType::Abs:
        newAbstract = abs_(expr->getArgument());
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(expr->getArgument(0), expr->getArgument(1), expr->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(expr->getArgument());
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(expr->getArgument());
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(expr->getArgument());
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(expr->getArgument());
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(expr->getArgument());
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(expr->getArgument());
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(expr->getArgument());
        break;

        case smType::Vector:
        foo = expr->getVectorArgument();
        newAbstract = vector_(foo);
        break;

        case smType::Matrix:
        foo = expr->getVectorArgument();
        newAbstract = matrix_(foo);
        break;

        case smType::HighDTensor:
        foo = expr->getVectorArgument();
        newAbstract = highDTensor_(foo);
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(expr);
        break;
        
        default:
        cout<<"Warning type "<<type<<" not known by Refresh function in symbol.cpp.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);

    return newAbstract;
}

Expr Refresh(const Expr& expr)
{
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        return expr;
    int type = expr->getType();
    Expr newAbstract = nullptr;
    vector<Expr > foo;
    Expr foo2;
    bool commutable = expr->getCommutable();
    vector<Expr > newArgument(0);
    switch(type)
    {
        case smType::Plus:
        newAbstract = plus_(expr->getVectorArgument());
        break;

        case smType::Times:
        newAbstract = times_(expr->getVectorArgument());
        break;

        case smType::Fraction:
        newAbstract = fraction_(expr->getArgument(0), expr->getArgument(1));
        break;

        case smType::Pow:
        newAbstract = pow_(expr->getArgument(0),expr->getArgument(1));
        break;

        case smType::Polynomial:
        foo = expr->getVectorArgument();
        foo2 = expr->getVariable();
        newAbstract = polynomial_(foo, foo2);
        break;

        case smType::Exp:
        newAbstract = exp_(expr->getArgument());
        break;

        case smType::Log:
        newAbstract = log_(expr->getArgument());
        break;

        case smType::Cos:
        newAbstract = cos_(expr->getArgument());
        break;

        case smType::Sin:
        newAbstract = sin_(expr->getArgument());
        break;

        case smType::Tan:
        newAbstract = tan_(expr->getArgument());
        break;

        case smType::ACos:
        newAbstract = acos_(expr->getArgument());
        break;

        case smType::ASin:
        newAbstract = asin_(expr->getArgument());
        break;

        case smType::ATan:
        newAbstract = atan_(expr->getArgument());
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(expr->getArgument(0),expr->getArgument(1));
        break;

        case smType::Abs:
        newAbstract = abs_(expr->getArgument());
        break;

        case smType::Derivative:
        newAbstract = make_shared<Derivative>(expr->getArgument(0), expr->getArgument(1), expr->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(expr->getArgument());
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(expr->getArgument());
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(expr->getArgument());
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(expr->getArgument());
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(expr->getArgument());
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(expr->getArgument());
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(expr->getArgument());
        break;

        case smType::Vector:
        foo = expr->getVectorArgument();
        newAbstract = vector_(foo);
        break;

        case smType::Matrix:
        foo = expr->getVectorArgument();
        newAbstract = matrix_(foo);
        break;

        case smType::HighDTensor:
        foo = expr->getVectorArgument();
        newAbstract = highDTensor_(foo);
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(expr);
        break;
        
        default:
        cout<<"Warning type "<<type<<" not known by Refresh function in symbol.cpp.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);

    return newAbstract;
}

Expr DeepRefresh(const Expr& expr)
{
    if (expr->isBuildingBlock() and expr->getType() != smType::ITensor)
        return expr;
    int type = expr->getType();
    Expr newAbstract = nullptr;
    vector<Expr > foo;
    Expr foo2;
    int nArgs;
    bool commutable = expr->getCommutable();
    vector<Expr > newArgument(0);
    switch(type)
    {
        case smType::Plus:
        nArgs = expr->getNArgs();
        newArgument = vector<Expr >(nArgs);
        for (int i=0; i<nArgs; i++)
            newArgument[i] = DeepRefresh(expr->getArgument(i));
        newAbstract = plus_(newArgument);
        break;

        case smType::Times:
        nArgs = expr->getNArgs();
        newArgument = vector<Expr >(nArgs);
        for (int i=0; i<nArgs; i++)
            newArgument[i] = DeepRefresh(expr->getArgument(i));
        newAbstract = times_(newArgument);
        break;

        case smType::Fraction:
        newAbstract = fraction_(DeepRefresh(expr->getArgument(0)),DeepRefresh(expr->getArgument(1)));
        break;

        case smType::Pow:
        newAbstract = pow_(DeepRefresh(expr->getArgument(0)),DeepRefresh(expr->getArgument(1)));
        break;

        case smType::Polynomial:
        foo = expr->getVectorArgument();
        for (size_t i=0; i<foo.size(); i++)
            foo[i] = DeepRefresh(foo[i]);
        foo2 = expr->getVariable();
        newAbstract = polynomial_(foo, foo2);
        break;

        case smType::Exp:
        newAbstract = exp_(DeepRefresh(expr->getArgument()));
        break;

        case smType::Log:
        newAbstract = log_(DeepRefresh(expr->getArgument()));
        break;

        case smType::Cos:
        newAbstract = cos_(DeepRefresh(expr->getArgument()));
        break;

        case smType::Sin:
        newAbstract = sin_(DeepRefresh(expr->getArgument()));
        break;

        case smType::Tan:
        newAbstract = tan_(DeepRefresh(expr->getArgument()));
        break;

        case smType::ACos:
        newAbstract = acos_(DeepRefresh(expr->getArgument()));
        break;

        case smType::ASin:
        newAbstract = asin_(DeepRefresh(expr->getArgument()));
        break;

        case smType::ATan:
        newAbstract = atan_(DeepRefresh(expr->getArgument()));
        break;

        case smType::Angle:
        newAbstract = make_shared<Angle>(DeepRefresh(expr->getArgument(0)),DeepRefresh(expr->getArgument(1)));
        break;

        case smType::Abs:
        newAbstract = abs_(DeepRefresh(DeepRefresh(expr->getArgument())));
        break;

        case smType::Derivative:
        newAbstract = derivative_(DeepRefresh(expr->getArgument(0)), DeepRefresh(expr->getArgument(1)), expr->getOrder());
        break;
    
        case smType::Cosh:
        newAbstract = make_shared<Cosh>(DeepRefresh(expr->getArgument()));
        break;
    
        case smType::Sinh:
        newAbstract = make_shared<Sinh>(DeepRefresh(expr->getArgument()));
        break;

        case smType::Tanh:
        newAbstract = make_shared<Tanh>(DeepRefresh(expr->getArgument()));
        break;
    
        case smType::ACosh:
        newAbstract = make_shared<ACosh>(DeepRefresh(expr->getArgument()));
        break;
    
        case smType::ASinh:
        newAbstract = make_shared<ASinh>(DeepRefresh(expr->getArgument()));
        break;

        case smType::ATanh:
        newAbstract = make_shared<ATanh>(DeepRefresh(expr->getArgument()));
        break;

        case smType::Factorial:
        newAbstract = make_shared<Factorial>(DeepRefresh(expr->getArgument()));
        break;

        case smType::Vector:
        nArgs = expr->getNArgs();
        newAbstract = ZERO;
        foo = expr->getVectorArgument();
        for (auto& arg : foo)
            arg = DeepRefresh(arg);
        newAbstract = vector_(foo);
        break;

        case smType::Matrix:
        nArgs = expr->getNArgs();
        newAbstract = ZERO;
        foo = expr->getVectorArgument();
        for (auto& arg : foo)
            arg = DeepRefresh(arg);
        newAbstract = matrix_(foo);
        break;

        case smType::HighDTensor:
        nArgs = expr->getNArgs();
        newAbstract = ZERO;
        foo = expr->getVectorArgument();
        for (auto& arg : foo)
            arg = DeepRefresh(arg);
        newAbstract = highDTensor_(foo);
        break;

        case smType::ITensor:
        newAbstract = make_shared<ITensor>(expr);
        break;
        
        default:
        cout<<"Warning type "<<type<<" not known by Refresh function in symbol.cpp.\n";
    }
    if (newAbstract) newAbstract->setCommutable(commutable);

    return newAbstract;
}

Expr Replace(const Expr& expr, const Expr& old_abstract, const Expr& new_abstract)
{
    /*cout<<"Replacing ";
    old_abstract->print();
    cout<<"by ";
    new_abstract->print();
    cout<<"in ";
    expr->print();
    cout<<"first cond = "<<(*expr==old_abstract)<<endl;
    cout<<"primaryType = "<<expr->getPrimaryType();*/
    if (*expr==old_abstract) return new_abstract;
    int type = expr->getPrimaryType();
    if (type < 10) return expr;
    if (type < 50 and type >= 20)
    {
        Expr foo = Copy(expr);
        foo->setArgument(Replace(expr->getArgument(), old_abstract, new_abstract),0);
        foo = DeepRefresh(foo);
        return foo;
    }
    if (type < 100)
    {
        Expr foo = Copy(expr);
        if (expr->getType() == smType::Polynomial and *old_abstract == expr->getVariable())
            foo = foo->getRegularExpression();
        for (int i=0; i<foo->getNArgs(); i++)
            foo->setArgument(Replace(expr->getArgument(i), old_abstract, new_abstract),i);
        foo = DeepRefresh(foo);
        return foo;
    }
    cout<<"Warning: type "<<type<<" not taken into account in \"Replace\".\n";

    return expr;
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
        // case ITensor not allowed!
        //case smType::ITensor:     return make_shared<ITensor>();     break;

        default: callWarning<smType::Type>(smError::UnknownType, "Empty(Type)", type); return ZERO;
    }
}
