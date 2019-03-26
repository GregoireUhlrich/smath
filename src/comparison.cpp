#include "comparison.h"

using namespace std;


Arbitrary::Arbitrary(int n): number(n)
{}

smType::Type Arbitrary::getType() const
{
    return smType::Arbitrary;
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
    if (not smComparator::correspondance[number]) {
        smComparator::correspondance[number] = expr;
        return true;
    }
    return (expr == smComparator::correspondance[number]);
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
    if (not arbitrary[n])
        arbitrary[n] = make_shared<Arbitrary>(n);

    return arbitrary[n];
}

void smComparator::clear()
{
    arbitrary.clear();
    correspondance.clear();
}
