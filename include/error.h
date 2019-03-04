#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <iostream>
#include <string>
#include <memory>

static const bool STOP_ERROR_DEBUG_MODE = true;

namespace smError{

    enum Error{
        AbstractFuncCalled=1,
        ElementSequence,
        OutOfBounds,
        EvalNotValued,
        UndefiniedBehaviour,
        ContractDummy,
        ContractionMismatch,
        SymmetryMismatch,
        UnknownProperty,

    };

    enum Warning{
        UnknownType=0,
        InvalidDimension,
        FactorialFloat,
        NotValued,
        Infinity,

    };

};

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
void callError(smError::Error error, const std::string& caller);

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

        default:
               std::cout<<"ScmType "<<(int)warning<<" not recognized.\n";
    }
}
void callWarning(smError::Warning warning, const std::string& caller);

#endif
