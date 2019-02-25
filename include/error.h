#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <iostream>
#include <string>
#include <memory>

static const bool STOP_ERROR_DEBUG_MODE = true;

enum Error{
    Abstract_func_called=1,
    Element_sequence,
    Out_of_bounds,
    Eval_not_valued,

};

enum Warning{
    Unknown_type=0,
    Invalid_dimension,
    Factorial_float,
    Not_valued,
    Infinity,

};


template<typename T>
inline void callError(Error error, const std::string& caller, T spec)
{
    std::cout<<"Error "<<(int)error<<": ";
    switch(error)
    {
        case Abstract_func_called:
               std::cout<<"Abstract function \""<<caller<<"\" called. Should not be, virtual function.\n"; break;
        case Out_of_bounds:
               std::cout<<"Index "<<spec<<" out of bounds in "<<caller<<".\n"; break;
        case Element_sequence:
               std::cout<<"Initializing a vector element with a sequence in "<<caller<<".\n"; break;
        case Eval_not_valued:
               std::cout<<"Evaluating the value of non valued Abstract in "<<caller<<".\n"; break;

        default:
               std::cout<<"Type "<<(int)error<<" not recognized.\n";
    }
    if (not STOP_ERROR_DEBUG_MODE)
        exit((int)error);
    else
    {
        std::shared_ptr<int> a = nullptr;
        std::cout<<*a<<std::endl;
    }
}
void callError(Error error, const std::string& caller);

template<typename T>
inline void callWarning(Warning warning, const std::string& caller, T spec)
{
    std::cout<<"Warning "<<(int)warning<<": ";
    switch(warning)
    {
        case Unknown_type:
               std::cout<<"Type "<<" unknown in function \""<<caller<<"\".\n"; break;
        case Invalid_dimension:
               std::cout<<"Invalid dimension "<<spec<<" in function "<<caller<<".\n"; break;
        case Factorial_float:
               std::cout<<"Float value encountered in Factorial. Replacing by rounded value.\n"; break;
        case Not_valued:
               std::cout<<"Evaluating non valued in "<<caller<<". Replacing by 0.\n"; break;
        case Infinity:
               std::cout<<"Infinite result found in "<<caller<<".\n"; break;

        default:
               std::cout<<"Type "<<(int)warning<<" not recognized.\n";
    }
}
void callWarning(Warning warning, const std::string& caller);

#endif
