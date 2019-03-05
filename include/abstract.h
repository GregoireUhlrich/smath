/*! \file abstract.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Base classes for all expressions in the program.
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
        Indicial=60, /*!<  = 60. Concerns all indicial expressions (and indices). */
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
Expr Empty(smType::Type type); // source in symbol.cpp

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
     * another expression.
     */
    virtual void print(int mode=0) const = 0;

    void printExplicit(int mode=0) const;

    /*! \brief Creates a LaTeX output for the Abstract.
     * \param mode Tells if the Abstract is printed alone (default) or in 
     * another expression.
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
     * different functions to know what type of expression they are 
     * manipulating (single number, scalar function with one argument, with 
     * multiple argumments, a Vector, etc) in order to do special treatments 
     * or simplifications.
     * \return type (a non memorized integer corresponding to the type of abstract)
     */
    virtual smType::PrimaryType getPrimaryType() const = 0; 

    /*! \brief Gives the \b type of Abstract.
     * \details In the program this function is very often called. It allows 
     * different functions to know what type of expression they are 
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

    virtual bool isBuildingBlock() const;

                                                       


    /*************************************************/
    // Access functions for specializations          //
    /*************************************************/

    // Numerical- and Literal-type expressions
    virtual bool isInteger() const;
    virtual bool getValued() const;
    virtual double getValue() const;

    // Class CFraction
    virtual int getNum() const; 
    virtual int getDenom() const; 

    // Multi-argument abstracts
    virtual int getNArgs(int axis=0) const; 
    virtual Expr getArgument(int iArg=0) const; 
    virtual Expr getArgument(const std::initializer_list<int>& indices) const;
    virtual Expr getArgument(const std::vector<int>& indices) const;
    virtual const std::vector<Expr >& getVectorArgument() const;

    // Derivative, Polynomial, Integral
    virtual Expr getVariable() const;
    virtual int getOrder() const;

    // Vectorial-type expressions
    virtual std::vector<int> getShape() const;

    // Indicial-type expressions
    virtual int getNIndices() const;
    virtual Index getIndex(int i=0) const;
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

    // Numerical- and Literal-Type
    virtual void setValue(double t_value);

    // Multi-argument abstracts
    virtual void setArgument(const Expr& t_abstract, int iArg=0);
    virtual void setArgument(const Expr& t_abstract,
                             const std::initializer_list<int>& indices);
    virtual void setArgument(const Expr& t_abstract,
                             const std::vector<int>& indices);
    virtual void setVectorArgument(const std::vector<Expr >& t_argument);

    // Plus- and Times-type.
    virtual void insert(const Expr& t_abstract, bool side=0);

    // Indicial-type
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
    // making canonical expressions
    virtual Expr getNumericalFactor() const;
    virtual int getNFactor() const;
    virtual std::vector<Expr > getFactors() const;
    virtual Expr getTerm();

    // Vectorial-expression: matching shapes before calculation
    virtual bool checkIndexStructure(const std::vector<Index>& t_index) const;
    virtual bool checkIndexStructure(const std::initializer_list<Index>& index) const;

                                                       
                                                       

    /*************************************************/
    // Getting properties depending on an expression //
    /*************************************************/

    virtual int getParity(const Expr& t_variable) const;

    virtual bool askTerm(const Expr& t_abstract, bool exact=false) const;

    virtual bool dependsOn(const Expr& t_abstract) const;

    virtual int isPolynomial(const Expr& t_abstract) const;

    virtual bool isProportionalTo(const Expr& t_abstract) const;

    virtual bool matchShape(const Expr& t_abstract, bool exact=false) const;




    /*************************************************/
    // Members that return new expressions           //
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
     * \details It is possible to derive wrt any complicated expression. 
     * In this case however, the calculation is \b not \b always \b 
     * mathematically \b correct. The program just searches for equal 
     * Abstract or Abstract with the same name. In particular dx/d(exp(x))=0.
     * \param t_abstract Expression wrt which we derive.
     * \return The derivative.
     */
    virtual Expr derive(const Expr& t_abstract) const; 

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

    /*! \brief Remove a factor from an expression, that must have been
     * determined before.
     * \param factor Expression to remove
     * \return The expression in which \b factor has been removed
     */
    virtual Expr suppressTerm(const Expr& t_abstract) const;

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
    // Members that return new expressions           //
    // results of specific calculations              //
    // SPECIFIC TO SOME ABSTRACTS PART               //
    /*************************************************/

    // Specialized for Numerical-, Vectorial-type.
    virtual Expr addition_own(const Expr& t_abstract) const;
    virtual Expr multiplication_own(const Expr& t_abstract) const;
    virtual Expr division_own(const Expr& t_abstract) const;
    virtual Expr exponentiation_own(const Expr& t_abstract) const;

    // Getting regular expression from a Polynomial-type
    virtual Expr getRegularExpression() const;

    // Vectorial-type functions
    virtual Expr tensor_dot(const Expr& t_abstract) const;
    virtual Expr dot(const Expr& t_abstract) const;
    virtual Expr getSum() const;
    virtual Expr getProduct() const; 
    virtual Expr getVectorialModulus() const;
    virtual Expr getSubVectorial(int iExcept) const;
    virtual Expr getSubVectorial(int iExcept, int jExcept) const;
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

    virtual void operator=(double t_value);

    // Comparison operators
    virtual bool operator==(int t_value) const; 
    virtual bool operator==(double t_value) const; 
    virtual bool operator!=(int t_value) const; 
    virtual bool operator!=(double t_value) const; 

    /*! \brief \b Compares the Abstract with another.
     * \details Here if two Abstracts have the same name, the function will 
     * return \b true even if they are \b not \b mathematically \b equal. 
     * So beware not to name different things the same way.
     * \param t_abstract Abstract to compare.
     * \return \b True if the two Abstracts are the same (or have the same name).
     * \return \b False else.
     */
    virtual bool operator==(const Expr& t_abstract) const = 0; 
    /*! \brief \b Compares the Abstract with another.
     * \param t_abstract Abstract to compare.
     * \return False if the two Abstracts are the same (or have the same name).
     * \return True else.
     */
    virtual bool operator!=(const Expr& t_abstract) const; 

    // Access operator for multi-argument expressions
    virtual Expr operator[](int iArg);

    // Comparison operators in terms of simplicity (for simplifications)
    // For example x < x² and (y*x + 1) > (1 + x*y)

    // operator corresponding to '=='
    virtual bool operator|=(const Expr& t_abstract) const;
    // operator corresponding to '!='
    virtual bool operator&=(const Expr& t_abstract) const;
    virtual bool operator>(const Expr& t_abstract) const = 0;
    virtual bool operator<(const Expr& t_abstract) const = 0;
    bool operator>=(const Expr& t_abstract) const;
    bool operator<=(const Expr& t_abstract) const;
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

    int getDim() const override { return 0;}
};

/*************************************************/
// Inline functions (non virtual and short)      //
/*************************************************/
inline Abstract::Abstract(): name(""), commutable(true){}
inline Abstract::Abstract(const std::string& t_name): name(t_name),
                                                      commutable(true){}
inline std::string Abstract::getName() const{
    return name;
}
inline int Abstract::getDim() const{
    return 0;
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


/*************************************************/
// Redefinition of operator for Expr alias       //
// std::shared_ptr<Abstract>. Allows then to use //
// operator with both syntaxes:                  //
// (*a op b) AND (a op b) with a and b Expr.     //
/*************************************************/
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

/*************************************************/
// Usefull function of Copy/Refresh of Expr      //
/*************************************************/
Expr Copy(const Abstract* t_abstract);

/*! \fn Expr Copy(const Expr& t_abstract) Expr Copy(const Expr& t_abstract)
 * \brief \b Copy an Abstract to depth 1.
 * \details \b Copy the depth 0 structure. For example the copy of cos(x+exp(y)) 
 * creates another cos function but take a reference to x+exp(y). Note that copy
 *  a \b Variable will create another with the same name. It could create 
 * misunderstanding in the following operations.
 * \param t_abstract Abstract to copy.
 * \return The copy.
 */
Expr Copy(const Expr& t_abstract);

Expr DeepCopy(const Abstract* t_abstract);

/*! \fn Expr DeepCopy(const Expr& t_abstract) Expr DeepCopy(const Expr& t_abstract)
 * \brief \b Copy an Abstract to the \b maximum depth.
 * \details \b Copy \b recursively the entire Abstract.
 * \param t_abstract The Abstract to copy.
 * \return The deepCopy.
 */
Expr DeepCopy(const Expr& t_abstract);

Expr Refresh(const Abstract* t_abstract);

/*! \fn Expr Refresh(const Expr& t_abstract) Expr Refresh(const Expr& t_abstract)
 * \brief \b Refresh an Abstract and apply basic simplifications.
 * \details Apply all simplifications that take place normally at the creation
 * of an Abstract. For example, a sum with only one term gives just the term in
 * question. The refresh is automatically resursive.
 * \param t_abstract The Abstract to refresh.
 * \return The refreshed Abstract.
 */
Expr Refresh(const Expr& t_abstract);

Expr DeepRefresh(const Expr& t_abstract);

/*! \fn Expr Replace(const Expr& t_abstract,
                     const Expr& old_abstract,
                     const Expr& new_abstract)
 * \brief \b Replace an Abstract by another in an expression.
 * \details This function allows to replace \a old_abstract by \a new_abstract 
 * in \a t_abstract. For example Replace(cos(x+x^2),x,y-1) = cos(y-1+(y-1)^2). 
 * It leaves the original Abstract \b invariant and returns another Abstract.
 * \param t_abstract Abstract in which the replacement takes place.
 * \param old_abstract Abstract to search and replace.
 * \param new_abstract Abstract by which we replace.
 * \return A \b new Abstract with the replacement done.
 */
Expr Replace(const Expr& t_abstract,
             const Expr& old_abstract,
             const Expr& new_abstract);

#endif
