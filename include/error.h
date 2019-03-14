/*! \file error.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief File containing functions that are called by the program
 * when something wrong happened: determines the behaviour in unexpected
 * cases.
 */
#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <iostream>
#include <string>
#include <memory>

/*! \var STOP_ERROR_DEBUG_MODE
 * \brief This variable is set to true in debug mode, in order to intentionnaly
 * crash the program and allow gdb to get the Traceback of function calls. In 
 * release mode, this variable should be set to false.
 */
static const bool STOP_ERROR_DEBUG_MODE = true;

namespace smError{

    /*! \enum Error
     * \brief List all error possible.
     */
    enum Error{
        AbstractFuncCalled=1, /*!<  A function has been called with an object 
                               for which it is not defined. */
        ElementSequence, /*!<  Setting an element of a vectorial expression  
                          with a sequence of element. */
        OutOfBounds, /*!<  Index out of bounds for Expression with mutiple
                      arguments. */
        EvalNotValued, /*!<  Evaluating an expression that cannot have a value. */
        UndefiniedBehaviour, /*!<  Apparition of a case that has not been defined.*/
        ContractDummy, /*!<  Trying to contract an index that is already contracted. */
        ContractionMismatch, /*!<  Trying to contract indices that do not match. */
        SymmetryMismatch, /*!<  Incompatibility between symmetries in the 
                           properties of an indicial expression. */
        UnknownProperty, /*!<  Trying to get a property of Abstract that is not
                          defined..*/
        InvalidITensor, /*!<  Invalid creation of ITensor: bad indices. */
        InvalidIndicialSum, /*!<  Summing to terms that have not the same index 
                             structure */
        BadDependency, /*!<  Setting a contradictory dependency for a variable. */

    };

    /*! \enum Warning
     * \brief List of all warning possible.
     */
    enum Warning{
        UnknownType=0, /*!<   The type of an expression is not handled in some
                        function.*/
        InvalidDimension, /*!<  Dimension mismatch when using Vectorial. */
        FactorialFloat, /*!<   Evaluating a factorial of non-integer value.*/
        NotValued, /*!<  Evaluating a literal that is not valued. */
        Infinity, /*!<  Apparition of infinity or undefined value in calculation. */
        CopyingBuildingBlock, /*!<  Copying building block (should not, they are 
                                and should stay shared_from_this) */

    };

};

/*! \fn callError(smError::Error error, const std::string& caller, T spec)
 * \brief Displays an error message depending on the error \b error, the name 
 * of the caller function \b caller and a possible specificity of the error \b spec.
 * For example spec is the index for OutOfBound error. This function stops 
 * the program.
 * \param error The type of error.
 * \param caller The caller function.
 * \param spec A printable specificity of the error.
 */
template<typename T>
inline void callError(smError::Error error, const std::string& caller, T spec)
{
    using namespace smError;
    std::cout<<"Error "<<(int)error<<": ";
    switch(error)
    {
        case AbstractFuncCalled:
               std::cout<<"Abstract function \""<<caller<<"\" called. Should not be, virtual function.\n"; break;
        case OutOfBounds:
               std::cout<<"Index "<<spec<<" out of bounds in "<<caller<<".\n"; break;
        case ElementSequence:
               std::cout<<"Initializing a vector element with a sequence in "<<caller<<".\n"; break;
        case EvalNotValued:
               std::cout<<"Evaluating the value of non valued Abstract in "<<caller<<".\n"; break;
        case UndefiniedBehaviour:
               std::cout<<"Undefined behaviour in "<<caller<<"\n."; break;
        case ContractDummy:
               std::cout<<"Contracting dummy index in "<<caller<<": "<<spec<<std::endl; break;
        case ContractionMismatch: 
               std::cout<<"Mismatch in contraction ("<<caller<<"): "<<spec<<std::endl; break;
        case SymmetryMismatch: 
               std::cout<<"Mismatch in symmetry in "<<caller<<".\n"; break;
        case UnknownProperty:
               std::cout<<"Unknown property in "<<caller<<": "<<spec<<std::endl; break;
        case InvalidITensor:
               std::cout<<"Bad set of indices in creation of ITensor in "<<caller<<std::endl; break;
        case InvalidIndicialSum:
               std::cout<<"Invalid sum of indicial objects in "<<caller<<std::endl; break;
        case BadDependency:
               std::cout<<"Bad dependency set for "<<spec<<" in "<<caller<<"\n"; break;

        default:
               std::cout<<"ScmType "<<(int)error<<" not recognized.\n";
    }
    if (not STOP_ERROR_DEBUG_MODE)
        exit((int)error);
    else
    {
        std::shared_ptr<int> a = nullptr;
        std::cout<<*a<<std::endl;
    }
}
/*! \fn callError(smError::Error error, const std::string& caller)
 * \brief Calls callError(smError::Error, const std::string&,T) with no spec.
 */
void callError(smError::Error error, const std::string& caller);

/*! \fn callWarning(smError::Warning warning, const std::string& caller, T spec)
 * \brief Displays a warning message depending on the warning \b warning, the name 
 * of the caller function \b caller and a possible specificity of the warning \b spec.
 * For example spec is the dimension for InvalidDimension error. This function
 * does not stop the program.
 * \param warning The type of warning.
 * \param caller The caller function.
 * \param spec A printable specificity of the warning.
 */
template<typename T>
inline void callWarning(smError::Warning warning, const std::string& caller, T spec)
{
    using namespace smError;
    std::cout<<"Warning "<<(int)warning<<": ";
    switch(warning)
    {
        case UnknownType:
               std::cout<<"ScmType "<<" unknown in function \""<<caller<<"\".\n"; break;
        case InvalidDimension:
               std::cout<<"Invalid dimension "<<spec<<" in function "<<caller<<".\n"; break;
        case FactorialFloat:
               std::cout<<"Float value encountered in Factorial. Replacing by rounded value.\n"; break;
        case NotValued:
               std::cout<<"Evaluating non valued in "<<caller<<". Replacing by 0.\n"; break;
        case Infinity:
               std::cout<<"Infinite result found in "<<caller<<".\n"; break;
        case CopyingBuildingBlock:
               std::cout<<"Copying building block in "<<caller<<": "<<spec<<"\n"; break;

        default:
               std::cout<<"ScmType "<<(int)warning<<" not recognized.\n";
    }
}
/*! \fn callWarning(smError::Warning warning, const std::string& caller)
 * \brief Calls callWarning(smError::Warning, const std::string&,T) with no spec.
 */
void callWarning(smError::Warning warning, const std::string& caller);

#endif
