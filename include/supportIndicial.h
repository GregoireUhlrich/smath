#ifndef SUPPORTINDICIAL_H_INCLUDED
#define SUPPORTINDICIAL_H_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <initializer_list>

#include <memory>

class Space;
class Index;
typedef std::shared_ptr<Index> Idx;

class Index{

    private:

    std::string name;
    bool free;
    bool sign;
    const Space* space;

    public:

    Index();

    explicit Index(const std::string& t_name);

    Index(const Index& index) = default;

    Index(const std::string& t_name, const Space* t_space);

    ~Index(){};

    std::string getName() const;

    bool getSign() const;

    bool getFree() const;

    int getMax() const;

    const Space* getSpace() const;

    void setName(const std::string& t_name);

    void setSign(bool t_sign);

    void setFree(bool t_free);

    bool testContraction(Index& t_index);

    void print() const;

    std::string printLaTeX() const;

    Index& operator=(const Index& index) = default;

    bool compareWithDummy(const Index& t_index) const;

    bool compareWithoutSign(const Index& t_index) const;

    bool exactMatch(const Index& t_index) const;

    bool operator==(const Index& t_index) const;

    bool operator!=(const Index& t_index) const;

    bool operator|=(const Index& index) const;

    bool operator&=(const Index& index) const;

    bool operator<(const Index& index) const;

    bool operator>(const Index& index) const;

    bool operator<=(const Index& index) const;

    bool operator>=(const Index& index) const;

    friend Index operator+(const Index& index);
     
    friend Index operator-(const Index& index);

    friend std::ostream& operator<<(std::ostream& fout, const Index& index);
};

Idx operator+(const Idx& index);
Idx operator-(const Idx& index);

class IndexStructure{

    private:

    int nIndices;
    std::vector<Idx> index;

    public:

    IndexStructure();

    explicit IndexStructure(int t_nIndices);

    IndexStructure(const IndexStructure& structure);

    explicit IndexStructure(const std::initializer_list<Idx>& structure);

    explicit IndexStructure(const std::vector<Idx>& structure);

    ~IndexStructure(){}

    int getNIndices() const;

    Idx getIndex(int i) const;

    std::vector<Idx> getIndex() const;

    std::vector<Idx> getFreeIndex() const;

    IndexStructure getFreeStructure() const;

    IndexStructure getSinglePermutation(int i1, int i2) const;

    IndexStructure getPermutation(const std::vector<int>& permutation) const;

    void setIndex(const Index& newIndex, int iIndex=0);

    IndexStructure& operator=(const IndexStructure& structure) = default;

    IndexStructure& operator+=(const Idx& newIndex);

    IndexStructure& operator+=(const IndexStructure& structure);

    IndexStructure operator+(const IndexStructure& structure) const;

    bool exactMatch(const IndexStructure& structure) const;
    bool compareWithDummy(const IndexStructure& structure) const;
    bool compareWithDummy(const IndexStructure& structure,
                          std::map<Index,Index>& constraints) const;

    bool operator==(const IndexStructure& structure) const;

    bool operator!=(const IndexStructure& structure) const;

    bool operator|=(const IndexStructure& structure) const;

    bool operator&=(const IndexStructure& structure) const;

    bool operator<(const IndexStructure& structure) const;

    bool operator>(const IndexStructure& structure) const;

    bool operator<=(const IndexStructure& structure) const;

    bool operator>=(const IndexStructure& structure) const;

    Idx operator[](int i) const;

    Idx& operator[](int i);

    friend std::ostream& operator<<(std::ostream& fout, const IndexStructure& structure);
};

/////
// Inline functions

inline IndexStructure::IndexStructure(): nIndices(0){}
inline IndexStructure::IndexStructure(int t_nIndices)
    :nIndices(t_nIndices),
    index(std::vector<Idx>(t_nIndices,std::make_shared<Index>())){}
inline IndexStructure::IndexStructure(const IndexStructure& t_index):
    nIndices(t_index.nIndices), index(t_index.index){}
inline IndexStructure::IndexStructure(const std::initializer_list<Idx>& t_index):
    IndexStructure(std::vector<Idx>(t_index)){}

inline int IndexStructure::getNIndices() const{
    return nIndices;
}
inline std::vector<Idx> IndexStructure::getIndex() const{
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

    int operator[](int i) const;

    friend std::ostream& operator<<(std::ostream& fout,
                                    const Permutation& permutation);
};

std::vector<std::vector<int> > permutations(const std::vector<int>& init);
std::vector<Permutation> permutations(const Permutation& init);
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
#endif
