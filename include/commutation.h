#ifndef COMMUTATION_H_INCLUDED
#define COMMUTATION_H_INCLUDED

#include "abstract.h"

Expr Commutation(const Expr& A, const Expr& B);

// A does not commut but B does (only check for derivatives etc)
Expr WeakCommutation(const Expr& A, const Expr& B);

Expr AntiCommutation(const Expr& A, const Expr& B);

#endif
