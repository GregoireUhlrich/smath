#include "indicial.h"
#include "error.h"

using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class Index                                   //
/*************************************************/
///////////////////////////////////////////////////

void Index::print() const {
    if (not free)
        cout<<"%";
    cout<<name;
}

string Index::printLaTeX() const {
    return name;
}

bool Index::operator==(const Index& t_index) const
{
    return (name == t_index.getName() and
            free == t_index.getFree() and 
            space == t_index.getSpace());
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
                    callError(smError::ContractionMismatch,
"IndicialParent::IndicialParent(string t_name, vector<Index> t_t_index)", 
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

Index IndexStructure::getIndex(int i) const
{
    if (i >= 0 and i<nIndices)
        return index[i];
    else 
        callError(smError::OutOfBounds,
                "IndexStructure::getIndex(int i) const", i);
    return Index();
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
        callError(smError::OutOfBounds,
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
        callWarning(smError::InvalidDimension,
"IndexStructure::getPermutation(const vector<int>& permutation) const",
permutation.size());
    }
    vector<Index> newIndex(0);
    for (int i=0; i<nIndices; ++i)
        newIndex.push_back(index[permutation[i]]);

    return IndexStructure(newIndex);
}

IndexStructure& IndexStructure::operator+=(const Index& newIndex)
{
    for (auto& i : index) {
        if (i == newIndex) {
            if (i.getFree()) {
                // If the index is equal to an already existing index,
                // Einstein convention: summation
                i.setFree(false);
                ++nIndices;
                index.push_back(i);
                return *this;
            }
            else // Index equal to a dummy index: Error
                callError(smError::ContractDummy, 
                        "IndexStructure::operator+=(const Index& newIndex)", 
                        i.getName()+"<->"+newIndex.getName());
        }
    }
    // New index (not already present: we add it simply)
    ++nIndices;
    index.push_back(newIndex);

    return *this;
}

IndexStructure& IndexStructure::operator+=(const IndexStructure& structure)
{
    const int n = structure.getNIndices();
    for (int i=0; i<n; ++i)
        operator+=(structure.getIndex(i));

    return *this;
}

IndexStructure IndexStructure::operator+(const IndexStructure& structure) const
{
    IndexStructure newStructure(*this);
    const int n = structure.getNIndices();
    for (int i=0; i<n; ++i)
        newStructure += structure.getIndex(i);

    return newStructure;
}

bool IndexStructure::operator==(const IndexStructure& structure) const
{
    int t_nIndices = structure.getNIndices();
    const vector<Index>& t_index = structure.getIndex();
    vector<int> indicesLeft(0);
    for (int i=0; i<t_nIndices; ++i)
        if (t_index[i].getFree())
            indicesLeft.push_back(i);

    for (int i=0; i!=nIndices; ++i) {
        if (index[i].getFree()) {
            bool match = false;
            for (size_t j=0; j!=indicesLeft.size(); ++j) {
                if (index[i] == t_index[indicesLeft[j]]) {
                    match = true;
                    indicesLeft.erase(indicesLeft.begin()+j);
                    break;
                }
            }
            if (not match)
                return false;
        }
    }

    if (not indicesLeft.empty())
        return false;

    return true;
}

bool IndexStructure::operator!=(const IndexStructure& structure) const
{
    return (not operator==(structure));
}

Index IndexStructure::operator[](int i) const
{
    if (i >= 0 and i < nIndices)
        return index[i];
    else
        callError(smError::OutOfBounds,
                "IndexStructure::operator[](int i)", i);
    return Index();
}

///////////////////////////////////////////////////
/*************************************************/
// Class Permutation                             //
/*************************************************/
///////////////////////////////////////////////////

Permutation::Permutation(): order(0),sign(0),symmetry(0),size(1),
                            permutation(vector<int>(1,0)){}

Permutation::Permutation(int n)
    :order(0), sign(0), symmetry(0), size(n), permutation(std::vector<int>(n))
{
    for (int i=0; i!=n; ++i)
        permutation[i] = i;
}

Permutation::Permutation(const std::vector<int>& t_permutation)
    :order(0), sign(0), symmetry(0), size(t_permutation.size())
{
    permutation = std::vector<int>(size);
    for (size_t i=0; i<size; ++i)
        permutation[i] = t_permutation[i];
}

Permutation::Permutation(int n, const std::initializer_list<int>& list)
    :Permutation(n,{list})
{}

Permutation::Permutation(int n,
        const std::initializer_list<std::initializer_list<int> >& list)
    :order(0), sign(0), symmetry(0), size(n)
{
    std::vector<int> indicesLeft(size);
    for (size_t i=0; i!=size; ++i) indicesLeft[i] = i;
    permutation = indicesLeft;
    for (auto cycle=list.begin(); cycle!=list.end(); ++cycle) {
        if (cycle->size() > 0) {
            for (auto element=cycle->begin()+1; element!=cycle->end(); ++element) {
                if (indicesLeft[*element] == -1 or 
                    indicesLeft[*element] < 0 or
                    indicesLeft[*element] >= n)
                    callError(smError::OutOfBounds,
    "Permutation::Permutation(const init_list<init_list<int> >& list)",*element);
                indicesLeft[*element] = -1;
                permutation[*(element-1)] = *element;
            }
            if (cycle->size() > 1) 
                permutation[*(cycle->end()-1)] = *cycle->begin();
        }
    }
}

Permutation::Permutation(const Permutation& t_permutation):
    order(t_permutation.order), sign(t_permutation.sign) ,
    symmetry(t_permutation.symmetry),
    size(t_permutation.getSize()), permutation(t_permutation.permutation){}

size_t Permutation::getSize() const {
    return size;
}

int Permutation::getElement(int i) const {
    if (i < 0 or i >= (int)size)
        callError(smError::OutOfBounds,
                "Permutation::getElement(int i) const", i);
    return permutation[i];
}

int Permutation::getOrder()
{
    if (order > 0) 
        return order;
    Permutation identity(size);
    order = 1;
    Permutation perm = (*this)*identity;
    while(perm != identity) {
        ++order;
        perm = (*this)*perm;
    }

    return order;
}

int Permutation::getSign()
{
    if (sign != 0) 
        return sign;
    sign = 1;
    Permutation foo(permutation);
    for (size_t i=0; i!=size; ++i) {
        if (foo[i] != (int)i) {
            for (size_t j=0; j!=size; ++j) {
                if (foo[j] == (int)i) {
                    std::swap(foo[i],foo[j]);
                    sign *= -1;
                    break;
                }
            }
        }
    }

    return sign;
}

int Permutation::getSymmetry() const {
    return symmetry;
}

void Permutation::setSymmetry(int t_symmetry) {
    if (t_symmetry != 1 and
        t_symmetry != 0 and 
        t_symmetry != -1)
        return;
    symmetry = t_symmetry;
}

bool Permutation::operator==(const Permutation& t_permutation) const {
    if (size != t_permutation.getSize()) 
        return false;
    for (size_t i=0; i<size; ++i)
        if (permutation[i] != t_permutation.getElement(i))
            return false;

    return true;
}

bool Permutation::operator!=(const Permutation& t_permutation) const {
    return (not (*this==t_permutation));
}

Permutation& Permutation::operator=(const Permutation& t_permutation)
{
    order = t_permutation.order;
    sign = t_permutation.sign;
    symmetry = t_permutation.symmetry;
    size = t_permutation.size;
    permutation = t_permutation.permutation;

    return *this;
}

Permutation Permutation::operator*(const Permutation& t_permutation) const
{
    std::vector<int> newPerm(size);
    for (size_t i=0; i!=size; ++i)
        newPerm[i] = permutation[t_permutation.getElement(i)];

    Permutation rep = Permutation(newPerm);
    rep.setSymmetry(symmetry*t_permutation.getSymmetry());

    return rep;
}

int& Permutation::operator[](int i) {
    if (i < 0 or i >= (int)size)
        callError(smError::OutOfBounds,
                "Permutation::operator[](int i) const", i);
    return permutation[i];
}

std::ostream& operator<<(std::ostream& fout, const Permutation& permutation)
{
    fout<<"Permutation of "<<permutation.size<<" elements: ";
    for (size_t i=0; i!=permutation.size; ++i)
        fout<<permutation.getElement(i)<<" ";
    
    return fout;
}

///////////////////////////////////////////////////
// Utils for permutations, as for example getting
// all permutations spanned by an intial set.
///////////////////////////////////////////////////

// Returns all permutations of elements in a vector<int>
// Returns then a vector<vector<int> >.
// Ex permutations({1,2,3}) =
// { {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1} }
vector<vector<int> > permutations(const vector<int>& init)
{
    const int n = init.size();
    if (n == 0) 
        return vector<vector<int> >(0);
    if (n == 1)
        return vector<vector<int> >(1,init);

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

// Erase redundant permutations in the vector permutation
void reducePermutation(std::vector<Permutation >& permutation)
{
    for (size_t i=0; i<permutation.size()-1; ++i) {
        for (size_t j=i+1; j!=permutation.size(); ++j) {
            if (permutation[i] == permutation[j]) {
                permutation.erase(permutation.begin()+j);
                --j;
            }
        }
    }
}

// Returns all the elements of the permutation group spanned by init
std::vector<Permutation > getSpan(const std::vector<Permutation >& init)
{
    std::vector<Permutation > rep = init;
    reducePermutation(rep);
    std::vector<Permutation > newPermutation = rep;
    while (not newPermutation.empty()) {
        const size_t size = rep.size();
        for (size_t i=0; i!=newPermutation.size(); ++i) {
            for (size_t j=0; j!=size; ++j) {
                rep.push_back(newPermutation[i]*rep[j]);
                rep.push_back(rep[j]*newPermutation[i]);
            }
        }
        reducePermutation(rep);
        newPermutation = std::vector<Permutation >(rep.begin()+size, rep.end());
    }

    return rep;
}

// Same as before, but simply adding element in spanned. This function 
// makes the assumption that spanned is already complete
void getSpan(std::vector<Permutation >& spanned, 
                                     const Permutation& element)
{
    spanned.push_back(element);
    std::vector<Permutation > newPermutation(1,element);
    while (not newPermutation.empty()) {
        const size_t size = spanned.size();
        for (size_t i=0; i!=newPermutation.size(); ++i) {
            for (size_t j=0; j!=size; ++j) {
                spanned.push_back(newPermutation[i]*spanned[j]);
                spanned.push_back(spanned[j]*newPermutation[i]);
            }
        }
        reducePermutation(spanned);
        newPermutation = std::vector<Permutation >(spanned.begin()+size, 
                                                   spanned.end());
    }
}

///////////////////////////////////////////////////
/*************************************************/
// Class Symmetry                                //
/*************************************************/
///////////////////////////////////////////////////

Symmetry::Symmetry(): dim(-1), permutation(std::vector<Permutation >(0)) {}

Symmetry::Symmetry(const Symmetry& symmetry):dim(-1),
                                             permutation(symmetry.permutation){}

int Symmetry::getDim() const {
    return dim;
}

size_t Symmetry::getNPermutation() const {
    return permutation.size();
}

vector<Permutation> Symmetry::getPermutation() const {
    return permutation;
}

void Symmetry::addSymmetry(const Permutation& newPermutation, int sym)
{
    if (dim != -1 and dim != (int)newPermutation.getSize()) {
        callError(smError::SymmetryMismatch,
    "Symmetry::addSymmetry(const Permutation& newPermutation, int sym)");
    }
    if (dim == -1)
        dim = newPermutation.getSize();

    if (sym > 0) 
        sym =  1;
    else         
        sym = -1;

    if (newPermutation.getSymmetry() != 0) 
        sym = newPermutation.getSymmetry();
    auto pos = find(permutation.begin(), permutation.end(), newPermutation);
    if (pos != permutation.end()) {
        if (sym == (*pos).getSymmetry())
            return;
        callError(smError::SymmetryMismatch,
    "Symmetry::addSymmetry(const Permutation& newPermutation, int sym)");
    }
    Permutation foo = newPermutation;
    foo.setSymmetry(sym);
    getSpan(permutation, foo);
}

bool Symmetry::operator==(const Symmetry& symmetry) const
{
    if (permutation.size() != symmetry.getNPermutation() 
            or dim != symmetry.getDim())
        return false;

    const vector<Permutation>& t_permutation = symmetry.getPermutation();
    vector<int> indicesLeft(t_permutation.size());
    for (size_t i=0; i!= indicesLeft.size(); ++i)
        indicesLeft[i] = i;

    for (size_t i=0; i!=permutation.size(); ++i) {
        bool match = false;
        for (size_t j=0; j!=indicesLeft.size(); ++j) {
            if (permutation[i] == t_permutation[indicesLeft[j]]) {
                match = true;
                indicesLeft.erase(indicesLeft.begin()+j);
                break;
            }
        }
        if (not match)
            return false;
    }

    return true;
}

bool Symmetry::operator!=(const Symmetry& symmetry) const
{
    return (not operator==(symmetry));
}

std::ostream& operator<<(std::ostream& fout, const Symmetry& symmetry)
{
    fout<<symmetry.permutation.size()<<" symmetries:\n";
    for (const auto& perm : symmetry.permutation) {
        if (perm.getSymmetry() == 1)
            fout<<"  -> Symmetry:     ";
        else 
            fout<<"  -> AntiSymmetry: ";
        fout<<perm<<std::endl;
    }

    return fout;
}

///////////////////////////////////////////////////
// Comparison operators between pairs of integers
///////////////////////////////////////////////////

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
//
///////////////////////////////////////////////////
/*************************************************/
// Class IndicialParent                        //
/*************************************************/
///////////////////////////////////////////////////

IndicialParent::IndicialParent(): name(""), commutable(true), dim(0), 
    space(vector<const Space*>(0)), symmetry(), fullySymmetric(false),
    fullyAntiSymmetric(false)
{}

IndicialParent::IndicialParent(const string& t_name): name(t_name),
    commutable(true), dim(0), space(vector<const Space*>(0)), symmetry(),
    fullySymmetric(false), fullyAntiSymmetric(false)
{}

IndicialParent::IndicialParent(const string& t_name,
                               const std::initializer_list<const Space*> t_space)
    :name(t_name), commutable(true), dim(t_space.size()), space(t_space),
    symmetry(), fullySymmetric(false), fullyAntiSymmetric(false)
{}

string IndicialParent::getName() const {
    return name;
}

bool IndicialParent::getCommutable() const {
    return commutable;
}

int IndicialParent::getDim() const {
    return dim;
}

bool IndicialParent::getFullySymmetric() const {
    return fullySymmetric;
}
bool IndicialParent::getFullyAntiSymmetric() const {
    return fullyAntiSymmetric;
}

void IndicialParent::setName(const std::string& t_name) {
    name = t_name;
}
void IndicialParent::setCommutable(bool t_commutable) {
    commutable = t_commutable;
}

void IndicialParent::setFullySymmetric() {
    fullySymmetric = true;
    fullyAntiSymmetric = false;
}
void IndicialParent::setFullyAntiSymmetric() {
    fullySymmetric = false;
    fullyAntiSymmetric = true;
}
void IndicialParent::addSymmetry(int i1, int i2)
{
    if (fullySymmetric) 
        return;
    if (fullyAntiSymmetric) 
        fullyAntiSymmetric = false;

    if (i1 < 0 or i2 < 0 or 
        i1 >= dim or i2 >= dim)
        callError(smError::OutOfBounds,"IndicialParent::addSymmetry(int i1, int i2)",
                (i1<0 or i1>=dim) ? i1 : i2);
}
void IndicialParent::addAntiSymmetry(int i1, int i2)
{
    if (fullyAntiSymmetric) return;
    if (fullySymmetric) fullySymmetric = false;
    if (i1 < 0 or i2 < 0 or 
        i1 >= dim or i2 >= dim)
        callError(smError::OutOfBounds,"ITensor::addAntiSymmetry(int i1, int i2)",
                (i1<0 or i1>=dim) ? i1 : i2);
}

Expr IndicialParent::operator()(const initializer_list<Index>& indices) const
{
    if (indices.size() != (size_t)dim) {
        callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Index>& indices) const");
    }
    for (auto index=indices.begin(); index!=indices.end(); ++index)
        if (index->getSpace() != space[distance(indices.begin(), index)])
            callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Index>& indices) const");

    return make_shared<ITensor>(name, commutable, indices, this);
}


////////////////////////////////////////////////////
///*************************************************/
// Class AbstractIndicial                          //
///*************************************************/
/////////////////////////////////////////////////////

AbstractIndicial::AbstractIndicial(): AbstractScalar() 
{}

AbstractIndicial::AbstractIndicial(const string& t_name)
    :AbstractScalar(t_name)
{}

AbstractIndicial::AbstractIndicial(const IndexStructure& t_index)
    :AbstractScalar(), index(t_index)
{}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const initializer_list<Index>& indices)
    :AbstractScalar(t_name), nIndices(indices.size()), index(indices)
{}

///////////////////////////////////////////////////
/*************************************************/
// Class ITensor                                 //
/*************************************************/
///////////////////////////////////////////////////

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const initializer_list<Index>& indices,
                 const IndicialParent* t_parent)
    :AbstractIndicial(t_name, indices), parent(t_parent)
{
    commutable = t_commutable;
}

// Constructor crashes if expr is not an ITensor
ITensor::ITensor(const Abstract*& expr): parent(expr->getParent())
{
    name = expr->getName();
    commutable = expr->getCommutable();
    nIndices = expr->getNIndices();
    index = expr->getIndexStructure();
}

// Constructor crashes if expr is not an ITensor
ITensor::ITensor(const Expr& expr): parent(expr->getParent())
{
    name = expr->getName();
    commutable = expr->getCommutable();
    nIndices = expr->getNIndices();
    index = expr->getIndexStructure();
}

Index ITensor::getIndex(int i) const
{
    if (i >= 0 and i < index.getNIndices()) 
        return index[i];
    callError(smError::OutOfBounds,"ITensor::getIndex(int i) const",i);
    return Index();
}

const IndicialParent* ITensor::getParent() const {
    return parent;
}

bool ITensor::checkIndexStructure(const vector<Index>& t_indices) const
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)t_indices.size()) 
        return false;
    vector<int> indicesLeft(nIndices);
    for (int i=0; i<nIndices;i++) 
        indicesLeft[i] = i;

    for (int i=0; i<nIndices; i++) {
        if (index[i].getFree()) {
            bool matched = 0;
            for (size_t j=0; j<indicesLeft.size(); j++) {
                Index foo = t_indices[indicesLeft[j]];
                if (not foo.getFree() or index[i] == foo) {
                    indicesLeft.erase(indicesLeft.begin()+j);
                    matched = 1;
                    break;
                }
            }
            if (!matched) 
                return false;
        }
    }
    return true;
}

bool ITensor::checkIndexStructure(
        const initializer_list<Index>& t_indices) const 
{
    return checkIndexStructure(vector<Index>(t_indices.begin(), t_indices.end()));
}

void ITensor::contractIndices(int axis1, int axis2)
{
    const int nIndices = index.getNIndices();
    if (axis1 < nIndices and axis2 < nIndices and
        axis1 >= 0 and axis2 >= 0) {
        if (index[axis1].getFree() and index[axis2].getFree()) {
            index[axis1].setFree(false);
            index[axis2] = index[axis1];
        }
        else
            callError(smError::ContractDummy,
                    "ITensor::contractIndices(int axis1, int axis2)",
                    index[axis1].getName()+"<->"+index[axis2].getName());
    }
    else 
        callError(smError::OutOfBounds,
                "ITensor::contractIndices(int axis1, int axis2)",
                ((axis1<0 or axis1>=nIndices) ? axis1 : axis2));
}

void ITensor::setIndexStructure(const std::vector<Index>& t_index)
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)t_index.size())
        callWarning(smError::InvalidDimension,
                "ITensor::setIndexStructure(const std::vector<Index>&)",
                t_index.size());
    else 
        index = IndexStructure(t_index);
}

Expr ITensor::applyPermutation(const vector<int>& permutations) const
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)permutations.size())
        callWarning(smError::InvalidDimension,
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
    if (parent->getFullySymmetric() or parent->getFullyAntiSymmetric()) {
        const int nIndices = index.getNIndices();
        vector<int> initPerm(nIndices);
        for (int i=0; i!=nIndices; ++i)
            initPerm[i] = i;
        vector<vector<int> > perm = permutations(initPerm);
        res = vector<Expr>(0);
        for (size_t i=0; i!=perm.size(); ++i)
            res.push_back(applyPermutation(perm[i]));
        return res;
    }

    return res;
}

void ITensor::print(int mode) const
{
    const int nIndices = index.getNIndices();
    cout<<name;
    if (nIndices > 0) {
        cout<<"_";
        if (nIndices > 1) {
            cout<<"{";
            for (int i=0; i<nIndices; i++)
                index[i].print();
            cout<<"}";
        }
        else 
            index[0].print();
    }
    if (mode == 0)
        cout<<endl;
}

string ITensor::printLaTeX(int mode) const
{
    const int nIndices = index.getNIndices();
    ostringstream sout;
    sout<<name;
    if (nIndices > 0) {
        sout<<"_";
        if (nIndices > 1) {
            sout<<"{";
            for (int i=0; i<nIndices; i++)
                index[i].print();
            sout<<"}";
        }
        else 
            index[0].print();
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

bool ITensor::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getType() != smType::ITensor) 
        return false;

    const int nIndices = index.getNIndices();
    if (name != expr->getName() or nIndices != expr->getNIndices()) 
        return false;

    return index == expr->getIndexStructure();
}

///////////////////////////////////////////////////
/*************************************************/
// Class ITerm                                   //
/*************************************************/
///////////////////////////////////////////////////

ITerm::ITerm(): AbstractIndicial()
{
    nArgs = 0;
    argument = vector<Expr >(0);
}

ITerm::ITerm(const Expr& leftOperand, const Expr& rightOperand)
    :AbstractIndicial(leftOperand->getIndexStructure()
            +rightOperand->getIndexStructure())
{
    if (leftOperand->getPrimaryType() != smType::Indicial
            or rightOperand->getPrimaryType() != smType::Indicial)
        callError(smError:: InvalidITensor, 
            "ITerm::ITerm(const Expr& leftOperand, const Expr& rightOperand)");

    nArgs = 2;
    argument = vector<Expr >(2);
    argument[0] = leftOperand;
    argument[1] = rightOperand;

    mergeTerms();
}

ITerm::ITerm(const std::vector<Expr >& operands)
{
    argument = operands;
    nArgs = argument.size();
    index = IndexStructure();
    for (const auto& operand : operands) {
        if (operand->getPrimaryType() != smType::Indicial)
            callError(smError::InvalidITensor,
                    "ITerm::ITerm(const vector<Expr>& operands");
        index += operand->getIndexStructure();
    }
    nIndices = index.getNIndices();

    mergeTerms();
}

void ITerm::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";
    if (mode > 2) 
        cout<<"(";
    for (int i=0; i<nArgs; i++)
        argument[i]->print(2);

    if (mode > 2) 
        cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ITerm::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";
    if (mode > 2) 
        sout<<"(";
    for (int i=0; i<nArgs; i++)
        sout<<argument[i]->printLaTeX(2);

    if (mode > 2) 
        sout<<")";
    if (mode == 0) 
        sout<<endl;

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
    if (iArg < nArgs) 
        return argument[iArg];
    else 
        cout<<"Warning: index "<<iArg<<" out of bound of ITerm.\n";

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
    for (int i=0; i<nArgs; i++) {
        argument[i]->print();
        cout<<endl;
        if (argument[i]->getType() == smType::ITerm) {
            int nArgs_bis = argument[i]->getNArgs();
            int i_bis = i;
            simplified = true;
            for (int j=0; j<nArgs_bis; j++) {
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

bool ITerm::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getType() != smType::ITerm) 
        return false;
    if (expr->getNArgs() != nArgs) 
        return false;
    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++) 
        indicesLeft[i] = i;

    Expr foo;
    for (int i=0; i<nArgs; i++) {
        bool matched = 0;
        for (size_t j=0; j<indicesLeft.size(); j++) {
            foo = expr->getArgument(indicesLeft[j]);
            if (!argument[i]-> getCommutable() 
                    and !foo->getCommutable() 
                    and *argument[i]!=foo) 
                break;
            if (*argument[i] == foo) {
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
