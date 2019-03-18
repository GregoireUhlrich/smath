#include "supportIndicial.h"

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

bool Index::compareWithDummy(const Index& t_index) const
{
    // equivalent to operator== for free indices,
    // more permissive for dummy indices: just tells if the 
    // two indices can be equivalent with a renaming
    if (free)
        return operator==(t_index);
    else
        return (not t_index.free
                and space == t_index.space);
}

bool Index::operator==(const Index& t_index) const
{
    return (name == t_index.name
            and free == t_index.free
            and space == t_index.space);
}

bool Index::operator!=(const Index& t_index) const {
    return !(*this==t_index);
}

bool Index::operator|=(const Index& t_index) const
{
    return operator==(t_index);
}

bool Index::operator&=(const Index& t_index) const
{
    return not operator|=(t_index);
}

bool Index::operator<(const Index& t_index) const
{
    return ((free and not t_index.free)
            or (not(not free and t_index.free)
                and name < t_index.name));
}

bool Index::operator>(const Index& t_index) const
{
    return ((not free and t_index.free)
            or (not(free and not t_index.free)
                and name < t_index.name));
}

bool Index::operator<=(const Index& t_index) const
{
    return (operator<(t_index)
            or operator|=(t_index));
}

bool Index::operator>=(const Index& t_index) const
{
    return (operator>(t_index)
            or operator|=(t_index));
}

ostream& operator<<(ostream& fout, const Index& index)
{
    if (not index.free)
        fout<<"%";
    fout<<index.name;

    return fout;
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
    bool contracted = false;
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
            else if (not contracted)
                contracted = true;
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

bool IndexStructure::compareWithDummy(const IndexStructure& structure,
                                      map<Index,Index>& constraints) const
{
    // Here we search an exact match of the two structures, to a 
    // renaming of dummy indices. The possible already found renaming
    // are in constraints (we must satisfy them) and we can add constraints
    // if we have the liberty
    // Ex: E_{ijk} A_j B_k == E_{iln} A_l B_n --> Comparison of E's adds 
    // the constraints j=l and k=n. Then A_j==A_l and B_k==B_n: Ok.
    // Same argument: E_{ijk} A_j B_k != E_{iln} A_n B_l: constraint found
    // with E is not respected with A and B.
    if (nIndices != structure.getNIndices())
        return false;

    const vector<Index>& t_index = structure.getIndex();
    for (int i=0; i!=nIndices; ++i) {
        // If the index is free, they must be the same
        if (index[i].getFree()) {
            if (index[i] != t_index[i])
                return false;
        }
        // Else we check if the dummie are already constrained, if the 
        // constraint is respected, or add a new constraint
        else {
            // t_index[i] must also be dummy here and must correpond (to a 
            // renaming) to index[i]
            if (not index[i].compareWithDummy(t_index[i]))
                return false;
            if (constraints.find(index[i]) == constraints.end()) {
                if (constraints.find(t_index[i]) == constraints.end()) {
                    // Here the dummies are not constrained: comparison
                    // is ok, and we add the new correspondance
                    constraints[index[i]] = t_index[i];
                    // If the two indices are different, we add the 
                    // correspondance in both directions
                    if (index[i] != t_index[i])
                        constraints[t_index[i]] = index[i];
                }
                else 
                    return false;
            }
            else if (not (constraints[index[i]] == t_index[i]))
                return false;
        }
    }

    return true;
}

bool IndexStructure::operator==(const IndexStructure& structure) const
{
    // Compare only free index Structure,
    // ignore dummy indices (just check compatibility)
    int t_nIndices = structure.getNIndices();
    const vector<Index>& t_index = structure.getIndex();
    vector<int> indicesLeft(0);
    for (int i=0; i<t_nIndices; ++i)
        // comparing only free indices
        if (t_index[i].getFree())
            indicesLeft.push_back(i);

    for (int i=0; i!=nIndices; ++i) {
        // Comparing only free indices
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

bool IndexStructure::operator|=(const IndexStructure& structure) const
{
    return (not operator<(structure) and not operator>(structure));
}

bool IndexStructure::operator&=(const IndexStructure& structure) const
{
    return not operator|=(structure);
}

bool IndexStructure::operator<(const IndexStructure& structure) const
{
    const int n = min(nIndices, structure.nIndices);
    for (int i=0; i!=n; ++i) 
        if (index[i] < structure.index[i])
            return true;
    return nIndices > structure.nIndices;
}

bool IndexStructure::operator>(const IndexStructure& structure) const
{
    const int n = min(nIndices, structure.nIndices);
    for (int i=0; i!=n; ++i) 
        if (index[i] > structure.index[i])
            return true;
    return nIndices < structure.nIndices;
}

bool IndexStructure::operator<=(const IndexStructure& structure) const
{
    return (operator<(structure)
            or operator|=(structure));
}

bool IndexStructure::operator>=(const IndexStructure& structure) const
{
    return (operator>(structure)
            or operator|=(structure));
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

Index& IndexStructure::operator[](int i)
{
    if (i >= 0 and i < nIndices)
        return index[i];
    else
        callError(smError::OutOfBounds,
                "IndexStructure::operator[](int i)", i);
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

vector<int> Permutation::getPermutation() const {
    return permutation;
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

int Permutation::operator[](int i) const {
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

vector<Permutation> permutations(const Permutation& init)
{
    vector<vector<int> > intermediateRep = permutations(
            init.getPermutation());
    vector<Permutation> rep(intermediateRep.size());
    for (size_t i=0; i!=rep.size(); ++i)
        rep[i] = Permutation(intermediateRep[i]);

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
