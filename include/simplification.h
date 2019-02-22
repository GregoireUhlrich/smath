/*! \file simplification.h
 * \author Grégoire Uhlrich
 * \version 1.0
 */
#ifndef SIMPLIFICATION_H_INCLUDED
#define SIMPLIFICATION_H_INCLUDED

#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "mathFunctions.h"
#include "symbol.h"
#include <algorithm>

static const int SIMPLIFICATION_METHOD=1;
static const int MAX_ALTERNATE_FORMS=10;
static const int MAX_RECURSION_ALTERNATE=3;

void printVector(const std::vector<Expr >& vector);

void addAlternateForm(std::vector<Expr >& alternateForms, const Expr& newAlternate, bool add_factor_develop=true);

void reduceAlternate(std::vector<Expr >& alternateForms);

void clearRedundancyAlternate(std::vector<Expr > alternateForms);

std::vector<Expr > getRegularExpression(const Expr& t_abstract, int depth=-1);

std::vector<Expr > internalRecursiveAlternateForms(const Expr& t_abstract, int depth=-1);

/*! \fn Expr Simplify(const Expr& t_abstract)
 * \brief \b Simplifies t_abstract depending on its type.
 * \param t_abstract Abstract to reduce.
 * \return The simplified Abstract.
 */
Expr Simplify(const Expr& t_abstract, int depth=-1);

#endif
