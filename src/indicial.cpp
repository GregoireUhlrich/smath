#include "indicial.h"

using namespace std;

void Index::contract(Index* t_contracted) 
{
    if (not free) {
        callError(Contract_dummy, "Index::contract(const Index*& contracted) ",
                   "("+name+" and "+t_contracted->getName());
    }
    if (max == t_contracted->getMax()) {
        free = false;
        contracted = t_contracted;
        if (contracted->getFree())
            contracted->contract(this);
    }
    else
        callError(Contraction_mismatch, "Index::contract(const Index*& contracted) ",
                   "("+name+" and "+t_contracted->getName());
}

void Index::print() const {
    if (not free) cout<<"%";
    cout<<name;
}

string Index::printLaTeX() const {
    return name;
}

bool Index::operator==(const Index& t_index) const
{
    return (name == t_index.getName() and
            free == t_index.getFree() and 
            max == t_index.getMax());
}

bool Index::operator!=(const Index& t_index) const {
    return !(*this==t_index);
}

bool operator<(std::pair<int,int> a, std::pair<int,int> b)
{
    return (a.first < b.first or
            (a.first == b.first and
             a.second < b.second));
}
bool operator>(std::pair<int,int> a, std::pair<int,int> b)
{
    return (a.first > b.first or
            (a.first == b.first and
             a.second > b.second));
}

AbstractIndicial::AbstractIndicial(): AbstractScalar()
{
    nIndices = 0;
    index = vector<Index>(0);

    nContractedPairs = 0;
    pair = map<int,int>();
}

AbstractIndicial::AbstractIndicial(string t_name): AbstractScalar(t_name)
{
    nIndices = 0;
    index = vector<Index>(0);

    nContractedPairs = 0;
    pair = map<int,int>();
}

AbstractIndicial::AbstractIndicial(string t_name, vector<Index> t_index): AbstractScalar(t_name)
{
    index = t_index;
    nIndices = index.size();

    nContractedPairs = 0;
    pair = map<int,int>();

    for (int i=0; i<nIndices; i++)
        pair.emplace_hint(pair.end(), i, -1);

    bool correctExpression = true;
    for (int i=0; i<nIndices-1; i++)
    {
        for (int j=i+1; j<nIndices; j++)
        {
            if (index[i] == index[j])
            {
                nContractedPairs += 1;
                if (pair[i] != -1 or pair[j] != -1) // index already contracted
                    correctExpression = false;
                pair[i] = j;
                pair[j] = i;
            }
        }
    }
    if (not correctExpression)
    {s
        cout<<"Warning: wrong contraction on indices. \n";
        nIndices = 0;
        index = vector<Index>(0);

        nContractedPairs = 0;
        pair = map<int,int>();
    }
    else
    {
        for (int i=0; i<nIndices; i++)
            if (pair[i] != -1)
                index[i].setFree(false);
    }
}

AbstractIndicial::AbstractIndicial(vector<Index> t_index): AbstractScalar()
{
    index = t_index;
    nIndices = index.size();

    nContractedPairs = 0;
    pair = map<int,int>();

    for (int i=0; i<nIndices; i++)
        pair.emplace_hint(pair.end(), i, -1);

    bool correctExpression = true;
    for (int i=0; i<nIndices-1; i++)
    {
        for (int j=i+1; j<nIndices; j++)
        {
            if (index[i] == index[j])
            {
                nContractedPairs += 1;
                if (pair[i] != -1 or pair[j] != -1) // index already contracted
                    correctExpression = false;
                pair[i] = j;
                pair[j] = i;
                index[i].setFree(false);
                index[j].setFree(false);
            }
        }
    }
    if (not correctExpression)
    {
        cout<<"Warning: wrong contraction on indices. \n";
        nIndices = 0;
        index = vector<Index>(0);

        nContractedPairs = 0;
        pair = map<int,int>();
    }
}

int AbstractIndicial::getNIndices() const
{
    return nIndices;
}

Index AbstractIndicial::getIndex(int i) const
{
    if (i < nIndices) return index[i];
    cout<<"Warning: dimension "<<i<<" out of bounds for "<<name<<".\n";
    return Index();
}

vector<Index> AbstractIndicial::getIndexStructure() const
{
    return index;
}

bool AbstractIndicial::checkIndexStructure(const vector<Index>& t_indices) const
{
    if (nIndices != (int)t_indices.size()) return false;
    vector<int> indicesLeft(nIndices);
    for (int i=0; i<nIndices;i++) indicesLeft[i] = i;

    Index foo;
    for (int i=0; i<nIndices; i++)
    {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++)
        {
            foo = t_indices[indicesLeft[j]];
            if (index[i] == foo)
            {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched) return false;
    }
    return true;
}

bool AbstractIndicial::checkIndexStructure(initializer_list<Index> t_indices) const
{
    vector<Index> foo(0);
    for ( Index index : t_indices)
        foo.push_back(index);
    return checkIndexStructure(foo);
}

int AbstractIndicial::getNContractedPairs() const
{
    return nContractedPairs;
}

map<int,int> AbstractIndicial::getPair() const
{
    return pair;
}

void AbstractIndicial::contractIndices(int axis1, int axis2)
{
    if (axis1 < nIndices and axis2 < nIndices)
    {
        if (index[axis1].getFree() and index[axis2].getFree())
        {
            index[axis1].setFree(false);
            index[axis2] = index[axis1];
            pair[axis1] = axis2;
            pair[axis2] = axis1;
        }
        else cout<<"Warning: contracted dummy indices.\n";
    }
    else cout<<"Warning: contracting axis out of bounds for indicial expression.\n";
}

ITensor::ITensor(): AbstractIndicial()
{}

ITensor::ITensor(string t_name): AbstractIndicial(t_name)
{}

ITensor::ITensor(string t_name, vector<Index> t_index): AbstractIndicial(t_name, t_index)
{}

ITensor::ITensor(vector<Index> t_index): AbstractIndicial(t_index)
{}

void ITensor::print(int mode) const
{
    cout<<name;
    if (nIndices > 0)
    {
        cout<<"_";
        if (nIndices > 1)
        {
            cout<<"{";
            for (int i=0; i<nIndices; i++)
                index[i].print();
            cout<<"}";
        }
        else index[0].print();
    }
    if (mode == 0)
        cout<<endl;
}

string ITensor::printLaTeX(int mode) const
{
    ostringstream sout;
    sout<<name;
    if (nIndices > 0)
    {
        sout<<"_";
        if (nIndices > 1)
        {
            sout<<"{";
            for (int i=0; i<nIndices; i++)
                index[i].print();
            sout<<"}";
        }
        else index[0].print();
    }
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

Expr ITensor::evaluate()
{
    cout<<"Warning: evaluate function for ITensor not yet implemented.\n";
    return ZERO;
}

bool ITensor::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (t_abstract->getType() != ITENSOR) return false;
    if (name != t_abstract->getName() or nIndices != t_abstract->getNIndices()) return false;
    for (int i=0; i<nIndices; i++)
        if (index[i] != t_abstract->getIndex(i))
            return false;
    return true;
}

Expr _itensor_(std::string name, Index index)
{
    vector<Index> indices(1,index);
    return make_shared<ITensor>(name, indices);
}

Expr _itensor_(std::string name, initializer_list<Index> t_indices)
{
    vector<Index> indices(0);
    for (Index index : t_indices)
        indices.push_back(index);

    return make_shared<ITensor>(name, indices);
}


ITerm::ITerm(): AbstractIndicial()
{
    nArgs = 0;
    argument = vector<Expr >(0);
}

ITerm::ITerm(const Expr& leftOperand, const Expr& rightOperand): AbstractIndicial()
{
    nArgs = 2;
    argument = vector<Expr >(2);
    argument[0] = leftOperand;
    argument[1] = rightOperand;

    index = argument[0]->getIndexStructure();
    vector<Index> foo = argument[1]->getIndexStructure();
    index.insert(index.end(), foo.begin(), foo.end());

    mergeTerms();
}

ITerm::ITerm(const std::vector<Expr >& operands)
{
    argument = operands;
    nArgs = argument.size();
    index = argument[0]->getIndexStructure();
    vector<Index> foo;
    for (int i=1; i<nArgs; i++)
    {
        foo = argument[i]->getIndexStructure();
        index.insert(index.end(), foo.begin(), foo.end());
    }
    mergeTerms();
}

void ITerm::print(int mode) const
{
    if (mode == 0 and name != "") cout<<name<<" = ";
    if (mode > 2) cout<<"(";
    for (int i=0; i<nArgs; i++)
        argument[i]->print(2);
    if (mode > 2) cout<<")";
    if (mode == 0) cout<<endl;
}

string ITerm::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") sout<<name<<" = ";
    if (mode > 2) sout<<"(";
    for (int i=0; i<nArgs; i++)
        sout<<argument[i]->printLaTeX(2);
    if (mode > 2) sout<<")";
    if (mode == 0) sout<<endl;

    return sout.str();
}

Expr ITerm::evaluate()
{
    return Copy(this);
}

int ITerm::getNArgs(int axis) const
{
    return nArgs;
}

Expr ITerm::getArgument(int iArg) const
{
    if (iArg < nArgs) return argument[iArg];
    else cout<<"Warning: index "<<iArg<<" out of bound of ITerm.\n";
    return ZERO;
}

const vector<Expr >& ITerm::getVectorArgument() const
{
    return argument;
}

bool ITerm::mergeTerms()
{
    bool simplified = false;
    print();
    for (int i=0; i<nArgs; i++)
    {
        argument[i]->print();
        cout<<endl;
        if (argument[i]->getType() == ITERM)
        {
            int nArgs_bis = argument[i]->getNArgs();
            int i_bis = i;
            simplified = true;
            for (int j=0; j<nArgs_bis; j++)
            {
                argument.insert(argument.begin()+i+1,argument[i_bis]->getArgument(j));
                i++;
                print();
            }
            argument.erase(argument.begin()+i_bis);
            i--;
        }
        nArgs = argument.size();
    }

    return simplified;
}

bool ITerm::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (t_abstract->getType() != ITERM) return false;
    if (t_abstract->getNArgs() != nArgs) return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++) indicesLeft[i] = i;

    Expr foo;
    for (int i=0; i<nArgs; i++)
    {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++)
        {
            foo = t_abstract->getArgument(indicesLeft[j]);
            if (!argument[i]-> getCommutable() and !foo->getCommutable() and *argument[i]!=foo) break;
            if (*argument[i] == foo)
            {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = 1;
                break;
            }
        }
        if (!matched) return false;
    }

    return true;
}

ITimes::ITimes(): Times(){}

ITimes::ITimes(const vector<Expr >& t_argument, bool explicitTimes): Times(t_argument, explicitTimes){}

ITimes::ITimes(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes): Times(leftOperand, rightOperand, explicitTimes){}
