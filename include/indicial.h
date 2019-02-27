#ifndef INDICIAL_H_INCLUDED
#define INDICIAL_H_INCLUDED

#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include <map>
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
    const int max;
    Index* contracted;

    public:

    Index();

    explicit Index(const std::string& t_name);

    Index(const std::string& t_name, unsigned int t_max);

    ~Index(){};

    std::string getName() const;

    bool getFree() const;

    const int getMax() const;

    void setName(const std::string& t_name);

    void contract(Index* t_contracted);

    void print() const;

    std::string printLaTeX() const;

    bool operator==(const Index& t_index) const;

    bool operator!=(const Index& t_index) const;
};

/////
// Inline functions

inline Index::Index(): name("i"), free(true), max(3), contracted(nullptr){}
inline Index::Index(const std::string& t_name): name(t_name), free(true),
                                                max(3), contracted(nullptr){}
inline Index::Index(const std::string& t_name, unsigned int t_max): name(t_name),
                                    free(true), max(t_max), contracted(nullptr){}

inline std::string Index::getName() const { return name;}
inline bool Index::getFree() const { return free;}
inline const int Index::getMax() const { return max;}

inline void Index::setName(const std::string& t_name) { name = t_name;}

/////

class AbstractIndicial: public AbstractScalar{

    protected:

    int nIndices;
    std::vector<Index> index;

    int nContractedPairs;
    std::map<int,int> pair;

    std::set<std::pair<int,int> > contraction;
    std::set<std::pair<int,int> > symmetry;
    std::set<std::pair<int,int> > antiSymmetry;

    public:

    AbstractIndicial();

    explicit AbstractIndicial(std::string t_name);

    AbstractIndicial(std::string t_name, std::vector<Index> t_index);

    explicit AbstractIndicial(std::vector<Index> t_index);
     
    ~AbstractIndicial(){};

    PrimaryType getPrimaryType() const { return INDICIAL;}

    int getNIndices() const;

    Index getIndex(int i) const;

    std::vector<Index> getIndexStructure() const;

    bool checkIndexStructure(const std::vector<Index>& t_index) const;

    bool checkIndexStructure(std::initializer_list<Index> index) const;

    int getNContractedPairs() const;

    std::map<int,int> getPair() const;

    void contractIndices(int axis1, int axis2);
};

class ITensor: public AbstractIndicial{

    private:

    public:

    ITensor();

    explicit ITensor(std::string t_name);

    ITensor(std::string t_name, std::vector<Index> t_index);

    explicit ITensor(std::vector<Index> t_index);

    ~ITensor(){};

    Type getType() const override { return ITENSOR;}

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

    PrimaryType getPrimaryType() const { return INDICIAL;}
};


Expr _itensor_(std::string name, Index index);

Expr _itensor_(std::string name, std::initializer_list<Index> indices);

#endif
