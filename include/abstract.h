/*! \file abstract.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Base classes for all exprs in the program.
 */

#pragma GCC diagnostic ignored "-Wunused-parameter"
#ifndef AbsTRACT_H_INCLUDED
#define AbsTRACT_H_INCLUDED
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <memory>
#include <algorithm>
#include <thread>
#include <mutex>
#include "error.h"

// Forward declaration of Abstract class
class Abstract;

// Definition of Expr type 
typedef std::shared_ptr<Abstract> Expr;

// Definition of contExpr type
typedef std::shared_ptr<const Abstract> constExpr;

// Definition of iter type
typedef std::vector<Expr>::iterator iter;

// Definition of const_iter type
typedef std::vector<Expr>::const_iterator const_iter;


namespace smType{


    /*! \enum Enum of the different primaryTypes of Abstract.*/
    enum PrimaryType {

        Numerical, /*!< = 0. Concerns Number and CFraction. */
        Literal, /*!< = 1. Concerns Variable, CFactorial and Imaginary. */
        MultiFunction=10, /*!< = 10. Concerns all scalar multi-variate functions
                            (Plus, Times, Pow, etc). */
        ScalarFunction=20, /*!< = 20. Concerns all scalar uni-variate functions
                             (Exp, Log, Cos, etc). */
        Vectorial=50,
        Indicial=60, /*!<  = 60. Concerns all indicial exprs (and indices). */
    };

    /*! \enum Enum of the different types of Abstract
      (i.e. list of all possible specializations).*/
    enum Type {

        Integer, /*!<  = 0. Abstract specialized in Integer */
        CFraction, /*!<  = 1. Abstract specialized in CFraction */
        Double, /*!<  = 2. Abstract specialized in Double */
        CFactorial, /*!<  = 3. Abstract specialized in CFactorial */
        Imaginary, /*!<  = 4. Abstract specialized in Imaginary */
        Constant, /*!<  = 5. Abstract specialized in Constant */
        Variable, /*!<  = 6. Abstract specialized in Variable */
        Plus=10, /*!<  = 10. Abstract specialized in Plus */
        Polynomial, /*!<  = 11. Abstract specialized in Polynomial */
        Times, /*!<  = 12. Abstract specialized in Times */
        Fraction, /*!<  = 13. Abstract specialized in Fraction */
        Pow, /*!<  = 14. Abstract specialized in Pow */
        Exp=20, /*!<  = 20. Abstract specialized in Exp */
        Log, /*!<  = 21. Abstract specialized in Log */
        Abs, /*!<  = 22. Abstract specialized in Abs */
        Cos, /*!<  = 23. Abstract specialized in Cos */
        Sin, /*!<  = 24. Abstract specialized in Sin */
        Tan, /*!<  = 25. Abstract specialized in Tan */
        Cosh, /*!<  = 26. Abstract specialized in Cosh */
        Sinh, /*!<  = 27. Abstract specialized in Sinh */
        Tanh, /*!<  = 28. Abstract specialized in Tanh */
        Derivative, /*!<  = 29. Abstract specialized in Derivative */
        Angle, /*!<  = 30. Abstract specialized in Angle */
        Factorial, /*!<  = 31. Abstract specialized in Factorial */
        ACos, /*!<  = 32. Abstract specialized in ACos */
        ASin, /*!<  = 33. Abstract specialized in ASin */
        ATan, /*!<  = 34. Abstract specialized in ATan */
        ACosh, /*!<  = 35. Abstract specialized in ACosh */
        ASinh, /*!<  = 36. Abstract specialized in ASinh */
        ATanh, /*!<  = 37. Abstract specialized in ATanh */

        Vector=50, /*!<  = 50. Abstract specialized in Vector */
        Matrix, /*!<  = 51. Abstract specialized in Matrix */
        HighDTensor, /*!<  = 52. Abstract specialized in HighDTensor */

        ITensor=60, /*!<  = 60. Abstract specialized in ITensor */
        ITerm, /*!<  = 61. Abstract specialized in ITerm */
    };

}; // End of namespace smType

namespace smProperty{

    enum OwnBProperty{
        BuildingBlock=0,
        Integer,
        Valued,
        Commutable,
    };

    enum DependBProperty{
        Proportionnal=0,
        Depends,
    };

    enum OwnIProperty{
        Value=0,
        Dim,
        Numerator,
        Denominator,
        NFactor,
        Order,
        NIndices,
    };

    enum DependIProperty{
        Polynomial=0,
        Parity,
    };

}; // End of namespace smProperty

std::ostream& operator<<(std::ostream& fout, smType::Type type);
std::ostream& operator<<(std::ostream& fout, smType::PrimaryType primaryType);

// Creates a generic Expression of a given type
Expr Empty(smType::Type type); // source in symbol.cpp

// Forward declaration of Index class (indicial.h)
class Index;


/*! \class Abstract
 * \brief \b Root class of the inheritance tree of abstracts.
 * \details Contains all functions that derived class needs. In particular all 
 * documented functions of the class Abstract are \b specialized in all the \b 
 * derived \b classes. 
 * \note Some functions are not documented here because not every derived class
 *  use them. 
 */
class Abstract{

    protected:
    /*! Name that will define the object, \b crucial \b in \b comparisons.*/
    std::string name; 

    /*! Determines if the object \b commutes with all other objects.*/
    bool commutable;

    public:

    /*************************************************/
    // Constructors and destructors                  //
    /*************************************************/

    /*!
     * \brief Default Constructor.
     * \details Initializes name empty and commutable to one.
     */
    Abstract();
    
    /*! \brief Set the name to t_name. */
    explicit Abstract(const std::string& t_name);

    /*! \brief Destructor.*/
    virtual ~Abstract(){}

                                                       
                                                       

    /*************************************************/
    // Utils, common to all Abstract                 //
    /*************************************************/

    /*! \brief Displays the abstract in standard output.
     * \param mode Tells if the Abstract is printed alone (default) or in 
     * another expr.
     */
    virtual void print(int mode=0) const = 0;

    void printExplicit(int mode=0) const;

    /*! \brief Creates a LaTeX output for the Abstract.
     * \param mode Tells if the Abstract is printed alone (default) or in 
     * another expr.
     * \return The string corresponding to the LaTeX output.
     */
    virtual std::string printLaTeX(int mode=0) const;

                                                       
                                                       

    /*************************************************/
    // Common access functions for all Abstracts     //
    /*************************************************/

    /*! \brief Returns the Abstract's name.
     * \return \a name
     */
    std::string getName() const; 
    
    /*! \brief Allows to know if the object commutes with all the others.
     * \return \a commutable
     */
    virtual bool getCommutable() const; 

    /*! \brief Gives the \b primary \b type of Abstract.
     * \details In the program this function is very often called. It allows 
     * different functions to know what type of expr they are 
     * manipulating (single number, scalar function with one argument, with 
     * multiple argumments, a Vector, etc) in order to do special treatments 
     * or simplifications.
     * \return type (a non memorized integer corresponding to the type of abstract)
     */
    virtual smType::PrimaryType getPrimaryType() const = 0; 

    /*! \brief Gives the \b type of Abstract.
     * \details In the program this function is very often called. It allows 
     * different functions to know what type of expr they are 
     * manipulating (cos, product, number, etc) in order to do special 
     * treatments or simplifications.
     * \return type (a non memorized integer corresponding to the type of abstract)
     */
    virtual smType::Type getType() const = 0;

    /*! \brief Gives the \b dimension of the object.
     * \details Allows to know if we are manipulating a pure scalar (i.e. that 
     * can have a real value) or something else. There is the particular case 
     * of the Imaginary \b i that is considered as a scalar for simplicity 
     * but in reality cannot be evaluated with a real. Example: 1 + \b i 
     * cannot be reduced.
     * \return dim (a non memorized integer corresponding to the dimension of 
     * the abstract)
     */
    virtual int getDim() const = 0;

    /*! \brief Tells if the expression is a Building Block or not.
     * \details Building blocks are derived classes that cannot contain further
     * expressions, i.e. expressions that are the leafs of the recursive
     * tree reprensent mathematical expressions: numerical or pure literal 
     * objects (variable, constant etc).
     * \return \b True if \a *this is a Building Block.
     * \return \b False else.
     */
    virtual bool isBuildingBlock() const;

                                                       


    /*************************************************/
    // Access functions for specializations          //
    /*************************************************/

    ///////////////////////////////////////////////////
    // Numerical- and Literal types
    ///////////////////////////////////////////////////

    /*! \brief Tells if the expression is an integer. Either an Integer object 
     * directly, or a Double that has an integer value.
     * \return \b True if \a *this is an Integer or a Double with integer value.
     * \return \b False else.
     */
    virtual bool isInteger() const;
    /*! \brief Tells if the expression is valued, i.e. is a function of numbers
     * and valued literals (a Variable or Constant is not valued by default).
     * \return \b True if the expression is valued.
     * \return \b False else.
     */
    virtual bool getValued() const;
    /*! \brief Returns the value of the expression, if it has one \b explicitely.
     * In particular, it will work only on Numbers and valued Literals, not on
     * functions.
     * \return The value of the expression.
     */
    virtual double getValue() const;

    ///////////////////////////////////////////////////
    // Class CFraction
    ///////////////////////////////////////////////////

    /*! \return The numerator for a CFraction.
     */
    virtual int getNum() const; 
    /*! \return The denominator for a CFraction.
     */
    virtual int getDenom() const; 

    ///////////////////////////////////////////////////
    // (Multiple) argument(s) functions
    ///////////////////////////////////////////////////

    /*! \brief Returns the number of arguments of the expression. If the 
     * expression is a building block  (AbstractBuildingBlock), this function
     * returns 0.
     * \return The number of arguments of the expression.
     */
    virtual int getNArgs(int axis=0) const;

    /*! \warning This function must not be called for building blocks, one must
     * check first that the expression has arguments.
     * \return The i^{th} argument of the expression.
     */
    virtual Expr getArgument(int iArg=0) const; 

    /*! \brief Allows to get specific arguments of expressions in multiple
     * dimensions, by giving the indices in each dimension.
     * \warning This function must not be called for building blocks, one must
     * check first that the expression has arguments.
     * \return The argument {i,j,...} of the expression.
     */
    virtual Expr getArgument(const std::initializer_list<int>& indices) const;

    /*! \brief Allows to get specific arguments of expressions in multiple
     * dimensions, by giving the indices in each dimension.
     * \warning This function must not be called for building blocks, one must
     * check first that the expression has arguments.
     * \return The argument {i,j,...} of the expression.
     */
    virtual Expr getArgument(const std::vector<int>& indices) const;

    /*! \brief Allows to get the entire std::vector of arguments of the expression.
     * \warning This function must not be called for building blocks, one must
     * check first that the expression has arguments.
     * \return The std::vector of argument.
     */
    virtual const std::vector<Expr >& getVectorArgument() const;

    ///////////////////////////////////////////////////
    // Derivative, Integral, Polynomial
    ///////////////////////////////////////////////////

    /*! \brief Accessor to the variable that defines certain types of expressions.
     * \return \b variable.
     */
    virtual Expr getVariable() const;

    /*! \brief Accessor to the order (integer) that defines certain types of
     * expressions.
     * \return \b order.
     */
    virtual int getOrder() const;

    ///////////////////////////////////////////////////
    // Vectorial-type expressions
    ///////////////////////////////////////////////////

    /*! \brief Accessor to the shape of the tensor in the form of a std::vector
     * of integers.
     * \return \b shape.
     */
    virtual std::vector<int> getShape() const;

    ///////////////////////////////////////////////////
    // Indicial-type expressions
    ///////////////////////////////////////////////////

    /*! \return The number of indices of an Indicial expression.
     */    
    virtual int getNIndices() const;
    /*! \param i Spot of the index to get.
     * \return the i^{th} index of an Indicial expression.
     */
    virtual Index getIndex(int i=0) const;
    /*! \return The index structure of the expression
     */
    virtual std::vector<Index> getIndexStructure() const;
    virtual int getNContractedPairs() const;
    virtual std::vector<Expr> getPermutations() const;
    virtual std::set<std::pair<int,int> > getContractedPair() const;

                                                       
                                                       

    /*************************************************/
    // Common modifiers for all Abstracts            //
    /*************************************************/

    /*! \brief Change the name of the abstract.
     * \param t_name Replaces name.
     */
    void setName(const std::string& t_name); 

    /*! \brief Allows the abstract to commute or not.
     * \param t_commutable Must be \b true if the abstract can commute.
     */
    void setCommutable(bool t_commutable); 

                                                       
                                                       

    /*************************************************/
    // Modifiers for specializations                 //
    /*************************************************/

    ///////////////////////////////////////////////////
    // Numerical- and Literal- types
    ///////////////////////////////////////////////////
    
    /*! \brief Sets the value if there is one (for Numerical and Literal valued).
     */
    virtual void setValue(double t_value);

    ///////////////////////////////////////////////////
    // (Multi) argument(s) functions
    ///////////////////////////////////////////////////

    /*! \brief Sets the argument at position \b iArg (default=0).
     * \param expr Expression that replaces the argument.
     * \param iArg the position of the argument to change.
     */
    virtual void setArgument(const Expr& expr, int iArg=0);

    /*! \brief Sets the argument at position \b {i,j,...} for multi-dimensions 
     * expressions.
     * \param expr Expression that replaces the argument.
     * \param indices An intializer_list containing the series of indices 
     * corresponding to the argument to replace.
     */
    virtual void setArgument(const Expr& expr,
                             const std::initializer_list<int>& indices);

    /*! \brief Sets the argument at position \b {i,j,...} for multi-dimensions 
     * expressions.
     * \param expr Expression that replaces the argument.
     * \param indices An std::vector containing the series of indices 
     * corresponding to the argument to replace.
     */
    virtual void setArgument(const Expr& expr,
                             const std::vector<int>& indices);

    /*! \brief Replace the entire std::vector of argument.
     * \param t_argument std::vector of expressions to copy.
     */
    virtual void setVectorArgument(const std::vector<Expr >& t_argument);

    ///////////////////////////////////////////////////
    // Plus and Times
    ///////////////////////////////////////////////////

    /*! \brief Inserts an expression in a sum or a product.
     * \details Allows to insert an element in a sum or product without 
     * comparing all existing terms. This saves time when inserting element by     
     * element. The \b side parameter allows to insert to the left (side = 0)
     * or to the right (side = 1) in products (useful when considering non
     * commutating expressions.
     * \param expr Expression to insert.
     * \param side Side of insertion for Times expressions.
     */
     virtual void insert(const Expr& expr, bool side=0);

    ///////////////////////////////////////////////////
    // Indicial types
    ///////////////////////////////////////////////////

    virtual void setIndexStructure(const std::vector<Index>& t_index);
    virtual void setFullySymmetric();
    virtual void setFullyAntiSymmetric();
    virtual void addSymmetry(int i1, int i2);
    virtual void addAntiSymmetry(int i1, int i2);
    virtual int permut(int i1, int i2);
    virtual void contractIndices(int axis1, int axis2);

                                                       
                                                       

    /*************************************************/
    // Getting properties that need calculation      //
    /*************************************************/

    // Usefull for factorization and
    // making canonical exprs
    virtual Expr getNumericalFactor() const;
    virtual int getNFactor() const;
    virtual std::vector<Expr > getFactors() const;
    virtual Expr getTerm();

    // Vectorial-expr: matching shapes before calculation
    virtual bool checkIndexStructure(const std::vector<Index>& t_index) const;
    virtual bool checkIndexStructure(const std::initializer_list<Index>& index) const;

                                                       
                                                       

    /*************************************************/
    // Getting properties depending on an expr //
    /*************************************************/

    virtual int getParity(const Expr& t_variable) const;

    virtual bool askTerm(const Expr& expr, bool exact=false) const;

    virtual bool dependsOn(const Expr& expr) const;

    virtual int isPolynomial(const Expr& expr) const;

    virtual bool isProportionalTo(const Expr& expr) const;

    virtual bool matchShape(const Expr& expr, bool exact=false) const;




    /*************************************************/
    // Members that return new exprs                 //
    // results of specific calculations              //
    // COMMON TO ALL ABSTRACTS PART                  //
    /*************************************************/

    /*! \brief \b Evaluates the value of the Abstract.
     * \details Tries to replace all variables by a real value. 
     * If it is not possible (for example treating a Vector or an Imaginary) 
     * the considered object is replaced by 0. A warning message is displayed 
     * in the case of i.
     * \return The value of the Abstract (double).
     */
    virtual double evaluateScalar() const; 

    /*! \brief \b Evaluates the Abstract.
     * \details Replaces all variables by their value and evaluating. 
     * This function must be used instead of evaluateScalar() when treating 
     * not only real scalars.* In particular (x=2, y=3) x+iy evaluates to 3+
     * 3i whereas evaluateScalar() would return 3.
     * \return The abstract result of the evaluation.
     */
    virtual Expr evaluate() = 0;

    /*! \brief Calculates the derivative of the Abstract wrt another.
     * \details It is possible to derive wrt any complicated expr. 
     * In this case however, the calculation is \b not \b always \b 
     * mathematically \b correct. The program just searches for equal 
     * Abstract or Abstract with the same name. In particular dx/d(exp(x))=0.
     * \param expr Expression wrt which we derive.
     * \return The derivative.
     */
    virtual Expr derive(const Expr& expr) const; 

    /*! \brief \b Factors the Abstract.
     * \details This function tries to factor the Abstract wrt any \b factor. 
     * This will be more involved in calculation than the other factorizing 
     * function that takes the factor as a parameter. So this function **must 
     * be used only** if we don't know the factors we want at the end.
     * \param full If true the factorization is \b recursive through all the Abstract.
     */
    virtual Expr factor(bool full=false);

    /*! \brief \b Factors the Abstract wrt a **particular** Abstract.
     * \param factor Abstract wrt which we try to factor.
     * \param full   If true the factorization is \b recursive through all the Abstract.
     */
    virtual Expr factor(const Expr& factor, bool full=false);

    /*! \brief Remove a factor from an expr, that must have been
     * determined before.
     * \param factor Expression to remove
     * \return The expr in which \b factor has been removed
     */
    virtual Expr suppressTerm(const Expr& expr) const;

    /*! \brief \b Develops the Abstract.
     * \details This function concerns only products (and exponents) that will be
     * flatten to give at the end a sum of independant terms.
     * \param full If true the development is \b recursive through all the Abstract.
     * \return The develop Abstract.
     */
    virtual Expr develop(bool full=false);

    /*! \brief \b Evaluates the **real part** of the Abstract and returns it.
     * \return The real part of the Abstract.
     */
    virtual Expr getRealPart();

    /*! \brief \b Evaluates the **imaginary part** of the Abstract and returns it.
     * \return The imaginary part of the Abstract.
     */
    virtual Expr getImaginaryPart() const;

    /*! \brief \b Evaluates the **modulus in the complex plane** of the Abstract 
     * and returns it.
     * \return The modulus part of the Abstract.
     */
    virtual Expr getComplexModulus();
    
    /*! \brief \b Evaluates the **argument in the complex plane** of the 
     * Abstract and returns it.
     * \return The argument part of the Abstract.
     */
    virtual Expr getComplexArgument();

    virtual Expr getComplexConjugate();

    virtual Expr getPolynomialTerm(const Expr& t_variable, int order);

    // Alternate forms for simplification
    virtual std::vector<Expr > getAlternateForms() const;




    /*************************************************/
    // Members that return new exprs                 //
    // results of specific calculations              //
    // SPECIFIC TO SOME ABSTRACTS PART               //
    /*************************************************/

    ///////////////////////////////////////////////////
    // Numerical- Polynomial- and Vectorial-types
    ///////////////////////////////////////////////////
    
    /*! \brief Contains implementation of special addition for Numerical- and
     * Vectorial-types. 
     * \param expr Right operrand of the addition.
     * \return The sum of the two operands.
     */
    virtual Expr addition_own(const Expr& expr) const;

    /*! \brief Contains implementation of special multiplication for Numerical- and
     * Vectorial-types. 
     * \param expr Right operrand of the product.
     * \return The product of the two operands.
     */
    virtual Expr multiplication_own(const Expr& expr) const;

    /*! \brief Contains implementation of special division for Numerical- and
     * Polynomial-types. For polynomial, the euclidean division of two polynomials
     * is implemented.
     * \param expr Right operrand of the division.
     * \return The division of the two operands.
     */
    virtual Expr division_own(const Expr& expr) const;

    /*! \brief Contains implementation of special exponentiation for Numerical- and
     * Vectorial-types. 
     * \param expr exponent.
     * \return The exponentiation of the two operands.
     */
    virtual Expr exponentiation_own(const Expr& expr) const;

    ///////////////////////////////////////////////////
    // Polynomial type
    ///////////////////////////////////////////////////

    /*! \brief Returns a regular expression from the polynomial, that is a sum
     * where the different powers of the variable appear explicitely.
     * \return a Plus expression equal to the polynomial.
     */
    virtual Expr getRegularExpression() const;

    ///////////////////////////////////////////////////
    // Vectorial type
    ///////////////////////////////////////////////////

    virtual Expr tensor_dot(const Expr& expr) const;
    virtual Expr dot(const Expr& expr) const;
    virtual Expr getSum() const;
    virtual Expr getProduct() const; 
    virtual Expr getVectorialModulus() const;
    /*! \brief Allows to pick a part of a Vectorial expression, excluding
     * the iExcept^{th} element.
     * \param iExcept Element to ignore.
     * \return The part of *this excluding iExcept.
     */
    virtual Expr getSubVectorial(int iExcept) const;
    /*! \brief Allows to pick a part of a Vectorial expression, excluding
     * the [iExcept^{th},jExcept^{th}] element (useful for matrices).
     * \param iExcept Element of the first axis to ignore.
     * \param jExcept Element of the second axis to ignore.
     * \return The part of *this excluding iExcept.
     */
    virtual Expr getSubVectorial(int iExcept, int jExcept) const;
    /*! \brief Allows to pick a part of a Vectorial expression, excluding
     * the iExcept^{th} element.
     * \param iExcept Element to ignore.
     * \return The part of *this excluding iExcept.
     */
    virtual Expr getSubVectorial(const std::vector<int>& exceptions) const;
    virtual Expr determinant() const;
    virtual Expr trace() const;
    virtual Expr trace(int axis1, int axis2) const;
    virtual Expr transpose() const;
    virtual Expr symmetrise() const;
    virtual Expr antisymmetrise() const;
    virtual Expr inverseMatrix() const;




    /*************************************************/
    // Operators                                     //
    /*************************************************/

    /*! \brief Equivalent to the setValue() function.
     * \param t_value The new value of the expression.
     */
    virtual void operator=(double t_value);

    /*! \return \b True if the expression is valued and is equal to t_value.
     * \return \b False else.
     */
    virtual bool operator==(int t_value) const; 
    /*! \return \b True if the expression is valued and is equal to t_value.
     * \return \b False else.
     */
    virtual bool operator==(double t_value) const; 
    /*! \return \b False if the expression is valued and is equal to t_value.
     * \return \b True else.
     */
    virtual bool operator!=(int t_value) const; 
    /*! \return \b False if the expression is valued and is equal to t_value.
     * \return \b True else.
     */
    virtual bool operator!=(double t_value) const; 

    /*! \brief \b Compares the Abstract with another.
     * \details Here if two Abstracts have the same name, the function will 
     * return \b true even if they are \b not \b mathematically \b equal. 
     * So beware not to name different things the same way.
     * \param expr Abstract to compare.
     * \return \b True if the two Abstracts are the same (or have the same name).
     * \return \b False else.
     */
    virtual bool operator==(const Expr& expr) const = 0; 

    /*! \brief \b Compares the Abstract with another.
     * \param expr Abstract to compare.
     * \return False if the two Abstracts are the same (or have the same name).
     * \return True else.
     */
    virtual bool operator!=(const Expr& expr) const; 

    // Access operator for multi-argument exprs
    virtual Expr operator[](int iArg);

    // Comparison operators in terms of simplicity (for simplifications)
    // For example x < x² and (y*x + 1) > (1 + x*y)


    /*! \brief Compares the simplicity of the expression to another.
     * \param expr \b Expression to compare.
     * \return \b True if the two expression have the same simplicity.
     * \return \b False else.
     */
    virtual bool operator|=(const Expr& expr) const;

    /*! \brief Compares the simplicity of the expression to another.
     * \param expr \b Expression to compare.
     * \return \b False if the two expression have the same simplicity.
     * \return \b True else.
     */
    virtual bool operator&=(const Expr& expr) const;

    /*! \brief Compares the simplicity of the expression to another.
     * \param expr \b Expression to compare.
     * \return \b True if \b expr is simpler.
     * \return \b False else.
     */
    virtual bool operator>(const Expr& expr) const = 0;

    /*! \brief Compares the simplicity of the expression to another.
     * \param expr \b Expression to compare.
     * \return \b False if \b expr is simpler or equivalent.
     * \return \b True else.
     */
    virtual bool operator<(const Expr& expr) const = 0;

    /*! \brief Compares the simplicity of the expression to another.
     * \param expr \b Expression to compare.
     * \return \b True if \b expr is simpler or equivalent.
     * \return \b False else.
     */
    bool operator>=(const Expr& expr) const;

    /*! \brief Compares the simplicity of the expression to another.
     * \param expr \b Expression to compare.
     * \return \b False if \b expr is simpler.
     * \return \b True else.
     */
    bool operator<=(const Expr& expr) const;
};


/*! \class AbstractScalar
 * \brief Abstract class concerning all scalars (dim = 0).
 * Allows to implement one time getDim() = 0 for all scalar 
 * specializations.
 */
class AbstractScalar: public Abstract{
    public:

    AbstractScalar();
    explicit AbstractScalar(const std::string& t_name);
    ~AbstractScalar(){}

    int getDim() const override {
        return 0;
    }
};

///////////////////////////////////////////////////
/*************************************************/
// Inline functions (non virtual and short)      //
/*************************************************/
///////////////////////////////////////////////////

inline Abstract::Abstract(): name(""), commutable(true){}
inline Abstract::Abstract(const std::string& t_name): name(t_name),
                                                      commutable(true){}
inline std::string Abstract::getName() const{
    return name;
}
inline bool Abstract::getCommutable() const {
    return commutable;
}
inline void Abstract::setName(const std::string& t_name) {
    name = t_name;
}
inline void Abstract::setCommutable(bool t_commutable) {
    commutable = t_commutable;
}
inline AbstractScalar::AbstractScalar(): Abstract(){}
inline AbstractScalar::AbstractScalar(const std::string& t_name)
    :Abstract(t_name){}


///////////////////////////////////////////////////
/*************************************************/
// Redefinition of operator for Expr alias       //
// std::shared_ptr<Abstract>. Allows then to use //
// operator with both syntaxes:                  //
// (*a op b) AND (a op b) with a and b Expr.     //
/*************************************************/
///////////////////////////////////////////////////

bool operator==(const Expr& a, const Expr& b);
bool operator==(const Expr& a, int b);
bool operator==(const Expr& a, double b);
bool operator!=(const Expr& a, const Expr& b);
bool operator!=(const Expr& a, int b);
bool operator!=(const Expr& a, double b);
bool operator>=(const Expr& a, const Expr& b);
bool operator<=(const Expr& a, const Expr& b);
bool operator>(const Expr& a, const Expr& b);
bool operator<(const Expr& a, const Expr& b);
bool operator|=(const Expr& a, const Expr& b);
bool operator&=(const Expr& a, const Expr& b);

///////////////////////////////////////////////////
/*************************************************/
// Usefull function of Copy/Refresh of Expr      //
/*************************************************/
///////////////////////////////////////////////////

Expr Copy(const Abstract* expr);

/*! \fn Expr Copy(const Expr& expr) Expr Copy(const Expr& expr)
 * \brief \b Copy an Abstract to depth 1.
 * \details \b Copy the depth 0 structure. For example the copy of cos(x+exp(y)) 
 * creates another cos function but take a reference to x+exp(y). Note that copy
 *  a \b Variable will create another with the same name. It could create 
 * misunderstanding in the following operations.
 * \param expr Abstract to copy.
 * \return The copy.
 */
Expr Copy(const Expr& expr);

Expr DeepCopy(const Abstract* expr);

/*! \fn Expr DeepCopy(const Expr& expr) Expr DeepCopy(const Expr& expr)
 * \brief \b Copy an Abstract to the \b maximum depth.
 * \details \b Copy \b recursively the entire Abstract.
 * \param expr The Abstract to copy.
 * \return The deepCopy.
 */
Expr DeepCopy(const Expr& expr);

Expr Refresh(const Abstract* expr);

/*! \fn Expr Refresh(const Expr& expr) Expr Refresh(const Expr& expr)
 * \brief \b Refresh an Abstract and apply basic simplifications.
 * \details Apply all simplifications that take place normally at the creation
 * of an Abstract. For example, a sum with only one term gives just the term in
 * question. The refresh is automatically resursive.
 * \param expr The Abstract to refresh.
 * \return The refreshed Abstract.
 */
Expr Refresh(const Expr& expr);

Expr DeepRefresh(const Expr& expr);

/*! \fn Expr Replace(const Expr& expr,
                     const Expr& old_abstract,
                     const Expr& new_abstract)
 * \brief \b Replace an Abstract by another in an expr.
 * \details This function allows to replace \a old_abstract by \a new_abstract 
 * in \a expr. For example Replace(cos(x+x^2),x,y-1) = cos(y-1+(y-1)^2). 
 * It leaves the original Abstract \b invariant and returns another Abstract.
 * \param expr Abstract in which the replacement takes place.
 * \param old_abstract Abstract to search and replace.
 * \param new_abstract Abstract by which we replace.
 * \return A \b new Abstract with the replacement done.
 */
Expr Replace(const Expr& expr,
             const Expr& old_abstract,
             const Expr& new_abstract);

#endif
