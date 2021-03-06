#include "mathFunctions.h"
#include "operations.h"
#include "comparison.h"

using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class Abs                                     //
/*************************************************/
///////////////////////////////////////////////////

void Abs::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";
    cout<<"abs(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Abs::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\text{bas}\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

Expr Abs::evaluate()
{
    double value;
    if (argument->getPrimaryType() == smType::Numerical) 
        value = argument->evaluateScalar();
    else 
        return make_shared<Abs>(argument);
    if (value > 0) 
        return argument->evaluate();
    return times_(int_(-1), argument->evaluate());
}

double Abs::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return abs(argument->evaluateScalar());
}

Expr Abs::derive(const Expr& expr)
{
    double value = argument->evaluateScalar();
    if (value > 0) 
        return int_(1);
    if (value < 0) 
        return int_(-1);

    return ZERO;
}

Expr abs_(const Expr& expr)
{
    int type = expr->getType();
    if (type == smType::Integer or type == smType::Double)
        return auto_number_(abs(expr->evaluateScalar()));
    else if (type == smType::CFraction)
        return _cfraction_(abs(expr->getNum()),
                           abs(expr->getDenom()));

    Expr res = make_shared<Abs>(expr);

    return res;
}

int Abs::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return 1;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Exp                                     //
/*************************************************/
///////////////////////////////////////////////////

Expr Exp::getRealPart()
{
    return times_(exp_(argument->getRealPart()), 
                  cos_(argument->getImaginaryPart()));
}

Expr Exp::getImaginaryPart() const
{
    return times_(exp_(argument->getRealPart()), 
                  sin_(argument->getImaginaryPart()));
}

Expr Exp::getComplexModulus()
{
    return exp_(argument->getRealPart());
}

Expr Exp::getComplexArgument()
{
    return argument->getImaginaryPart();
}

void Exp::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";
    cout<<"exp(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Exp::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"e^{";
    sout<<argument->printLaTeX(1);
    sout<<"}";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Exp::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return exp(argument->evaluateScalar());
}

Expr Exp::derive(const Expr& expr)
{
    return times_(argument->derive(expr), exp_(argument));
}

int Exp::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return 0;
}

Expr exp_(const Expr& expr)
{
    int type = expr->getPrimaryType();
    if (type == smType::Numerical) {
        double value = expr->evaluateScalar();
        int value_int = round(value);
        if (value == value_int) {
            if (value_int == 0)
                return int_(1);
            if (value_int == 1)
                return e_;
        }
    }
    type = expr->getType();
    if (type == smType::Log)
        return expr->getArgument();

    Expr res = make_shared<Exp>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Log                                     //
/*************************************************/
///////////////////////////////////////////////////

Expr Log::getRealPart() {
    return log_(argument->getComplexModulus());
}

Expr Log::getImaginaryPart() const
{
    Expr foo = argument->getComplexArgument();
    double value = foo->evaluateScalar();
    if (abs (value) > M_PI) // Taking the argument mod 2 pi
        foo = plus_(foo, double_(-M_PI*floor(abs(value)/M_PI)));

    return foo;
}

Expr Log::getComplexModulus()
{
    return plus_(pow_(getRealPart(),int_(2)),
                 pow_(getImaginaryPart(), int_(2)));
}

Expr Log::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void Log::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"log(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Log::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\log\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Log::evaluateScalar() const
{
    if (argument->getDim() > 0) return 0;
    return log(argument->evaluateScalar());
}

Expr Log::derive(const Expr& expr)
{
    return times_(argument->derive(expr), pow_(argument,int_(-1)));
}

int Log::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return 0;
}

Expr log_(const Expr& expr)
{
    if (expr == ONE)
        return ZERO;
    if (expr->getType() == smType::Exp)
        return expr->getArgument();

    Expr res = make_shared<Log>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Cos                                     //
/*************************************************/
///////////////////////////////////////////////////

Expr Cos::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(cosh_(im),cos_(re));
}

Expr Cos::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(int_(-1),times_(sinh_(im),sin_(re)));
}

Expr Cos::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return plus_(times_(pow_(cosh_(im),int_(2)),
                        pow_(cos_(re),int_(2))),
                 times_(pow_(sinh_(im),int_(2)),
                        pow_(sin_(re),int_(2))));
}

Expr Cos::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void Cos::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"cos(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Cos::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\cos\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Cos::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return cos(argument->evaluateScalar());
}

Expr Cos::derive(const Expr& expr)
{
    return times_(argument->derive(expr),
                  times_(int_(-1),sin_(argument)));
}

int Cos::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return 1;
}

Expr cos_(const Expr& expr)
{
    if (expr->getType() == smType::Arbitrary)
        return make_shared<Cos>(expr);
    //int type = expr->getPrimaryType();
    if (*expr == ZERO)
        return int_(1);
    if (*expr == fraction_(pi_,int_(2)))
        return ZERO;
    if (*expr == fraction_(times_(int_(-3),pi_),int_(2)))
        return ZERO;
    if (*expr == pi_)
        return int_(-1);
    if (*expr == times_(int_(-1),pi_))
        return int_(-1);
    if (*expr == times_(int_(3),fraction_(pi_,int_(2))))
        return ZERO;
    if (*expr == fraction_(times_(int_(-1),pi_),int_(2)))
        return ZERO;
    if (*expr == fraction_(pi_,int_(3)))
        return _cfraction_(1,2);
    if (*expr == times_(_cfraction_(2,3),pi_))
        return _cfraction_(-1,2);
    if (*expr == fraction_(pi_,int_(6)))
        return fraction_(sqrt_(int_(3)),int_(2));
    if (*expr == times_(int_(5),fraction_(pi_,int_(6))))
        return fraction_(times_(int_(-1),sqrt_(int_(3))),int_(2));
    if (*expr == fraction_(pi_,int_(4)))
        return fraction_(sqrt_(int_(2)),int_(2));
    if (*expr == times_(int_(3),fraction_(pi_,int_(4))))
        return times_(int_(-1),fraction_(sqrt_(int_(2)),int_(2)));
    
    Expr res = make_shared<Cos>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Sin                                     //
/*************************************************/
///////////////////////////////////////////////////

Expr Sin::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(cosh_(im),sin_(re));
}

Expr Sin::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(sinh_(im),cos_(re));
}

Expr Sin::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return plus_(times_(pow_(cosh_(im),int_(2)),
                        pow_(sin_(re),int_(2))),
                 times_(pow_(sinh_(im),int_(2)),
                        pow_(cos_(re),int_(2))));
}

Expr Sin::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void Sin::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"sin(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Sin::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\sin\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Sin::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return sin(argument->evaluateScalar());
}

Expr Sin::derive(const Expr& expr)
{
    return times_(argument->derive(expr), cos_(argument));
}

int Sin::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr sin_(const Expr& expr)
{
    if (expr->getType() == smType::Arbitrary)
        return make_shared<Sin>(expr);
    if (*expr == ZERO)
        return ZERO;
    if (*expr == fraction_(pi_,int_(2)))
        return int_(1);
    if (*expr == fraction_(times_(int_(-3),pi_),int_(2)))
        return int_(1);
    if (*expr == pi_)
        return ZERO;
    if (*expr == times_(int_(-1),pi_))
        return ZERO;
    if (*expr == times_(int_(3),fraction_(pi_,int_(2))))
        return int_(-1);
    if (*expr == fraction_(times_(int_(-1),pi_),int_(2)))
        return int_(-1);
    if (*expr == fraction_(pi_,int_(3)))
        return fraction_(sqrt_(int_(3)),int_(2));
    if (*expr == times_(_cfraction_(2,3),pi_))
        return fraction_(sqrt_(int_(3)),int_(2));
    if (*expr == fraction_(pi_,int_(6)))
        return _cfraction_(1,2);
    if (*expr == times_(int_(5),fraction_(pi_,int_(6))))
        return _cfraction_(1,2);
    if (*expr == fraction_(pi_,int_(4)))
        return fraction_(sqrt_(int_(2)),int_(2));
    if (*expr == times_(int_(3),fraction_(pi_,int_(4))))
        return fraction_(sqrt_(int_(2)),int_(2));
    Expr res = make_shared<Sin>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Tan                                     //
/*************************************************/
///////////////////////////////////////////////////

Expr Tan::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    Expr modulus = plus_(times_(pow_(cosh_(im),int_(2)),
                                pow_(cos_(re),int_(2))),
                         times_(pow_(sinh_(im),int_(2)),
                                pow_(sin_(re),int_(2))));

    return fraction_(times_(cos_(re),sin_(re)),modulus);
}

Expr Tan::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    Expr modulus = plus_(times_(pow_(cosh_(im),int_(2)),
                                pow_(cos_(re),int_(2))),
                         times_(pow_(sinh_(im),int_(2)),
                                pow_(sin_(re),int_(2))));

    return fraction_(times_(cosh_(im),sinh_(im)),modulus);
}

Expr Tan::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();

    Expr modulus = plus_(times_(pow_(cosh_(im),int_(2)),
                                pow_(cos_(re),int_(2))),
                         times_(pow_(sinh_(im),int_(2)),
                                pow_(sin_(re),int_(2))));

    Expr modulus2 = plus_(times_(pow_(cosh_(im),int_(2)),
                                 pow_(sinh_(im),int_(2))),
                          times_(pow_(sin_(re),int_(2)),
                                 pow_(cos_(im),int_(2))));

    return fraction_(modulus2, modulus);
}

Expr Tan::getComplexArgument()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();

    return make_shared<Angle>(times_(cosh_(im), sinh_(im)),
                              times_(cos_(re),sin_(re)));
}

void Tan::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"tan(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Tan::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\tan\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Tan::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return tan(argument->evaluateScalar());
}

Expr Tan::derive(const Expr& expr)
{
    return times_(argument->derive(expr), 
                  plus_(int_(1),pow_(tan_(argument),int_(2))));
}

int Tan::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr tan_(const Expr& expr)
{
    if (*expr == ZERO)
        return ZERO;
    if (*expr == fraction_(pi_,int_(2)))
        return INF;
    if (*expr == fraction_(times_(int_(-3),pi_),int_(2)))
        return INF;
    if (*expr == pi_)
        return ZERO;
    if (*expr == times_(int_(-1),pi_))
        return ZERO;
    if (*expr == times_(int_(3),fraction_(pi_,int_(2))))
        return INF;
    if (*expr == fraction_(times_(int_(-1),pi_),int_(2)))
        return INF;
    if (*expr == fraction_(pi_,int_(3)))
        return sqrt_(int_(3));
    if (*expr == times_(_cfraction_(2,3),pi_))
        return times_(int_(-1),sqrt_(int_(3)));
    if (*expr == fraction_(pi_,int_(6)))
        return fraction_(int_(1),sqrt_(int_(3)));
    if (*expr == times_(int_(5),fraction_(pi_,int_(6))))
        return fraction_(int_(-1),sqrt_(int_(3)));
    if (*expr == fraction_(pi_,int_(4)))
        return int_(1);
    if (*expr == times_(int_(3),fraction_(pi_,int_(4))))
        return int_(1);
    Expr res = make_shared<Tan>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class ACos                                    //
/*************************************************/
///////////////////////////////////////////////////

Expr ACos::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(acosh_(im),acos_(re));
}

Expr ACos::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(int_(-1),times_(asinh_(im),asin_(re)));
}

Expr ACos::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();

    return plus_(times_(pow_(acosh_(im),int_(2)),
                        pow_(acos_(re),int_(2))),
                 times_(pow_(asinh_(im),int_(2)),
                        pow_(asin_(re),int_(2))));
}

Expr ACos::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void ACos::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"acos(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ACos::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\acos\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double ACos::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return acos(argument->evaluateScalar());
}

Expr ACos::derive(const Expr& expr)
{
    return times_(argument->derive(expr), 
                  fraction_(int_(-1),
                            pow_(plus_(int_(1),
                                       times_(int_(-1),
                                              pow_(argument,int_(2)))),
                                _cfraction_(1,2)))); 
}

int ACos::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;

    return 0;
}

Expr acos_(const Expr& expr)
{
    if (expr == ZERO)
        return fraction_(pi_,int_(2));
    return make_shared<ACos>(expr);
}

///////////////////////////////////////////////////
/*************************************************/
// Class ASin                                    //
/*************************************************/
///////////////////////////////////////////////////

Expr ASin::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(acosh_(im),asin_(re));
}

Expr ASin::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(asinh_(im),acos_(re));
}

Expr ASin::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return plus_(times_(pow_(acosh_(im),int_(2)),
                        pow_(asin_(re),int_(2))),
                 times_(pow_(asinh_(im),int_(2)),
                        pow_(acos_(re),int_(2))));
}

Expr ASin::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void ASin::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"asin(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ASin::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\asin\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double ASin::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return asin(argument->evaluateScalar());
}

Expr ASin::derive(const Expr& expr)
{
    return times_(argument->derive(expr), 
                  fraction_(int_(1),
                            pow_(plus_(int_(1),
                                       times_(int_(-1),
                                              pow_(argument,int_(2)))),
                                _cfraction_(1,2))));
}

int ASin::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;

    return -1;
}

Expr asin_(const Expr& expr)
{
    if (*expr == ZERO)
        return ZERO;
    return make_shared<ASin>(expr);
}

///////////////////////////////////////////////////
/*************************************************/
// Class ATan                                    //
/*************************************************/
///////////////////////////////////////////////////

void ATan::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"atan(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ATan::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\atan\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double ATan::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return atan(argument->evaluateScalar());
}

Expr ATan::derive(const Expr& expr)
{
    return fraction_(argument->derive(expr),
                     fraction_(int_(1),
                               plus_(int_(1),
                                     pow_(argument, int_(2)))));
}

int ATan::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr atan_(const Expr& expr)
{
    if (*expr == ZERO)
        return ZERO;
    Expr res = make_shared<ATan>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Cosh                                    //
/*************************************************/
///////////////////////////////////////////////////

Expr Cosh::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(cos_(im),cosh_(re));
}

Expr Cosh::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(sin_(im),sinh_(re));
}

Expr Cosh::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return plus_(times_(pow_(cos_(im),int_(2)),
                        pow_(cosh_(re),int_(2))),
                 times_(pow_(sin_(im),int_(2)),
                        pow_(sinh_(re),int_(2))));
}

Expr Cosh::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void Cosh::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"cosh(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Cosh::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\cosh\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Cosh::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return cosh(argument->evaluateScalar());
}

Expr Cosh::derive(const Expr& expr)
{
    return times_(argument->derive(expr), sinh_(argument));
}

int Cosh::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return 1;
}

Expr cosh_(const Expr& expr)
{
    if (*expr == ZERO)
        return int_(1);
    Expr res = make_shared<Cosh>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Sinh                                    //
/*************************************************/
///////////////////////////////////////////////////

Expr Sinh::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(cos_(im),sinh_(re));
}

Expr Sinh::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return times_(sin_(im),cosh_(re));
}

Expr Sinh::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    return plus_(times_(pow_(cos_(im),int_(2)),
                        pow_(sinh_(re),int_(2))),
                 times_(pow_(sin_(im),int_(2)),
                        pow_(cosh_(re),int_(2))));
}

Expr Sinh::getComplexArgument()
{
    return make_shared<Angle>(getImaginaryPart(), getRealPart());
}

void Sinh::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"sinh(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Sinh::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\sinh\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Sinh::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return sinh(argument->evaluateScalar());
}

Expr Sinh::derive(const Expr& expr)
{
    return times_(argument->derive(expr), cosh_(argument));
}

int Sinh::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr sinh_(const Expr& expr)
{
    if (expr == ZERO)
        return ZERO;
    Expr res = make_shared<Sinh>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Tanh                                    //
/*************************************************/
///////////////////////////////////////////////////

Expr Tanh::getRealPart()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    Expr modulus = plus_(times_(pow_(cos_(im),int_(2)),
                                pow_(cosh_(re),int_(2))),
                         times_(pow_(sin_(im),int_(2)),
                                pow_(sinh_(re),int_(2))));

    return fraction_(times_(sinh_(re),cosh_(re)), modulus);
}

Expr Tanh::getImaginaryPart() const
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();
    Expr modulus = plus_(times_(pow_(cos_(im),int_(2)),
                                pow_(cosh_(re),int_(2))),
                         times_(pow_(sin_(im),int_(2)),
                                pow_(sinh_(re),int_(2))));

    return fraction_(times_(sin_(im),cos_(im)), modulus);
}

Expr Tanh::getComplexModulus()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();

    Expr modulus = plus_(times_(pow_(cos_(im),int_(2)),
                                pow_(cosh_(re),int_(2))),
                         times_(pow_(sin_(im),int_(2)),
                                pow_(sinh_(re),int_(2))));

    Expr modulus2 = plus_(pow_(times_(sin_(im),cos_(im)),
                               int_(2)),
                          pow_(times_(sin_(im),cos_(im)),
                               int_(2)));

    return fraction_(modulus2, modulus);
}

Expr Tanh::getComplexArgument()
{
    Expr re = argument->getRealPart();
    Expr im = argument->getImaginaryPart();

    return make_shared<Angle>(times_(cos_(im), sin_(im)),
                              times_(cosh_(re),sinh_(re)));
}

void Tanh::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"tanh(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Tanh::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\tanh\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double Tanh::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return tanh(argument->evaluateScalar());
}

Expr Tanh::derive(const Expr& expr)
{
    return times_(argument->derive(expr), 
                  plus_(int_(1),
                        times_(int_(-1),pow_(tanh_(argument),
                                             int_(2)))));
}

int Tanh::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr tanh_(const Expr& expr)
{
    if (*expr == ZERO)
        return ZERO;
    Expr res = make_shared<Tanh>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class ACosh                                   //
/*************************************************/
///////////////////////////////////////////////////

Expr ACosh::getRealPart()
{
    cout<<"Warning: function \"ACosh::getRealPart\" not yet implemented.\n";
    return ZERO;
}

Expr ACosh::getImaginaryPart() const
{
    cout<<"Warning: function \"ACosh::getImaginaryPart\" not yet implemented.\n";
    return ZERO;
}

Expr ACosh::getComplexModulus()
{
    cout<<"Warning: function \"ACosh::getComplexModulus\" not yet implemented.\n";
    return ZERO;
}

Expr ACosh::getComplexArgument()
{
    cout<<"Warning: function \"ACosh::getComplexArgument\" not yet implemented.\n";
    return ZERO;
}

void ACosh::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"acosh(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ACosh::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\acosh\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double ACosh::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return acosh(argument->evaluateScalar());
}

Expr ACosh::derive(const Expr& expr)
{
    return times_(argument->derive(expr), 
                  fraction_(int_(1),
                            pow_(plus_(pow_(argument,int_(2)),
                                       int_(-1)),
                                _cfraction_(1,2))));
}

int ACosh::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) return 1;
    return 0;
}

Expr acosh_(const Expr& expr)
{
    if (*expr == ZERO)
        return int_(1);
    Expr res = make_shared<ACosh>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class ASinh                                   //
/*************************************************/
///////////////////////////////////////////////////

Expr ASinh::getRealPart()
{
    cout<<"Warning: function \"ASinh::getRealPart\" not yet implemented.\n";
    return ZERO;
}

Expr ASinh::getImaginaryPart() const
{
    cout<<"Warning: function \"ASinh::getImaginaryPart\" not yet implemented.\n";
    return ZERO;
}

Expr ASinh::getComplexModulus()
{
    cout<<"Warning: function \"ASinh::getComplexModulus\" not yet implemented.\n";
    return ZERO;
}

Expr ASinh::getComplexArgument()
{
    cout<<"Warning: function \"ASinh::getComplexArgument\" not yet implemented.\n";
    return ZERO;
}

void ASinh::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"asinh(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ASinh::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\asinh\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double ASinh::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;

    return asinh(argument->evaluateScalar());
}

Expr ASinh::derive(const Expr& expr)
{
    return times_(argument->derive(expr),
                  fraction_(int_(1),
                            pow_(plus_(pow_(argument,int_(2)),
                                       int_(1)),
                                _cfraction_(1,2))));
}

int ASinh::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr asinh_(const Expr& expr)
{
    if (*expr == ZERO)
        return ZERO;
    Expr res = make_shared<ASinh>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class ATanh                                   //
/*************************************************/
///////////////////////////////////////////////////

Expr ATanh::getRealPart()
{
    cout<<"Warning: function \"ATanh::getRealPart\" not yet implemented.\n";
    return ZERO;
}

Expr ATanh::getImaginaryPart() const
{
    cout<<"Warning: function \"ATanh::getImaginaryPart\" not yet implemented.\n";
    return ZERO;
}

Expr ATanh::getComplexModulus()
{
    cout<<"Warning: function \"ATanh::getComplexModulus\" not yet implemented.\n";
    return ZERO;
}

Expr ATanh::getComplexArgument()
{
    cout<<"Warning: function \"ATanh::getComplexArgument\" not yet implemented.\n";
    return ZERO;
}

void ATanh::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";

    cout<<"atanh(";
    argument->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string ATanh::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";

    sout<<"\\atanh\\left(";
    sout<<argument->printLaTeX(1);
    sout<<"\\right)";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

double ATanh::evaluateScalar() const
{
    if (argument->getDim() > 0) 
        return 0;
    return atanh(argument->evaluateScalar());
}

Expr ATanh::derive(const Expr& expr)
{
    return times_(argument->derive(expr),
                  fraction_(int_(1),
                            plus_(int_(1),
                                  times_(int_(-1),
                                         pow_(argument,int_(2)))))); 
}

int ATanh::getParity(const Expr& t_variable) const
{
    int parity = argument->getParity(t_variable);
    if (parity == 1) 
        return 1;
    if (parity == 0) 
        return 0;
    return -1;
}

Expr atanh_(const Expr& expr)
{
    if (*expr == ZERO)
        return ZERO;
    Expr res = make_shared<ATanh>(expr);

    return res;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Angle                                   //
/*************************************************/
///////////////////////////////////////////////////

void Angle::print(int mode) const
{
    cout<<"Angle(";
    argument[0]->print(1);
    cout<<", ";
    argument[1]->print(1);
    cout<<")";
    if (mode == 0) 
        cout<<endl;
}

string Angle::printLaTeX(int mode) const
{
    ostringstream sout;
    sout<<"\\text{ang}\\left("<<argument[0]->printLaTeX(1);
    sout<<", "<<argument[1]->printLaTeX(1)<<"\\right) ";

    return sout.str();
}

double Angle::evaluateScalar() const
{
    double a = argument[1]->evaluateScalar();
    double b = argument[0]->evaluateScalar();

    if (b == 0) {
        if (a >= 0) 
            return 0;
        return M_PI;
    }
    if (a > 0) 
        return atan(b/a);
    if (a < 0) 
        return M_PI - atan(b/abs(a));

    callWarning(smError::Infinity, "Angle::evaluateScalar() const");
    return 0; // Infinite result
}

Expr Angle::evaluateAngle() const
{
    double a = argument[1]->evaluateScalar();
    double b = argument[0]->evaluateScalar();

    if (b == 0) {
        if (a >= 0) return ZERO;
        return pi_;
    }
    if (a > 0) 
        return atan_(fraction_(argument[0],argument[1]));
    if (a < 0) 
        return plus_(pi_,times_(int_(-1),
                                atan_(fraction_(argument[0],
                                                abs_(argument[1])))));

    callWarning(smError::Infinity, "Angle::evaluateAngle() const");
    return INF; // Infinite result
}

Expr Angle::evaluate()
{
    double a = argument[1]->evaluateScalar();
    double b = argument[0]->evaluateScalar();

    if (b == 0) {
        if (a >= 0) return ZERO;
        return pi_;
    }
    if (a > 0) 
        return atan_(fraction_(argument[0]->evaluate(),
                               argument[1]->evaluate()))->evaluate();
    if (a < 0) 
        return plus_(pi_,
           times_(int_(-1),
                  atan_(fraction_(argument[0]->evaluate(),
                                  abs_(argument[1]->evaluate())))))->evaluate();

    callWarning(smError::Infinity, "Angle::evaluateAngle() const");
    return INF; // Infinite result
}

Expr Angle::derive(const Expr& expr) {
    return evaluateAngle()->derive(expr);
}

bool Angle::operator==(const Expr& expr) const
{
    if (expr->getName() == smComparator::dummyName) 
        return expr->operator==(DummyCopy(this));
    if (expr->getType() != smType::Angle) 
        return false;
    return (*fraction_(argument[0],
                       argument[1])==fraction_(expr->getArgument(0),
                                               expr->getArgument(1)));
}

int Angle::getParity(const Expr& t_variable) const
{
    int parity = argument[0]->getParity(t_variable);
    int parity2 = argument[1]->getParity(t_variable);
    if (parity2 == 1) 
        return parity;

    return 0;
}

///////////////////////////////////////////////////
/*************************************************/
// Class Factorial                               //
/*************************************************/
///////////////////////////////////////////////////

void Factorial::print(int mode) const
{
    if (mode == 0 and name != "") 
        cout<<name<<" = ";
    argument->print(1);
    cout<<"!";
    if (mode == 0) 
        cout<<endl;
}

string Factorial::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0 and name != "") 
        sout<<name<<" = ";
    sout<<argument->printLaTeX(1);
    sout<<"!";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

Expr Factorial::evaluate() {
    return int_(evaluateScalar());
}

double Factorial::evaluateScalar() const
{
    double value = argument->evaluateScalar();
    if (value != round(value)) {
        callWarning(smError::FactorialFloat,"");
        value = round(value);
    }
    return factorial(value);
}

Expr Factorial::derive(const Expr& expr) {
    return ZERO;
}

int Factorial::getParity(const Expr& t_variable) const {
    return 0;
}

Expr factorial_(const Expr& expr) {
    if (expr->isInteger())
        return make_shared<CFactorial>(expr->evaluateScalar());
    return make_shared<Factorial>(expr);
}

