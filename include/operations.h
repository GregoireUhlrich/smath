/*! \file operations.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Objects handling multi-argument functions, primordial operations (+,*,/,etc)
 */
#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED
#include "scalarFunc.h"
#include "support.h"
#include <iostream>

/*! \class Plus
 * \brief Handles a sum, function of multiple arguments
 */
class Plus: public AbstractMultiFunc{

    public:

    /*! \brief Default constructor. Initializes \b argument to an empty std::vector.
     */
    Plus();

    /*! \brief Initializes \b argument to \a operands (copy each element)
     * \param operands Operands of the sum, copied in the object.
     */
    Plus(const std::vector<Expr >& operands, bool explicitPlus=false);

    /*! \brief Creates the sum of \& leftOperand and \a rightOperand.
     * \param leftOperand  Left operand.
     * \param rightOperand Right operand.
     */
    Plus(const Expr& leftOperand, const Expr& rightOperand);

    /*! \brief Destructor.
     */
    ~Plus(){};

    /*! \brief Gives the **type** of a Plus object.
     * \return 10
     */
    Type getType() const override { return PLUS;}

    Expr getRealPart() override;

    Expr getImaginaryPart() const override;

    Expr getComplexModulus() override;
    
    Expr getComplexArgument() override;

    std::vector<Index> getIndexStructure() const override;

    void insert(const Expr& t_abstract, bool side=0) override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Return the \b sum of all the arguments.
     * \return The sum of the scalar evaluation of all the arguments.
     * \note For this function to be justified, all the arguments must be \b scalar and \b real.
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Merge identical terms.
     * \details When identical terms (identical to a numerical factor) appear this function 
     * merge them in the same term. Example: x+y+2*x -> 3*x+y.
     * \return \b True if terms have been merged.
     * \return \b False else.
     */
    bool mergeTerms();

    void orderTerms();

    /*! \brief Derives the sum.
     * \param t_abstract Argument of the derivation.
     * \return The sum of the derivatives of the arguments
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief Factors the expression if common factors are found.
     * \param full If \b true factors recursively all the arguments.
     */
    Expr factor(bool full=false) override;

    /*! \brief Factors the expression by t_abstract if it is a common factor.
     * \param t_abstract Factor.
     * \param full       If \b true factors recursively all the arguments.
     */
    Expr factor(const Expr& t_abstract, bool full=false) override;

    int getParity(const Expr& t_variable) const override;

    bool operator==(const Expr& t_abstract) const override;

    std::vector<Expr > getAlternateForms() const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

/*! \class Polynomial
 * \brief Handles a polynomial, function of multiple arguments
 */
class Polynomial: public AbstractMultiFunc{

    private:

    Expr variable;

    public:

    /*! \brief Default constructor. Initializes \b argument to an empty std::vector, \b order to 0.
     */
    Polynomial();

    /*! \brief Initializes the polynomial from another Abstract. Detect the proper terms in it.
     *  \param t_abstract Abstract that we want to transform in a polynomial
     * \param t_variable Variable of the polynomial.
     */
    Polynomial(const Expr& t_abstract, const Expr& t_variable);
    
    /*! \brief Initializes the polynomial from a vector of terms, and a defined \b variable.
     *  \param terms for the creation of the polynomial.
     *  \param t_variable Variable of the polynomial.
     */
    Polynomial(const std::vector<Expr >& terms, const Expr& t_variable);
    
    /*! \brief Destructor.
     */
    ~Polynomial(){};

    bool mergeTerms();

    /*! \brief Gives the **type** of a Polynomial object.
     * \return 14
     */
    Type getType() const override { return POLYNOMIAL;}

    int getOrder() const override;

    Expr getVariable() const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Return the \b polynomial of all the arguments.
     * \return The polynomial of the scalar evaluation of all the arguments.
     * \note For this function to be justified, all the arguments must be \b scalar and \b real.
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Derives the polynomial.
     * \param t_abstract Argument of the derivation.
     * \return The polynomial of the derivatives of the arguments
     */
    Expr derive(const Expr& t_abstract) const override;

    int getParity(const Expr& t_variable) const override;

    Expr getRegularExpression() const override;

    Expr addition_own(const Expr& t_abstract) const override;

    Expr multiplication_own(const Expr& t_abstract) const override;
    
    Expr division_own(const Expr& t_abstract) const override;

    Expr factor(bool full=false) override;

    bool operator==(const Expr& t_abstract) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

void getExponentStructure(const Expr& argument, Expr& term, Expr& exponent);

/*! \class Times
 * \brief Handles a product, function of multiple arguments
 */
class Times: public AbstractMultiFunc{

    public:

    /*! \brief Default constructor. Initializes \b argument to an empty std::vector.
     */
    Times();

    /*! \brief Initializes \b argument to \a operands (copy each element)
     * \param operands Operands of the product, copied in the object.
     * \param explicitTimes Must be true if no modification of the vector \b argument is needed.
     */
    Times(const std::vector<Expr >& t_argument, bool explicitTimes=0);

    /*! \brief Creates the product of \& leftOperand and \a rightOperand.
     * \param leftOperand  Left operand.
     * \param rightOperand Right operand.
     * \param explicitTimes Must be true if no modification of the vector \b argument is needed.
     */
    Times(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes=0);

    /*! \brief Destructor.
     */
    ~Times(){};

    /*! \brief Gives the **type** of a Times object.
     * \return 11
     */
    Type getType() const override { return TIMES;}

    Expr getRealPart() override;

    Expr getImaginaryPart() const override;

    Expr getComplexModulus() override;
    
    Expr getComplexArgument() override;

    /*! \return The numerical factor of the product.
     */
    Expr getNumericalFactor() const override;

    /*! \return The product of all the terms but the nunmerical factor.
     */
    Expr getTerm() override;

    /*! \brief Returns the number of possible factors in the expression.
     * \return \b nArgs
     */
    int getNFactor() const override;

    /*! \brief Returns all the possible factors.
     * \return The concatenation of all possible factors for the arguments.
     */
    std::vector<Expr > getFactors() const override;

    /*! \brief Tells if the factor \a t_abstract appear in the product.
     * \param t_abstract Factor to test.
     * \return \b True if t_abstract can factor the product.
     * \return \b False else.
     */
    bool askTerm(const Expr& t_abstract, bool exact=false) const override;

    /*! \brief Suppresses the term t_abstract in the product.
     * \warning This function supposes that the function askTerm() has been called 
     * precedently and does not warn the user if the factor t_abstract is not present.
     * \param t_abstract Factor to suppress in the product.
     * \return \b The product amputated of \b t_abstract.
     */
    Expr suppressTerm(const Expr& t_abstract) const override;

    void insert(const Expr& t_abstract, bool side=0) override;
    void leftInsert(const Expr& t_abstract);
    void rightInsert(const Expr& t_abstract);

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Return the \b product of all the arguments.
     * \return The product of the scalar evaluation of all the arguments.
     * \note For this function to be justified, all the arguments must be \b scalar and \b real.
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Merge identical terms.
     * \details When identical terms (identical to a numerical factor) appear this function 
     * merge them in the same term. Example: x*y*x^2 -> x^3+y.
     * \return \b True if terms have been merged.
     * \return \b False else.
     */
    bool mergeTerms();

    void orderTerms();

    /*! \brief Derives the product.
     * \param t_abstract Argument of the derivation.
     * \return The derivative following the formula ...
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief \b Develops the product by expanding the sums inside.
     * \param full If true the development is \b recursive through all the Abstract.
     * \return The developed product.
     */
    Expr develop(bool full=false) override;

    int isPolynomial(const Expr& t_abstract) const override;

    Expr getPolynomialTerm(const Expr& t_variable, int order) override;

    int getParity(const Expr& t_variable) const override;
    
    bool operator==(const Expr& t_abstract) const override;

    std::vector<Expr > getAlternateForms() const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

/*! \class Fraction
 * \brief Handles a fraction of 2 arguments
 */
class Fraction: public AbstractDuoFunc{

    public:

    /*! \brief Default constructor. Initializes both arguments to 0.
     */
    Fraction();

    /*! \brief Creates the fraction of \& leftOperand and \a rightOperand.
     * \param leftOperand  Left operand.
     * \param rightOperand Right operand.
     */
    Fraction(const Expr& leftOperand, const Expr& rightOperand);

    /*! \brief Destructor.
     */
    ~Fraction(){};

    /*! \brief Gives the **type** of a Fraction object.
     * \return 12
     */
    Type getType() const override { return FRACTION;}

    /*! \brief Returns the number of possible factors in the expression.
     * \return \b The sum of the number of factors of the 2 arguments.
     */
    int getNFactor() const override;

    /*! \brief Returns all the possible factors.
     * \return The concatenation of all possible factors for the arguments.
     */
    std::vector<Expr > getFactors() const override;

    /*! \brief Tells if the factor \a t_abstract appear in the fraction.
     * \param t_abstract Factor to test.
     * \return \b True if t_abstract can factor the fraction.
     * \return \b False else.
     */
    bool askTerm(const Expr& t_abstract, bool exact=false) const override;

    /*! \brief Suppresses the term t_abstract in the fraction.
     * \warning This function supposes that the function askTerm() has been called 
     * precedently and does not warn the user if the factor t_abstract is not present.
     * \param t_abstract Factor to suppress in the fraction.
     * \return \b The fraction divided by \b t_abstract.
     */
    Expr suppressTerm(const Expr& t_abstract) const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Return the \b division of the two arguments.
     * \return The division of the scalar evaluation of the two arguments.
     * \note For this function to be justified, all the arguments must be \b scalar and \b real.
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Merge composition of fractions.
     * \details This function replaces compositions of fractions. For example
     * a/(b/c) givec a*c/b etc.
     * \return \b True if terms have been merged.
     * \return \b False else.
     */
    bool mergeTerms();

    /*! \brief Derives the fraction.
     * \param t_abstract Argument of the derivation.
     * \return The derivative following the formula ...
     */
    Expr derive(const Expr& t_abstract) const override;

    int isPolynomial(const Expr& t_abstract) const override;

    Expr getPolynomialTerm(const Expr& t_variable, int order) override;

    int getParity(const Expr& t_variable) const override;
    
    bool operator==(const Expr& t_abstract) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

/*! \class Pow
 * \brief Handles the exponentiation of one Abstract wrt another.
 */
class Pow: public AbstractDuoFunc{

    public:

    /*! \brief Default constructor. Initializes both arguments to 0.
     */
    Pow();

    /*! \brief Creates the exponentiation of \& leftOperand wrt \a rightOperand.
     * \param leftOperand  Left operand.
     * \param rightOperand Right operand.
     */
    Pow(const Expr& leftOperand, const Expr& rightOperand);

    /*! \brief Destructor.
     */
    ~Pow(){};

    /*! \brief Gives the **type** of a Pow object.
     * \return 13
     */
    Type getType() const override { return POW;}

    /*! \brief Returns the number of possible factors in the expression.
     * \return \b A function of the exponent if it is a Number.
     * \return \b 1 else.
     */
    int getNFactor() const override;

    /*! \brief Returns all the possible factors.
     * \return The concatenation of all possible factors for the arguments.
     */
    std::vector<Expr > getFactors() const override;

    /*! \brief Tells if the factor \a t_abstract appear in the exponentiation.
     * \param t_abstract Factor to test.
     * \return \b True if t_abstract can factor the exponentiation.
     * \return \b False else.
     */
    bool askTerm(const Expr& t_abstract, bool exact=false) const override;

    /*! \brief Suppresses the term t_abstract in the exponentiation.
     * \warning This function supposes that the function askTerm() has been called 
     * precedently and does not warn the user if the factor t_abstract is not present.
     * \param t_abstract Factor to suppress in the exponentiation.
     * \return \b The exponentiation divided by \b t_abstract.
     */
    Expr suppressTerm(const Expr& t_abstract) const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Return the \b exponentiation of the two arguments.
     * \return The exponentiation of the scalar evaluation of the two arguments.
     * \note For this function to be justified, all the arguments must be \b scalar and \b real.
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Merge composition of exponentiations.
     * \details This function replaces compositions of exponentiations. For example
     * (a^b)^c -> a^(b*c).
     * \return \b True if terms have been merged.
     * \return \b False else.
     */
    bool mergeTerms();

    /*! \brief Derives the exponentiation.
     * \param t_abstract Argument of the derivation.
     * \return The derivative following the formula ...
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief \b Develops the exponentiation by expanding the sums inside.
     * \param full If true the development is \b recursive through all the Abstract.
     * \return The developed exponentiation.
     */
    Expr develop(bool full=false) override;

    Expr getRealPart() override;

    Expr getImaginaryPart() const override;

    Expr getComplexModulus() override;

    Expr getComplexArgument() override;

    int isPolynomial(const Expr& t_abstract) const override;

    Expr getPolynomialTerm(const Expr& t_variable, int order) override;

    int getParity(const Expr& t_variable) const override;
    
    bool operator==(const Expr& t_abstract) const override;

    std::vector<Expr > getAlternateForms() const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};


/*! \class Derivative
 * \brief Handles the exponentiation of one Abstract wrt another.
 */
class Derivative: public AbstractDuoFunc{

    protected:

    int order;

    public:

    /*! \brief Default constructor. Initializes both arguments to 0, \b order to 1.
     */
    Derivative();

    /*! \brief Creates the derivative operator wrt variable at order \b order. It is applied when it appears in a multiplication.
     * \param variable Variable wrt which we derive.
     * \param order Order of the derivation.
     */
    Derivative(const Expr& variable, int order);

    /*! \brief Creates the derivative of \& leftOperand wrt \a rightOperand, to \b order 1.
     * \param leftOperand  Left operand.
     * \param rightOperand Right operand.
     */
    Derivative(const Expr& leftOperand, const Expr& rightOperand);

    /*! \brief Creates the derivative of \& leftOperand wrt \a rightOperand, to \b order \a t_order.
     * \param leftOperand  Left operand.
     * \param rightOperand Right operand.
     */
    Derivative(const Expr& leftOperand, const Expr& rightOperand, int t_order);

    /*! \brief Destructor.
     */
    ~Derivative(){};

    /*! \brief Gives the **type** of a Derivative object.
     * \return 29
     */
    Type getType() const override { return DERIVATIVE;}

    int getOrder() const override;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Return the \b derivative of the first argument wrt the second.
     * \return The derivative of the scalar evaluation of the two arguments.
     * \note For this function to be justified, all the arguments must be \b scalar and \b real.
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Derives the derivative.
     * \param t_abstract Argument of the derivation.
     * \return The derivative following the formula ...
     */
    Expr derive(const Expr& t_abstract) const override;

    int getParity(const Expr& t_variable) const override;
    
    bool operator==(const Expr& t_abstract) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

/////
// Inline functions

inline Plus::Plus(): AbstractMultiFunc(){}
inline Times::Times(): AbstractMultiFunc(){}
inline Polynomial::Polynomial(): AbstractMultiFunc(), variable(ZERO){}
inline Fraction::Fraction(): AbstractDuoFunc(){}
inline Pow::Pow(): AbstractDuoFunc(){}

inline Derivative::Derivative(): AbstractDuoFunc(), order(1){}
inline Derivative::Derivative(const Expr& t_variable,
                              int t_order): AbstractDuoFunc(), order(t_order){
    argument[1] = t_variable;
}
inline Derivative::Derivative(const Expr& leftOperand,
                              const Expr& rightOperand,
                              int t_order): AbstractDuoFunc(), order(t_order){
    argument[0] = leftOperand;
    argument[1] = rightOperand;
}
/////


/*! \fn Expr plus_(const Expr& leftOperand, const Expr& rightOperand)
  * \brief Returns the \b sum of the two operands, applying basic simplifications. 
  * \details This function possibly returns an object different from a Plus object if the
  * simplification requires so. For example 0+x -> x that is a Variable.
  * \param leftOperand  Left operand.
  * \param rightOperand Right operand.
  * \return The sum of \b leftOperand and \b rightOperand.
  */
Expr plus_(const Expr& leftOperand, const Expr& rightOperand);

/*! \fn Expr plus_(const std::vector<Expr >& operands)
  * \brief Returns the \b sum of the operands, applying basic simplifications. 
  * \details This function possibly returns an object different from a Plus object if the
  * simplification requires so. For example 0+x+2x -> 3x that is a Times object.
  * \param operands vector containing the operands.
  * \return The sum of the operands.
  */
Expr plus_(const std::vector<Expr >& operands);

/*! \fn Expr minus_(const Expr& leftOperand, const Expr& rightOperand)
  * \brief Returns the \b sum of the two operands (with a minus sign), applying basic simplifications. 
  * \details This function possibly returns an object different from a Plus object if the
  * simplification requires so. For example 0+x -> x that is a Variable. The Minus object 
  * does not exists, this function applies leftOperand + (-1*rightOperand).
  * \param leftOperand  Left operand.
  * \param rightOperand Right operand.
  * \return The sum of \b leftOperand and \b rightOperand.
  */
Expr minus_(const Expr& leftOperand, const Expr& rightOperand);

/*! \fn Expr times_(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes=0)
  * \brief Returns the \b product of the two operands, applying basic simplifications. 
  * \details This function possibly returns an object different from a Times object if the
  * simplification requires so. For example 1*x -> x that is a Variable.
  * \param leftOperand  Left operand.
  * \param rightOperand Right operand.
  * \param explicitTimes If \b true Times::mergeTerms() is not called and no simplification 
  * is done concerning the reordering/merging of terms.
  * \return The product of \b leftOperand and \b rightOperand.
  */
Expr times_(const Expr& leftOperand, const Expr& rightOperand, bool explicitTimes=0);

/*! \fn Expr times_(const std::vector<Expr >& operands)
  * \brief Returns the \b product of the operands, applying basic simplifications. 
  * \details This function possibly returns an object different from a Times object if the
  * simplification requires so. For example 1*x*x^2 -> x^3 that is a Pow.
  * \param operands vector containing the operands.
  * \param explicitTimes If \b true Times::mergeTerms() is not called and no simplification 
  * \return The product of \b leftOperand and \b rightOperand.
  */
Expr times_(const std::vector<Expr >& operands, bool explicitTimes=false);

/*! \fn Expr fraction_(const Expr& leftOperand, const Expr& rightOperand)
  * \brief Returns the \b fraction of the two operands, applying basic simplifications. 
  * \details This function possibly returns an object different from a Fraction object if the
  * simplification requires so. For example 1/(x^(-1)) -> x that is a Variable.
  * \param leftOperand  Left operand.
  * \param rightOperand Right operand.
  * \return The fraction of \b leftOperand and \b rightOperand.
  */
Expr fraction_(const Expr& leftOperand, const Expr& rightOperand);

/*! \fn Expr pow_(const Expr& leftOperand, const Expr& rightOperand)
  * \brief Returns the \b exponentiation of the two operands, applying basic simplifications. 
  * \details This function possibly returns an object different from a Pow object if the
  * simplification requires so. For example x^1 -> x that is a Variable.
  * \param leftOperand  Left operand.
  * \param rightOperand Right operand.
  * \return The exponentiation of \b leftOperand and \b rightOperand.
  */
Expr pow_(const Expr& leftOperand, const Expr& rightOperand);

Expr sqrt_(const Expr& operand);

/*! \fn Expr derivative_(const Expr& leftOperand, const Expr& rightOperand, int order)
  * \brief Returns the \b derivative of \b leftOperand wrt \a rightOperand, applying basic simplifications. 
  * \details This function possibly returns an object different from a Derivative object if the
  * simplification requires so.
  * \param leftOperand  Left operand.
  * \param rightOperand Right operand.
  * \param order Order of derivation.
  * \return The derivative of \b leftOperand wrt \b rightOperand at the order \b order.
  */
Expr derivative_(const Expr& leftOperand, const Expr& rightOperand, int order=1);

Expr derivative_(const Expr& variable, int order=1);

Expr polynomial_(const Expr& t_abstract, const Expr& t_variable);

Expr polynomial_(const std::vector<Expr >& operands, const Expr& t_variable);

#endif
