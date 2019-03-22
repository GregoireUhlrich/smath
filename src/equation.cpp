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

void Equation::replace(const Expr& oldE, const Expr& newE)
{
    leftHandSide = Replace(leftHandSide, oldE, newE);
    rightHandSide = Replace(rightHandSide, oldE, newE);
    if (oldE->isBuildingBlock())
        for (iter arg=buildingBlocks.begin(); arg!=buildingBlocks.end(); ++arg)
            if (**arg == oldE) {
                buildingBlocks.erase(arg);
                break;
            }

    if (newE->isBuildingBlock()
            and find(buildingBlocks.begin(), buildingBlocks.end(), newE) 
                == buildingBlocks.end())
        buildingBlocks.push_back(newE);
}

void Equation::replace(const Symbol& oldS, const Symbol& newS)
{
    replace(oldS.getAbstract(), newS.getAbstract());
}

void Equation::simplify()
{
    leftHandSide = Simplify(leftHandSide);
    rightHandSide = Simplify(rightHandSide);
}

void Equation::isolate(const Expr& expr)
{
    isolationStep(expr);
}

void Equation::isolationStep(const Expr& expr)
{
    if (not expr->isBuildingBlock())
        callError(smError::UndefinedBehaviour,
                "Equation::isolationStep(const Expr&)");
    Expr sum = ZERO;
    // Suprressing all terms on the left that do not depend on expr
    if (leftHandSide->getType() == smType::Plus) {
        for (const_iter arg=leftHandSide->begin();
                arg!=leftHandSide->end(); ++arg)
            if (not (*arg)->dependsExplicitelyOn(expr))
                sum = plus_(sum, *arg);
    }
    // Suprressing all terms on the right that do depend on expr
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
    // Searching expr in denominators
    Expr product = ONE;
    if (leftHandSide->getType() == smType::Plus) {

        for (iter arg=leftHandSide->begin(); arg!=leftHandSide->end(); ++arg) {
            if ((*arg)->getType() == smType::Pow
                    and (*arg)->getArgument(1)->isInteger()
                    and (*arg)->getArgument(1)->evaluateScalar() < 0) {
                Expr foo = pow_((*arg)->getArgument(0),
                        -1*(*arg)->getArgument(1));
                for (iter argModif=leftHandSide->begin();
                        argModif!=leftHandSide->end(); ++argModif)
                    (*argModif) = (*argModif)*foo;
                product = product*foo;
            }
            else if ((*arg)->getType() == smType::Times) {
                for (iter arg2=(*arg)->begin();
                        arg2!=(*arg)->end(); ++arg2) {
                    if ((*arg2)->getType() == smType::Pow
                            and (*arg2)->getArgument(1)->isInteger()
                            and (*arg2)->getArgument(1)->evaluateScalar() < 0) {
                        Expr foo = pow_((*arg2)->getArgument(0),
                                -1*(*arg2)->getArgument(1));
                        for (iter arg2Modif=leftHandSide->begin();
                                arg2Modif!=leftHandSide->end(); ++arg2Modif)
                            (*arg2Modif) = (*arg2Modif)*foo;
                        product = product*foo;
                        if ((*arg)->getType() == smType::Times)
                            --arg;
                        break;
                    }
                }
            }
        }
    }
    else if (leftHandSide->getType() == smType::Times) {
        for (iter arg=(leftHandSide)->begin();
                arg!=(leftHandSide)->end(); ++arg) {
            if ((*arg)->getType() == smType::Pow
                    and (*arg)->getArgument(1)->isInteger()
                    and (*arg)->getArgument(1)->evaluateScalar() < 0) {
                Expr foo = pow_((*arg)->getArgument(0),
                        -1*(*arg)->getArgument(1));
                for (iter argModif=leftHandSide->begin();
                        argModif!=leftHandSide->end(); ++argModif)
                    (*argModif) = (*argModif)*foo;
                product = product*foo;
            }
        }
    }
    if (*product != ONE) {
        leftHandSide = DeepRefresh(leftHandSide);
        rightHandSide = (rightHandSide*product)->develop();
        isolationStep(expr);
        return;
    }

    if (leftHandSide->getPrimaryType() == smType::ScalarFunction) {
        cout<<*this<<endl;
        switch(leftHandSide->getType()) {
            case smType::Exp: rightHandSide = log_(rightHandSide); break;
            case smType::Log: rightHandSide = exp_(rightHandSide); break;
            case smType::Cos: rightHandSide = acos_(rightHandSide); break;
            case smType::Sin: rightHandSide = asin_(rightHandSide); break;
            case smType::Tan: rightHandSide = atan_(rightHandSide); break;
            case smType::ACos: rightHandSide = cos_(rightHandSide); break;
            case smType::ASin: rightHandSide = sin_(rightHandSide); break;
            case smType::ATan: rightHandSide = tan_(rightHandSide); break;
            case smType::Cosh: rightHandSide = acosh_(rightHandSide); break;
            case smType::Sinh: rightHandSide = asinh_(rightHandSide); break;
            case smType::Tanh: rightHandSide = atanh_(rightHandSide); break;
            case smType::ACosh: rightHandSide = cosh_(rightHandSide); break;
            case smType::ASinh: rightHandSide = sinh_(rightHandSide); break;
            case smType::ATanh: rightHandSide = tanh_(rightHandSide); break;
            default: return;
        }
        leftHandSide = leftHandSide->getArgument();
        isolationStep(expr);
        return;
    }
    if (leftHandSide->getPrimaryType() == smType::MultiFunction) {
        Expr foo;
        switch(leftHandSide->getType()) {
            
            case smType::Pow:
            if (not leftHandSide->getArgument(1)->dependsExplicitelyOn(expr)) {
                rightHandSide = pow_(rightHandSide,1/leftHandSide->getArgument(1));
                leftHandSide = leftHandSide->getArgument(0);
            }
            else
                return;
            break;

            case smType::Plus:
            foo = leftHandSide->factor(expr);
            if (*foo != leftHandSide) 
                leftHandSide = foo;
            else
                return;
            break;

            case smType::Times:
            foo = ONE;
            for (iter arg=leftHandSide->begin(); arg!=leftHandSide->end();
                    ++arg)
                if (not (*arg)->dependsExplicitelyOn(expr))
                    foo = foo*(*arg);
            if (*foo != ONE) {
                leftHandSide = leftHandSide/foo;
                rightHandSide = (rightHandSide/foo)->develop();
            }
            else
                return;
            break;

            default: return;
        }
        isolationStep(expr);
        return;
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
