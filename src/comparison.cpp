#include "comparison.h"

using namespace std;

bool smComparator::dummyComparisonActive = false;
std::string smComparator::dummyName = "ARBITRARY";
std::map<int,Expr> smComparator::arbitrary = std::map<int,Expr>();
std::map<int,Expr> smComparator::correspondance
            = std::map<int,Expr>();

//std::map<Index,Index> smComparator::indexCorrepondance
//            = std::map<Index,Index>();

Arbitrary::Arbitrary(int n)
    :AbstractLiteral(smComparator::dummyName), number(n)
{}

smType::Type Arbitrary::getType() const
{
    return smType::Arbitrary;
}

int Arbitrary::getNum() const
{
    return number;
}

void Arbitrary::print(int mode) const
{
    cout<<name;
    if (mode > 0)
        cout<<endl;
}

string Arbitrary::printLaTeX(int mode) const
{
    return name;
}

Expr Arbitrary::evaluate()
{
    callError(smError::ArbitraryEvaluated,
            "Arbitrary::evaluate()");
    return ZERO;
}

bool Arbitrary::operator==(const Expr& expr) const
{
    return smComparator::compare(expr, shared_from_this());
}

bool Arbitrary::operator<(const Expr& expr) const
{
    return false;
}

bool Arbitrary::operator>(const Expr& expr) const
{
    return true;
}

Expr smComparator::dummy(int n)
{
    if (arbitrary.find(n) == arbitrary.end())
        arbitrary[n] = make_shared<Arbitrary>(n);

    return arbitrary[n];
}

bool smComparator::compare(const Expr& expr, const constExpr& dummy)
{
    if (dummy->getType() != smType::Arbitrary)
        callError(smError::ComparingNotDummy,
                "smComparator::compare(const Abstract*, const Expr&)");
    if (expr->getType() == smType::Arbitrary)
        return (dummy->getNum() == expr->getNum());
    if (not dummyComparisonActive)
        return false;
    const int number = dummy->getNum();
    if (correspondance.find(number) == correspondance.end()) {
        correspondance[number] = expr;
        return true;
    }
    return (expr->operator==(correspondance[number]));
}

bool smComparator::dummyComparison(const Expr& expr, const Expr& dummyExpr)
{
    dummyComparisonActive = true;
    bool rep = expr->operator==(dummyExpr);
    clear();

    return rep;
}


void smComparator::clear()
{
    arbitrary.clear();
    correspondance.clear();
    dummyComparisonActive = false;
}
