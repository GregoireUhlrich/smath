/*! \file simplification.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Automatic simplification framework. Sources in simplification.cpp and
 * alternateForms.cpp. 
 */
#ifndef SIMPLIFICATION_H_INCLUDED
#define SIMPLIFICATION_H_INCLUDED

#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "mathFunctions.h"
#include "symbol.h"
#include <algorithm>

/*! \var SIMPLIFICATION_METHOD
 * \brief Determines which simplification method is applied. Ther used to be 2, 
 * now there is only one method. It may be useful in the future.
 */
static const int SIMPLIFICATION_METHOD=1;

/*! \var MAX_ALTERNATE_FORMS
 * \brief Maximum number of alternate forms given by getRecursiveAlternateForms().
 * When getting alternate forms of an expression, we keep only the 
 * MAX_ALTERNATE_FORMS simpler.
 */
static const int MAX_ALTERNATE_FORMS=7;

/*! \var MAX_RECURSION_ALTERNATE
 * \brief When getting alternateForms, we iterate MAX_RECURSION_ALTERNATE times
 * (getting alternate forms of the alternate forms) in order to allow alternates
 * that need several steps of transformation.
 */
static const int MAX_RECURSION_ALTERNATE=7;

/*! \fn printVector(const std::vector<Expr>& vector)
 * \brief Display a vector of expressions. Useful in debug.
 * \param vector std::vector of expressions to display.
 */
void printVector(const std::vector<Expr >& vector);

/*! \fn addAlternateForm(std::vector<Expr>& alternateForms,
 *                       const Expr& newAlternate,
 *                       bool add_factor_develop)
 * \brief Try to add \b newAlternate in the set \b alternateForms. We simply
 * test if the alternate is already present in the set \b newAlternate and add
 * it if it is not the case. If \b add_factor_develop is set to \b true, we try
 * to add the developed and the factored forms of \b newAlternate.
 * \param alternateForms std::vector of expressions in which we add \b newAlternate.
 * \param newAlternate Expression to add.
 * \param add_factor_develop Boolean determining if we want to add also the factored
 * and developed versions of \b newAlternate.
 */
void addAlternateForm(std::vector<Expr >& alternateForms,
                      const Expr& newAlternate,
                      bool add_factor_develop=true);

/*! \fn reduceAlternate(std::vector<Expr>& alternateForms)
 * \brief Reduces the number of elements in \b alternateForms to MAX_ALTERNATE_FORMS.
 * \param alternateForms std::vector of expressions to reduce.
 */
void reduceAlternate(std::vector<Expr >& alternateForms);

/*! \fn clearRedundancyAlternate(std::vector<Expr>& alternateForms)
 * \brief Search and remove redundancies (equal alternate forms) in \b alternateForms.
 * \param alternateForms std::vector of expressions to reduce.
 */
void clearRedundancyAlternate(std::vector<Expr >& alternateForms);

/*! \fn getRecursiveAlternateForms(const Expr& expr, int depth=-1)
 * \brief Returns the alternate forms of \b expr by applying recursively
 * internalRecursiveAlternateForms() MAX_RECURSION_ALTERNATE times: take 
 * alternates, then alternates of the alternates etc. 
 * \param expr Expression from which we search alternates.
 * \param depth Recursion depth transmitted to internalRecursiveAlternateForms().
 * \return a std::vector of expressions containing alternates of \b expr.
 */
std::vector<Expr > getRecursiveAlternateForms(const Expr& expr, int depth=-1);

/*! \fn internalRecursiveAlternateForms(const Expr& expr, int depth=-1)
 * \brief Calculates and return all alternate forms of \b expr, by getting
 * (once) alternate forms of the possible arguments of \b expr, and then the
 * specific alternates of expr.
 * \param expr Expression from which we get alternate forms.
 * \param depth Recursion depth (default = -1, we take the alternate forms of 
 * all the recursion tree).
 * \return A std::vector of expressions containing the alternate forms of \b expr.
 */
std::vector<Expr > internalRecursiveAlternateForms(const Expr& expr, int depth=-1);

/*! \fn Expr Simplify(const Expr& expr, int depth=-1)
 * \brief \b Simplifies \b expr depending on its type.
 * \param expr Expression to reduce.
 * \param depth Depth of simplification. Default=1: **max depth**.
 * \return The simplified expression.
 */
Expr Simplify(const Expr& expr, int depth=-1);

#endif
