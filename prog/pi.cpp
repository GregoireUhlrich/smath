#include "smath.h"
using namespace std;

int main(){

    Symbol v1("v1"), v2("v2"), u1("u1"), u2("u2");
    Symbol m("m");

    Symbol p("p");
    p = v1 + m*v2;
    Symbol E("E");
    E = (v1^2) + m*(v2^2);
    u1 = p-m*u2;
    u1.print();
    Symbol eq("eq");
    Symbol Ep = E;
    Ep = Ep.replace(v2,u2);
    Ep = Ep.replace(v1,u1);
    eq = E - Ep;
    eq = Refresh(eq);
    eq = eq.full_develop();
    eq.print();
    eq = polynomial_(eq, u2);
    eq.print();

    Symbol factored = eq.polynomialFactorization();
    factored.print();

    return 0;
}
