#ifndef EQUATION_H_INCLUDED
#define EQUATION_H_INCLUDED

#include "abstract.h"

namespace smEquation{

    enum Type{

        Equal,
        NEqual,
        Greater,
        Smaller,
        EGreater,
        ESmaller,
    };
};

std::ostream& operator<<(std::ostream& fout, smEquation::Type type);

std::vector<Expr> listBuildingBlocks(const Expr& expr);

// Forward declaration of class Symbol
class Symbol;

class Equation{

    protected:

    smEquation::Type type;

    Expr leftHandSide;
    Expr rightHandSide;

    // Contains all concerned building blocks
    std::vector<Expr> buildingBlocks;

    protected:

    void searchBuildingBlocks();
    void isolationStep(const Expr& expr);

    public:

    Equation();
    Equation(const Expr& leftHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Expr& leftHandSide,
             const Expr& rightHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Symbol& leftHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Symbol& leftHandSide,
             const Symbol& rightHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Equation&) = default;
    ~Equation(){};

    smEquation::Type getType() const;
    Expr getLHS() const;
    Expr getRHS() const;
    const std::vector<Expr>& getBuildingBlocks() const;

    void setBuildingBlocks(const std::vector<Expr>& t_buildingBlocks);

    void replace(const Expr& oldE, const Expr& newE);
    void replace(const Symbol& oldS, const Symbol& newS);
    void simplify();
    void makeLHSimple();
    void isolate(const Expr& expr);
    void isolate(const Symbol& expr);

    bool operator==(const Equation& eq) const;
    bool operator!=(const Equation& eq) const;

    friend std::ostream& operator<<(std::ostream& fout, const Equation& eq);
};

#endif
