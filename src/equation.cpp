#include "equation.h"

using namespace std;

vector<Expr> listBuildingBlocks(const Expr& expr)
{
    if (expr->isBuildingBlock())
        return vector<Expr>(1,expr);
    vector<Expr> list(0);
    int nArgs = expr->getNArgs();
    for (int i=0; i!=nArgs; ++i) {
        vector<Expr> list2 = listBuildingBlocks(expr->getArgument(i));
        if (list2.size() != 0)
            list.insert(list.end(), list2.begin(), list2.end());
    }

    return list;
}

Equation::Equation()
    :type(smEquation::Equal), leftHandSide(ZERO), rightHandSide(ZERO)
{
    searchBuildingBlocks();
}

Equation::Equation(const Expr& LHS, smEquation::Type t_type)
    :type(t_type), leftHandSide(LHS), rightHandSide(ZERO)
{
    searchBuildingBlocks();
}

Equation::Equation(const Expr& LHS, const Expr& RHS, smEquation::Type t_type)
    :type(t_type), leftHandSide(LHS), rightHandSide(RHS)
{
    searchBuildingBlocks();
}

Equation::Equation(const Symbol& LHS, smEquation::Type t_type)
    :type(t_type), leftHandSide(LHS.getAbstract()), rightHandSide(ZERO)
{
    searchBuildingBlocks();
}

Equation::Equation(const Symbol& LHS, const Symbol& RHS, smEquation::Type t_type)
    :type(t_type), leftHandSide(LHS.getAbstract()),
    rightHandSide(RHS.getAbstract())
{
    searchBuildingBlocks();
}


void Equation::searchBuildingBlocks()
{
    buildingBlocks = listBuildingBlocks(leftHandSide);
    vector<Expr> list = listBuildingBlocks(rightHandSide);
    buildingBlocks.insert(buildingBlocks.end(), list.begin(), list.end());
}

void Equation::isolate(const Expr& expr)
{
    Expr sum = ZERO;
    leftHandSide = leftHandSide->develop(true);
    rightHandSide = rightHandSide->develop(true);
    if (leftHandSide->getType() == smType::Plus) {
        for (const_iter arg=leftHandSide->begin();
                arg!=leftHandSide->end(); ++arg)
            if (not (*arg)->dependsExplicitelyOn(expr))
                sum = plus_(sum, *arg);
    }
    if (rightHandSide->getType() == smType::Plus) {
        for (const_iter arg=rightHandSide->begin();
                arg!=rightHandSide->end(); ++arg)
            if ((*arg)->dependsExplicitelyOn(expr))
                sum = plus_(sum, *arg);
    }
    if (*sum != ZERO) {
        leftHandSide = leftHandSide - sum;
        rightHandSide = rightHandSide - sum;
        leftHandSide = leftHandSide->develop(true);
        rightHandSide = rightHandSide->develop(true);
    }

    if (leftHandSide->getType() == smType::Plus) {
        leftHandSide = leftHandSide->factor(expr);
    }
    int order = leftHandSide->isPolynomial(expr);
    if (order > 0) {
        rightHandSide = rightHandSide / (leftHandSide / (expr^order));
        leftHandSide = expr^order;
    }
}

void Equation::isolate(const Symbol& expr)
{
    isolate(expr.getAbstract());
}

ostream& operator<<(ostream& fout, const Equation& eq)
{
    eq.leftHandSide->print(1);
    fout<<eq.type;
    eq.rightHandSide->print(1);

    return fout;
}

ostream& operator<<(ostream& fout, smEquation::Type type)
{
    switch(type) {

        case smEquation::Equal:    fout<<" = ";  break;
        case smEquation::NEqual:   fout<<" != "; break;
        case smEquation::Greater:  fout<<" > ";  break;
        case smEquation::Smaller:  fout<<" < ";  break;
        case smEquation::EGreater: fout<<" >= "; break;
        case smEquation::ESmaller: fout<<" <= "; break;

        default: callError(smError::UnknownEquation,
                "operator<<(ostream&, smEquation::Type)", type);
    }

    return fout;
}
