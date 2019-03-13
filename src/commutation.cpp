#include "commutation.h"
#include "symbol.h"
using namespace std;

Expr Commutation(const Expr& A, const Expr& B)
{
    if (A->getCommutable()) 
        if (B->getCommutable())
            return ZERO;
        else 
            return -1*WeakCommutation(B,A);
    else
        if (B->getCommutable())
            return WeakCommutation(A,B);

    // Here A and B are non-commutable objects
    // To implement...
    if (A == B)
        return ZERO;
    return A*B - B*A;
}

Expr WeakCommutation(const Expr& A, const Expr& B)
{
    switch(A->getType()) {

        case smType::Derivative:
        if (not A->isEmpty()) {
            if (*Commutation(A->getArgument(), B) == ZERO)
                return ZERO;
            else
                return A*B-B*A;
        }
        if (not B->dependsOn(A->getVariable())) {
            if (*Commutation(A->getArgument(),B) == ZERO)
                return ZERO;
            else
                return A*B-B*A;
        }
        if (*Commutation(A->getArgument(), B) == ZERO and A->getOrder() == 1)
            return derivative_(A->getArgument()*B,A->getVariable(), 1);
        return A*B-B*A;
        break;

        // Warning here by default this function assumes [A,B] = 0
        default:
        return ZERO;
    }
}

