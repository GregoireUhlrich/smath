#ifndef INDICIAL_H_INCLUDED
#define INDICIAL_H_INCLUDED

#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include <map>
#include <string>
#include <set>
#include <initializer_list>

enum VectorSpace {
    Default,
    Lorentz,
    Dirac,

};

// Returns a < b with specific rules on a and b
bool operator<(std::pair<int,int> a, std::pair<int,int> b);
bool operator>(std::pair<int,int> a, std::pair<int,int> b);

class Index{

    private:

    std::string name;
    bool free;
    int max;

    public:

    Index();

    explicit Index(const std::string& t_name);

    Index(const Index& index) = default;

    Index(const std::string& t_name, unsigned int t_max);

    ~Index(){};

    std::string getName() const;

    bool getFree() const;

    int getMax() const;

    void setName(const std::string& t_name);

    void setFree(bool t_free);

    void print() const;

    std::string printLaTeX() const;

    Index& operator=(const Index& index) = default;

    bool operator==(const Index& t_index) const;

    bool operator!=(const Index& t_index) const;
};

/////
// Inline functions

inline Index::Index(): name("i"), free(true), max(3){}
inline Index::Index(const std::string& t_name): name(t_name), free(true),
                                                max(3){}
inline Index::Index(const std::string& t_name, unsigned int t_max): name(t_name),
                                    free(true), max(t_max){}

inline std::string Index::getName() const { return name;}
inline bool Index::getFree() const { return free;}
inline int Index::getMax() const { return max;}

inline void Index::setName(const std::string& t_name) { name = t_name;}
inline void Index::setFree(bool t_free) { free = t_free;}
/////

class IndexStructure{

    private:

    int nIndices;
    std::vector<Index> index;

    public:

    IndexStructure();

    IndexStructure(const IndexStructure& t_index);

    explicit IndexStructure(const std::initializer_list<Index>& t_index);

    explicit IndexStructure(const std::vector<Index>& t_index);

    ~IndexStructure(){}

    int getNIndices() const;

    std::vector<Index> getIndex() const;

    std::vector<Index> getFreeIndex() const;

    IndexStructure getSinglePermutation(int i1, int i2) const;

    IndexStructure getPermutation(const std::vector<int>& permutation) const;

    IndexStructure& operator=(const IndexStructure& t_index) = default;
};

/////
// Inline functions

inline IndexStructure::IndexStructure(): nIndices(0){}
inline IndexStructure::IndexStructure(const IndexStructure& t_index):
    nIndices(t_index.nIndices), index(t_index.index){}
inline IndexStructure::IndexStructure(const std::initializer_list<Index>& t_index):
    IndexStructure(std::vector<Index>(t_index.begin(), t_index.end())){}

inline int IndexStructure::getNIndices() const{
    return nIndices;
}
inline std::vector<Index> IndexStructure::getIndex() const{
    return index;
}
/////

template<int t_n>
class Permutation{

    private:

    const int n=t_n;
    std::array<int,t_n> permutation;

    public:

    Permutation();

    explicit Permutation(const std::array<int,t_n>& t_permutation);

    Permutation(const Permutation& permutation);

    ~Permutation(){}

    int getSize() const;
    
    std::array<int,t_n> getPermutation() const;

    Permutation& operator=(const Permutation& t_permutation);

    Permutation operator*(const Permutation& t_permutation);

    private:

    void checkPermutation(const Permutation& t_permutation);
};

/////
// Inline functions

template<int n>
inline Permutation<n>::Permutation(){
    for (int i=0; i<n; ++i)
        permutation[i] = i;
}

template<int n>
inline Permutation<n>::Permutation(const Permutation& t_permutation) {
    checkPermutation(t_permutation);
    for (int i=0; i<n; ++i)
        permutation[i] = t_permutation.permutation[i];
}

template<int n>
inline int Permutation<n>::getSize() const {
    return n;
}

template<int n>
inline void Permutation<n>::checkPermutation(const Permutation& t_permutation) {
    if (n != t_permutation.getSize())
        callError(Invalid_dimension,
        "Permutation<n>::checkPermutation(const Permutation& t_permutation)",
        t_permutation.getSize());
}

class Symmetry{

    public:

    Symmetry();

    Symmetry(const Symmetry& t_symmetry);

    ~Symmetry(){}

    Symmetry& operator=(const Symmetry& t_symmetry) = default;
};

class AbstractIndicial: public AbstractScalar{

    protected:

    int nIndices;
    std::vector<Index> index;

    std::set<std::pair<int,int> > contraction;
    bool fullySymmetric;
    std::set<std::pair<int,int> > symmetry;
    bool fullyAntiSymmetric;
    std::set<std::pair<int,int> > antiSymmetry;

    public:

    AbstractIndicial();

    explicit AbstractIndicial(const std::string& t_name);

    explicit AbstractIndicial(const std::vector<Index>& t_index);

    AbstractIndicial(const AbstractIndicial& abstract) = default;

    AbstractIndicial(const std::string& t_name, const std::vector<Index>& t_index);
     
    ~AbstractIndicial(){};

    PrimaryType getPrimaryType() const override { return INDICIAL;}

    int getNIndices() const override;

    Index getIndex(int i) const override;

    std::vector<Index> getIndexStructure() const override;

    bool checkIndexStructure(const std::vector<Index>& t_index) const override;

    bool checkIndexStructure(const std::initializer_list<Index>& index) const override;

    int getNContractedPairs() const override;

    std::set<std::pair<int,int> > getContractedPair() const override;

    void contractIndices(int axis1, int axis2) override;

    void setIndexStructure(const std::vector<Index>& t_index) override;
};

std::vector<std::vector<int> > permutations(const std::vector<int>& init);

class ITensor: public AbstractIndicial{

    private:

    public:

    ITensor();

    explicit ITensor(const std::string& t_name);

    ITensor(const std::string& t_name, const std::vector<Index>& t_index);

    explicit ITensor(const std::vector<Index>& t_index);

    ITensor(const ITensor& tensor) = default;

    ~ITensor(){};

    Type getType() const override { return ITENSOR;}

    bool getFullySymmetric() const;
    bool getFullyAntiSymmetric() const;
    void setFullySymmetric() override;
    void setFullyAntiSymmetric() override;
    void addSymmetry(int i1, int i2);
    void addAntiSymmetry(int i1, int i2);
    int permut(int i1, int i2) override;
    Expr applyPermutation(const std::vector<int>& permutations) const;
    std::vector<Expr> getPermutations() const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    Expr evaluate() override;

    bool operator==(const Expr& t_abstract) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

class ITerm: public AbstractIndicial{

    private:

    int nArgs;
    std::vector<Expr > argument;

    public:

    ITerm();

    ITerm(const Expr& leftOperand, const Expr& rightOperand);

    explicit ITerm(const std::vector<Expr >& operands);

    ~ITerm(){};

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    Expr evaluate() override;

    Type getType() const override { return ITERM;}

    int getNArgs(int axis=0) const override;

    Expr getArgument(int iArg=0) const override;

    const std::vector<Expr >& getVectorArgument() const override;

    bool mergeTerms();

    bool operator==(const Expr& t_abstract) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

class ITimes: public Times{

    public:

    ITimes();

    ITimes(const std::vector<Expr >& t_argument, bool explicitTimes=0);

    ITimes(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes=0);

    ~ITimes(){};

    PrimaryType getPrimaryType() const override { return INDICIAL;}
};


Expr _itensor_(const std::string& name, Index index);

Expr _itensor_(const std::string& name, const std::initializer_list<Index>& indices);

#endif
