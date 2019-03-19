#include "operations.h"
#include "indicial.h"
#include "mathFunctions.h"
#include "vector.h"
#include "simplification.h"
#include "commutation.h"
using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class Plus                                    //
/*************************************************/
///////////////////////////////////////////////////

Plus::Plus(const vector<Expr >& operands, bool explicitPlus)
    :AbstractMultiFunc() 
{
    nArgs = operands.size();
    argument = operands;
    if (not explicitPlus and nArgs > 0)
        mergeTerms();
    selfCheckIndexStructure();
}

Plus::Plus(const Expr& leftOperand, const Expr& rightOperand)
    :AbstractMultiFunc()
{
    // We check if one ooperand is already a Plus expression,
    // in which case we insert the other operand in it if the 
    // other operand is not a Plus
    if (leftOperand->getType() == smType::Plus and
        rightOperand->getType() != smType::Plus) 
    {
        argument = leftOperand->getVectorArgument();
        nArgs = argument.size();
        insert(rightOperand);
    }
    else if (rightOperand->getType() == smType::Plus and
             leftOperand->getType() != smType::Plus) 
    {
        argument = rightOperand->getVectorArgument();
        nArgs = argument.size();
        insert(leftOperand);
    }
    else {
        nArgs = 2;
        argument = vector<Expr>(2);
        argument[0] = leftOperand;
        argument[1] = rightOperand;
        mergeTerms();
    }
    selfCheckIndexStructure();
}

Expr Plus::getRealPart()
{
    // Real part sum of real parts of arguments
    Expr realPart = ZERO;
    for (int i=0; i<nArgs; i++)
        realPart = plus_(realPart, argument[i]->getRealPart());

    return realPart;
}

Expr Plus::getImaginaryPart() const
{
    // Imaginary part sum of imaginary parts of arguments
    Expr imaginaryPart = ZERO;
    for (int i=0; i<nArgs; i++)
        imaginaryPart = plus_(imaginaryPart,
                              argument[i]->getImaginaryPart());

    return imaginaryPart;
}

Expr Plus::getComplexModulus()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
     
    return pow_(plus_(pow_(real,int_(2)),
                      pow_(im,int_(2))),
                double_(0.5));
}

Expr Plus::getComplexArgument()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();

    return make_shared<Angle>(im,real);
}

IndexStructure Plus::getIndexStructure() const
{
    // If the expression has a non trivial index structure, we suppose 
    // (the program should maintain that property) that all arguments have the 
    // same structure, in particular the first
    if (nArgs > 0)
        return argument[0]->getIndexStructure();

    return IndexStructure();
}

void Plus::selfCheckIndexStructure() const
{
    // Checking if all terms have the same indexStructure.
    if (nArgs == 0) return;
    IndexStructure structure = argument[0]->getIndexStructure();
    for (const_iter arg=1+argument.begin(); arg!=argument.end(); ++arg)
        if (structure != (**arg).getIndexStructure())
            callError(smError::InvalidIndicialSum,
                    "Plus::selfCheckIndexStructure() const");
}

void Plus::insert(const Expr& expr, bool side)
{
    if (nArgs == 0) {
        nArgs++;
        argument.insert(argument.begin(), expr);
        return;
    }
    if (expr->getPrimaryType() == smType::Numerical) {
        // If the inserted expression is numerical, it's easy
        if (argument[0]->getPrimaryType() == smType::Numerical)
            argument[0] = argument[0]->addition_own(expr);
        else {
            argument.insert(argument.begin(), expr);
            ++nArgs;
        }

        if (*argument[0] == ZERO) {
            argument.erase(argument.begin());
            --nArgs;
        }
        return;
    }

    // If not numerical, we search for a similar term
    Expr term = expr->getTerm();
    Expr numericalFact = expr->getNumericalFactor();
    Expr term2;
    for (iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        term2 = (*arg)->getTerm();
        if (*term == term2) {
            *arg = times_((*arg)->getNumericalFactor()->addition_own(numericalFact),
                          term);
            if (**arg == ZERO) {
                // x-x = 0
                arg = argument.erase(arg);
                --nArgs;
            }
            return;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    // with respect to its simplicity
    for (const_iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        if (expr < *arg) {
            argument.insert(arg, expr);
            ++nArgs;
            return;
        }
    }

    // no term is more complicated than expr, we put it at the end
    argument.push_back(expr);
    ++nArgs;
}

void Plus::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        cout<<"(";
    for (int i=0; i<nArgs; i++) {
        argument[i]->print(1);
        if (i < nArgs-1)
            cout<<" + ";
    }
    if (mode > 1)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Plus::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    for (int i=0; i<nArgs; i++) {
        sout<<argument[i]->printLaTeX(1);
        if (i < nArgs-1)
            sout<<"+";
    }
    if (mode > 1)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Plus::evaluateScalar() const
{
    double sum=0;
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getDim() > 0) 
            // if the sum contains a non-scalar term, the function returns 0.
            return 0;
        sum += argument[i]->evaluateScalar();
    }
    return sum;
}

bool Plus::contractIndex(const Index& indexToContract,
                         const Index& newIndices)
{
    bool contracted = false;
    for (auto& arg : argument) {
        if (not arg->contractIndex(indexToContract, newIndices)) {
            if (not contracted)
                return false;
            else
                callError(smError::BadContraction,
                        "Plus::contractIndex(const Index&, const Index&)",
                        indexToContract);
        }
        else 
            contracted = true;
    }
}

Expr Plus::evaluate()
    // Evaluates the expression replacing valued Variables and constants by
    // their values
{
    bool number = true;
    Expr numericalRes = ZERO;
    Expr result = ZERO;
    Expr foo;
    // In the loop we keep track separately of numbers and expression that do not
    // evaluate to numbers to save time.
    for (int i=0; i<nArgs; i++) {
        foo = argument[i]->evaluate();
        if (foo->getPrimaryType() == smType::Numerical)
            numericalRes = numericalRes->addition_own(foo);
        else {
            result = plus_(result, foo);
            number = false;
        }
    }
    if (number) 
        return numericalRes;

    return plus_(numericalRes,result);
}
bool Plus::mergeTerms()
    // Merges similar terms: numbers and identical terms to a numerical factor
    // (2*x ~ x etc). Ex: 2 + 2*x + 1/2 + 1/2*x -> 5/2 + 5/2*x.
{
    bool simplified = false;
    shared_ptr<Abstract> arg;

    // Here we check if there are Plus terms in the arguments, we flatten the 
    // whole thing to have only non-plus arguments.
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == smType::Plus) { // Plus(Plus(.. 
            int t_nArgs = argument[i]->getNArgs();
            vector<shared_ptr<Abstract> > t_argument =
                        argument[i]->getVectorArgument();
            for (int j=0; j<nArgs; j++)
                if (i != j)
                    t_argument.push_back(argument[j]);

            i += t_nArgs-1;
            nArgs += t_nArgs-1;
            argument = t_argument;
        }
    }

    // Here is the merge of numbers in the expression (for example 3+x+2 = 5+x)
    nArgs = argument.size();
    bool numericalFactor = (argument[0]->getPrimaryType() == smType::Numerical);
    for (int i=numericalFactor; i<nArgs; i++) {
        if (argument[i]->getPrimaryType() == smType::Numerical) {
            if (!numericalFactor) {
                shared_ptr<Abstract> foo = argument[i];
                argument.erase(argument.begin()+i);
                argument.insert(argument.begin(),foo);
                numericalFactor = true;
                i--;
            }
            else {
                argument[0] = argument[0]->addition_own(argument[i]);
                argument.erase(argument.begin()+i);
                nArgs--;
                i--;
            }
        }
    }

    // If the numerical factor is zero we delete it: 0+x = x
    if (numericalFactor and *argument[0] == ZERO and nArgs > 1) {
        numericalFactor = false;
        argument.erase(argument.begin());
        nArgs--;
    }

    // Check for identical terms in the sum, x + 2*x = 3*x
    shared_ptr<Abstract> term;
    shared_ptr<Abstract> term2;
    shared_ptr<Abstract> factor;
    for (int i=numericalFactor; i<nArgs-1; i++) {
        term = argument[i]->getTerm();
        factor = argument[i]->getNumericalFactor();
        bool matched = false;
        for (int j=i+1; j<nArgs; j++) {
            term2 = argument[j]->getTerm();
            if (*term==term2) {
                factor = factor->addition_own(argument[j]->getNumericalFactor());
                matched = true;
                argument.erase(argument.begin()+j);
                j--;
                nArgs--;
            }
        }
        if (matched) {
            argument[i] = times_(factor, term);
            if (*argument[i] == ZERO) {
                argument.erase(argument.begin()+i);
                i--;
                nArgs--;
            }
        }
    }
    orderTerms();

    return simplified;
}

void Plus::orderTerms()
    // Sorts the different arguments by simplicity, ex x*y+2 -> 2+x*y
{
    // The sort function of <algorithm> header uses the operator< between 
    // Expr, that is defined as the simplicity order. Therefore it sorts 
    // the arguments by order of simplicity
    sort(argument.begin(), argument.end());
    return;
}

Expr Plus::derive(const Expr& expr)
{
    // Derivative is the sum of the derivatives of arguments
    Expr rep = ZERO;
    for (int i=0; i<nArgs; i++)
        rep = plus_(rep,argument[i]->derive(expr));

    return rep;
}

Expr Plus::factor(bool full)
    // We try to factor the sum without knowing a specific factor
{
    if (nArgs == 0) return ZERO;
    vector<Expr > arg = argument;
    // If full, we factor first the arguments independently
    if (full) {
        for (int i=0; i<nArgs; i++)
            arg[i] = arg[i]->factor(full);
    }

    // We start to ask each term how many factors are possible for it
    // We take then the factors from the term that has the smaller number
    // of possible factors.
    Expr result = plus_(arg);
    int mini = 0;
    int nFactorsMini = arg[0]->getNFactor();
    for (int i=1; i<nArgs; i++) {
        if (nFactorsMini > arg[i]->getNFactor()) {
            mini = i;
            nFactorsMini = arg[i]->getNFactor();
        }
    }

    // For each factor we found, we keep only those which are possible
    // for all the arguments of the sum.
    vector<Expr > factors = arg[mini]->getFactors();
    if (factors.size() == 0) factors = vector<Expr >(1,arg[mini]);
    for (int i=0; i<nArgs; i++) {
        if (i != mini) {
            for (size_t j=0; j<factors.size(); j++) {
                if (!arg[i]->askTerm(factors[j])) {
                    factors.erase(factors.begin()+j);
                    j--;
                }
            }
            if (factors.size() == 0) 
                break;
        }
    }
    if (factors.size() == 0) 
        return result;

    // Here we clear redundant factors, i.e. different powers of the same object.
    // For example if x, x^2, x^3 are possible we only keep x^3.
    Expr exponent_i;
    Expr exponent_j;
    for (size_t i=0; i<factors.size(); i++) {
        if (factors[i]->getType() == smType::Pow) {
            exponent_i = factors[i]->getArgument(1);
            if (exponent_i->getPrimaryType() != smType::Numerical) {
                factors.erase(factors.begin()+i);
                i--;
                break;
            }

            for (size_t j=0; j<factors.size(); j++) {
                if (i != j) {
                    if (factors[j]->getType() == smType::Pow) {
                        exponent_j = factors[j]->getArgument(1);
                        if (exponent_j->getPrimaryType() != smType::Numerical){
                            factors.erase(factors.begin()+j);
                            if (i > j)
                                i--;
                            break;
                        }
                        if (abs(exponent_i->evaluateScalar()) <
                                abs(exponent_j->evaluateScalar()))
                        {
                            factors.erase(factors.begin()+i);
                            i--;
                            break;
                        }
                        factors.erase(factors.begin()+j);
                        if (i > j)
                            i--;
                        break;
                    }
                    else if (*factors[j] == factors[i]->getArgument(0)) {
                        if (abs(exponent_i->evaluateScalar()) > 1) {
                            factors.erase(factors.begin()+j);
                            if (i > j)
                                i--;
                            break;
                        }
                        factors.erase(factors.begin()+j);
                        if (i > j)
                            i--;
                        break;
                    }
                }
            }
        }
    }

    // Finally, if there is some factors left, we factor them out of the
    // expression
    Expr expr;
    Expr newAbstract;
    for (size_t j=0; j<factors.size(); j++) {
        expr = factors[j];
        newAbstract = ZERO;
        for (int i=0; i<nArgs; i++) {
            if (*arg[i]==expr)
                arg[i] = int_(1);
            else {
                int type = arg[i]->getType();
                if (type == smType::Times or type == smType::Pow) {
                    if (arg[i]->askTerm(expr))
                        arg[i] = arg[i]->suppressTerm(expr);
                    else
                        return Copy(this);
                }
                else
                    Copy(this);
            }
        }
    }

    return times_(times_(factors),plus_(arg));
}

Expr Plus::factor(const Expr& expr, bool full)
    // This function tries to factor the sum with respect to a particular
    // expression
{

    // If (full) we first factor recursively the arguments independently
    vector<Expr > arg = argument;
    if (full)
        for (int i=0; i<nArgs; i++)
            arg[i] = arg[i]->factor(expr, true);

    // Here we test the factor for each argument (if it is a valid factor)
    Expr newAbstract = ZERO;
    vector<int> toFactor(0);
    for (int i=0; i<nArgs; i++) {
        if (*arg[i] == expr)
            toFactor.push_back(i);
        else {
            int type = arg[i]->getType();
            if (type == smType::Times or type == smType::Pow) {
                if (arg[i]->askTerm(expr))
                    toFactor.push_back(i);
                else
                    newAbstract = plus_(newAbstract, arg[i]);
            }
            else
                newAbstract = plus_(newAbstract, arg[i]);
        }
    }

    // If the number of arguments that can be factored is greater than 2, 
    // We factor them
    if (toFactor.size() >= 2) {
        Expr factored = ZERO;
        for (size_t i=0; i<toFactor.size(); i++)
            factored = plus_(factored, arg[toFactor[i]]->suppressTerm(expr));
        newAbstract = plus_(newAbstract, times_(expr, factored));

        return newAbstract;
    }
    else
        return plus_(arg);
}

int Plus::getParity(const Expr& t_variable) const
{
    // The parity of a sum is the parity of its arguments if they
    // all have the same
    int parity = argument[0]->getParity(t_variable);
    if (parity == 0)
        return 0;

    for (int i=1; i<nArgs; i++)
        if (parity != argument[i]->getParity(t_variable))
            return 0;

    return parity;
}

bool Plus::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (nArgs == 1) 
        return *argument[0]==expr;
    if (expr->getType() == smType::Polynomial)
        return *this==expr->getRegularExpression();
    if (expr->getType() != smType::Plus) 
        return false;
    if (nArgs != expr->getNArgs()) 
        return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++) 
        indicesLeft[i] = i;

    for (int i=0; i<nArgs; i++) {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++) {
            if (*argument[i] == expr->getArgument(indicesLeft[j])) {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched)
            return false;
    }

    return true;
}

Expr plus_(const Expr& leftOperand, const Expr& rightOperand)
    // Creates a Plus object a priori but can return other types
    // in particular cases
{
    if (leftOperand->getPrimaryType() == smType::Vectorial)
        return leftOperand->addition_own(rightOperand);
    if (rightOperand->getPrimaryType() == smType::Vectorial)
        return rightOperand->addition_own(leftOperand);
    if (leftOperand->getType() == smType::Polynomial)
        return leftOperand->addition_own(rightOperand);
    if (rightOperand->getType() == smType::Polynomial)
        return rightOperand->addition_own(leftOperand);

    Expr foo = make_shared<Plus>(leftOperand, rightOperand);
    if (foo->getNArgs() == 1) {
        Expr foo2 = foo->getArgument();
        return foo2;
    }
    else if (foo->getNArgs() == 0)
        return ZERO;

    return foo;
}

Expr plus_(const vector<Expr >& operands)
{
    if (operands.size() == 0)
        return ZERO;
    if (operands[0]->getPrimaryType() == smType::Vectorial) {
        Expr foo = highDTensor_(operands);
        return foo->trace(0,0);
    }
    Expr foo = make_shared<Plus>(operands);
    if (foo->getNArgs() == 1) {
        Expr foo2 = foo->getArgument();
        return foo2;
    }
    else if (foo->getNArgs() == 0)
        return ZERO;

    return foo;
}

Expr minus_(const Expr& leftOperand, const Expr& rightOperand) {
    // minus(a,b) = plus(a,-b)
    return plus_(leftOperand,times_(int_(-1),rightOperand));
}

///////////////////////////////////////////////////
/*************************************************/
// Class Times                                   //
/*************************************************/
///////////////////////////////////////////////////

Times::Times(const vector<Expr >& operands, bool explicitTimes)
    :AbstractMultiFunc()
{
    nArgs = operands.size();
    argument = operands;
    if (not explicitTimes and nArgs > 0)
        mergeTerms();
    else 
        orderTerms();
    nArgs = argument.size();
}

Times::Times(const Expr& leftOperand,
             const Expr& rightOperand,
             bool explicitTimes): AbstractMultiFunc()
{
    if (leftOperand->getType() == smType::Times and
        rightOperand->getType() != smType::Times) 
    {
        argument = leftOperand->getVectorArgument();
        nArgs = argument.size();
        insert(rightOperand, true); // rightOperand inserted to the right
                                    // of leftOperand
        if (rightOperand->getPrimaryType() == smType::Indicial)
            selfCheckIndexStructure();
    }
    else if (rightOperand->getType() == smType::Times and
             leftOperand->getType() != smType::Times)    
    {
        argument = rightOperand->getVectorArgument();
        nArgs = argument.size();
        insert(leftOperand, false); // leftOperand inserted to the left
                                    // of rightOperand
        if (leftOperand->getPrimaryType() == smType::Indicial)
            selfCheckIndexStructure();
    }
    else {
        nArgs = 2;
        argument = vector<Expr>(2);
        argument[0] = leftOperand;
        argument[1] = rightOperand;
        if (not explicitTimes)
            mergeTerms();
        else 
            orderTerms();
        selfCheckIndexStructure();
    }
}

Expr Times::getNumericalFactor() const
{
    if (argument[0]->getPrimaryType() == smType::Numerical)
        return argument[0];

    return int_(1);
}

Expr Times::getTerm()
{
    if (argument[0]->getPrimaryType() == smType::Numerical) {
        vector<Expr > foo(argument);
        foo.erase(foo.begin());
        return times_(foo);
    }

    return Copy(this);
}

int Times::getNFactor() const
{
    int nFactor = 1;
    for (int i=0; i<nArgs; i++)
        nFactor *= argument[i]->getNFactor();

    return nFactor;
}

vector<Expr > Times::getFactors() const
{
    vector<Expr > foo(0), foo2;
    for (int i=0; i<nArgs; i++) {
        foo2 = argument[i]->getFactors();
        if (foo2.size() == 0) foo2 = vector<Expr >(1,argument[i]);
        foo.insert(foo.end(), foo2.begin(), foo2.end());
    }
    return foo;
}

bool Times::askTerm(const Expr& expr, bool exact) const
{
    for (int i=0; i<nArgs; i++) {
        if (*argument[i]==expr) 
            return true;
        else if (!exact and argument[i]->getType() == smType::Pow and // Pow
                 argument[i]->askTerm(expr))
            return true;
    }

    return false;
}

Expr Times::suppressTerm(const Expr& expr) const
{
    shared_ptr<Abstract> newAbstract = int_(1);
    bool matched = false;
    for (int i=0; i<nArgs; i++) {
        if (not matched) {
            if (argument[i]->getType() == smType::Pow) { // Pow 
                if (argument[i]->askTerm(expr)) {
                    newAbstract = times_(newAbstract,
                                         argument[i]->suppressTerm(expr));
                    matched = true;
                    continue;
                }
                else
                    newAbstract = times_(newAbstract, argument[i]);
            }
            else if (*argument[i]==expr) {
                matched = true;
                continue;
            }
            else
                newAbstract = times_(newAbstract, argument[i]);
        }
        else
            newAbstract = times_(newAbstract, argument[i]);
    }

    return newAbstract;
}

IndexStructure Times::getIndexStructure() const
{
    if (isIndexed()) {
        IndexStructure structure;
        for (auto arg=argument.rbegin(); arg!=argument.rend(); ++arg) {
            if ((**arg).isIndexed())
                structure += (**arg).getIndexStructure();
            else 
                break;
        }

        return structure;
    }

    return IndexStructure();
}

void Times::selfCheckIndexStructure()
{
    // Check the indexStructure of a product and apply Einstein's convention
    // in the case of a repeated index. This algorithm is O(N^2) with N the
    // total number of indices in the product (check for each index if it is
    // present elsewhere.

    //Structure of each argument in a vector
    vector<IndexStructure> structure(0);
    //For each argument
    for (iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        if ((*arg)->isIndexed()) {
            // We get its structure in fooStruct
            IndexStructure fooStruct = (*arg)->getIndexStructure();
            // Now we check for each new index if it is present before in
            // the structure, in which case we contract it
            // (Einstein's convention).
            // For each new index: 
            for (int k=0; k!=fooStruct.getNIndices(); ++k) {
                //For each former structure (former arguments)
                for (size_t i=0; i!=structure.size(); ++i) {
                    const int nIndices = structure[i].getNIndices();
                    bool breakValue = false;
                    // For each index in the structure
                    for (int j=0; j!=nIndices; ++j) {
                        // If the index is already present
                        if (structure[i][j] == fooStruct[k]
                                and fooStruct[k].getFree()) {
                            structure[i][j].setFree(false);
                            // We replace fooStruct[k] (not contracted)
                            // by structure[i][j] (contracted).
                            // If the contraction is not valid, we raise an 
                            // error.
                            if (not argument[i]->contractIndex(fooStruct[k],
                                                               structure[i][j]))
                                callError(smError::BadContraction,
                                        "Times::selfCheckIndexStructure()",
                                        fooStruct[k]);
                            if (not (*arg)->contractIndex(fooStruct[k],
                                                          structure[i][j]))
                                callError(smError::BadContraction,
                                        "Times::selfCheckIndexStructure()",
                                        fooStruct[k]);

                            fooStruct[k].setFree(false);
                            breakValue = true;
                            break;
                        }
                    }
                    if (breakValue)
                        break;
                }
            }
            // We add fooStruct to the vector of structures
            structure.push_back(fooStruct);
        }
    }
}

Expr Times::getRealPart()
{
    Expr realPart = argument[0]->getRealPart();
    Expr imaginaryPart = argument[0]->getImaginaryPart();
    Expr foo;
    for (int i=1; i<nArgs; i++) {
        foo = Copy(realPart);
        realPart = plus_(times_(realPart,argument[i]->getRealPart()),
                         times_(int_(-1),
                                times_(imaginaryPart,
                                       argument[i]->getImaginaryPart())));
        if (i < nArgs-1)
            imaginaryPart = plus_(times_(foo,argument[i]->getImaginaryPart()),
                                  times_(imaginaryPart,
                                         argument[i]->getRealPart()));
    }

    return realPart;
}

Expr Times::getImaginaryPart() const
{
    Expr realPart = argument[0]->getRealPart();
    Expr imaginaryPart = argument[0]->getImaginaryPart();
    Expr foo;
    for (int i=1; i<nArgs; i++) {
        foo = Copy(realPart);
        if (i < nArgs-1)
            realPart = plus_(times_(realPart,argument[i]->getRealPart()),
                             times_(int_(-1),
                                    times_(imaginaryPart,
                                           argument[i]->getImaginaryPart())));
        imaginaryPart = plus_(times_(foo,argument[i]->getImaginaryPart()),
                              times_(imaginaryPart, argument[i]->getRealPart()));
    }

    return imaginaryPart;
}

Expr Times::getComplexModulus()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
    return pow_(plus_(pow_(real,int_(2)),pow_(im,int_(2))), double_(0.5));
}

Expr Times::getComplexArgument()
{
    Expr real = getRealPart();
    Expr im = getImaginaryPart();
    return make_shared<Angle>(im,real);
}

void Times::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 2) // Priority lesser than the previous operation: brackets
        cout<<"(";
    vector<int> denominatorIndices(0);
    vector<int> numeratorIndices(0);
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == smType::Pow and
            argument[i]->getArgument(1)->isInteger() and
            argument[i]->getArgument(1)->evaluateScalar() == -1)
            denominatorIndices.push_back(i);
        else
            numeratorIndices.push_back(i);
    }
    for (size_t i=0; i<numeratorIndices.size(); i++) {
        argument[numeratorIndices[i]]->print(2);
        if (i <numeratorIndices.size() - 1)
            cout<<"*";
    }
    if (denominatorIndices.size() > 0) {
        cout<<"/";
        if (denominatorIndices.size() == 1)
            argument[denominatorIndices[0]]->getArgument(0)->print(3);
        else {
            cout<<"(";
            for(size_t i=0; i<denominatorIndices.size(); i++) {
                argument[denominatorIndices[i]]->getArgument(0)->print(2);
                if (i < denominatorIndices.size()-1)
                    cout<<"*";
            }
            cout<<")";
        }
    }
    if (mode > 2)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Times::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 2) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    for (int i=0; i<nArgs; i++)
    {
        sout<<argument[i]->printLaTeX(2);
        if (i < nArgs-1)
            if (argument[i+1]->getType() == smType::Fraction or
                argument[i+1]->getType() == smType::CFraction or
                (argument[i]->getPrimaryType() < 10 and
                 argument[i+1]->getPrimaryType() >= 10))
                sout<<"\\cdot ";
    }
    if (mode > 2)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

void getExponentStructure(const Expr& argument, Expr& term, Expr& exponent)
    // Search for argument = term^exponent (default argument = argument^1)
    // This function is used assuming that exponent is Numerical
    // Therefore exponent must always be Numerical
{
    if (argument->getType() == smType::Pow) {
        exponent = argument->getArgument(1);
        if (exponent->getPrimaryType() != smType::Numerical) {
            exponent = ONE;
            term = argument;
        }
        else term = argument->getArgument(0);
    }
    else {
        term = argument;
        exponent = ONE;
    }
}

// side = 0 insertion to the Left, = 1 to the right.
void Times::insert(const Expr& expr, bool side)
{
    if (nArgs == 0) {
        nArgs++;
        argument.insert(argument.begin(), expr);
        return;
    }
    // If numerical, easy
    if (expr->getPrimaryType() == smType::Numerical) {
        if (argument[0]->getPrimaryType() == smType::Numerical)
            argument[0] = argument[0]->multiplication_own(expr);
        else {
            argument.insert(argument.begin(), expr);
            ++nArgs;
        }
        if (*argument[0] == ZERO) {
            argument.clear();
            argument.push_back(ZERO);
            nArgs = 1;
        }
        else if (*argument[0] == ONE) {
            argument.erase(argument.begin());
            --nArgs;
        }
        return;
    }

    if (expr->getType() == smType::Derivative 
            and expr->isEmpty()
            and not side) {
        if (*expr->getArgument(0) == ONE)
            argument = vector<Expr>(1,derivative_(Copy(this),
                        expr->getArgument(1),
                        expr->getOrder()));
        else 
            argument =  vector<Expr>(1,derivative_(
                        expr->getArgument(0)*Copy(this),
                        expr->getArgument(1),
                        expr->getOrder()));
        nArgs = 1;
        return;
    }
                
    if (side) rightInsert(expr);
    else      leftInsert (expr);
}
void Times::leftInsert(const Expr& expr)
{
    // If not numerical, we search for a similar term
    int max = nArgs;
    Expr term, exponent;
    getExponentStructure(expr, term, exponent);
    for (int i=0; i<nArgs; i++) {
        Expr term2, exponent2;
        getExponentStructure(argument[i], term2, exponent2);
        if (*Commutation(expr, argument[i]) == ZERO) {
            // If we found the right term, it's done
            if (*term == term2) {
                argument[i] = pow_(term, exponent->addition_own(exponent2));
                if (*argument[i] == ONE) {
                    argument.erase(argument.begin()+i);
                    --nArgs;
                }
                return;
            }
        }
        else if (*term == term2) {
            argument[i] = pow_(term, exponent->addition_own(exponent2));
            if (*argument[i] == ONE) {
                argument.erase(argument.begin()+i);
                --nArgs;
            }
            return;
        }
        else {
            // max is the position not reachable because of commutation not trivial
            max = i;
            break;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    for (int i=0; i<max; i++) 
        if (expr < argument[i] or *Commutation(expr, argument[i]) != ZERO) {
            ++nArgs;
            argument.insert(argument.begin()+i, expr);
            return;
        }

    // no term is more complicated than expr, we put it at the end
    argument.insert(argument.begin()+max, expr);
    ++nArgs;
}
void Times::rightInsert(const Expr& expr)
{
    // If not numerical, we search for a similar term
    int max = -1;
    Expr term, exponent;
    getExponentStructure(expr, term, exponent);
    for (int i=nArgs-1; i>=0; --i) {
        Expr term2, exponent2;
        getExponentStructure(argument[i], term2, exponent2);
        if (*Commutation(expr, argument[i]) == ZERO) {
            // If we found the right term, it's done
            if (*term == term2) {
                argument[i] = pow_(term, exponent->addition_own(exponent2));
                if (*argument[i] == ONE) {
                    argument.erase(argument.begin()+i);
                    --nArgs;
                }
                return;
            }
        }
        else if (*term == term2) {
            argument[i] = pow_(term, exponent->addition_own(exponent2));
            if (*argument[i] == ONE) {
                argument.erase(argument.begin()+i);
                --nArgs;
            }
            return;
        }
        else {
            // max is the position not reachable because of commutation not trivial
            max = i;
            break;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    for (int i=nArgs-1; i>max; --i)  {
        if (expr > argument[i] or *Commutation(expr, argument[i]) != ZERO) {
            ++nArgs;
            argument.insert(argument.begin()+i+1, expr);
            return;
        }
    }

    // no term is more complicated than expr, we put it at the end
    argument.insert(argument.begin()+max+1, expr);
    ++nArgs;
}


double Times::evaluateScalar() const
{
    double product=1;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getDim() > 0) return 0;
        product *= argument[i]->evaluateScalar();
    }
    return product;
}

Expr Times::evaluate()
{
    bool number = true;
    Expr numericalRes = ONE;
    Expr result = int_(1);
    for (int i=0; i<nArgs; i++) {
        const Expr foo = argument[i]->evaluate();
        if (foo->getPrimaryType() == smType::Numerical)
            numericalRes = numericalRes->multiplication_own(foo);
        else {
            result = times_(result, foo);
            number = false;
        }
    }
    if (number) return numericalRes;
    else        return times_(numericalRes,result);
}

bool Times::mergeTerms()
{
    bool simplified = false;
    nArgs = argument.size();
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == smType::Times) { 
            vector<shared_ptr<Abstract> > t_argument =
                argument[i]->getVectorArgument();

            for (int j=i-1; j>=0; --j)
                t_argument.insert(t_argument.begin(),argument[j]);
            for (int j=i+1; j<nArgs; ++j)
                t_argument.push_back(argument[j]);
            nArgs += argument[i]->getNArgs()-1;
            i += argument[i]->getNArgs()-1;
            argument = t_argument;
        }
    }
    bool numericalFactor = (argument[0]->getPrimaryType() == smType::Numerical);
    for (int i=numericalFactor; i<nArgs; i++) {
        if (argument[i]->getPrimaryType() == smType::Numerical) {
            if (!numericalFactor) {
                shared_ptr<Abstract> foo = argument[i];
                argument.erase(argument.begin()+i);
                argument.insert(argument.begin(),foo);
                numericalFactor = true;
                i--;
            }
            else {
                argument[0] = argument[0]->multiplication_own(argument[i]);
                argument.erase(argument.begin()+i);
                nArgs--;
                i--;
            }
        }
    }
    if (numericalFactor and argument[0]->evaluateScalar()==1 and nArgs > 1) {
        argument.erase(argument.begin());
        nArgs--;
    }
    else if (numericalFactor and argument[0]->evaluateScalar()==0) {
        argument = vector<shared_ptr<Abstract>>(1);
        argument[0] = ZERO;
        nArgs = 1;
        return false;
    }
    shared_ptr<Abstract> term, term2;
    shared_ptr<Abstract> factor, factor2;
    bool matched;
    for (int i=numericalFactor; i<nArgs-1; i++) {
        factor = ONE;
        if (argument[i]->getType() == smType::Pow) { //Pow 
            term = argument[i]->getArgument(1);
            if (term->getPrimaryType() == smType::Numerical) {
                factor = term;
                term = argument[i]->getArgument();
            }
            else 
                term = argument[i];
        }
        else term = argument[i];
        //bool indicial = (argument[i]->getPrimaryType() == smType::Indicial);

        ///// 
        // Must merge the two conditions with new commutability !!
        /*if (false and argument[i]->getCommutable()) {
            if (indicial) {
                for (int j=i+1; j<nArgs; j++) {
                    if (argument[j]->getPrimaryType() == smType::Indicial) {
                        argument[i] = make_shared<ITerm>(argument[i], argument[j]);
                        argument.erase(argument.begin()+j);
                        j--;
                        nArgs--;
                    }
                }
            }
            else {
                for (int j=i+1; j<nArgs; j++) {
                    factor2 = ONE;
                    if (argument[j]->getType() == smType::Pow) { //Pow
                        term2 = argument[j]->getArgument(1);
                        if (term2->getPrimaryType() == smType::Numerical) {
                            factor2 = term2;
                            term2 = argument[j]->getArgument();
                        }
                        else 
                            term2 = argument[j];
                    }
                    else term2 = argument[j];
                    if (*term==term2) {
                        factor = factor->addition_own(factor2);
                        matched = true;
                        argument.erase(argument.begin()+j);
                        j--;
                        nArgs--;
                    }
                }
            }
        }*/
        /*if (indicial) { for (int j=i+1; j<nArgs; j++) {
                if(*Commutation(argument[i],argument[j]) != ZERO)
                    break;
                if (argument[j]->getPrimaryType() == smType::Indicial) {
                    argument[i] = make_shared<ITerm>(argument[i], argument[j]);
                    argument.erase(argument.begin()+j);
                    j--;
                    nArgs--;
                }
            }
        }*/
        for (int j=i+1; j<nArgs; j++) {
            if(*Commutation(argument[i], argument[j]) != ZERO)
                break;
            factor2 = ONE;
            if (argument[j]->getType() == smType::Pow) {  //Pow
                term2 = argument[j]->getArgument(1);
                if (term2->getPrimaryType() == smType::Numerical) {
                    factor2 = term2;
                    term2 = argument[j]->getArgument();
                }
                else 
                    term2 = argument[j];
            }
            else term2 = argument[j];
            if (*term==term2) {
                factor = factor->addition_own(factor2);
                matched = true;
                argument.erase(argument.begin()+j);
                j--;
                nArgs--;
            }
        }
        if (matched) {
            argument[i] = pow_(term, factor);
            if (*argument[i] == ONE and nArgs > 1){
                argument.erase(argument.begin()+i);
                --i;
                --nArgs;
            }
            simplified = true;
        } 
    }

    orderTerms();
    return simplified;
}

void Times::orderTerms() 
{
    if (getCommutable()) {
        sort(argument.begin(), argument.end());
        return;
    }
    Expr foo;
    for (int i=0; i<nArgs-1; i++) {
        int simpler = i;
        if (not argument[i]->getCommutable())
            continue;
        for (int j=i+1; j<nArgs; j++) {
            if (not argument[j]->getCommutable()) 
                break;
            if (*argument[j] < argument[simpler]) // argument[j] simpler
                simpler = j;
        }
        if (simpler != i) {
            foo = argument[i];
            argument[i] = argument[simpler];
            argument[simpler] = foo;
        }
    }
}

Expr Times::derive(const Expr& expr)
{
    if (expr == nullptr) return ZERO;
    Expr rep = ZERO;
    Expr intermediateResult = nullptr;
    for (int i=0; i<nArgs; i++) {
        intermediateResult = int_(1);
        for (int j=0; j<nArgs; j++) {
           if (j != i)
               intermediateResult = times_(intermediateResult,
                                           argument[j]);
           else
               intermediateResult = times_(intermediateResult,
                                           argument[j]->derive(expr));
        } 
        rep = plus_(rep,intermediateResult);
    }

    return rep;
}

Expr Times::develop(bool full)
{
    Expr copy = Copy(this);
    if (full)
        for (int i=0; i<nArgs; i++)
            copy->setArgument(argument[i]->develop(true),i);
    vector<Expr > newAbstracts(1);
    newAbstracts[0] = int_(1);
    vector<Expr > foo(0);
    int nArgsBis;
    for (int i=0; i<nArgs; i++) {
        if (copy->getArgument(i)->getType() == smType::Plus) {
            nArgsBis = copy->getArgument(i)->getNArgs();
            for (int j=0; j<nArgsBis; j++)
                for (size_t k=0; k<newAbstracts.size(); k++)
                    foo.push_back(times_(newAbstracts[k],
                                         copy->getArgument(i)->getArgument(j)));

            newAbstracts = foo;
            foo.clear();
        }
        else {
            for (size_t j=0; j<newAbstracts.size(); j++)
                newAbstracts[j] = times_(newAbstracts[j], copy->getArgument(i));
        }
    }
    return plus_(newAbstracts);
}

int Times::isPolynomial(const Expr& expr) const
{
    bool polynomialTermFound = false;
    bool dependencyFound = false;
    int order = 0;
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->dependsExplicitelyOn(expr)) {
            order = argument[i]->isPolynomial(expr);
            if (order > 0) {
                for (int j=i+1; j<nArgs; ++j)
                    if (*Commutation(argument[j], expr) != ZERO) 
                        return 0;
                polynomialTermFound = true;
            }
            else 
                dependencyFound = true;
        }
    }
    if (polynomialTermFound and not dependencyFound)
        return order;
    return 0;
}

Expr Times::getPolynomialTerm(const Expr& t_variable, int order)
{
    int argument_order;
    Expr result = Copy(this);
    if (order == 0)
        return result;
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->dependsExplicitelyOn(t_variable)) {
            argument_order = argument[i]->isPolynomial(t_variable);
            if (order == argument_order) {
                Expr foo = argument[i]->suppressTerm(pow_(t_variable,
                                                          int_(order)));
                result->setArgument(foo,i);
                break;
            }
        }
    }

    return Refresh(result);
}

int Times::getParity(const Expr& t_variable) const
{
    int parity = 1;
    for (int i=0; i<nArgs; i++) {
        parity *= argument[i]->getParity(t_variable);
        if (parity == 0)
            return 0;
    }
    return parity;
}

bool Times::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())
        return true;
    if (nArgs == 1)
        return *argument[0]==expr;
    if (expr->getType() != smType::Times)
        return false;
    if (nArgs != expr->getNArgs())
        return false;

    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++)
        indicesLeft[i] = i;

    Expr foo;
    for (int i=0; i<nArgs; i++) {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++) {
            foo = expr->getArgument(indicesLeft[j]);
            if (!argument[i]-> getCommutable() and
                !foo->getCommutable() and
                *argument[i]!=foo)
                break;
            if (*argument[i] == foo) {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched) return false;
    }

    return true;
}

void applyDerivative(Expr& product)
{
    if (product->getType() != smType::Times)
        callError(smError::BadType,
                "applyDerivative(Expr& product)", smType::Times);

    const vector<Expr>& argument = product->getVectorArgument();
    for (const_iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        if ((*arg)->getType() == smType::Derivative
                and (*arg)->isEmpty()) {
            Expr left = ONE;
            Expr derivativeArgument = ONE;
            Expr right = ONE;
            if (arg != argument.begin())
                left = times_(vector<Expr>(argument.begin(),arg)); 
            if (arg+1 != argument.end())
                right = times_(vector<Expr>(arg+1, argument.end()));
            if (left->getType() == smType::Times)
                applyDerivative(left);
            if (right->getType() == smType::Times)
                applyDerivative(right);
            if (*right != ONE)
                product = left*(*arg*right);
            break;
        }
    }
}

Expr times_(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes)
{
    if (leftOperand->getType() == smType::Derivative and
        leftOperand->isEmpty()) {
        return derivative_(leftOperand->getArgument(0)*rightOperand,
                leftOperand->getArgument(1), leftOperand->getOrder());
    }
    if (leftOperand->getPrimaryType() == smType::Vectorial)
        return leftOperand->multiplication_own(rightOperand);
    if (rightOperand->getPrimaryType() == smType::Vectorial)
        return rightOperand->multiplication_own(leftOperand,0);

    if (leftOperand->getType() == smType::Polynomial) {
        if (rightOperand->getType() == smType::Polynomial and explicitTimes)
            return make_shared<Times>(leftOperand, rightOperand);
        return leftOperand->multiplication_own(rightOperand);
    }
    if (rightOperand->getType() == smType::Polynomial) {
        if (leftOperand->getType() == smType::Polynomial and explicitTimes)
            return make_shared<Times>(leftOperand, rightOperand);
        return rightOperand->multiplication_own(leftOperand,0);
    }

    if (leftOperand->getPrimaryType() == smType::Numerical) 
        if (rightOperand->getPrimaryType() == smType::Numerical) 
            return leftOperand->multiplication_own(rightOperand);

    Expr foo = make_shared<Times>(leftOperand, rightOperand, explicitTimes);
    applyDerivative(foo);
    if (foo->getPrimaryType() == smType::MultiFunction
            and foo->getNArgs() == 1)
        return foo->getArgument();
    if (foo->getPrimaryType() == smType::MultiFunction
            and foo->getNArgs() == 0)
        return int_(1);

    return foo;
}

Expr times_(const vector<Expr >& operands, bool explicitTimes)
{
    for (auto op=operands.begin(); op!=operands.end(); ++op) {
        // Checking if there is an Empty derivative in the arguments.
        if ((*op)->getType() == smType::Derivative 
                and (*op)->isEmpty()) {
            Expr left = ONE;
            if (op != operands.begin())
                left = times_(vector<Expr>(operands.begin(),op));
            Expr right = ONE;
            if (op+1 != operands.end())
                right = times_(vector<Expr>(op+1, operands.end()));
            return left*derivative_((*op)->getArgument(0)*right,
                    (*op)->getArgument(1), (*op)->getOrder());
        }
    }

    Expr result = make_shared<Times>(operands, explicitTimes);
    applyDerivative(result);
    if (result->getPrimaryType() == smType::MultiFunction
            and result->getNArgs() == 1)
        return result->getArgument();
    if (result->getPrimaryType() == smType::MultiFunction
            and result->getNArgs() == 0)
        return int_(1);

    return result;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Fraction                                //
/*************************************************/
///////////////////////////////////////////////////

Fraction::Fraction(const Expr& leftOperand, const Expr& rightOperand)
    :AbstractDuoFunc()
{
    argument[0] = leftOperand;
    argument[1] = rightOperand;
    mergeTerms();
}

int Fraction::getNFactor() const {
    return (max(1,argument[0]->getNArgs())+
            max(1,argument[1]->getNArgs()));
}

vector<Expr > Fraction::getFactors() const
{
    vector<Expr > foo = argument[0]->getFactors();
    vector<Expr > foo2 = argument[1]->getFactors();
    for (auto& arg_foo2: foo2)
        arg_foo2 = pow_(arg_foo2,int_(-1));

    foo.insert(foo.end(), foo2.begin(), foo2.end());
    return foo;
}

bool Fraction::askTerm(const Expr& expr, bool exact) const
{
    if (argument[0]->askTerm(expr))
        return true;
    if (argument[1]->askTerm(pow_(expr,int_(-1))))
        return true;

    return false;
}

Expr Fraction::suppressTerm(const Expr& expr) const
{
    if (argument[0]->askTerm(expr))
        return fraction_(argument[0]->suppressTerm(expr),
                         argument[1]);
    if (argument[1]->askTerm(pow_(expr,int_(-1))))
        return fraction_(argument[0],
                         argument[1]->suppressTerm(pow_(expr,int_(-1))));

    cout<<"Warning problem with factors in fraction, expr probably wrong...\n";
    return Copy(this);
}

void Fraction::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 3) // Priority lesser than the previous operation: brackets
        cout<<"(";
    argument[0]->print(3);
    cout<<"/";
    argument[1]->print(3);
    if (mode > 3)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Fraction::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 3) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    sout<<"\\frac{";
    sout<<argument[0]->printLaTeX(1);
    sout<<"}{";
    sout<<argument[1]->printLaTeX(1);
    sout<<"}";
    if (mode > 3)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Fraction::evaluateScalar() const
{
    if (argument[0]->getDim() > 0 or argument[1]->getDim() > 0)
        return 0;

    return argument[0]->evaluateScalar()/argument[1]->evaluateScalar();
}

Expr Fraction::evaluate()
{
    Expr foo1 = argument[0]->evaluate();
    Expr foo2 = argument[1]->evaluate();
    if (foo1->getPrimaryType() == smType::Numerical and
        foo2->getPrimaryType() == smType::Numerical)
        return foo1->division_own(foo2);

    return fraction_(foo1,foo2);
}

bool Fraction::mergeTerms()
{
    bool simplified = false;
    if (argument[0]->getType() == smType::Fraction) {
        if (argument[1]->getType() == smType::Fraction) {
            Expr foo = times_(argument[0]->getArgument(0),
                              argument[1]->getArgument(1));
            argument[1] = times_(argument[0]->getArgument(1),
                                 argument[1]->getArgument(0));
            argument[0] = foo;
        }
        else {
            argument[1] = times_(argument[0]->getArgument(1),argument[1]);
            argument[0] = argument[0]->getArgument();
        }
    }
    else if (argument[1]->getType() == smType::Fraction) {
        argument[0] = times_(argument[1]->getArgument(1),argument[0]);
        argument[1] = argument[1]->getArgument(0);
    }
    
    return simplified;
}

Expr Fraction::derive(const Expr& expr)
{
    if (expr == nullptr)
        return ZERO;

    return fraction_(minus_(times_(argument[0]->derive(expr),
                                   argument[1]),
                            times_(argument[0],
                                   argument[1]->derive(expr))),
                     pow_(argument[1],int_(2)));
}

int Fraction::isPolynomial(const Expr& expr) const
{
    if (argument[1]->isPolynomial(expr) == 0)
        return argument[0]->isPolynomial(expr);

    return 0;
}

Expr Fraction::getPolynomialTerm(const Expr& t_variable, int order)
{
    return fraction_(argument[0]->getPolynomialTerm(t_variable, order),
                    argument[1]);
}

int Fraction::getParity(const Expr& t_variable) const
{
    int parity = argument[0]->getParity(t_variable);
    if (parity == 0)
        return 0;

    return parity*argument[1]->getParity(t_variable);
}

bool Fraction::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())
        return true;
    if (expr->getType() != smType::Fraction)
        return false;

    if (*argument[0] != expr->getArgument(0) or
            *argument[1]!=expr->getArgument(1))
        return false;

    return true;
}

Expr fraction_(const Expr& leftOperand, const Expr& rightOperand)
{
    if (rightOperand->getPrimaryType() == smType::Numerical and 
            rightOperand->evaluateScalar() == 0)
        return INF;

    Expr foo = make_shared<Fraction>(leftOperand, rightOperand);
    Expr arg = foo->getArgument();
    Expr arg2 = foo->getArgument(1);
    if (arg->getPrimaryType() == smType::Numerical and 
            arg2->getPrimaryType() == smType::Numerical)
    {
        if (arg2->getType() == smType::CFraction)
            arg2 = _cfraction_(arg2->getDenom(), arg2->getNum());
        else if (arg2->isInteger())
            arg2 = _cfraction_(1, (int)arg2->evaluateScalar());
        else
            arg2 = double_(1./arg2->evaluateScalar());

        return arg->multiplication_own(arg2);
    }
    if (*arg == ZERO or *arg2 == ONE)
        return arg;
    if (rightOperand->isInteger())
        return times_(_cfraction_(1,rightOperand->evaluateScalar()),leftOperand);
    if (rightOperand->getType() == smType::CFraction)
        return times_(_cfraction_(rightOperand->getDenom(),
                                  rightOperand->getNum()),
                      leftOperand);

    if (*arg->getNumericalFactor() != int_(1)) {
        if (*arg2->getNumericalFactor() != int_(1))
            return times_(fraction_(arg->getNumericalFactor(),
                                    arg2->getNumericalFactor()),
                          fraction_(arg->getTerm(),
                                    arg2->getTerm()));
        else 
            return times_(arg->getNumericalFactor(),
                          fraction_(arg->getTerm(),
                                    arg2));
    }
    else if (*arg2->getNumericalFactor() != int_(1)) {
        return times_(fraction_(int_(1),
                                arg2->getNumericalFactor()),
                      fraction_(arg, 
                                arg2->getTerm()));
    }

    return times_(leftOperand,pow_(rightOperand,int_(-1)));
}

///////////////////////////////////////////////////
/*************************************************/
// Class Pow                                     //
/*************************************************/
///////////////////////////////////////////////////

Pow::Pow(const Expr& leftOperand, const Expr& rightOperand): AbstractDuoFunc()
{
    argument[0] = leftOperand;
    argument[1] = rightOperand;
    mergeTerms();
}

int Pow::getNFactor() const
{
    if (argument[1]->getPrimaryType() != smType::Numerical) return 1;
    return 2*floor(argument[1]->evaluateScalar())+1;
}

vector<Expr > Pow::getFactors() const
{
    //return Abstract::getFactors();
    if (argument[1]->getPrimaryType() != smType::Numerical)
        return Abstract::getFactors();
    vector<Expr > foo(0);
    if (argument[1]->getType() == smType::Integer or
            argument[1]->getType() == smType::Double)
    {
        int a = argument[1]->evaluateScalar();
        for (int i=sgn(a); abs(i)<=abs(a); i+=sgn(a))
            foo.push_back(pow_(argument[0],int_(i)));
    }
    else {
        int num = argument[1]->getNum();
        int denom = argument[1]->getDenom();
        if (num < 0) {
            if (denom < 0) {
                num = -num;
                denom = -denom;
            }
        }
        else if (denom < 0) {
            num = -num;
            denom = -denom;
        }
        for (int delta_num=0;
                sgn(num+delta_num)==sgn(num);
                delta_num-=sgn(num)*denom)
            foo.push_back(pow_(argument[0],_cfraction_(num+delta_num,denom)));

        if (PGCD(num,denom) != 1) {
            for (int i=sgn(num); abs(i)<abs(num*1.)/denom; i+=sgn(num))
                foo.push_back(pow_(argument[0], int_(i)));
        }
    }
    return foo;
}

bool Pow::askTerm(const Expr& expr, bool exact) const
{
    if (exact) return ((*this)==expr);
    if (expr->getType() == smType::Pow) {
        Expr a = expr->getArgument(1);
        Expr b = argument[1];
        if (*argument[0] != expr->getArgument(0))
            return false;
        if (*a == b)
            return true;
        if (a->getPrimaryType() != smType::Numerical or 
                b->getPrimaryType() != smType::Numerical)
            return false;

        if (a->getType() == smType::Integer or a->getType() == smType::Double){
            double a_val = a->evaluateScalar();
            double b_val = b->evaluateScalar();

            return (abs(b_val)>abs(a_val) and sgn(a_val)==sgn(b_val));
        }
        else if (a->getType() == smType::CFraction) {
            int a_denom = a->getDenom();
            int b_denom = b->getDenom();
            double a_val = a->evaluateScalar();
            double b_val = b->evaluateScalar();
            return (a_denom==b_denom and
                    abs(a_val)<abs(b_val) and
                    sgn(a_val)==sgn(b_val));
        }
        return ((*this)==expr);
    }
    else
        return (*argument[0]==expr and
                (argument[1]->isInteger() or
                 argument[1]->getType() == smType::CFraction) and
                argument[1]->evaluateScalar() > 0);
}

Expr Pow::suppressTerm(const Expr& expr) const
{
    // Caution here: we do not re-test if the term corresponds (we do not call askTerm
    // we suppose it has been done before calling this function...)
    if (expr->getType() == smType::Pow)
    {
        return pow_(argument[0],minus_(argument[1], expr->getArgument(1)));
    }
    else return pow_(argument[0],minus_(argument[1], int_(1)));
}

void Pow::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 4) // Priority lesser than the previous operation: brackets
        cout<<"(";
    argument[0]->print(4);
    cout<<"^";
    argument[1]->print(4);
    if (mode > 4)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Pow::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 4) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    sout<<argument[0]->printLaTeX(4);
    sout<<"^{";
    sout<<argument[1]->printLaTeX(1);
    sout<<"}";
    if (mode > 4)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Pow::evaluateScalar() const
{
    if (argument[0]->getDim() > 0 or argument[1]->getDim() > 0) return 0;
    return pow(argument[0]->evaluateScalar(), argument[1]->evaluateScalar());
}

Expr Pow::evaluate()
{
    Expr foo1 = argument[0]->evaluate();
    Expr foo2 = argument[1]->evaluate();
    if (foo1->getPrimaryType() == smType::Numerical
            and foo2->getPrimaryType() == smType::Numerical)
        return foo1->exponentiation_own(foo2);
    return pow_(foo1,foo2);
}

bool Pow::mergeTerms()
{
    bool simplified = false;
    Expr arg;
    if (argument[0]->getType() == smType::Pow) {
        // (a^b)^c = a^(b*c)
        argument[1] = times_(argument[0]->getArgument(1),argument[1]);
        argument[0] = argument[0]->getArgument();
    }
    else if ((argument[0]->getType() == smType::Double or
              argument[0]->getType() == smType::Integer) and
                (argument[1]->getType() == smType::Double or
                 argument[1]->getType() == smType::Integer))
    {
        // Numerical1^Numerical2 = Numerical3
        argument[0] = auto_number_(pow(argument[0]->evaluateScalar(),
                                       argument[1]->evaluateScalar()));
        argument[1] = int_(1);
    }
    else if ((argument[0]->getType() == smType::Double or
              argument[0]->getType() == smType::Integer) and
            argument[1]->getType() == smType::CFraction and
            argument[1]->evaluateScalar() == 0.5)
    {
        // Numerical1^Numerical2 = Numerical3
        double value = sqrt(argument[0]->evaluateScalar());
        if (value == round(value)) {
            argument[0] = int_(value);
            argument[1] = int_(1);
        }
    }
    else if (argument[0]->getType() == smType::Fraction and
            (argument[1]->getNumericalFactor() < 0 or
             (argument[1]->getPrimaryType() == smType::Numerical and
              argument[1]->evaluateScalar() < 0))) 
    {
        // (a/b)^(-c) = (b/a)^c
        Expr tmp = argument[0]->getArgument(0);
        argument[0]->setArgument(argument[0]->getArgument(1),0);
        argument[0]->setArgument(tmp,1);
        if (argument[1]->getPrimaryType() == smType::Numerical)
            argument[1] = argument[1]->multiplication_own(int_(-1));
        else
            argument[1] = times_(argument[1],int_(-1));
    }
    else if (argument[0]->getType() == smType::Times) {
        // (a*b*...)^c = a^c*b^c*....
        vector<Expr > newArgument(0);
        for (int i=0; i<argument[0]->getNArgs(); i++)
            newArgument.push_back(pow_(argument[0]->getArgument(i),
                                       argument[1]));
        argument[1] = int_(1);
        argument[0] = times_(newArgument);
    }

    return simplified;
}

Expr Pow::derive(const Expr& expr)
{
    if (expr == nullptr)
        return ZERO;
    return plus_(times_(times_(argument[1]->derive(expr),
                               log_(argument[0])),
                        pow_(argument[0],
                             argument[1])),
                 times_(times_(argument[0]->derive(expr),
                               argument[1]),
                        pow_(argument[0],
                             minus_(argument[1], int_(1)))));
}

Expr Pow::develop(bool full)
{
    if (full) {
        Expr foo1 = argument[0]->develop(true);
        Expr foo2 = argument[1]->develop(true);
        if (foo2->isInteger() 
                and foo2->evaluateScalar() > 0 
                and foo1->getType() == smType::Plus) {
            double value = argument[1]->evaluateScalar();
            if (value == floor(value)) {
                int iMax = round(abs(value));
                Expr result = int_(1);
                for (int i=0; i<iMax; i++)
                    result = times_(result, foo1,true);
                result = result->develop(true);
                if (value < 0)
                    pow_(result, int_(-1));

                return result;
            }
        }
        Expr result = pow_(foo1,foo2);

        return result;
    }

    return Copy(this);
}

Expr Pow::getRealPart()
{
    cout<<"Warning: function \"Pow::getRealPart\" not yet implemented.\n";
    return ZERO;
}

Expr Pow::getImaginaryPart() const
{
    cout<<"Warning: function \"Pow::getImaginaryPart\" not yet implemented.\n";
    return ZERO;
}

Expr Pow::getComplexModulus()
{
    cout<<"Warning: function \"Pow::getComplexModulus\" not yet implemented.\n";
    return ZERO;
}

Expr Pow::getComplexArgument()
{
    cout<<"Warning: function \"Pow::getComplexArgument\" not yet implemented.\n";
    return ZERO;
}

int Pow::isPolynomial(const Expr& expr) const
{
    if (argument[1]->isInteger())
        if (*argument[0]==expr)
                return (int)argument[1]->evaluateScalar();
    return 0;
}

Expr Pow::getPolynomialTerm(const Expr& t_variable, int order)
{
    if (*argument[0] == t_variable and
            argument[1]->isInteger() and
            argument[1]->evaluateScalar() == order)
        return int_(1);
    else if (order == 0)
        return Copy(this);
    else
        return ZERO;
}

int Pow::getParity(const Expr& expr) const
{
    int parity = argument[0]->getParity(expr);
    int parity2 = argument[1]->getParity(expr);
    if (parity == 1 and parity2 == 1)
        return 1;
    if (parity == 0 or parity2 == 0)
        return 0;
    if (not argument[1]->isInteger())
        return 0;
    
    double value = argument[1]->evaluateScalar();
    return -2*((int)value%2)+1;
}

bool Pow::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())
        return true;
    if (expr->getType() != smType::Pow)
        return false;
    if (*argument[0] != expr->getArgument(0) or
            *argument[1] != expr->getArgument(1))
        return false;

    return true;
}

Expr pow_(const Expr& leftOperand, const Expr& rightOperand)
{
    if (*leftOperand == i_ and
            (rightOperand->getType() == smType::Double or
             rightOperand->getType()  == smType::Integer))
    {
        double value = rightOperand->evaluateScalar();
        if (value == round(value)) {
            int n = round(value);
            if (n%2 == 1) return times_(int_(pow(-1,(n/2)%2)),i_);
            return int_(pow(-1,(n/2)%2));
        }
    }
    if (*leftOperand == e_)
        return exp_(rightOperand);

    Expr foo = make_shared<Pow>(leftOperand, rightOperand);
    Expr arg0 = foo->getArgument(0);
    Expr arg1 = foo->getArgument(1);
    if (*arg1==ZERO) // x^0 = 1 (including 0^0 for now)
        return ONE;
    if (*arg0==ZERO) // 0^x = 0
        return ZERO;
    if (*arg0==ONE) // 1^x = 1
        return ONE;
    if (*arg1==ONE) // x^1 = x
        return arg0;

    return foo;
}

Expr sqrt_(const Expr& operand)
{
    return pow_(operand, _cfraction_(1,2));
}

///////////////////////////////////////////////////
/*************************************************/
// Class Polynomial                              //
/*************************************************/
///////////////////////////////////////////////////

Polynomial::Polynomial(const Expr& expr, const Expr& t_variable)
    :AbstractMultiFunc()
{
    variable = t_variable;
    Expr exprBis;
    if (expr->getType() == smType::Polynomial and
            *t_variable != expr->getVariable())
        exprBis = expr->getRegularExpression();
    else
        exprBis = expr;

    if (exprBis->getType() == smType::Plus) {
        int max_order = 0;
        argument = vector<Expr >(1);
        argument[0] = ZERO;
        Expr foo;
        for (int i=0; i<exprBis->getNArgs(); i++) {
            foo = exprBis->getArgument(i);
            int argument_order = foo->isPolynomial(t_variable);
            if (argument_order > max_order)
                for (int i=0; i<argument_order-max_order; i++)
                    argument.push_back(ZERO);
            argument[argument_order] = plus_(argument[argument_order],
                                       foo->getPolynomialTerm(t_variable,
                                                              argument_order));
        }
    }
    else {
        int max_order = exprBis->isPolynomial(t_variable);
        argument = vector<Expr >(0);
        for (int i=0; i<max_order+1; i++)
            argument.push_back(ZERO);
        argument[max_order] = exprBis->getPolynomialTerm(t_variable,
                                                              max_order);
    }
    nArgs = argument.size();
    mergeTerms();
}

Polynomial::Polynomial(const vector<Expr >& terms, const Expr& t_variable): AbstractMultiFunc()
{
    argument = terms;
    variable = t_variable;
    nArgs = argument.size();
    mergeTerms();
}

bool Polynomial::mergeTerms()
{
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == smType::Polynomial)
            argument[i] = argument[i]->getRegularExpression();
    }
    for (int i=nArgs-1; i>=1; i--) {
        if (*argument[i] == ZERO) {
            argument.erase(argument.begin()+i);
            nArgs--;
        }
        else 
            break;
    }
    return false;
}

int Polynomial::getOrder() const
{
    return nArgs - 1;
}

Expr Polynomial::getVariable() const
{
    return variable;
}

bool Polynomial::isIndexed() const
{
    return (variable->isIndexed() or AbstractMultiFunc::isIndexed());
}

IndexStructure Polynomial::getIndexStructure() const
{
    // If the expression has a non trivial index structure, we suppose 
    // (the program should maintain that property) that all arguments have the 
    // same structure, in particular the first
    if (nArgs > 0 and argument[0]->getPrimaryType() == smType::Indicial)
        return argument[0]->getIndexStructure()+variable->getIndexStructure();

    return variable->getIndexStructure();
}

void Polynomial::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        cout<<"(";
    for (int i=0; i<nArgs; i++) {
        if (*argument[i] != ZERO) {
            if (i == 0 or *argument[i] != int_(1))
                argument[i]->print(2);
            if (i > 0) {
                if (*argument[i] != int_(1))
                    cout<<"*";
                variable->print(4);
                if (i > 1)
                    cout<<"^"<<i;
            }
            if (i < nArgs-1) 
                cout<<" + ";
        }
    }
    if (mode > 1)
        cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Polynomial::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    if (mode > 1) // Priority lesser than the previous operation: brackets
        sout<<"\\left(";
    for (int i=0; i<nArgs; i++)
    {
        sout<<argument[i]->printLaTeX(1);
        if (i < nArgs-1)
            sout<<"+";
    }
    if (mode > 1)
        sout<<"\\right)";
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

double Polynomial::evaluateScalar() const
{
    double sum=0;
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getDim() > 0)
            return 0;
        sum += argument[i]->evaluateScalar()*pow(variable->evaluateScalar(),i);
    }
    return sum;
}

Expr Polynomial::evaluate()
{
    Expr result = ZERO;
    Expr foo, foo2;
    for (int i=0; i<nArgs; i++) {
        foo = pow_(variable->evaluate(),int_(i));
        foo2 = times_(argument[i]->evaluate(),foo->evaluate());
        result = plus_(result, foo2->evaluate())->evaluate();
    }
    return result;
}

Expr Polynomial::derive(const Expr& expr)
{
    Expr rep;
    vector<Expr > newTerms = argument;
    if (*expr == variable) {
        Expr foo = newTerms[0]->derive(expr);
        newTerms.erase(newTerms.begin());
        if (*foo != ZERO) {
            if (newTerms.size() > 0)
                newTerms[0] = plus_(newTerms[0], foo);
            else
                newTerms.insert(newTerms.begin(),foo);
        }
        for(size_t i=0; i<newTerms.size(); i++)
            newTerms[i] = times_(int_(i+1), newTerms[i]);
        
        return make_shared<Polynomial>(newTerms, variable);
    }
    for (int i=0; i<nArgs; i++)
        newTerms[i] = newTerms[i]->derive(expr);
    for (int i=newTerms.size()-1; i>= 0; i--)
        if (*newTerms[i] == ZERO)
            newTerms.erase(newTerms.begin()+i);

    return make_shared<Polynomial>(newTerms, variable);
}

int Polynomial::getParity(const Expr& t_variable) const
{
    int parity = 0;
    int newParity;
    if (*variable == t_variable) {
        if (*argument[0] != ZERO) parity = argument[0]->getParity(t_variable);
        for (int i=1; i<nArgs; i++) {
            if (*argument[i] != ZERO) {
                if (parity == 0)
                    parity = -(i%2);
                else {
                    newParity = -2*(i%2)+1;
                    if (parity != newParity)
                        return 0;
                }
            }
        }
        if (parity == 0)
            return 1;

        return parity;
    }
    parity = argument[0]->getParity(t_variable);
    if (parity == 0 or variable->getParity(t_variable) == 0)
        return 0;
    for (int i=1; i<nArgs; i++) {
        newParity = argument[i]->getParity(t_variable);
        if (newParity != parity)
            return 0;
    }

    return parity*variable->getParity(t_variable);
}

Expr Polynomial::getRegularExpression() const
{
    Expr result = ZERO;
    for (int i=0; i<nArgs; i++)
        result = plus_(result,times_(argument[i],pow_(variable,int_(i))));

    return result;
}

Expr Polynomial::addition_own(const Expr& expr) const
{
    Expr foo;
    if (expr->getType() != smType::Polynomial)
        foo = make_shared<Polynomial>(expr, variable);
    else 
        foo = expr;
    vector<Expr > foo_argument = argument;
    int foo_nArgs = nArgs;
    if (*variable == foo->getVariable()) {
        for (int i=0; i<foo->getNArgs(); i++) {
            if (i >= foo_nArgs) {
                foo_nArgs++;
                foo_argument.push_back(ZERO);
            }
            foo_argument[i] = plus_(foo_argument[i], foo->getArgument(i));
        }
        return make_shared<Polynomial>(foo_argument, variable);
    }

    return plus_(getRegularExpression(),foo->getRegularExpression());
}

Expr Polynomial::multiplication_own(const Expr& expr, bool side) const
{
    Expr foo;
    if (expr->getType() != smType::Polynomial)
        foo = make_shared<Polynomial>(expr, variable);
    else 
        foo = expr;

    //side = true;
    if (*variable == foo->getVariable()) {
        vector<Expr > foo_argument(nArgs+foo->getNArgs()-1,ZERO);
        for (int i=0; i<foo->getNArgs(); i++) {
            if (*Commutation(variable,foo->getArgument(i)) != ZERO){
                if (side)
                    return times_(getRegularExpression(),foo->getRegularExpression());
                else
                    return times_(foo->getRegularExpression(),getRegularExpression());
            }
            for (int j=0; j<nArgs; j++) {
                if (*Commutation(variable,argument[j]) != ZERO){
                    if (side)
                        return times_(getRegularExpression(),foo->getRegularExpression());
                    else
                        return times_(foo->getRegularExpression(),getRegularExpression());
                }
                if (side)
                    foo_argument[i+j] = plus_(foo_argument[i+j],
                                              times_(argument[j],
                                                     foo->getArgument(i)));
                else
                    foo_argument[i+j] = plus_(foo_argument[i+j],
                                              times_(foo->getArgument(i),
                                                     argument[j]));
            }
        }

        return make_shared<Polynomial>(foo_argument, variable);
    }

    if (side)
        return times_(getRegularExpression(),foo->getRegularExpression());
    else
        return times_(foo->getRegularExpression(),getRegularExpression());
}

Expr Polynomial::division_own(const Expr& expr) const
// Euclidean division of a polynomial by another. If expr is not
// a polynomial (or is a polynomial of a different variable, it is first
// converted in a polynomial of the same variable.
{
    Expr foo = Copy(expr);
    if (foo->getType() != smType::Polynomial or *foo->getVariable() != variable)
        foo = polynomial_(foo,variable);
    if (foo->getNArgs() > nArgs)
        return Copy(this);

    // If the variable does not commute with one argument, we cannot 
    // divide the polynomial
    /*
    for (int i=0; i<foo->getNArgs(); ++i)
        if (*Commutation(foo->getArgument(i),variable) != ZERO)
            return Copy(this);
    for (int i=0; i<nArgs; ++i)
        if (*Commutation(argument[i],variable) != ZERO)
            return Copy(this);
    */
    //cout<<"Divinding "; print();
    //cout<<"by : "; foo->print();
    
    Expr q = polynomial_(ZERO, variable);
    Expr r = polynomial_(argument, variable);
    Expr t;
    int iter = 0;
    int maxiter = 10;
    while(*r!=ZERO and r->getNArgs()>=foo->getNArgs() and iter < maxiter) {
        //cout<<"q = "; q->print();
        //cout<<"r = "; r->print();
        t = fraction_(r->getArgument(r->getNArgs()-1),
                      foo->getArgument(foo->getNArgs()-1));
        t = t->develop(true);
        t = times_(t,pow_(variable,int_(r->getNArgs()-foo->getNArgs())));
        t = t->develop(true);
        q = plus_(q,t);
        r = plus_(r,times_(times_(int_(-1),t),foo));
        //r = r+(1*foo*t);
        r = r->develop(true);
        q = q->develop(true);
        ++iter;
    }
        //cout<<"q = "; q->print();
        //cout<<"r = "; r->print();
    if (*r == ZERO)
        return q;

    return Copy(this);
}

Expr Polynomial::factor(bool full)
{
    if (nArgs == 3) {
        // Canonical factorization of order 2 polynomial
        // x = -b/2a +- sqrt(delta)/2a
       Expr delta = plus_(pow_(argument[1],int_(2)),
                          times_(times_(int_(-4),argument[0]),
                                 argument[2]));
       Expr mean = times_(int_(-1), argument[1]);
       Expr diff = sqrt_(delta);
       Expr root1 = fraction_(plus_(mean, diff),
                              times_(int_(2),argument[2]));
       Expr root2 = fraction_(plus_(mean, times_(int_(-1),diff)),
                              times_(int_(2),argument[2]));

       Expr pol1 = polynomial_(minus_(variable, root1), variable);
       Expr pol2 = polynomial_(minus_(variable, root2), variable);

       return times_(argument[2],times_(pol1, pol2, true));
    }
    return Copy(this);
}

bool Polynomial::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())
        return true;
    if (nArgs == 1)
        return *argument[0]==expr;
    if (expr->getType() == smType::Polynomial) {
        Expr t_variable = expr->getVariable();
        if (*variable != t_variable)
            return false;

        vector<Expr > t_argument = expr->getVectorArgument();
        if (t_argument.size() != argument.size())
            return false;
        for (size_t i=0; i<t_argument.size(); i++)
            if (*argument[i] != t_argument[i])
                return false;

        return true;
    }
    if (expr->getType() != smType::Plus)
        return false;
    if (nArgs != expr->getNArgs())
        return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++)
        indicesLeft[i] = i;

    for (int i=0; i<nArgs; i++) {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++) {
            if (*times_(argument[i],pow_(variable,int_(i))) ==
                    expr->getArgument(indicesLeft[j]))
            {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched)
            return false;
    }

    return true;
}

Expr polynomial_(const Expr& expr, const Expr& t_variable)
{
    if (expr->getPrimaryType() == smType::Vectorial) {
        Expr foo = tensor_(expr->getShape());
        for (int i=0; i<expr->getNArgs(); i++)
            foo->setArgument(polynomial_(expr->getArgument(i),t_variable),i);
        return foo;
    }

    Expr res = make_shared<Polynomial>(expr, t_variable);
    return res;
}

Expr polynomial_(const vector<Expr >& operands, const Expr& t_variable)
{
    Expr res =  make_shared<Polynomial>(operands, t_variable);
    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Derivative                              //
/*************************************************/
///////////////////////////////////////////////////

Expr Derivative::getVariable() const {
    return argument[1];
}

int Derivative::getOrder() const {
    return order;
}

bool Derivative::isEmpty() const {
    return empty;
}

void Derivative::print(int mode) const
{
    if (mode == 0 and name != "")
        cout<<name<<" = ";
    cout<<"d";
    if (order > 1)
        cout<<"^"<<order;
    cout<<"/d";
    cout<<"(";
    argument[1]->print(1);
    cout<<")";
    if (order > 1)
        cout<<"^"<<order;
    cout<<"(";
    if (empty) {
        if (*argument[0] != ONE)
            argument[0]->print(1);
        if (mode == 0)
            cout<<endl;
        return;
    }
    argument[0]->print(1);
    cout<<")";
    if (mode == 0)
        cout<<endl;
}

string Derivative::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "")
        sout<<name<<" = ";
    sout<<"\\dfrac{d^"<<order<<"}{d";
    sout<<argument[1]->printLaTeX(1);
    sout<<"^"<<order<<"}\\left(";
    if (empty) {
        if (*argument[0] != ONE)
            sout<<argument[0]->printLaTeX(1);
        return sout.str();
    }
    sout<<argument[0]->printLaTeX(1);
    sout<<"\\right)";

    return sout.str();
}

double Derivative::evaluateScalar() const
{
    if (argument[0]->getDim() > 0 or argument[1]->getDim() > 0)
        return 0;
    Expr df = argument[0];
    for (int i=0; i<order; i++)
        df = df->derive(argument[1]);

    return df->evaluateScalar();
}

Expr Derivative::evaluate()
{
    if (argument[0]->getType() == smType::Times) {
        vector<Expr> t_argument(argument[0]->getNArgs());
        for (size_t i=0; i!=t_argument.size(); ++i) {
            t_argument[i] = Copy(argument[0]);
            t_argument[i]->setArgument(
                    derivative_(argument[0]->getArgument(i), argument[1],
                        1), i);
        }
        if (order > 1)
            return derivative_(
                    plus_(t_argument),argument[1],order-1)->evaluate();
        else 
            return plus_(t_argument)->evaluate();
    }
    if (argument[0]->dependsExplicitelyOn(argument[1])) {
        Expr df = argument[0]->evaluate();
        for (int i=0; i<order; i++)
            df = df->derive(argument[1]);

        return df;
    }

    return derivative_(argument[0]->evaluate(), 
                       argument[1]->evaluate(), order);
}

Expr Derivative::derive(const Expr& expr)
{
    return derivative_(argument[0]->derive(expr), argument[1], order);
}

int Derivative::getParity(const Expr& t_variable) const
{
    int parity = argument[0]->getParity(t_variable);
    if (parity == -1)
        parity = -2*(order%2)+1;

    if (parity == 0)
        return 0;
    else
        return parity*argument[1]->getParity(t_variable);
}

bool Derivative::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())
        return true;
    if (expr->getType() != smType::Derivative)
        return false;
    if (*argument[0] != expr->getArgument(0) or
            *argument[1] != expr->getArgument(1) or
            order != expr->getOrder())
        return false;

    return true;
}

Expr derivative_(const Expr& leftOperand, const Expr& rightOperand, int order)
{
    return derivative_(leftOperand, rightOperand, order, false);
}

Expr derivative_(const Expr& leftOperand, const Expr& rightOperand, int order,
     bool empty) 
{
    if (order <= 0)
        return rightOperand;
    //We calculate the derivative and if it is 0 (many cases) we return 0.
    if (leftOperand->getPrimaryType() == smType::Vectorial) {
        Expr res = tensor_(leftOperand->getShape());
        for (int i=0; i!=res->getNArgs(); ++i)
            res->setArgument(
                    derivative_(leftOperand->getArgument(i),rightOperand,order,
                        empty)
                    ,i);

        return res;
    }
    if (rightOperand->getPrimaryType() == smType::Vectorial) {
        Expr res = tensor_(rightOperand->getShape());
        for (int i=0; i!=res->getNArgs(); ++i)
            res->setArgument(
                    derivative_(leftOperand,rightOperand->getArgument(i),
                        order, empty)
                    ,i);

        return res;
    }

    if (not leftOperand->dependsOn(rightOperand)
            and *leftOperand != ONE)
        return ZERO;

    vector<Expr> foo;
    int posDerivative=0;
    int endDerivative;
    switch(leftOperand->getType()) {

        case smType::Plus:
        // d/dx(a1+a2...) = da1/dx+da2/dx+...
        foo = leftOperand->getVectorArgument();
        for (auto& arg : foo) 
            arg = derivative_(arg, rightOperand, order, empty);

        return plus_(foo);
        break;

        case smType::Times:
        // d/dx(a*f(x)*...*b) = a*d(f(x)...)/dx*b
        foo = leftOperand->getVectorArgument();
        endDerivative = foo.size();
        for (int i=0; i!=endDerivative; ++i) {
            if (not foo[i]->dependsOn(rightOperand)) {
                bool constantPulled = false;
                bool blocked = false;
                for (int j=i-1; j>=posDerivative; --j) {
                    if (*Commutation(foo[j], foo[i]) != ZERO) {
                        blocked = true;
                        break;
                    }
                }
                if (not blocked) {
                    Expr foo2 = foo[i];
                    foo.erase(foo.begin()+i);
                    foo.insert(foo.begin()+posDerivative, foo2);
                    ++posDerivative;
                    constantPulled = true;
                }
                if (not constantPulled) {
                    blocked = false;
                    for (int j=i+1; j<endDerivative; ++j) {
                        if (*Commutation(foo[i], foo[j]) != ZERO) {
                            blocked = true;
                            break;
                        }
                    }
                    if (not blocked) {
                        Expr foo2 = foo[i];
                        foo.erase(foo.begin()+i);
                        foo.insert(foo.begin()+endDerivative-1, foo2);
                        --endDerivative;
                        --i;
                    }
                }
            }
        }
        if (posDerivative != 0 or endDerivative != (int)foo.size()) {
            Expr leftConstants = ONE;
            Expr rightConstants = ONE;
            Expr argument = ONE;
            if (posDerivative != 0)
                leftConstants = times_(vector<Expr>(foo.begin(),
                            foo.begin()+posDerivative));
            if (endDerivative - posDerivative > 0)
                argument = times_(vector<Expr>(foo.begin()+posDerivative, 
                            foo.begin()+endDerivative));
            if (endDerivative != (int)foo.size())
                rightConstants = times_(vector<Expr>(foo.begin()+endDerivative,
                            foo.end()));
            if (*argument != ONE)
                return leftConstants 
                    * make_shared<Derivative>(argument, rightOperand,
                            order,empty)
                    * rightConstants;
            else
                return ZERO;
        }
        else 
            return make_shared<Derivative>(leftOperand, rightOperand,
                    order, empty);
        break;

        default:
        return make_shared<Derivative>(leftOperand, rightOperand, 
                order, empty);
    }
}

Expr derivative_(const Expr& variable, int order)
{
    if (order <= 0)
        return ZERO;
    
    return make_shared<Derivative>(variable, order);
}

