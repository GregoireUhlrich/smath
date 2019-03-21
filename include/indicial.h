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
#include "supportIndicial.h"
#include <map>
#include <string>
#include <set>
#include <initializer_list>

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
    
    std::vector<Permutation> getPermutation() const;

    void setName(const std::string& t_name);

    void setCommutable(bool t_commutable);

    void setFullySymmetric();

    void setFullyAntiSymmetric();

    void addSymmetry(int i1, int i2);

    void addAntiSymmetry(int i1, int i2);

    void setSymmetry(const Symmetry& t_symetry);

    Expr operator()(const Index& index) const;

    Expr operator()(const std::initializer_list<Index>& indices) const;

};

class AbstractIndicial: public AbstractBuildingBlock{

    protected:

    int nIndices;
    IndexStructure index;

    public:

    AbstractIndicial();
    explicit AbstractIndicial(const std::string& t_name);
    explicit AbstractIndicial(const IndexStructure& t_index);
    AbstractIndicial(const std::string& t_name,
                     const Index& t_index);
    AbstractIndicial(const std::string& t_name,
                     const std::initializer_list<Index>& indices);
    ~AbstractIndicial(){};

    smType::PrimaryType getPrimaryType() const override {
        return smType::Indicial;
    }

    bool isIndexed() const override {
        return true;
    }

    int getNIndices() const override {
        return nIndices;
    }

    IndexStructure getIndexStructure() const override {
        return index;
    }

    bool compareWithDummy(const Expr& expr,
            std::map<Index,Index>& constraints) const override;
};

class ITensor: public AbstractIndicial{

    protected:

    std::vector<Abstract*> contractions;
    const IndicialParent* parent;

    public:

    // Friend member of IndicialParent that has access to constructors of 
    // ITensor.
    //friend Expr IndicialParent::operator()(
    //        const std::initializer_list<Index>& indices) const;

    //ITensor() = delete;   

    ITensor(const std::string& t_name,
            bool t_commutable, 
            const Index& t_index,
            const IndicialParent* t_parent);

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

    bool contractIndex(const Index& indexToContract,
                       const Index& newIndex,
                       Abstract* conctracted) override;

    void setIndexStructure(const IndexStructure& t_index) override;

    Expr applyPermutation(const Permutation& permutations) const;

    std::vector<Expr> getPermutations() const override;

    std::vector<Expr> getAlternateForms() const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    Expr evaluate() override;

    bool operator==(const Expr& expr) const override;

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
};

#endif
