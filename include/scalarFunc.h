/*! \file scalarFunc.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Base classes for scalar functions.
 */
#ifndef SCALARFUNC_H_INCLUDED
#define SCALARFUNC_H_INCLUDED
#include "variable.h"
#include <vector>

/*! \class AbstractFunc
 * \brief Base class for **scalar functions of one argument.**
 * \details From this class will derive functions with a **unique argument**.
 * In particular all mathematical functions will be derived classes. In the case of 
 * the call of a simplification function, if recursive, the function will be first
 * applied on the \b argument, then to the function itself.
 */
class AbstractFunc: public AbstractScalar{

    protected:

    Expr argument; /*!< \brief Argument of the considered function. */

    public:

    /*! \brief Default constructor.
     * \details Initializes the argument to \b 0 (Number).
     */
    AbstractFunc();

    /*! \brief Initializes \b name and the \b argument to 0.
     */
    explicit AbstractFunc(const std::string& t_name);

    /*! \brief Destructor.
     */
    ~AbstractFunc(){}

    /*! Gives the **primary type** of an AbstractFunc.
     * \return \b 20
     */
    smType::PrimaryType getPrimaryType() const override{
        return smType::ScalarFunction;
    }

    /*! \brief Tells if the AbstractFunc is commutable.
     * \details The commutability of a function depends on the one of its \b 
     * argument.
     * \return \b True if the AbstractFunc is commutable.
     * \return \b False else.
     */
    bool getCommutable() const override;

    bool isIndexed() const override;

    IndexStructure getIndexStructure() const override;

    int getNArgs(int axis=0) const override;

    /*! \brief Returns the \b argument of the function.
     * \details The parameter \a iArg is usefull for AbstractMultiFunc. 
     * It is present ere in order to have only one access function for 
     * arguments in the Abstract class.
     * \param iArg Index of the argument, silent here.
     * \return \b argument
     */
    Expr getArgument(int iArg=0) const override;

    Expr getComplexConjugate() override;

    /*! \brief Replace the \b argument of the AbstractFunc.
     * \details The parameter \a iArg is usefull for AbstractMultiFunc. 
     * It is present ere in order to have only one access function for 
     * arguments in the Abstract class.
     * \param t_argument New \b argument.
     * \param iArg       Index of the \b argument, silent here.
     */
    void setArgument(const Expr& t_argument, int iArg=0) override;

    virtual bool contractIndex(const Index& indexToContract,
                               const Index& newIndex) override;

    virtual Expr factor(bool full=false) override;

    virtual Expr factor(const Expr& expr, bool full=false) override;

    Expr develop(bool full=false) override;

    bool dependsOn(const Expr& expr) const override;

    bool dependsExplicitelyOn(const Expr& expr) const override;

    int isPolynomial(const Expr& expr) const override;

    /*! \brief \b Evaluates the function after evaluating the \b argument.
     * \details Except particular cases (cos(0), exp(0) etc) this function returns
     * the same AbstractFunc with \b argument.evaluate() as argument.
     * \return The function of the evaluated \b argument.
     */
    Expr evaluate() override;

    bool operator==(const Expr& expr) const override;

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
};


/*! \class AbstractDuoFunc
 * \brief Handle functions of \b multiple arguments. In the case of 
 * the call of a simplification function, if recursive, the function will be first
 * applied on all the \b arguments, then to the function itself.
 */
class AbstractDuoFunc: public AbstractScalar{

    protected:

    std::array<Expr,2> argument; /*!< \brief std::array containing the arguments. */

    public:

    /*! \brief Default Constructor, initializes the std::array argument empty
     */
    AbstractDuoFunc();

    /*! \brief Initializes \b name and the std::array \b argument empty.
     * \param t_name
     */
    explicit AbstractDuoFunc(const std::string& t_name);

    /*! \brief Destructor.
     */
    ~AbstractDuoFunc(){};

    /*! \brief Gives the **primary type** of an AbstractDuoFunc.
     * \return 10
     */
    smType::PrimaryType getPrimaryType() const override{
        return smType::MultiFunction;
    }

    /*! \brief Tells if the AbstractDuoFunc is commutable.
     * \details The commutability of a multi-function depends on the one of its 
     * \b arguments and the properties of the multi-function itself.
     * \return \b True if the AbstractFunc is commutable.
     * \return \b False else.
     */
    bool getCommutable() const override;

    bool isIndexed() const override;

    IndexStructure getIndexStructure() const override;

    /*! \brief Returns the **number of arguments** of the AbstractDuoFunc.
     * \return \b nArgs
     */
    int getNArgs(int axis=0) const override{
        return 2;
    }

    /*! \brief Returns one particular \b argument.
     * \param iArg(default=0) Index of the argument to return in the std::array 
     * \b argument.
     * \return \b argument[iArg]
     */
    Expr getArgument(int iArg=0) const override;

    /*! \brief Replaces one particular \b argument.
     * \param t_argument      New argument.
     * \param iArg(default=0) Index of the argument to replace with t_argument.
     */
    void setArgument(const Expr& t_argument, int iArg=0) override;

    virtual bool contractIndex(const Index& indexToContract,
                               const Index& newIndex) override;

    virtual Expr factor(bool full=false) override;

    virtual Expr factor(const Expr& expr, bool full=false) override;

    virtual Expr develop(bool full=false) override;

    bool dependsOn(const Expr& expr) const override;

    bool dependsExplicitelyOn(const Expr& expr) const override;

    int isPolynomial(const Expr& expr) const override;

    virtual bool operator==(const Expr& t_argument) const override {
        return false;
    }
};

/*! \class AbstractMultiFunc
 * \brief Handle functions of \b multiple arguments. In the case of 
 * the call of a simplification function, if recursive, the function will be 
 * first applied on all the \b arguments, then to the function itself.
 */
class AbstractMultiFunc: public AbstractScalar{

    protected:

    int nArgs; /*!< \brief Number of arguments. */

    std::vector<Expr> argument; /*!< \brief std::vector containing the arguments. */

    public:

    /*! \brief Default Constructor, initializes the std::vector argument empty
     */
    AbstractMultiFunc();

    /*! \brief Initializes \b name and the std::vector \b argument empty.
     * \param t_name
     */
    explicit AbstractMultiFunc(const std::string& t_name);

    /*! \brief Destructor.
     */
    ~AbstractMultiFunc(){};

    /*! \brief Gives the **primary type** of an AbstractMultiFunc.
     * \return 10
     */
    virtual smType::PrimaryType getPrimaryType() const override {
        return smType::MultiFunction;
    }

    /*! \brief Tells if the AbstractMultiFunc is commutable.
     * \details The commutability of a multi-function depends on the one of 
     * its \b arguments and the properties of the multi-function itself.
     * \return \b True if the AbstractFunc is commutable.
     * \return \b False else.
     */
    bool getCommutable() const override;

    virtual bool isIndexed() const override;

    /*! \brief Returns the **number of arguments** of the AbstractMultiFunc.
     * \return \b nArgs
     */
    int getNArgs(int axis=0) const override {
        return nArgs;
    }

    /*! \brief Returns the std::vector \b argument directly.
     * \return \b argument
     */
    const std::vector<Expr >& getVectorArgument() const override;

    /*! \brief Returns one particular \b argument.
     * \param iArg(default=0) Index of the argument to return in the 
     * std::vector \b argument.
     * \return \b argument[iArg]
     */
    Expr getArgument(int iArg=0) const override;

    /*! \brief Replaces one particular \b argument.
     * \param t_argument      New argument.
     * \param iArg(default=0) Index of the argument to replace with t_argument.
     */
    void setArgument(const Expr& t_argument, int iArg=0) override;

    void setVectorArgument(const std::vector<Expr >& t_argument) override;

    virtual bool contractIndex(const Index& indexToContract,
                               const Index& newIndex) override;

    virtual Expr factor(bool full=false) override;

    virtual Expr factor(const Expr& expr, bool full=false) override;

    virtual Expr develop(bool full=false) override;

    bool dependsOn(const Expr& expr) const override;

    bool dependsExplicitelyOn(const Expr& expr) const override;

    int isPolynomial(const Expr& expr) const override;

    virtual bool operator==(const Expr& t_argument) const override {
        return false;
    }
};

/*************************************************/
// Inline functions                              //
/*************************************************/
inline AbstractFunc::AbstractFunc(): AbstractScalar(), argument(ZERO){}
inline AbstractFunc::AbstractFunc(const std::string& t_name)
    :AbstractScalar(t_name), argument(ZERO){}

inline AbstractDuoFunc::AbstractDuoFunc(): AbstractScalar(){
    argument[0] = ZERO;
    argument[1] = ZERO;
}
inline AbstractDuoFunc::AbstractDuoFunc(const std::string& t_name)
    :AbstractScalar(t_name)
{
    argument[0] = ZERO;
    argument[1] = ZERO;
}

inline AbstractMultiFunc::AbstractMultiFunc()
    :AbstractScalar(), nArgs(0), argument(std::vector<Expr>(0)){}
inline AbstractMultiFunc::AbstractMultiFunc(const std::string& t_name)
    :AbstractScalar(t_name), nArgs(0), argument(std::vector<Expr>(0)){}

#endif
