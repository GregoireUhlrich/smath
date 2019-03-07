/*! \file symbol.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief User class that encapsulate every nasty detail.
 */
#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED
#include "abstract.h"
#include "vector.h"
#include "variable.h"
#include "operations.h"
#include "mathFunctions.h"
#include "indicial.h"

/*! \class Symbol
 * \brief Encapsulates a Expr in order to make the user's life easier.
 */
class Symbol{

    private:

    std::string name; /*!< \brief Name of the symbol. */

    Expr abstract; /*!< \brief Abstract that the Symbol manages.*/

    public:

    /*! \brief Default Constructor, initializes the Abstract to 0.
     */    
    Symbol();

    /*! \brief Initializes \b name and the Abstract to 0.
     */    
    explicit Symbol(std::string t_name);

    /*! \brief Initialized the Abstract to Number(value).
     * \param value 
     */    
    Symbol(int value);

    /*! \brief Initialized the Abstract to Number(value).
     * \param value 
     */    
    Symbol(double value);

    /*! \brief Initializes \b abstract to \a expr.
     *  \param expr
     */   
    Symbol(const Expr& expr);

    /*! \brief Copy constructor, copy \a name and \a abstract of \a t_symbol.
     * \param t_symbol Symbol to copy.
     */
    Symbol(const Symbol& t_symbol);

    /*! \brief Destructor.
     */
    ~Symbol();

    /*! \brief Clear all references of \a abstract.
     * \details Replaces \b abstract by a Variable (not changing \b name) equal to zero.
     * This function should be called by the user when lenghty exprs are not used
     * anymore: it will be deleted only once nothing is referencing it.
     */
    void clear();

    /*! \brief Returns the \b name of the Symbol.
     * \return \b name
     */
    std::string getName() const;

    int getDim() const;

    /*! \brief Returns the \b type of \b abstract.
     * \return \b abstract.getType()
     */
    smType::Type getType() const;

    smType::PrimaryType getPrimaryType() const;

    /*! \brief Tells if the Symbol can commute with all the others.
     * \return \b abstract.commutable
     */
    bool getCommutable() const;

    /*! \brief Returns the Abstract encapsulated in the Symbol.
     * \return \b abstract
     */
    Expr getAbstract() const;

    /*! \brief \b Evaluates the **real part** of the Symbol and returns it.
     * \return The real part of the Symbol.
     */
    Symbol getRealPart() const;

    /*! \brief \b Evaluates the **imaginary part** of the Symbol and returns it.
     * \return The imaginary part of the Symbol.
     */
    Symbol getImaginaryPart() const;

    /*! \brief \b Evaluates the **modulus in the complex plane** of the Symbol and returns it.
     * \return The modulus part of the Symbol.
     */
    Symbol getComplexModulus() const;
    
    /*! \brief \b Evaluates the **argument in the complex plane** of the Symbol and returns it.
     * \return The argument part of the Symbol.
     */
    Symbol getComplexArgument() const;

    /*! \brief Change the \b name of the Symbol.
     * \details Change also the name of \b abstract if it has no name already.
     * \param t_name New name.
     */
    void setName(std::string t_name);

    /*! \brief Set the commutability of \b abstract.
     * \param t_commutable \b True if the Symbol commutes with the others.
     */
    void setCommutable(bool t_commutable);

    /*! \brief Change the Abstract managed.
     * \param expr New \b abstract for the Symbol.
     */
    void setAbstract(const Expr& expr);

    void setArgument(const Symbol& expr, int iArg=0);

    void setArgument(const Symbol& expr, int iArg, int jArg);

    void setArgument(const Symbol& expr, int iArg, int jArg, int kArg);

    void setArgument(const Symbol& expr, const std::vector<int> indices);


    /*! \brief Prints \b abstract on standard output
     */
    void print() const;

    void printExplicit() const;

    /*! \brief Returns the LaTeX formula for \b abstract.
     * \return The LaTeX formula corresponding to \b abstract.
     */
    std::string printLaTeX() const;

    /*! \brief \b Evaluates the Symbol.
     * \details As most of the Symbol's functions this one simply calls the corresponding 
     * Abstract function of \b abstract.
     * \return The evaluated Symbol.
     */
    Symbol evaluate();

    /*! \brief Returns te scalar real evaluation of \b abstract.
     * \details As for an AAbstract, this function makes sense if and only if 
     * the Symbol is a real scalar. An Imaginary, Vector, etc will be badly
     * evaluated. In the case of an Imaginary, a warning message is printed.
     * \return The scalar real evaluation of \b abstract.
     */
    double evaluateScalar();

    /*! \brief Derives the Symbol.
     * \details Derives \b abstract and returns the result in a new Symbol.
     * \param t_symbol Symbol wrt which we derive.
     * \return The derivative.
     */
    Symbol derive(Symbol t_symbol) const;

    /*! \fn void full_factor(Symbol& t_symbol)
     * \brief \b Factors recursively the Symbol \a t_symbol: see Abstract::factor(bool).
     * \param t_symbol Symbol to factor. 
     */
    Symbol full_factor() const;

    /*! \fn Symbol factor(Symbol& t_symbol)
     * \brief \b Factors the Symbol \a t_symbol: see Abstract::factor(bool).
     * \param t_symbol Symbol to factor. 
     */
    Symbol factor() const;

    /*! \fn Symbol full_factor(Symbol& t_symbol, const Symbol& factor)
     * \brief \b Factors recursively the Symbol \a t_symbol wrt \a factor: see Abstract::factor(const Expr&, bool).
     * \param t_symbol Symbol to factor. 
     * \param factor Symbol wrt which we factor.
     */
    Symbol full_factor(const Symbol& factor) const;

    /*! \fn Symbol factor(Symbol& t_symbol, const Symbol& factor)
     * \brief \b Factors the Symbol \a t_symbol wrt \a factor: see Abstract::factor(const Expr&, bool).
     * \param t_symbol Symbol to factor. 
     * \param factor Symbol wrt which we factor.
     */
    Symbol factor(const Symbol& factor) const;

    /*! \fn Symbol full_develop(Symbol& t_symbol)
     * \brief \b Develops recursively the Symbol \a t_symbol: see Abstract::develop(bool).
     * \param t_symbol Symbol to develop. 
     */
    Symbol full_develop() const;

    /*! \fn Symbol develop(Symbol& t_symbol)
     * \brief \b Develops the Symbol \a t_symbol: see Abstract::develop(bool).
     * \param t_symbol Symbol to develop. 
     */
    Symbol develop() const;

    /*! \brief Replaces \a old_symbol by \a new_symbol in the expr.
     * \param old_symbol Symbol to search and replace.
     * \param new_symbol Symbol that will take the place of \b old_symbol.
     */
    Symbol replace(const Symbol& old_symbol, const Symbol& new_symbol) const;

    int getParity(const Symbol& t_symbol);

    Symbol polynomialDivision(const Symbol& t_symbol) const;

    Symbol polynomialFactorization() const;

    Symbol sum() const;

    Symbol product() const;

    Symbol determinant() const;

    Symbol trace() const;

    Symbol transpose() const;

    Symbol symmetrise() const;

    Symbol antisymmetrise() const;

    Symbol trace(int axis1, int axis2) const;

    Symbol inverseMatrix() const;

    bool checkIndexStructure(const std::vector<Index>& t_index) const;

    bool checkIndexStructure(std::initializer_list<Index> index) const;

    /*! \brief \b Compares the Symbol with another, does not consider the name.
     * \param t_symbol Symbol to compare.
     * \return \b True if the Abstract of the two Symbols are the same.
     * \return \b False else.
     */
    bool operator==(const Symbol& t_symbol);

    /*! \brief \b Compares the Symbol with another, does not consider the name.
     * \param t_symbol Symbol to compare.
     * \return \b False if the Abstract of the two Symbols are the same.
     * \return \b True else.
     */
    bool operator!=(const Symbol& t_symbol);

    /*! \brief \b Replaces \b abstract by the one of \a t_symbol.
     * \param t_symbol Symbol from which we copy the Abstract.
     * \return A reference to \b *this.
     */
    Symbol& operator=(const Symbol& t_symbol);

    /*! Tries to associate a number with the Abstract.
     * \details If \a abstract has a type that allows the association of a number
     * then we set the \b value of \b abstract using setValue(): this concerns
     * Number, Variable, and CFraction for now. Else \b abstract is replaced with 
     * a pure Number. 
     * \param t_value New value for the Symbol.
     * \return A reference to \b *this
     * \warning If we try to set the value of a not directly-valued expr (cos(x)) 
     * for example, then the expr is erased and replaced with a Number.
     */
    Symbol& operator=(double t_value);

    /*! Tries to associate a number with the Abstract.
     * \details If \a abstract has a type that allows the association of a number
     * then we set the \b value of \b abstract using setValue(): this concerns
     * Number, Variable, and CFraction for now. Else \b abstract is replaced with 
     * a pure Number. 
     * \param t_value New value for the Symbol.
     * \return A reference to \b *this
     * \warning If we try to set the value of a not directly-valued expr (cos(x)) 
     * for example, then the expr is erased and replaced with a Number.
     */
    Symbol& operator=(int t_value);

    Symbol operator[](int iArg) const;

    Symbol operator[](const std::vector<int>& indices) const;

    bool operator|=(const Symbol& t_symbol) const;

    bool operator&=(const Symbol& t_symbol) const;

    bool operator>(const Symbol& t_symbol) const;

    bool operator<(const Symbol& t_symbol) const;

    bool operator>=(const Symbol& t_symbol) const;

    bool operator<=(const Symbol& t_symbol) const;
};

/*! \fn Symbol Copy(const Symbol& t_symbol)
 * \brief Copy the \b abstract of \a t_symbol in a new one: see Copy(const Expr&).
 * \param t_symbol Symbol to copy.
 * \return The copy.
 */
Symbol Copy(const Symbol& t_symbol);

/*! \fn Symbol DeepCopy(const Symbol& t_symbol)
 * \brief DeepCopy the \b abstract of \a t_symbol in a new one: see DeepCopy(const Expr&).
 * \param t_symbol Symbol to copy.
 * \return The \b deep copy.
 */
Symbol DeepCopy(const Symbol& t_symbol);

/*! \fn Symbol Refresh(const Symbol& t_symbol)
 * \brief Refresh the \b abstract of \a t_symbol and put it in a new one: see Refresh(const Expr&).
 * \param t_symbol Symbol to refresh.
 * \return The refreshed Symbol.
 */
Symbol Refresh(const Symbol& t_symbol1);

/*! \fn Symbol DeepRefresh(const Symbol& t_symbol)
 * \brief Refresh recursively the \b abstract of \a t_symbol and put it in a new
 * one: see DeepRefresh(const Expr&).
 * \param t_symbol Symbol to refresh.
 * \return The refreshed Symbol.
 */
Symbol DeepRefresh(const Symbol& t_symbol);

Symbol Simplify(const Symbol& t_symbol, int recursion=-1);

/*! \fn Symbol cfraction_(int value1, int value2)
 * \brief Creates a \b constant fraction of two integers.
 * \param value1 Numerator
 * \param value2 Denominator
 * \return The Symbol corresponding to valu1/value2.
 */
Symbol cfraction_(int value1, int value2);

/*! \fn Symbol fraction_(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Creates the fraction \a t_symbol1/\a t_symbol2
 * \param t_symbol1 Numerator
 * \param t_symbol2 Denominator
 * \return The Symbol corresponding to t_symbol1/t_symbol2
 */
Symbol fraction_(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn Symbol factorial_(const Symbol& t_symbol1)
 * \brief Creates the factorial \a t_symbol1!
 * \param t_symbol1 Argument of the factorial.
 * \return The Symbol corresponding to t_symbol1!
 */
Symbol factorial_(const Symbol& t_symbol1);

/*! \fn Symbol pow_(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Creates the exponentiation \a t_symbol1/\a t_symbol2
 * \param t_symbol1 The Symbol that we exponentiate.
 * \param t_symbol2 The \b exponent.
 * \return The Symbol corresponding to t_symbol1/t_symbol2
 */
Symbol pow_(const Symbol& t_symbol1, const Symbol& t_symbol2);

Symbol sqrt_(const Symbol& t_symbol);

/*! \fn Symbol exp_(const Symbol& t_symbol)
 * \brief Returns the \b exponential function applied on t_symbol.
 * \param t_symbol Symbol on which we apply exp.
 * \return The Symbol corresponding to exp(\a t_symbol).
 */
Symbol exp_(const Symbol& t_symbol);

/*! \fn Symbol log_(const Symbol& t_symbol)
 * \brief Returns the \b logarithm function applied on t_symbol.
 * \param t_symbol Symbol on which we apply log.
 * \return The Symbol corresponding to log(\a t_symbol).
 */
Symbol log_(const Symbol& t_symbol);

/*! \fn Symbol cos_(const Symbol& t_symbol)
 * \brief Returns the \b cos function applied on t_symbol.
 * \param t_symbol Symbol on which we apply cos.
 * \return The Symbol corresponding to cos(\a t_symbol).
 */
Symbol cos_(const Symbol& t_symbol);

/*! \fn Symbol sin_(const Symbol& t_symbol)
 * \brief Returns the \b sin function applied on t_symbol.
 * \param t_symbol Symbol on which we apply sin.
 * \return The Symbol corresponding to sin(\a t_symbol).
 */
Symbol sin_(const Symbol& t_symbol);

/*! \fn Symbol tan_(const Symbol& t_symbol)
 * \brief Returns the \b tan function applied on t_symbol.
 * \param t_symbol Symbol on which we apply tan.
 * \return The Symbol corresponding to tan(\a t_symbol).
 */
Symbol tan_(const Symbol& t_symbol);

/*! \fn Symbol acos_(const Symbol& t_symbol)
 * \brief Returns the \b acos function applied on t_symbol.
 * \param t_symbol Symbol on which we apply acos.
 * \return The Symbol corresponding to acos(\a t_symbol).
 */
Symbol acos_(const Symbol& t_symbol);

/*! \fn Symbol asin_(const Symbol& t_symbol)
 * \brief Returns the \b asin function applied on t_symbol.
 * \param t_symbol Symbol on which we apply asin.
 * \return The Symbol corresponding to asin(\a t_symbol).
 */
Symbol asin_(const Symbol& t_symbol);

/*! \fn Symbol atan_(const Symbol& t_symbol)
 * \brief Returns the \b atan function applied on t_symbol.
 * \param t_symbol Symbol on which we apply atan.
 * \return The Symbol corresponding to atan(\a t_symbol).
 */
Symbol atan_(const Symbol& t_symbol);

/*! \fn Symbol cosh_(const Symbol& t_symbol)
 * \brief Returns the \b cosh function applied on t_symbol.
 * \param t_symbol Symbol on which we apply cosh.
 * \return The Symbol corresponding to cosh(\a t_symbol).
 */
Symbol cosh_(const Symbol& t_symbol);

/*! \fn Symbol sinh_(const Symbol& t_symbol)
 * \brief Returns the \b sinh function applied on t_symbol.
 * \param t_symbol Symbol on which we apply sinh.
 * \return The Symbol corresponding to sinh(\a t_symbol).
 */
Symbol sinh_(const Symbol& t_symbol);

/*! \fn Symbol tanh_(const Symbol& t_symbol)
 * \brief Returns the \b tanh function applied on t_symbol.
 * \param t_symbol Symbol on which we apply tanh.
 * \return The Symbol corresponding to tanh(\a t_symbol).
 */
Symbol tanh_(const Symbol& t_symbol);

/*! \fn Symbol acosh_(const Symbol& t_symbol)
 * \brief Returns the \b acosh function applied on t_symbol.
 * \param t_symbol Symbol on which we apply acosh.
 * \return The Symbol corresponding to acosh(\a t_symbol).
 */
Symbol acosh_(const Symbol& t_symbol);

/*! \fn Symbol asinh_(const Symbol& t_symbol)
 * \brief Returns the \b asinh function applied on t_symbol.
 * \param t_symbol Symbol on which we apply asinh.
 * \return The Symbol corresponding to asinh(\a t_symbol).
 */
Symbol asinh_(const Symbol& t_symbol);

/*! \fn Symbol atanh_(const Symbol& t_symbol)
 * \brief Returns the \b atanh function applied on t_symbol.
 * \param t_symbol Symbol on which we apply atanh.
 * \return The Symbol corresponding to atanh(\a t_symbol).
 */
Symbol atanh_(const Symbol& t_symbol);

Symbol derivative_(const Symbol& t_variable, int order=1);

Symbol derivative_(const Symbol& t_symbol, const Symbol& t_variable, int order=1);

Symbol polynomial_(const Symbol& t_symbol, const Symbol& t_variable);

Symbol vector_(int t_nElements);

Symbol vector_(int t_nElements, const Symbol& t_symbol, const Symbol& index);

Symbol vector_(const std::vector<Symbol>& t_arguments);

Symbol matrix_(int t_nArgs);

Symbol matrix_(int t_x_nArgs, int t_y_nArgs);

Symbol matrix_(int t_x_nArgs, int t_y_nArgs, const Symbol& t_symbol, const Symbol& index_x, const Symbol& index_y);

Symbol matrix_(const std::vector<std::vector<Symbol> >& t_argument);

Symbol itensor_(std::string t_name, Index index);

Symbol itensor_(std::string t_name, std::initializer_list<Index> t_indices);

Symbol scalarDot(const Symbol& t_symbol1, const Symbol& t_symbol2);

Symbol dot(const Symbol& t_symbol1, const Symbol& t_symbol2);

Symbol tensor_dot(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn Symbol Taylor(const Symbol& t_symbol, const Symbol& variable, unsigned int max_order)
 * \brief Return the **Talyor development** of \a t_symbol wrt \a variable up to the order \a max_order included.
 * \param t_symbol Symbol we develop.
 * \param variable Symbol wrt which we develop.
 * \param max_order Maximal included order in the development.
 * \return The **Taylor expansion**.
 */
Symbol Taylor(const Symbol& t_symbol, const Symbol& variable, unsigned int max_order);

/*! \fn Symbol operator+(const Symbol& t_symbol, int t_value)
 * \brief Returns the \b addition of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, an integer.
 * \return The sum of the two operands.
 */
Symbol operator+(const Symbol& t_symbol, int t_value);

/*! \fn Symbol operator+(int t_value, const Symbol& t_symbol)
 * \brief Returns the \b addition of \a t_value and \a t_symbol.
 * \param t_value  Left operand, an integer.
 * \param t_symbol Right operand, a Symbol.
 * \return The sum of the two operands.
 */
Symbol operator+(int t_value, const Symbol& t_symbol);

/*! \fn Symbol operator+(const Symbol& t_symbol, double t_value)
 * \brief Returns the \b addition of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, a double.
 * \return The sum of the two operands.
 */
Symbol operator+(const Symbol& t_symbol, double t_value);

/*! \fn Symbol operator+(double t_value, const Symbol& t_symbol)
 * \brief Returns the \b addition of \a t_value and \a t_symbol.
 * \param t_value  Left operand, a double.
 * \param t_symbol Right operand, a Symbol.
 * \return The sum of the two operands.
 */
Symbol operator+(double t_value, const Symbol& t_symbol);

/*! \fn Symbol operator+(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Returns the \b addition of \a t_symbol1 and \a t_symbol2.
 * \param t_symbol1  Left operand, a Symbol.
 * \param t_symbol2 Right operand, a Symbol.
 * \return The sum of the two operands.
 */
Symbol operator+(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn Symbol operator-(const Symbol& t_symbol, int t_value)
 * \brief Returns the \b difference of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, an integer.
 * \return The difference of the two operands.
 */
Symbol operator-(const Symbol& t_symbol, int t_value);

/*! \fn Symbol operator-(int t_value, const Symbol& t_symbol)
 * \brief Returns the \b difference of \a t_value and \a t_symbol.
 * \param t_value  Left operand, an integer.
 * \param t_symbol Right operand, a Symbol.
 * \return The difference of the two operands.
 */
Symbol operator-(int t_value, const Symbol& t_symbol);

/*! \fn Symbol operator-(const Symbol& t_symbol, double t_value)
 * \brief Returns the \b difference of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, a double.
 * \return The difference of the two operands.
 */
Symbol operator-(const Symbol& t_symbol, double t_value);

/*! \fn Symbol operator-(double t_value, const Symbol& t_symbol)
 * \brief Returns the \b difference of \a t_value and \a t_symbol.
 * \param t_value  Left operand, a double.
 * \param t_symbol Right operand, a Symbol.
 * \return The difference of the two operands.
 */
Symbol operator-(double t_value, const Symbol& t_symbol);

/*! \fn Symbol operator-(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Returns the \b difference of \a t_symbol1 and \a t_symbol2.
 * \param t_symbol1  Left operand, a Symbol.
 * \param t_symbol2 Right operand, a Symbol.
 * \return The difference of the two operands.
 */
Symbol operator-(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn Symbol operator-(const Symbol& t_symbol)
 * \brief Unary - operator for Symbol.
 * \param t_symbol  Operand, a Symbol.
 * \return -\b Operand
 */
Symbol operator-(const Symbol& t_symbol);

/*! \fn Symbol operator*(const Symbol& t_symbol, int t_value)
 * \brief Returns the \b product of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, an integer.
 * \return The product of the two operands.
 */
Symbol operator*(const Symbol& t_symbol, int t_value);

/*! \fn Symbol operator*(int t_value, const Symbol& t_symbol)
 * \brief Returns the \b product of \a t_value and \a t_symbol.
 * \param t_value  Left operand, an integer.
 * \param t_symbol Right operand, a Symbol.
 * \return The product of the two operands.
 */
Symbol operator*(int t_value, const Symbol& t_symbol);

/*! \fn Symbol operator*(const Symbol& t_symbol, double t_value)
 * \brief Returns the \b product of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, a double.
 * \return The product of the two operands.
 */
Symbol operator*(const Symbol& t_symbol, double t_value);

/*! \fn Symbol operator*(double t_value, const Symbol& t_symbol)
 * \brief Returns the \b product of \a t_value and \a t_symbol.
 * \param t_value  Left operand, a double.
 * \param t_symbol Right operand, a Symbol.
 * \return The product of the two operands.
 */
Symbol operator*(double t_value, const Symbol& t_symbol);

/*! \fn Symbol operator*(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Returns the \b product of \a t_symbol1 and \a t_symbol2.
 * \param t_symbol1  Left operand, a Symbol.
 * \param t_symbol2 Right operand, a Symbol.
 * \return The product of the two operands.
 */
Symbol operator*(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn Symbol operator/(const Symbol& t_symbol, int t_value)
 * \brief Returns the \b division of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, an integer.
 * \return The division of the two operands.
 */
Symbol operator/(const Symbol& t_symbol, int t_value);

/*! \fn Symbol operator/(int t_value, const Symbol& t_symbol)
 * \brief Returns the \b division of \a t_value and \a t_symbol.
 * \param t_value  Left operand, an integer.
 * \param t_symbol Right operand, a Symbol.
 * \return The division of the two operands.
 */
Symbol operator/(int t_value, const Symbol& t_symbol);

/*! \fn Symbol operator/(const Symbol& t_symbol, double t_value)
 * \brief Returns the \b division of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, a double.
 * \return The division of the two operands.
 */
Symbol operator/(const Symbol& t_symbol, double t_value);

/*! \fn Symbol operator/(double t_value, const Symbol& t_symbol)
 * \brief Returns the \b division of \a t_value and \a t_symbol.
 * \param t_value  Left operand, a double.
 * \param t_symbol Right operand, a Symbol.
 * \return The division of the two operands.
 */
Symbol operator/(double t_value, const Symbol& t_symbol);

/*! \fn Symbol operator/(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Returns the \b division of \a t_symbol1 and \a t_symbol2.
 * \param t_symbol1  Left operand, a Symbol.
 * \param t_symbol2 Right operand, a Symbol.
 * \return The division of the two operands.
 */
Symbol operator/(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn Symbol operator^(const Symbol& t_symbol, int t_value)
 * \brief Returns the \b division of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, an integer.
 * \return The division of the two operands.
 */
Symbol operator^(const Symbol& t_symbol, int t_value);

/*! \fn Symbol operator^(int t_value, const Symbol& t_symbol)
 * \brief Returns the \b division of \a t_value and \a t_symbol.
 * \param t_value  Left operand, an integer.
 * \param t_symbol Right operand, a Symbol.
 * \return The division of the two operands.
 */
Symbol operator^(int t_value, const Symbol& t_symbol);

/*! \fn Symbol operator^(const Symbol& t_symbol, double t_value)
 * \brief Returns the \b division of \a t_symbol and \a t_value.
 * \param t_symbol Left operand, a Symbol.
 * \param t_value  Right operand, a double.
 * \return The division of the two operands.
 */
Symbol operator^(const Symbol& t_symbol, double t_value);

/*! \fn Symbol operator^(double t_value, const Symbol& t_symbol)
 * \brief Returns the \b division of \a t_value and \a t_symbol.
 * \param t_value  Left operand, a double.
 * \param t_symbol Right operand, a Symbol.
 * \return The division of the two operands.
 */
Symbol operator^(double t_value, const Symbol& t_symbol);

/*! \fn Symbol operator^(const Symbol& t_symbol1, const Symbol& t_symbol2)
 * \brief Returns the \b division of \a t_symbol1 and \a t_symbol2.
 * \param t_symbol1  Left operand, a Symbol.
 * \param t_symbol2 Right operand, a Symbol.
 * \return The division of the two operands.
 */
Symbol operator^(const Symbol& t_symbol1, const Symbol& t_symbol2);

/*! \fn std::ostream& operator<<(std::ostream& fout, const Symbol& t_symbol)
 * \brief Prints \b abstract in standard output.
 */
std::ostream& operator<<(std::ostream& fout, const Symbol& t_symbol);

#endif
