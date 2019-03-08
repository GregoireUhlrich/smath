/*! \file indicial.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Objects handling indexed expressions in order to perform indicial tensor
 * calculations.
 */
#ifndef Indicial_H_INCLUDED
#define Indicial_H_INCLUDED

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

class Permutation{

    private:

    int order;
    int sign;
    int symmetry;
    size_t size;
    std::vector<int> permutation;

    public:

    Permutation();
    explicit Permutation(int n);
    explicit Permutation(const std::vector<int>& t_permutation);
    Permutation(int n, const std::initializer_list<int>& list);
    Permutation(int n,
                const std::initializer_list<std::initializer_list<int> >& list);
    Permutation(const Permutation& permutation);

    ~Permutation(){}

    size_t getSize() const;
    int getElement(int i) const;
    int getOrder();
    int getSign();
    int getSymmetry() const;
    std::vector<int> getPermutation() const;

    void setSymmetry(int t_symmetry);

    Permutation& operator=(const Permutation& t_permutation);
    Permutation operator*(const Permutation& t_permutation) const;
    bool operator==(const Permutation& t_permutation) const;
    bool operator!=(const Permutation& t_permuation) const;
    int& operator[](int i);
    friend std::ostream& operator<<(std::ostream& fout,
                                    const Permutation& permutation);
};

void reducePermutation(std::vector<Permutation>& permutation);
std::vector<Permutation> getSpan(const std::vector<Permutation>& init);
void getSpan(std::vector<Permutation >& spanned, 
                                     const Permutation& element);

class Symmetry{

    private:

    std::vector<Permutation > permutation;

    public:

    Symmetry();

    Symmetry(const Symmetry& t_symmetry);

    ~Symmetry(){}

    void addSymmetry(const Permutation& newPermutation, int sym=1);

    Symmetry operator*(const Symmetry& symmetry) const;

    friend std::ostream& operator<<(std::ostream& fout, const Symmetry& symmetry);
};

class AbstractIndicial: public AbstractScalar{

    protected:

    int nIndices;
    std::vector<Index> index;

    std::set<std::pair<int,int> > contraction;
    bool fullySymmetric;
    bool fullyAntiSymmetric;

    public:

    AbstractIndicial();

    explicit AbstractIndicial(const std::string& t_name);

    explicit AbstractIndicial(const std::vector<Index>& t_index);

    AbstractIndicial(const AbstractIndicial& abstract) = default;

    AbstractIndicial(const std::string& t_name, const std::vector<Index>& t_index);
     
    ~AbstractIndicial(){};

    smType::PrimaryType getPrimaryType() const override { return smType::Indicial;}

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

    Symmetry symmetry;

    public:

    ITensor();

    explicit ITensor(const std::string& t_name);

    ITensor(const std::string& t_name, const std::vector<Index>& t_index);

    explicit ITensor(const std::vector<Index>& t_index);

    ITensor(const ITensor& tensor) = default;

    ~ITensor(){};

    smType::Type getType() const override {
        return smType::ITensor;
    }

    bool getFullySymmetric() const;
    bool getFullyAntiSymmetric() const;
    void setFullySymmetric() override;
    void setFullyAntiSymmetric() override;
    void addSymmetry(int i1, int i2) override;
    void addAntiSymmetry(int i1, int i2) override;
    int permut(int i1, int i2) override;
    Expr applyPermutation(const std::vector<int>& permutations) const;
    std::vector<Expr> getPermutations() const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    Expr evaluate() override;

    bool operator==(const Expr& expr) const override;

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
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

    smType::Type getType() const override {
        return smType::ITerm;
    }

    int getNArgs(int axis=0) const override;

    Expr getArgument(int iArg=0) const override;

    const std::vector<Expr >& getVectorArgument() const override;

    bool mergeTerms();

    bool operator==(const Expr& expr) const override;

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
};

class ITimes: public Times{

    public:

    ITimes();

    ITimes(const std::vector<Expr >& t_argument, bool explicitTimes=0);

    ITimes(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes=0);

    ~ITimes(){};

    smType::PrimaryType getPrimaryType() const override {
       return smType::Indicial;
    }
};


Expr _itensor_(const std::string& name, Index index);

Expr _itensor_(const std::string& name,
               const std::initializer_list<Index>& indices);

#endif
