#ifndef EQUATION_H_INCLUDED
#define EQUATION_H_INCLUDED

#include "symbol.h"

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

class Equation{

    protected:

    smEquation::Type type;

    Expr leftHandSide;
    Expr rightHandSide;

    // Contains all concerned building blocks
    std::vector<Expr> buildingBlocks;

    protected:

    void searchBuildingBlocks();

    public:

    Equation();
    Equation(const Expr& leftHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Expr& leftHandSide,
             const Expr& rightHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Symbol& leftHandSide, smEquation::Type=smEquation::Equal);
    Equation(const Symbol& leftHandSide,
             const Symbol& rightHandSide, smEquation::Type=smEquation::Equal);
    ~Equation(){};

    void isolate(const Expr& expr);
    void isolate(const Symbol& expr);

    friend std::ostream& operator<<(std::ostream& fout, const Equation& eq);
};

#endif
