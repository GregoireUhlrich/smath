/*! \file variable.h
 * \brief Scalar objects not functions of others.
 */
#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED
#include "abstract.h"
#include "support.h"
#include <iostream>

class AbstractBuildingBlock: public AbstractScalar{
    public:

    AbstractBuildingBlock();
    explicit AbstractBuildingBlock(const std::string& t_name);
    virtual ~AbstractBuildingBlock(){}

    bool isBuildingBlock() const override { return true;}
};

class AbstractNumerical: public AbstractBuildingBlock{
    public:

    AbstractNumerical();
    explicit AbstractNumerical(const std::string& t_name);
    virtual ~AbstractNumerical(){}

    PrimaryType getPrimaryType() const override { return NUMERICAL;}
};

class AbstractLiteral: public AbstractBuildingBlock{
    public:

    AbstractLiteral();
    explicit AbstractLiteral(const std::string& t_name);
    virtual ~AbstractLiteral(){};

    PrimaryType getPrimaryType() const override { return LITERAL;}
};

/////
// Inline functions (non-virtual and very short)
inline AbstractBuildingBlock::AbstractBuildingBlock(): AbstractScalar(){}
inline AbstractBuildingBlock::AbstractBuildingBlock(const std::string& t_name): AbstractScalar(t_name){}

inline AbstractNumerical::AbstractNumerical(): AbstractBuildingBlock(){}
inline AbstractNumerical::AbstractNumerical(const std::string& t_name): AbstractBuildingBlock(t_name){}

inline AbstractLiteral::AbstractLiteral(): AbstractBuildingBlock(){}
inline AbstractLiteral::AbstractLiteral(const std::string& t_name): AbstractBuildingBlock(t_name){}
/////

/*! \class Integer
 * \brief Handle numbers in expression
 * \details Handle the same manner for now double or int values (in a double).
 */
class Integer: public AbstractNumerical{

    protected:

    int value; /*!< \brief Value of the number. */

    public:

    /*! \brief Default constructor.
     * \details Initialize \b value to 0.
     */
    Integer();

    /*! \details Initialize a Integer with the \b value \a t_value.
     * \param t_value double.
     */
    explicit Integer(int t_value);

    /*! \brief Destructor. */
    ~Integer(){};

    /*! \brief Returns the \b type corresponding to an object Integer.
     * \return 0
     */
    Type getType() const;

    bool isInteger() const { return true;}

    /*! \brief Sets the \b value of the Integer.
     * \param t_value New \b value for the Integer.
     */
    void setValue(double t_value);

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    double evaluateScalar() const;

    Expr evaluate() override;

    /*! \brief Multiplicates two pure Numbers.
     * \details If \a t_abstract is not a Number, returns 0. Else returns a Number which value 
     * is equal to the product of \b value and t_abstract.value.
     * \param t_abstract Other Number for the multiplication.
     * \return **value*t_abstract.evaluateScalar()**.
     */
    Expr multiplication_own(const Expr& t_abstract) const override;

    /*! \brief Adds two pure Numbers.
     * \details If \a t_abstract is not a Number, returns 0. Else returns a Number which value 
     * is equal to the sum of \b value and t_abstract.value.
     * \param t_abstract Other Number for the sum.
     * \return **value+t_abstract.evaluateScalar()**.
     */
    Expr addition_own(const Expr& t_abstract) const override;

    /*! \brief Derive the Number.
     * \details The derivative of a Number is \b always 0.
     * \param t_abstract Argument of the derivation.
     * \return \b 0
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(int t_value);
   
    bool operator==(const Expr& t_abstract) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};


/*! \class Double
 * \brief Handle numbers in expression
 * \details Handle the same manner for now double or int values (in a double).
 */
class Double: public AbstractNumerical{

    protected:

    double value; /*!< \brief Value of the number. */

    public:

    /*! \brief Default constructor.
    developed = ZERO;
     * \details Initialize \b value to 0.
     */
    Double();

    /*! \details Initialize a Double with the \b value \a t_value.
     * \param t_value double.
     */
    explicit Double(double t_value);

    /*! \brief Destructor. */
    ~Double(){};

    /*! \brief Returns the \b type corresponding to an object Double.
     * \return 0
     */
    Type getType() const;

    bool isInteger() const { return (value==round(value));}

    /*! \brief Sets the \b value of the Double.
     * \param t_value New \b value for the Double.
     */
    void setValue(double t_value);

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    double evaluateScalar() const;

    Expr evaluate() override;

    /*! \brief Multiplicates two numbers.
     * \details If \a t_abstract is not a Number, returns 0. Else returns a Number which value 
     * is equal to the product of \b value and t_abstract.value.
     * \param t_abstract Other Number for the multiplication.
     * \return **value*t_abstract.evaluateScalar()**.
     */
    Expr multiplication_own(const Expr& t_abstract) const override;

    /*! \brief Adds two pure Numbers.
     * \details If \a t_abstract is not a Number, returns 0. Else returns a Number which value 
     * is equal to the sum of \b value and t_abstract.value.
     * \param t_abstract Other Number for the sum.
     * \return **value+t_abstract.evaluateScalar()**.
     */
    Expr addition_own(const Expr& t_abstract) const override;

    /*! \brief Derives the Double.
     * \details The derivative of a Double is \b always 0.
     * \param t_abstract Argument of the derivation.
     * \return \b 0
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(int t_value);
   
    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(double t_value);

    bool operator==(const Expr& t_abstract) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

/*! \class CFraction
 * \brief Handles \b fractions of Number.
 * \details This class take care of fractionnal arithmetics i.e. reduction
 * of fractions by calculating the PGCD, finding common denominator etc.
 */
class CFraction: public AbstractNumerical{

    protected:

    int num; /*!< Numerator. */
    int denom; /*!< Denominator. */

    public:

    /*! \brief Default Constructor.
     * \details Initializes \b num = 0 and \b denom = 1.
     */
    CFraction();

    /*! \details Initializes \b num = \a t_num and \b denom = 1.
     * \param t_num Numerator.
     */
    explicit CFraction(int t_num);

    /*! \details Initializes both the \b numerator and the \b denominator.
     * \param t_num Numerator.
     * \param t_denom Denominator.
     */
    CFraction(int t_num, int t_denom);

    /*! \brief Destructor
     */
    ~CFraction(){};

    /*! \brief Gives the \b type of a CFraction.
     * \return 2
     */
    Type getType() const;

    /*! \brief Returns the numerator.
     * \return \b num
     */
    int getNum() const;

    /*! \brief Return the denominator.
     * \return \b denom
     */
    int getDenom() const;

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Evaluates the CFraction.
     * \return double(\b num/\b denom)
     */
    double evaluateScalar() const;

    Expr evaluate() override;

    /*! \brief \b Multiplicates the CFraction with a Number or a CFraction.
     * \details This function is specialy designed for the multiplication of 
     * numbers. It shouldn't be used directly by the user in general, because
     * more general product functions will \b automatically call this one when needed.
     * \param t_abstract Number or CFraction for the product.
     * \return The product.
     */
    Expr multiplication_own(const Expr& t_abstract) const override;

    /*! \brief \b Adds the CFraction with a Number or a CFraction.
     * \details This function is specialy designed for the multiplication of 
     * numbers. It shouldn't be used directly by the user in general, because
     * more general sum functions will \b automatically call this one when needed.
     * \param t_abstract Number or CFraction for the sum.
     * \return The sum.
     */
    Expr addition_own(const Expr& t_abstract) const override;

    /*! \brief Derives the CFraction wrt the argument.
     * \param t_abstract Argument of the derivation.
     * \return \b 0
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief Sets num to t_value and denom to 1.
     * \param t_value
     */
    void operator=(int t_value);

    /*! \brief Sets num to t_value and denom to 1.
     * \param t_value
     */
    void operator=(double t_value);

    bool operator==(const Expr& t_abstract) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

/////
// Inline functions
inline Integer::Integer(): AbstractNumerical(), value(0){}
inline Integer::Integer(int t_value): AbstractNumerical(), value(t_value){}

inline Double::Double(): AbstractNumerical(), value(0){}
inline Double::Double(double t_value): AbstractNumerical(), value(t_value){}

//The CFraction constructor with t_num and t_denom is in the .cpp file (more complex).
inline CFraction::CFraction(): AbstractNumerical(), num(0), denom(1){}
inline CFraction::CFraction(int t_num): AbstractNumerical(), num(t_num), denom(1){}
/////

/*! \class Constant
 * \brief Handle an object with a \b name and a \b value.
 */
class Constant: public AbstractLiteral{

    protected:

    bool valued;
    double value; /*!<  Value of the Constant. */

    public:

    /*! \brief Default constructor.
     * \details Initializes the Constant with no \b name and value=0.
     */
    Constant();

    /*! \brief Initalize the \b name to \a t_name and \b value=0.
     * \param t_name 
     */
    explicit Constant(const std::string& t_name);

    /*! \brief Initializes \a name and \a value of the Constant.
     * \param t_name string
     * \param t_value double
     */
    Constant(const std::string& t_name, double t_value);

    /*! \brief Destructor. */
    ~Constant(){};

    /*! \brief Gives the \b primary \b type of a Constant. 
     * \details The primaryType of Constant is 1, it concerns a scalar object not function
     * of others and that is real-valued.
     * \return \b 1
     */
    PrimaryType getPrimaryType() const;

    /*! \brief Gives the \b type of a Constant.
     * \return \b 1
     */
    Type getType() const;

    bool getValued() const;

    /*! \brief Sets the \b value.
     * \details Allows to associate a number to each Constant 
     * before evaluating an expression.
     * \param t_value New \b value for the Constant.
     */
    void setValue(double t_value);

    /*! \brief Displays the Constant on standard output.
     * \details If mode==0 prints the Constant alone with its \b value, else prints the Constant considering it in a larger expression.
     * \param mode Type of printing.
     */
    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    double evaluateScalar() const;

    Expr evaluate() override;

    /*! \brief Derives the Constant wrt \b t_abstract.
     * \param t_abstract Abstract
     * \return \b 1 if \b t_abstract is a Constant with the **same name**.
     * \return \b 0 else.
     */
    Expr derive(const Expr& t_abstract) const override;

    int getParity(const Expr& t_variable) const;
    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(int t_value);

    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(double t_value);

    /*! \brief Compares \b value with another Abstract.
     * \param t_abstract Abstract to compare.
     * \return \b 1 if t_abstract is a Constant with the **same name**.
     * \return \b 0 else.
     */
    bool operator==(const Expr& t_abstract) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

/*! \class Variable
 * \brief Handle an object with a \b name and a \b value.
 */
class Variable: public AbstractLiteral{

    protected:

    bool valued;
    double value; /*!<  Value of the Variable. */

    public:

    //std::shared_ptr<const Abstract> develop() const { return std::make_shared<Integer>(3);}

    /*! \brief Default constructor.
     * \details Initializes the Variable with no \b name and value=0.
     */
    Variable();

    /*! \brief Initalize the \b name to \a t_name and \b value=0.
     * \param t_name 
     */
    explicit Variable(const std::string& t_name);

    /*! \brief Initializes \a name and \a value of the Variable.
     * \param t_name string
     * \param t_value double
     */
    Variable(const std::string& t_name, double t_value);

    /*! \brief Destructor. */
    ~Variable(){};

    /*! \brief Gives the \b primary \b type of a Variable. 
     * \details The primaryType of Variable is 1, it concerns a scalar object not function
     * of others and that is real-valued.
     * \return \b 1
     */
    PrimaryType getPrimaryType() const;

    /*! \brief Gives the \b type of a Variable.
     * \return \b 1
     */
    Type getType() const;

    bool getValued() const;

    /*! \brief Sets the \b value.
     * \details Allows to associate a number to each Variable 
     * before evaluating an expression.
     * \param t_value New \b value for the Variable.
     */
    void setValue(double t_value);

    /*! \brief Displays the Variable on standard output.
     * \details If mode==0 prints the Variable alone with its \b value, else prints the Variable considering it in a larger expression.
     * \param mode Type of printing.
     */
    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    double evaluateScalar() const;

    Expr evaluate() override;

    /*! \brief Derives the Variable wrt \b t_abstract.
     * \param t_abstract Abstract
     * \return \b 1 if \b t_abstract is a Variable with the **same name**.
     * \return \b 0 else.
     */
    Expr derive(const Expr& t_abstract) const override;

    int getParity(const Expr& t_variable) const;
    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(int t_value);

    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(double t_value);

    /*! \brief Compares \b value with another Abstract.
     * \param t_abstract Abstract to compare.
     * \return \b 1 if t_abstract is a Variable with the **same name**.
     * \return \b 0 else.
     */
    bool operator==(const Expr& t_abstract) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

/*! \class CFactorial
 * \brief Handles factorial of a Number.
 * \details This class allows to manipulate very big numbers without
 * evaluating them first, for example in **Taylor expansions**.
 */
class CFactorial: public AbstractLiteral{

    protected:

    int value; /*!< Integer value from which we take the factorial. */

    public:

    /*! \brief Default Constructor.
     * \details Initializes \b value to 0, then the expression evaluates to 0!=1.
     */
    CFactorial();

    /*!
     * \brief Initializes \b value to \a t_value.
     * \param t_value integer.
     */
    explicit CFactorial(int t_value);

    /*! \brief Destructor.
     */
    ~CFactorial(){};

    /*! \brief Returns the \b value in the factorial.
     * \details Caution with this function: it returns \b value and (except for the special value 1) 
     * it is **different from the return \b value of evaluateScalar()**.
     * \return \b value
     */
    int getValue() const { return value;}

    /*! \brief Gives the **primary type** of a CFraction.
     * \details The **primary type** is the same as the one of Variable.
     * \return \b 1
     */
    PrimaryType getPrimaryType() const { return LITERAL;};

    /*! \brief Gives the \b type of a CFraction.
     * \return \b 3
     */
    Type getType() const { return CFACTORIAL;};

    /*! \brief Sets the \b value from which we want the \b factorial.
     * \param t_value
     */
    void setValue(int t_value);

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief Returns the **evaluation of the factorial**.
     * \return **value!**
     */
    double evaluateScalar() const override;

    Expr evaluate() override;

    /*! \brief Derives the CFactorial wrt t_abstract.
     * \param t_abstract Argument of the derivative.
     * \return \b 0
     */
    Expr derive(const Expr& t_abstract) const override;

    /*! \brief Sets value to t_value
     * \param t_value
     */
    void operator=(int t_value);
    /*! Compares value with another Abstract
     * \param t_abstract Abstract
     * \return 1 if t_abstract is a CFactorial with the same value
     * \return 0 else
     */
    bool operator==(const Expr& t_abstract) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

/*! \class Imaginary
 * \brief Numerical representation of \b i.
 * \details This class should not be used by the user. An instance **i_** is statically
 * defined below and is used in all the program.
 */
class Imaginary: public AbstractLiteral{

    public: 

    /*! \brief Default constructor.
     * \details Initializes the \b name to "Imaginary" and \b value
     * to 0, even if it should not be used: a warning message is printed if so.
     */
    Imaginary();

    /*! \brief Destructor.
     */
    ~Imaginary(){};

    /*! Gives the **primary type** of the Imaginary.
     * \return \b 1
     */
    PrimaryType getPrimaryType() const { return LITERAL;}

    /*! \brief Gives the \b type of the Imaginary.
     * \return \b 4
     */
    Type getType() const { return IMAGINARY;}

    Expr getRealPart();

    Expr getImaginaryPart() const;

    Expr getComplexModulus();
    
    Expr getComplexArgument();
    
    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    /*! \brief \b Tries to evaluate the Imaginary **as a real**.
     * \details This function returns \b 0 and prints a \b warning message
     * because \b i should not be interpreted as a real in a calculation.
     * \return \b 0
     */
    double evaluateScalar() const;

    /*! \brief \b Tries to evaluate the Imaginary.
     * \details This function should return the object itself since we cannot
     * further evaluate \b i. Because of the shared_ptr machinery this object 
     * cannot do that and the functions returns \b nullptr. We then need the use 
     * of the Recover() function to keep a valid expression.
     * \return \b nullptr
     */
    Expr evaluate() override;

    /*! \brief Derives the Imaginary wrt \b t_abstract.
     * \return \b 0
     */
    Expr derive(const Expr& t_abstract) const override;

    bool operator==(const Expr& t_abstract) const; 

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

/////
// Inline functions
inline Variable::Variable(): AbstractLiteral(), valued(false), value(0){}
inline Variable::Variable(const std::string& t_name): AbstractLiteral(t_name), valued(false), value(0){}
inline Variable::Variable(const std::string& t_name, double t_value): AbstractLiteral(t_name), valued(true), value(t_value){}

inline Constant::Constant(): AbstractLiteral(), valued(false), value(0){}
inline Constant::Constant(const std::string& t_name): AbstractLiteral(t_name), valued(false), value(0){}
inline Constant::Constant(const std::string& t_name, double t_value): AbstractLiteral(t_name), valued(true), value(t_value){}

inline CFactorial::CFactorial(): AbstractLiteral(), value(0){}
inline CFactorial::CFactorial(int t_value): AbstractLiteral(), value(t_value){}

inline Imaginary::Imaginary(): AbstractLiteral(){}
/////


/*! 
 * \var i_
 * \brief Represents the imaginary unit \b i in the program.
 */
static const Expr i_ = std::make_shared<Imaginary>();

/*!
 * \var pi_
 * \brief Represents the number \b pi to include in expressions
 */
static const Expr ZERO = std::make_shared<Integer>(0);

static const Expr ONE = std::make_shared<Integer>(1);

static const Expr pi_ = std::make_shared<Variable>("\\pi ",M_PI);

static const Expr e_ = std::make_shared<Variable>("e",M_E);

/*!
 * \var INF
 * \brief Represents \b infinity in the program.
 * \details When an infinity appears in the abstract evaluation the program should return \b INF. 
 * \b INF is treated like a Variable. It is simply here to inform the user that 
 * **something bad happened** in the expression.
 * \bug Will not work for many cases, in particular log(0)!=\b INF. Not yet implemented.
 */
static Expr INF = std::make_shared<Variable>("inf");

static Expr WHATEVER = std::make_shared<Variable>("###");

/*! \fn Expr cfactorial_(int value)
 * \param value \b Initializer of the CFactorial.
 * \return CFactorial(value) if value > 2
 * \return Number(value) else
 * \note This function can be used to return a Symbol. The Symbol constructor 
 * Symbol::Symbol(const Expr&) is implemented and allows to 
 * put the return value of this function in a Symbol.
 */
Expr cfactorial_(int value);

Expr double_(double value);

Expr int_(int value);

Expr auto_number_(double value);

Expr _cfraction_(int num, int denom);

Expr var_(std::string name);

Expr var_(std::string name, double value);

#endif
