#include "simplification.h"

using namespace std;


void printVector(const vector<Expr >& vector)
{
    for (const auto& arg: vector)
        arg->print();
}

void addAlternateForm(vector<Expr >& alternateForms, const Expr& newAlternate, bool add_factor_develop)
{
    if (alternateForms.size() == 0) alternateForms.push_back(newAlternate);
    vector<Expr >::iterator it;
    it = find(alternateForms.begin(), alternateForms.end(), newAlternate);
    if (it == alternateForms.end()) // We did not find the newAlternate
        alternateForms.push_back(newAlternate);

    if (add_factor_develop)
    {
        Expr foo = newAlternate->develop();
        if (*foo != newAlternate)
            addAlternateForm(alternateForms, foo, false);
        foo = newAlternate->factor();
        if (*foo != newAlternate)
            addAlternateForm(alternateForms, foo, false);
    }
}

// Reduces the number of alternate forms to MAX_ALTERNATE_FORMS
// Take only the bests (simpler) exprs
void reduceAlternate(vector<Expr >& alternateForms)
{
    int nArgs = alternateForms.size();
    if (nArgs <= MAX_ALTERNATE_FORMS) return;
    partial_sort(alternateForms.begin(), alternateForms.begin()+MAX_ALTERNATE_FORMS, alternateForms.end());
    alternateForms.erase(alternateForms.begin()+MAX_ALTERNATE_FORMS, alternateForms.end());
}

void clearRedundancyAlternate(vector<Expr > alternateForms)
{
    for (size_t i=0; i!=alternateForms.size(); ++i) 
        for (size_t j=i+1; j!=alternateForms.size(); ++j) 
            if (*alternateForms[i] == alternateForms[j]) {
                alternateForms.erase(alternateForms.begin()+j);
                --j;
            }
}

//Returns alternateForms of expr recursively (get alternateForms of alternateForms etc up to MAX_RECURSION_ALTERNATE). 
vector<Expr > getRecursiveAlternateForms(const Expr& expr, int depth)
{
    vector<Expr > alternateForms;
    //taking alternateForms a first time
    vector<Expr > toReturn = internalRecursiveAlternateForms(expr,depth-1);
    if (toReturn.size() == 0) // no alternate form for expr
        return vector<Expr >(0);
    vector<Expr > fooVec = toReturn;
    //We take alternate of alternate MAX_RECURSION_ALTERNATE-1 times
    for (int i=1; i<MAX_RECURSION_ALTERNATE; i++)
    {
        alternateForms = toReturn;
        toReturn = vector<Expr >(0);
        Expr foo;
        for (size_t j=0; j<alternateForms.size(); j++)
        {
            //taking alternate of alternate
            fooVec = internalRecursiveAlternateForms(alternateForms[j],depth-1);
            if (fooVec.size() == 0)
                fooVec.push_back(Copy(alternateForms[j]));
            
            for (size_t k=0; k<fooVec.size(); k++)
                addAlternateForm(toReturn, fooVec[k]);
        }
    }
    reduceAlternate(toReturn);

    return toReturn;
}

vector<Expr > internalRecursiveAlternateForms(const Expr& expr, int depth) 
{
    int nArgs = expr->getNArgs();
    vector<Expr > alternateForms(0);
    // if no Argument, no alternate form (for now)
    if (nArgs == 0) return alternateForms;
    if (depth != 0)
    {
        vector<Expr> argument(0);
        ////
        // Warning: here specific if-else conditions on types,
        // could be wrong if changes occur in structure....
        ////
        if (nArgs == 1) argument = vector<Expr>(1,expr->getArgument());
        else if (expr->getPrimaryType() == smType::Vectorial or
                 expr->getType() == smType::Plus or
                 expr->getType() == smType::Times or
                 expr->getType() == smType::Polynomial)
            argument = expr->getVectorArgument();
        else if (nArgs == 2) {
            argument = vector<Expr>(2);
            argument[0] = expr->getArgument(0);
            argument[1] = expr->getArgument(1);
        }
        else 
            callError(smError::UndefiniedBehaviour,
                    "internalRecursiveAlternateForms(const Expr& expr, int depth)");

        vector<Expr > fooVec;
        Expr foo;
        vector<vector<Expr > > newArguments(0);
        if (nArgs > 1)
        {
            fooVec = internalRecursiveAlternateForms(argument[0],depth-1);
            if (fooVec.size() == 0) // if no alternate, we keep at least the argument itself
                fooVec = vector<Expr >(1,Copy(argument[0]));
            for (int i=1; i<nArgs; i++)
            {
                fooVec = internalRecursiveAlternateForms(argument[i],depth-1);
                if (fooVec.size() == 0)
                    fooVec = vector<Expr >(1,Copy(argument[i]));
                for (size_t j=0; j<fooVec.size()-1; j++) // We take 1+n-1 copies of actual alternates
                {
                    foo = Copy(expr);
                    foo->setArgument(Refresh(fooVec[j]),i);
                    addAlternateForm(alternateForms, Refresh(foo));
                }
            }
            /*foo = Copy(expr); // Create an Abstract of same type as expr
            foo->setVectorArgument(vector<Expr >(1,ZERO)); // filling it with a short expr
            alternateForms = vector<Expr >(newArguments.size(),foo);
            for (int i=0; i<alternateForms.size(); i++)
            {
                if (i % 1000 == 0)
                {
                    cout<<"NEW "<<i<<"/"<<alternateForms.size()<<endl;
                    alternateForms[i]->print();
                }
                alternateForms[i]->setVectorArgument(newArguments[i]);
                alternateForms[i] = Refresh(alternateForms[i]);
            }*/
            clearRedundancyAlternate(alternateForms);
        }
        else
        {
            fooVec = internalRecursiveAlternateForms(expr->getArgument(),depth-1);
            for (size_t i=0; i<fooVec.size(); i++)
            {
                alternateForms.push_back(Copy(expr));
                alternateForms[i]->setArgument(Refresh(fooVec[i]));
            }
        }

        // Now that we have a list of all possible alternates for the arguments
        // we take the specific alternate forms of the results
        if (alternateForms.size() == 0)
            alternateForms.push_back(Copy(expr));
        vector<Expr > toReturn(0);
        for (size_t i=0; i<alternateForms.size(); i++)
        {
            alternateForms[i] = Refresh(alternateForms[i]);
            fooVec = alternateForms[i]->getAlternateForms();
            if (fooVec.size() == 0)
                fooVec.push_back(Copy(alternateForms[i]));
            for (size_t j=0; j<fooVec.size(); j++)
                addAlternateForm(toReturn, Refresh(fooVec[j]));
        }
        reduceAlternate(toReturn);
        /*int countTHIS = 0;
        for (int i=0; i<toReturn.size(); i++)
        {
            if (*expr == toReturn[i])
                countTHIS++;
            if (countTHIS > 1)
            {
                toReturn.erase(toReturn.begin()+i);
                i--;
            }
        }
        if (countTHIS == 0 and toReturn.size() > 0)
            toReturn.push_back(Copy(expr));*/

        return toReturn;
    }
    return expr->getAlternateForms();
}

Expr Simplify(const Expr& expr, int depth)
{
    int nArgs = expr->getNArgs();
    vector<Expr > trials;
    Expr simplifiedAbstract;
    simplifiedAbstract = Copy(expr);
    if (depth != 0 and nArgs > 0)
    {
        for (int i=0; i<nArgs; i++)
            simplifiedAbstract->setArgument(Simplify(simplifiedAbstract->getArgument(i)),i);
        simplifiedAbstract = Refresh(simplifiedAbstract);
    }

    int iter = 0;
    int maxIter = 3;
    bool simplified = true;
    while(simplified and iter < maxIter)
    {
        simplified = false;

        trials = getRecursiveAlternateForms(simplifiedAbstract, depth);
        for (size_t i=0; i<trials.size(); i++)
        {
            trials[i] = DeepRefresh(trials[i]);
            if (*trials[i] < simplifiedAbstract)
            {
                simplified = true;
                simplifiedAbstract = trials[i];
            }
            /*else
            {
                if (trials[i]->getNArgs() > 0)
                {
                    for (int i=0; i<trials[i]->getNArgs(); i++)
                        trials[i]->setArgument(Simplify(trials[i]->getArgument(i)),i);
                    trials[i] = Refresh(trials[i]);
                    if (*trials[i] < simplifiedAbstract)
                    {
                        simplified = true;
                        simplifiedAbstract = trials[i];
                    }
                }
            }*/
        }
        iter++;
    }
    //if (iter == maxIter) cout<<"Maxiter reahed in simplification!\n";

    return simplifiedAbstract;
}

vector<Expr > Plus::getAlternateForms() const
{
    Expr foo = Copy(this);
    Expr foo2;
    Expr foo3, foo4;
    foo4 = Copy(this);
    vector<Expr > alternateForms(0);
    vector<Expr > alternateArg(0);
    int size;

    //Plus-specific alternate forms
    int nArgs2;
    for (int i=0; i<nArgs; i++)
    {
        if (argument[i]->getType() == smType::Times) // Searching fraction => same denominator
        {
            nArgs2 = argument[i]->getNArgs();
            for (int j=0; j<nArgs2; j++)
            {
                foo2 = Copy(argument[i]->getArgument(j));
                if (foo2->getType() == smType::Pow)
                {
                    if (foo2->getArgument(1)->isInteger() and foo2->getArgument(1)->evaluateScalar() < 0)
                    {
                        int power = -1*foo2->getArgument(1)->evaluateScalar();
                        foo2->setArgument(int_(power),1);
                        for (int k=0; k<nArgs; k++)
                            foo->setArgument(times_(Copy(foo2),Copy(argument[k])),k);
                        foo2->setArgument(int_(-power),1);

                        foo = Refresh(foo);
                        foo3 = times_(foo2, foo->develop(true));
                        if (*foo3 != foo4)
                            alternateForms.push_back(foo3);
                        foo3 = times_(foo2, foo->develop());
                        if (*foo3 != foo4)
                            alternateForms.push_back(foo3);
                        foo3 = times_(foo,foo2);
                        if (*foo3 != foo4)
                            alternateForms.push_back(Copy(foo3));
                    }
                }
            }
        }
        else if (argument[i]->getType() == smType::Pow) // Searching fraction => same denominator
        {
            foo2 = Copy(argument[i]);
            if (foo2->getArgument(1)->isInteger() and foo2->getArgument(1)->evaluateScalar() < 0)
            {
                int power = -1*foo2->getArgument(1)->evaluateScalar();
                foo2->setArgument(int_(power),1);
                for (int k=0; k<nArgs; k++)
                    foo->setArgument(times_(Copy(foo2),Copy(argument[k])),k);
                foo2->setArgument(int_(-power),1);

                foo = Refresh(foo);
                foo3 = times_(foo2, foo->develop(true));
                if (*foo3 != foo4)
                    alternateForms.push_back(foo3);
                foo3 = times_(foo2, foo->develop());
                if (*foo3 != foo4)
                    alternateForms.push_back(foo3);
                foo3 = times_(foo,foo2);
                if (*foo3 != foo4)
                    alternateForms.push_back(Copy(foo3));
            }
        }
        if (false and argument[i]->getType() == smType::Times and argument[i]->getNArgs() == 2)
        {
            Expr number = argument[i]->getArgument(0);
            if (number->isInteger() and abs(number->evaluateScalar()) < 10) // n*X, n integer
            {
                int value = number->evaluateScalar();
                Expr arg = Copy(argument[i]->getArgument(1));
                alternateArg = argument;
                alternateArg.erase(alternateArg.begin()+i);
                if (value > 0)
                {
                    for (int j=0; j<value; j++)
                        alternateArg.push_back(arg);
                }
                else if (value < 0)
                {
                    arg = minus_(ZERO,arg);
                    for (int j=0; j<abs(value); j++)
                        alternateArg.push_back(arg);
                }
                foo3 = make_shared<Plus>();
                foo3->setVectorArgument(alternateArg);
                alternateForms.push_back(foo3);
            }
        }
    }
    foo = Copy(this);

    size = alternateForms.size();
    for (int i=0; i<size; i++)
    {
        foo = alternateForms[i]->develop(true);
        if (*foo != alternateForms[i])
            alternateForms.push_back(foo);
        foo = alternateForms[i]->factor();
        if (*foo != alternateForms[i])
            alternateForms.push_back(foo);
    }
    
    return alternateForms;
}

vector<Expr > Times::getAlternateForms() const
{
    Expr foo = Copy(this);
    Expr foo2;
    vector<Expr > alternateForms(0);
    vector<Expr > alternateArg(0);
    int size;

    alternateForms = vector<Expr >(0);
    bool cosProdFound = false;
    for (int i=0; i<nArgs; i++)
    {
        int type = argument[i]->getType();
        if (not cosProdFound and type == smType::Cos)
        {
            for (int j=i+1; j<nArgs; j++)
            {
                type = argument[j]->getType();
                if (type == smType::Cos) // cos(a)cos(b)=cos(a+b)+sin(a)sin(b)
                {
                    cosProdFound = true;
                    Expr a = argument[i]->getArgument();
                    Expr b = argument[j]->getArgument();
                    foo2 = Copy(this);
                    foo2->setArgument(ONE,i);
                    foo2->setArgument(ONE,j);
                    foo2 = times_(foo2,plus_(cos_(plus_(a,b)),times_(sin_(a),sin_(b))));
                    alternateForms.push_back(foo2);
                }
                else if (type == smType::Sin) // cos(a)sin(b) = sin(a+b)-sin(a)cos(b)
                {
                    cosProdFound = true;
                    Expr a = argument[i]->getArgument();
                    Expr b = argument[j]->getArgument();
                    foo2 = Copy(this);
                    foo2->setArgument(ONE,i);
                    foo2->setArgument(ONE,j);
                    foo2 = times_(foo2,minus_(sin_(plus_(a,b)),times_(sin_(a),cos_(b))));
                    alternateForms.push_back(foo2);
                }
            }
        }
        else if (not cosProdFound and type == smType::Sin)
        {
            for (int j=i+1; j<nArgs; j++)
            {
                type = argument[j]->getType();
                if (type == smType::Sin) // sin(a)sin(b)=cos(a)cos(b)-cos(a+b)
                {
                    cosProdFound = true;
                    Expr a = argument[i]->getArgument();
                    Expr b = argument[j]->getArgument();
                    foo2 = Copy(this);
                    foo2->setArgument(ONE,i);
                    foo2->setArgument(ONE,j);
                    foo2 = times_(foo2,minus_(times_(cos_(a),cos_(b)),cos_(plus_(a,b))));
                    alternateForms.push_back(foo2);
                }
                else if (type == smType::Cos) // cos(b)sin(a) = sin(a+b)-sin(b)cos(a)
                {
                    cosProdFound = true;
                    Expr a = argument[i]->getArgument();
                    Expr b = argument[j]->getArgument();
                    foo2 = Copy(this);
                    foo2->setArgument(ONE,i);
                    foo2->setArgument(ONE,j);
                    foo2 = times_(foo2,minus_(sin_(plus_(a,b)),times_(sin_(b),cos_(a))));
                    alternateForms.push_back(foo2);
                }
            }
        }
    }
    size = alternateForms.size();
    for (int i=0; i<size; i++)
    {
        // We add automatically developped alternate form
        foo = alternateForms[i]->develop();
        if (*foo != alternateForms[i])
            alternateForms.push_back(foo);

        foo = alternateForms[i]->develop(true);
        if (*foo != alternateForms[i])
            alternateForms.push_back(foo);
        foo = alternateForms[i]->factor();
        if (*foo != alternateForms[i])
            alternateForms.push_back(foo);
    }
    if (alternateForms.size() > 0)
        alternateForms.insert(alternateForms.begin(), Copy(this));

    return alternateForms;
}

vector<Expr > Pow::getAlternateForms() const
{
    vector<Expr > alternateForms(0);
    if (argument[0]->getType() == smType::Cos)
    {
        if (*argument[1] == 2) // cos(x)^2
        {
            alternateForms.push_back(minus_(ONE,pow_(sin_(argument[0]->getArgument()),int_(2)))); // 1-sin(x)^2
            alternateForms.push_back(times_(plus_(ONE,cos_(times_(int_(2),argument[0]->getArgument()))),_cfraction_(1,2))); // (1+cos(2x))/2
        }
        else if (*argument[1] == -2) // 1/cos(x)^2
            alternateForms.push_back(plus_(ONE,pow_(tan_(argument[0]->getArgument()),int_(2)))); // = 1 + tan(x)^2
    }
    else if (argument[0]->getType() == smType::Sin) // sin(x)^2
    {
        if (*argument[1] == 2)
        {
            alternateForms.push_back(minus_(ONE,pow_(cos_(argument[0]->getArgument()),int_(2)))); // = 1-cos(x)^2
            alternateForms.push_back(times_(minus_(ONE,cos_(times_(int_(2),argument[0]->getArgument()))),_cfraction_(1,2))); // (1-cos(2x))/2
        }
    }
    if (argument[0]->getType() == smType::Cosh)
    {
        if (*argument[1] == 2) // cosh(x)^2
        {
            alternateForms.push_back(minus_(ONE,pow_(sinh_(argument[0]->getArgument()),int_(2)))); // 1-sinh(x)^2
            alternateForms.push_back(times_(plus_(ONE,cosh_(times_(int_(2),argument[0]->getArgument()))),_cfraction_(1,2))); // (1+cosh(2x))/2
        }
        else if (*argument[1] == -2) // 1/cosh(x)^2
            alternateForms.push_back(plus_(ONE,pow_(tanh_(argument[0]->getArgument()),int_(2)))); // = 1 + tanh(x)^2
    }
    else if (argument[0]->getType() == smType::Sinh) // sinh(x)^2
    {
        if (*argument[1] == 2)
        {
            alternateForms.push_back(minus_(ONE,pow_(cosh_(argument[0]->getArgument()),int_(2)))); // = 1-cosh(x)^2
            alternateForms.push_back(times_(minus_(cosh_(times_(int_(2),argument[0]->getArgument())),ONE),_cfraction_(1,2))); // (cosh(2x)-1)/2
        }
    }
    if (alternateForms.size() > 0)
        alternateForms.insert(alternateForms.begin(), Copy(this));

    return alternateForms;
}

vector<Expr > Cos::getAlternateForms() const
{
    vector<Expr > foo(0);
    if (argument->getType() == smType::Plus and argument->getNArgs() == 2) // cos(a+b)
    {
        Expr a = argument->getArgument(0);
        Expr b = argument->getArgument(1);
        foo.push_back(minus_(times_(cos_(a),cos_(b)),times_(sin_(a),sin_(b)))); // = cos(a)cos(b)-sin(a)sin(b)
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and argument->getArgument(0) == int_(2)) // cos(2a)
    {
        Expr a = argument->getArgument(1);
        foo.push_back(minus_(pow_(cos_(a),int_(2)),pow_(sin_(a),int_(2)))); // = cos(a)^2-sin(a)^2
    }
    if (argument->getType() == smType::Times and argument->getNArgs() == 2 and *argument->getArgument(1) == pi_) // cos(a*pi)
    {
        Expr a = argument->getArgument(0);
        if (a->isInteger())
        {
            int newValue = (int)(a->evaluateScalar())%2;
            if (newValue != a->evaluateScalar())
                foo.push_back(cos_(times_(int_(newValue),pi_)));
        }
    }
    if (argument->getNumericalFactor()->evaluateScalar() < 0) // cos(-X)
    {
        foo.push_back(cos_((times_(int_(-1),argument))));
    }
    if (foo.size() > 0)
        foo.insert(foo.begin(), Copy(this));

    return foo;
}

vector<Expr > Sin::getAlternateForms() const
{
    vector<Expr > foo(0);
    if (argument->getType() == smType::Plus and argument->getNArgs() == 2) // sin(a+b)
    {
        Expr a = argument->getArgument(0);
        Expr b = argument->getArgument(1);
        foo.push_back(plus_(times_(cos_(a),sin_(b)),times_(sin_(a),cos_(b)))); // = cos(a)sin(b)+sin(a)cos(b)
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and argument->getArgument(0) == int_(2)) // sin(2a)
    {
        Expr a = argument->getArgument(1);
        foo.push_back(times_(times_(int_(2),cos_(a)),sin_(a))); // = 2cos(a)sin(a)
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and *argument->getArgument(1) == pi_) // sin(a*pi)
    {
        Expr a = argument->getArgument(0);
        if (a->isInteger())
        {
            int newValue = (int)(a->evaluateScalar())%2;
            if (newValue != a->evaluateScalar())
                foo.push_back(sin_(times_(int_(newValue),pi_)));
        }
    }
    if (argument->getNumericalFactor()->evaluateScalar() < 0) // sin(-X)
    {
        foo.push_back(times_(int_(-1),sin_(times_(int_(-1),argument))));
    }
    if (foo.size() > 0)
        foo.insert(foo.begin(), Copy(this));

    return foo;
}

vector<Expr > Tan::getAlternateForms() const
{
    vector<Expr > foo(2);
    foo[0] = fraction_(sin_(argument),cos_(argument));
    foo[1] = Copy(this);
    if (argument->getType() == smType::Plus and argument->getNArgs() == 2) // tan(a+b)
    {
        Expr arg1 = argument->getArgument(0);
        Expr arg2 = argument->getArgument(1);
        foo.push_back(times_(plus_(tan_(arg1),tan_(arg2)),pow_(minus_(ONE,times_(tan_(arg1),tan_(arg2))),int_(-1)))); // = (tan(a)+tan(b))/(1-tan(a)*tan(b))
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and *argument->getArgument(0) == int_(2)) // tan(2a)
    {
        Expr arg = argument->getArgument(1);
        foo.push_back(times_(times_(int_(2),tan_(arg)),pow_(minus_(ONE,pow_(tan_(arg),int_(2))),int_(-1)))); // = 2tan(a)/(1-tan(a)^2)
    }
    if (argument->getNumericalFactor()->evaluateScalar() < 0) // tan(-X)
    {
        foo.push_back(times_(int_(-1),tan_(times_(int_(-1),argument))));
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and *argument->getArgument(1) == pi_) // tan(a*pi)
    {
        Expr a = argument->getArgument(0);
        if (a->isInteger())
        {
            int newValue = (int)(a->evaluateScalar())%2;
            if (newValue != a->evaluateScalar())
                foo.push_back(tan_(times_(int_(newValue),pi_)));
        }
    }

    return foo;
}

vector<Expr > Cosh::getAlternateForms() const
{
    vector<Expr > foo(0);
    if (argument->getType() == smType::Plus and argument->getNArgs() == 2) // cosh(a+b)
    {
        Expr a = argument->getArgument(0);
        Expr b = argument->getArgument(1);
        foo.push_back(plus_(times_(cosh_(a),cosh_(b)),times_(sinh_(a),sinh_(b)))); // = cosh(a)cosh(b)+sinh(a)sinh(b)
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and argument->getArgument(0) == int_(2)) // cosh(2a)
    {
        Expr a = argument->getArgument(1);
        foo.push_back(plus_(pow_(cosh_(a),int_(2)),pow_(sinh_(a),int_(2)))); // = cosh(a)^2+sinh(a)^2
    }
    if (foo.size() > 0)
        foo.insert(foo.begin(), Copy(this));

    return foo;
}

vector<Expr > Sinh::getAlternateForms() const
{
    vector<Expr > foo(0);
    if (argument->getType() == smType::Plus and argument->getNArgs() == 2) // sinh(a+b)
    {
        Expr a = argument->getArgument(0);
        Expr b = argument->getArgument(1);
        foo.push_back(plus_(times_(cosh_(a),sinh_(b)),times_(sinh_(a),cosh_(b)))); // = cosh(a)sinh(b)+sinh(a)cosh(b)
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and argument->getArgument(0) == int_(2)) // sinh(2a)
    {
        Expr a = argument->getArgument(1);
        foo.push_back(times_(times_(int_(2),cosh_(a)),sinh_(a))); // = 2cosh(a)sinh(a)
    }
    if (foo.size() > 0)
        foo.insert(foo.begin(), Copy(this));

    return foo;
}

vector<Expr > Tanh::getAlternateForms() const
{
    vector<Expr > foo(2);
    foo[0] = fraction_(sinh_(argument),cosh_(argument));
    foo[1] = Copy(this);
    if (argument->getType() == smType::Plus and argument->getNArgs() == 2) // tanh(a+b)
    {
        Expr arg1 = argument->getArgument(0);
        Expr arg2 = argument->getArgument(1);
        foo.push_back(times_(plus_(tanh_(arg1),tanh_(arg2)),pow_(plus_(ONE,times_(tanh_(arg1),tanh_(arg2))),int_(-1)))); // = (tanh(a)+tanh(b))/(1+tanh(a)*tanh(b))
    }
    else if (argument->getType() == smType::Times and argument->getNArgs() == 2 and *argument->getArgument(0) == int_(2)) // tanh(2a)
    {
        Expr arg = argument->getArgument(1);
        foo.push_back(times_(times_(int_(2),tanh_(arg)),pow_(plus_(ONE,pow_(tanh_(arg),int_(2))),int_(-1)))); // = 2tanh(a)/(1+tanh(a)^2)
    }

    return foo;
}
