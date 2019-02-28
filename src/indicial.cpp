#include "indicial.h"

using namespace std;

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

IndexStructure::IndexStructure(const vector<Index>& t_index): 
    nIndices(t_index.size()), index(t_index)
{
    for (auto it=index.begin(); it!=index.end()-1; ++it) {
        for (auto jt=it+1; jt!=index.end(); ++jt) {
            if (*it == *jt) {
                if (it->getFree() xor jt->getFree()) {
                    ostringstream sout;
                    sout<<it->getName()<<"<->"<<jt->getName();
                    callError(Contraction_mismatch,
"AbstractIndicial::AbstractIndicial(string t_name, vector<Index> t_t_index)", 
sout.str());
                }
                else if (it->getFree()){
                    it->setFree(false);
                    *jt = *it;
                }
            }
        }
    }
}

vector<Index> IndexStructure::getFreeIndex() const
{
    vector<Index> rep(0);
    for (const auto& i: index)
        if (i.getFree())
            rep.push_back(i);

    return rep;
}

IndexStructure IndexStructure::getSinglePermutation(int i1, int i2) const
{
    if (i1 < 0 or i2 < 0 or
        i1 >= nIndices or i2 >= nIndices) {
        callError(Out_of_bounds,
"IndexStructure::getSinglePermutation(int i1, int i2) const",
((i1<0 or i1>=nIndices) ? i1 : i2));
    }
    IndexStructure rep = *this;
    swap(rep.index[i1],rep.index[i2]);

    return rep;
}

IndexStructure IndexStructure::getPermutation(const vector<int>& permutation) const
{
    if ((int)permutation.size() != nIndices) {
        callWarning(Invalid_dimension,
"IndexStructure::getPermutation(const vector<int>& permutation) const",
permutation.size());
    }
    vector<Index> newIndex(0);
    for (int i=0; i<nIndices; ++i)
        newIndex.push_back(index[permutation[i]]);

    return IndexStructure(newIndex);
}

template<int n>
Permutation<n>& Permutation<n>::operator=(const Permutation& t_permutation)
{
    checkPermutation(t_permutation);
    for (int i=0; i<n; ++i)
        permutation[i] = t_permutation.permutation[i];

    return *this;
}

template<const int n>
Permutation<n> Permutation<n>::operator*(const Permutation& t_permutation)
{
    checkPermutation(t_permutation);
    array<int,n> newPerm;



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
    fullySymmetric = false;
    fullyAntiSymmetric = false;
}

AbstractIndicial::AbstractIndicial(const string& t_name): AbstractScalar(t_name)
{
    nIndices = 0;
    index = vector<Index>(0);
    fullySymmetric = false;
    fullyAntiSymmetric = false;
}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const vector<Index>& t_index)
                                   :AbstractScalar(t_name)
{
    index = t_index;
    nIndices = index.size();
    fullySymmetric = false;
    fullyAntiSymmetric = false;

    for (int i=0; i<nIndices-1; i++) {
        for (int j=i+1; j<nIndices; j++) {
            if (index[i] == index[j]) {
                if (index[i].getFree() xor index[j].getFree()) {
                    ostringstream sout;
                    sout<<i<<"<->"<<j;
                    callError(Contraction_mismatch,
"AbstractIndicial::AbstractIndicial(string t_name, vector<Index> t_index)", 
sout.str());
                }
                else if (index[i].getFree()){
                    index[i].setFree(false);
                    index[j] = index[i];
                    contraction.emplace(std::pair<int,int>(i,j));
                }
            }
        }
    }
}

AbstractIndicial::AbstractIndicial(const vector<Index>& t_index): AbstractIndicial("",t_index)
{}

int AbstractIndicial::getNIndices() const {
    return nIndices;
}

Index AbstractIndicial::getIndex(int i) const
{
    if (i >= 0 and i < nIndices) return index[i];
    callError(Out_of_bounds,"AbstractIndicial::getIndex(int i) const",i);
    return Index();
}

vector<Index> AbstractIndicial::getIndexStructure() const {
    return index;
}

bool AbstractIndicial::checkIndexStructure(const vector<Index>& t_indices) const
{
    if (nIndices != (int)t_indices.size()) return false;
    vector<int> indicesLeft(nIndices);
    for (int i=0; i<nIndices;i++) indicesLeft[i] = i;

    for (int i=0; i<nIndices; i++) {
        if (index[i].getFree()) {
            bool matched = 0;
            for (size_t j=0; j<indicesLeft.size(); j++) {
                Index foo = t_indices[indicesLeft[j]];
                if (not foo.getFree() or index[i] == foo)
                {
                    indicesLeft.erase(indicesLeft.begin()+j);
                    matched = 1;
                    break;
                }
            }
            if (!matched) return false;
        }
    }
    return true;
}

bool AbstractIndicial::checkIndexStructure(const initializer_list<Index>& t_indices) const {
    return checkIndexStructure(vector<Index>(t_indices.begin(), t_indices.end()));
}

int AbstractIndicial::getNContractedPairs() const {
    return contraction.size();
}

set<pair<int,int> > AbstractIndicial::getContractedPair() const {
    return contraction;
}

void AbstractIndicial::contractIndices(int axis1, int axis2)
{
    if (axis1 < nIndices and axis2 < nIndices and
        axis1 >= 0 and axis2 >= 0) {
        if (index[axis1].getFree() and index[axis2].getFree()) {
            index[axis1].setFree(false);
            index[axis2] = index[axis1];
            contraction.emplace(pair<int,int>(axis1,axis2));
        }
        else
            callError(Contract_dummy,"AbstractIndicial::contractIndices(int axis1, int axis2)",
                                     index[axis1].getName()+"<->"+index[axis2].getName());
    }
    else 
        callError(Out_of_bounds,"AbstractIndicial::contractIndices(int axis1, int axis2)",
                ((axis1<0 or axis1>=nIndices) ? axis1 : axis2));
}

void AbstractIndicial::setIndexStructure(const std::vector<Index>& t_index)
{
    if (nIndices != (int)index.size())
        callWarning(Invalid_dimension,
                "AbstractIndicial::setIndexStructure(const std::vector<Index>& t_index)",
                index.size());
    else
        index = t_index;
}

ITensor::ITensor(): AbstractIndicial()
{}

ITensor::ITensor(const string& t_name): AbstractIndicial(t_name)
{}

ITensor::ITensor(const string& t_name, const vector<Index>& t_index): AbstractIndicial(t_name, t_index)
{}

ITensor::ITensor(const vector<Index>& t_index): AbstractIndicial(t_index)
{}

bool ITensor::getFullySymmetric() const {
    return fullySymmetric;
}
bool ITensor::getFullyAntiSymmetric() const {
    return fullyAntiSymmetric;
}
void ITensor::setFullySymmetric() {
    fullySymmetric = true;
    fullyAntiSymmetric = false;
    symmetry.clear();
    antiSymmetry.clear();
}
void ITensor::setFullyAntiSymmetric() {
    fullySymmetric = false;
    fullyAntiSymmetric = true;
    symmetry.clear();
    antiSymmetry.clear();
}
void ITensor::addSymmetry(int i1, int i2)
{
    if (fullySymmetric) return;
    if (fullyAntiSymmetric) fullyAntiSymmetric = false;
    if (i1 < 0 or i2 < 0 or 
        i1 >= nIndices or i2 >= nIndices)
        callError(Out_of_bounds,"ITensor::permut(int i1, int i2)",
                (i1<0 or i1>=nIndices) ? i1 : i2);
    pair<int,int> couple(i1,i2);
    auto pos = antiSymmetry.find(couple);
    if (pos != antiSymmetry.end())
        antiSymmetry.erase(pos);
    symmetry.emplace(couple);
}
void ITensor::addAntiSymmetry(int i1, int i2)
{
    if (fullyAntiSymmetric) return;
    if (fullySymmetric) fullySymmetric = false;
    if (i1 < 0 or i2 < 0 or 
        i1 >= nIndices or i2 >= nIndices)
        callError(Out_of_bounds,"ITensor::permut(int i1, int i2)",
                (i1<0 or i1>=nIndices) ? i1 : i2);
    pair<int,int> couple(i1,i2);
    auto pos = symmetry.find(couple);
    if (pos != symmetry.end())
        antiSymmetry.erase(pos);
    antiSymmetry.emplace(couple);
}
int ITensor::permut(int i1, int i2) 
{
// Returns 1 if permutation symmetric
// Returns -1 if permutation antisymmetric
// Returns 0 (and does not permut) else
    if (i1 < 0 or i2 < 0 or 
        i1 >= nIndices or i2 >= nIndices)
        callError(Out_of_bounds,"ITensor::permut(int i1, int i2)",
                (i1<0 or i1>=nIndices) ? i1 : i2);
    swap(index[i1],index[i2]);
    return 0;
    if (i2 < i1) swap(i1,i2);
    const pair<int,int> toPermut(i1,i2);
    if (symmetry.find(toPermut) != symmetry.end()) {
        swap(index[i1],index[i2]);
        return 1;
    }
    else if (antiSymmetry.find(toPermut) != antiSymmetry.end()) {
        swap(index[i1],index[i2]);
        return -1;
    }
    return 0;
}

vector<vector<int> > permutations(const vector<int>& init)
{
    const int n = init.size();
    if (n == 0) return vector<vector<int> >(0);
    if (n == 1) return vector<vector<int> >(1,init);

    vector<vector<int> > rep(0);
    vector<int> foo(init);
    for (int i=0; i<n; ++i) {
        foo.erase(foo.begin()+i);
        vector<vector<int> >intermediateRep = permutations(foo);
        for (size_t j=0; j<intermediateRep.size(); ++j)
            intermediateRep[j].insert(intermediateRep[j].begin(), init[i]);
        foo.insert(foo.begin()+i,init[i]);
        rep.insert(rep.end(), intermediateRep.begin(), intermediateRep.end());
    }

    return rep;
}

Expr ITensor::applyPermutation(const vector<int>& permutations) const
{
    if (nIndices != (int)permutations.size())
        callWarning(Invalid_dimension,
                "ITensor::applyPermutation(const vector<int>& permutations) const",
                permutations.size());
    else {
        vector<Index> newIndex(nIndices);
        for (int i=0; i!=nIndices; ++i)
            newIndex[i] = index[permutations[i]];
        Expr res = make_shared<ITensor>(*this);
        res->setIndexStructure(newIndex);
        return res;
    }
    return ZERO;
}

vector<Expr> ITensor::getPermutations() const
{
    vector<Expr> res(1,Copy(this));
    if (fullySymmetric or fullyAntiSymmetric) {
        vector<int> initPerm(nIndices);
        for (int i=0; i!=nIndices; ++i)
            initPerm[i] = i;
        vector<vector<int> > perm = permutations(initPerm);
        res = vector<Expr>(0);
        for (size_t i=0; i!=perm.size(); ++i)
            res.push_back(applyPermutation(perm[i]));
        return res;
    }
    for (auto sym=symmetry.begin(); sym!=symmetry.end(); ++sym) {
        res.insert(res.end(), res.begin(), res.end());
        for (size_t i=res.size()/2; i!=res.size(); ++i) 
            res[i]->permut((*sym).first,(*sym).second);
    }
    for (auto asym=antiSymmetry.begin(); asym!=antiSymmetry.end(); ++asym) {
        res.insert(res.end(), res.begin(), res.end());
        for (size_t i=res.size()/2; i!=res.size(); ++i) 
            res[i]->permut((*asym).first,(*asym).second);
    }

    return res;
}

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

Expr _itensor_(const std::string& name, Index index)
{
    vector<Index> indices(1,index);
    return make_shared<ITensor>(name, indices);
}

Expr _itensor_(const std::string& name, const initializer_list<Index>& t_indices) {
    return make_shared<ITensor>(name,vector<Index>(t_indices.begin(),
                                                   t_indices.end()));
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
