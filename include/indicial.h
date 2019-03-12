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


// Returns a < b with specific rules on a and b
bool operator<(std::pair<int,int> a, std::pair<int,int> b);
bool operator>(std::pair<int,int> a, std::pair<int,int> b);

// Only using Space* type. Non-copyable class, One space corresponds to only
// one instance --> comparison of spaces <==> comparison of pointers.
class Space{

    private:

    std::string name;
    int dim;
    bool signedIndex;

    public:

    Space() = delete;
    Space(const Space&) = delete;
    Space(const std::string& t_name, int t_dim);
    Space(const std::string& t_name, int t_dim, bool t_signedIndexed);
    ~Space(){};

    std::string getName() const;
    int getDim() const;
    bool getSignedIndex() const;

    Space& operator=(const Space&) = delete;
};

///////////////////////////////////////////////////
//// Inline functions
///////////////////////////////////////////////////

inline Space::Space(const std::string& t_name, int t_dim)
    :name(t_name), dim(t_dim), signedIndex(false) 
{}

inline Space::Space(const std::string& t_name, int t_dim, bool t_signedIndexed)
    :name(t_name), dim(t_dim), signedIndex(t_signedIndexed) 
{}

inline std::string Space::getName() const {
    return name;
}

inline int Space::getDim() const {
    return dim;
}

inline bool Space::getSignedIndex() const {
    return signedIndex;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////


static const Space Euclid_R("R", 1);
static const Space Euclid_R2("R2", 2);
static const Space Euclid_R3("R3", 3);
static const Space Euclid_R4("R4", 4);
static const Space Lorentz("L",4,true);

class Index{

    private:

    std::string name;
    bool free;
    const Space* space;

    public:

    Index();

    explicit Index(const std::string& t_name);

    Index(const Index& index) = default;

    Index(const std::string& t_name, const Space* t_space);

    ~Index(){};

    std::string getName() const;

    bool getFree() const;

    int getMax() const;

    const Space* getSpace() const;

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

inline Index::Index(): name("i"), free(true), space(&Euclid_R3){}
inline Index::Index(const std::string& t_name): name(t_name), free(true),
                                              space(&Euclid_R3){}
inline Index::Index(const std::string& t_name, const Space* t_space)
     :name(t_name), free(true), space(t_space){}

inline std::string Index::getName() const { return name;}
inline bool Index::getFree() const { return free;}
inline const Space* Index::getSpace() const { return space;}
inline int Index::getMax() const { return space->getDim();}

inline void Index::setName(const std::string& t_name) { name = t_name;}
inline void Index::setFree(bool t_free) { free = t_free;}
/////

class IndexStructure{

    private:

    int nIndices;
    std::vector<Index> index;

    public:

    IndexStructure();

    IndexStructure(const IndexStructure& structure);

    explicit IndexStructure(const std::initializer_list<Index>& structure);

    explicit IndexStructure(const std::vector<Index>& structure);

    ~IndexStructure(){}

    int getNIndices() const;

    Index getIndex(int i) const;

    std::vector<Index> getIndex() const;

    std::vector<Index> getFreeIndex() const;

    IndexStructure getSinglePermutation(int i1, int i2) const;

    IndexStructure getPermutation(const std::vector<int>& permutation) const;

    IndexStructure& operator=(const IndexStructure& structure) = default;

    IndexStructure& operator+=(const Index& newIndex);
    IndexStructure& operator+=(const IndexStructure& structure);
    IndexStructure operator+(const IndexStructure& structure) const;

    bool operator==(const IndexStructure& structure) const;

    bool operator!=(const IndexStructure& structure) const;

    Index operator[](int i) const;
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

    int dim;
    std::vector<Permutation > permutation;

    public:

    Symmetry();

    Symmetry(const Symmetry& t_symmetry);

    ~Symmetry(){}

    int getDim() const;

    size_t getNPermutation() const;

    std::vector<Permutation> getPermutation() const;

    void addSymmetry(const Permutation& newPermutation, int sym=1);

    Symmetry operator*(const Symmetry& symmetry) const;

    bool operator==(const Symmetry& symmetry) const;

    bool operator!=(const Symmetry& symmetry) const;

    friend std::ostream& operator<<(std::ostream& fout, const Symmetry& symmetry);
};

class ITensor;

class IndicialParent{

    protected:

    std::string name;
    bool commutable;

    int dim;
    std::vector<const Space*> space;
    Symmetry symmetry;

    bool fullySymmetric;
    bool fullyAntiSymmetric;

    public:

    IndicialParent();

    explicit IndicialParent(const std::string& t_name);

    IndicialParent(const IndicialParent& abstract) = default;

    IndicialParent(const std::string& t_name,
                   std::initializer_list<const Space*> t_space);
     
    ~IndicialParent(){};

    std::string getName() const;

    bool getCommutable() const;

    int getDim() const;

    int getDim(const Space* t_space) const;

    bool getFullySymmetric() const;

    bool getFullyAntiSymmetric() const;

    void setName(const std::string& t_name);

    void setCommutable(bool t_commutable);

    void setFullySymmetric();

    void setFullyAntiSymmetric();

    void addSymmetry(int i1, int i2);

    void addAntiSymmetry(int i1, int i2);

    Expr operator()(const std::initializer_list<Index>& indices) const;

};

std::vector<std::vector<int> > permutations(const std::vector<int>& init);


class AbstractIndicial: public AbstractScalar{

    protected:

    int nIndices;
    IndexStructure index;

    public:

    AbstractIndicial();
    explicit AbstractIndicial(const std::string& t_name);
    explicit AbstractIndicial(const IndexStructure& t_index);
    AbstractIndicial(const std::string& t_name,
                     const std::initializer_list<Index>& indices);
    ~AbstractIndicial(){};

    smType::PrimaryType getPrimaryType() const override {
        return smType::Indicial;
    }

    int getNIndices() const override {
        return nIndices;
    }

    IndexStructure getIndexStructure() const override {
        return index;
    }
};

class ITensor: public AbstractIndicial{

    protected:

    const IndicialParent* parent;

    public:

    // Friend member of IndicialParent that has access to constructors of 
    // ITensor.
    //friend Expr IndicialParent::operator()(
    //        const std::initializer_list<Index>& indices) const;

    //ITensor() = delete;   

    ITensor(const std::string& t_name,
            bool t_commutable, 
            const std::initializer_list<Index>& indices, 
            const IndicialParent* t_parent);

    explicit ITensor(const Abstract*& expression);

    explicit ITensor(const Expr& expression);

    ~ITensor(){};

    smType::Type getType() const override {
        return smType::ITensor;
    }

    Index getIndex(int i) const override;
    
    const IndicialParent* getParent() const override;

    bool checkIndexStructure(const std::vector<Index>& t_index) const override;

    bool checkIndexStructure(const std::initializer_list<Index>& index) const override;

    void contractIndices(int axis1, int axis2) override;

    void setIndexStructure(const std::vector<Index>& t_index) override;

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


#endif
