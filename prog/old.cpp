#include <iostream>
#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "symbol.h"
#include "simplification.h"
using namespace std;

int main(){

    cout.precision(10);
    bool everythingOK = true;

    Symbol xS("x");
    Symbol yS("y");

    yS = Symbol(1)/3+xS+Symbol(5)/7 + 1+2+3+4+5+6;
    xS = 3;
    cout<<"xS = "<<xS.evaluateScalar()<<endl;
    cout<<"xS = 3\n";
    cout<<"yS = "<<yS.evaluate()<<endl;
    cout<<"yS = 526/21\n";
    yS.clear();

    shared_ptr<Abstract> copy = xS.getAbstract();
    xS = xS+1;
    xS.clear();

    Symbol derivative("d");
    Symbol zero;
    (xS*xS).print();
    cout<<"x^2\n";
    derivative = xS*xS*yS-3*xS*exp_(cos_(xS))*sin_(xS)+exp_(sin_(zero))*cos_(zero)+pow_(yS,xS)+pow_(xS,yS);
    derivative.print();
    cout<<"1 + x^y + y^x + x^2*y + (-3)*sin(x)*exp(cos(x))*x"<<endl;

    derivative = derivative.derive(xS);
    derivative.print();
    cout<<"2*y*x + y*x^((-1) + y) + log(y)*y^x + (-3)*exp(cos(x))*sin(x) + (-3)*x*exp(cos(x))*cos(x) + 3*x*sin(x)^2*exp(cos(x))\n";

    Symbol frac1 = cfraction_(15,54);
    Symbol frac2 = cfraction_(12,54);
    (frac1+frac2).print();
    cout<<"Fraction: 1/2\n";
    fraction_(xS,Symbol(1)).print();
    cout<<"x\n";
    fraction_(xS,yS).print();
    cout<<"x/y\n";
    pow_(xS,Symbol(1)).print();
    cout<<"x = 0\n";
    pow_(xS,Symbol(0)).print();
    cout<<"1\n";
    pow_(Symbol(1),xS).print();
    cout<<"1\n";
    pow_(Symbol(0),xS).print();
    cout<<"0\n";
    pow_(Symbol(0),Symbol(0)).print();
    cout<<"1\n";

    (xS*xS*xS*(6*xS*xS*log_(1+yS)+3*xS*log_(yS+1)*xS)).print();
    cout<<"9*x^5*log(1 + y)\n";
    
    

    // First test to set the structure of diagnostic.cpp
    cout<<"First basic arithmetic test...\n";

    // Basic test of scalar variables
    cout<<"Basic test of scalar variables...\n";
    shared_ptr<Abstract> testNumber = int_(3);
    if (testNumber->getName() != "" or testNumber->getType() != smType::Integer or testNumber->evaluateScalar() != 3)
    {
        cout<<"Bad initialization of number.\n";
        everythingOK = false;
    }
    testNumber = int_(0);
    if (testNumber->getName() != "" or testNumber->getType() != smType::Integer or testNumber->evaluateScalar() != 0)
    {
        cout<<"Bad initialization of number.\n";
        everythingOK = false;
    }
    testNumber = make_shared<Variable>("x",4);
    if (testNumber->getName() != "x" or testNumber->getType() != smType::Variable or testNumber->evaluateScalar() != 4)
    {
        cout<<"Bad initialization of variable.\n";
        everythingOK = false;
    }
    testNumber = make_shared<Variable>("x");
    if (testNumber->getName() != "x" or testNumber->getType() != smType::Variable or testNumber->evaluateScalar() != 0)
    {
        cout<<"Bad initialization of variable.\n";
        everythingOK = false;
    }
    testNumber = make_shared<CFraction>();
    if (testNumber->getName() != "" or testNumber->getType() != smType::CFraction or testNumber->evaluateScalar() != 0)
    {
        cout<<"Bad initialization of CFraction.\n";
        everythingOK = false;
    }
    testNumber = make_shared<CFraction>(4);
    if (testNumber->getName() != "" or testNumber->getType() != smType::CFraction or testNumber->evaluateScalar() != 4)
    {
        cout<<"Bad initialization of CFraction.\n";
        everythingOK = false;
    }
    testNumber = make_shared<CFraction>(4,3);
    if (testNumber->getName() != "" or testNumber->getType() != smType::CFraction or testNumber->evaluateScalar() != 4./3)
    {
        cout<<"Bad initialization of CFraction.\n";
        everythingOK = false;
    }
    shared_ptr<Abstract> testVariable = make_shared<Variable>("x");
    std::shared_ptr<Abstract> testVariable2 = make_shared<Variable>("y",2);
    std::shared_ptr<Abstract> testConstant = int_(3);
    std::shared_ptr<Abstract> deriveXX = testVariable->derive(testVariable);
    std::shared_ptr<Abstract> deriveXY = testVariable->derive(testVariable2);
    if (*deriveXX != 1 or *deriveXY != 0 or *testVariable == testVariable2 or *testVariable != testVariable)
    {
        cout<<"Error in basic comparison or derivative of variables.\n";
        everythingOK = false;
    }
    if (*testConstant != 3 or *testVariable2 != 2 or *testNumber != 4./3)
    {
        cout<<"Error in basic comparison of scalars.\n";
        everythingOK = false;
    }

    if (PGCD(-7,3) != 1 or PGCD(-64,8) != 8 or PGCD(1805,325) != 5 or PGCD(-2, -8) != 2)
    {
        cout<<"Error in PGCD.\n";
        everythingOK = false;
    }
    shared_ptr<Abstract> sum = plus_(plus_(plus_(plus_(testNumber,make_shared<CFraction>(-7,2)),int_(2)),int_(-3)),make_shared<CFraction>(18,37));
    if (sum->getNArgs() > 0)
    {
        cout<<"Error in merge numeric terms in plus.\n";
        everythingOK = false;
    }
    if (sum->getNum() != -595 or sum->getDenom() != 222)
    {
        cout<<"Error in fraction/number reduction: -595/222 becomes "<<sum->getNum()<<"/"<<sum->getDenom()<<endl;
        everythingOK = false;
    }
    sum = plus_(int_(2),int_(3));
    sum = plus_(sum, int_(4));
    sum = plus_(sum, int_(4));
    shared_ptr<Abstract> x = make_shared<Variable>("x");
    std::shared_ptr<Abstract> y = make_shared<Variable>("y");

    testVariable = plus_(x,times_(y,times_(int_(2),x)));
    testVariable2 = plus_(times_(times_(times_(int_(1),int_(2)),y),x),x);
    if (*x == y or *x != x or *plus_(x,y)!=plus_(y,x) or *times_(x,y)!=times_(y,x) or *testVariable!=testVariable2)
    {
        testVariable->print();
        testVariable2->print();
        cout<<"Problem with operator== for plus and times.\n";
        everythingOK = false;
    }

    testVariable = (times_(x,x))->derive(x);
    testVariable2 = (plus_(times_(x,x),times_(times_(times_(y,y),x),int_(2))))->derive(x);
    if (*x->derive(x)!=int_(1) or *x->derive(y)!=int_(0) or *testVariable!=plus_(x,x) or *testVariable2!=plus_(plus_(times_(times_(int_(2),y),y),x),x))
    {
        cout<<"Problem with basic derivations.\n";
        testVariable->print();
        testVariable2->print();
        everythingOK = false;
    }

    Symbol toFactor = xS*cos_(xS*xS+xS) + 2*xS*xS*cos_(xS*xS+xS) + 3*xS*xS*xS*cos_(xS+xS*xS);
    toFactor = toFactor.factor(xS);
    toFactor.print();
    cout<<"x*(cos(x^2 + x) + 2*cos(x^2 + x)*x + 3*cos(x + x^2)*x^2)\n";
    toFactor = toFactor.factor(cos_(xS+xS*xS));
    toFactor.print();
    cout<<"cos(x + x^2)*(x + 2*x^2 + 3*x^3)\n";
    toFactor = toFactor.full_factor();
    toFactor.print();
    cout<<"cos(x*(1 + x))*x*(1 + 2*x + 3*x^2)\n";
    Symbol developSimple = DeepCopy(toFactor);
    Symbol developFull = DeepCopy(toFactor);
    developSimple = developSimple.develop();
    developFull = developFull.full_develop();
    developSimple.print();
    cout<<"2*cos(x*(1 + x))*x^2 + x*cos(x*(1 + x)) + 3*cos(x*(1 + x))*x^3\n";
    developFull.print();
    cout<<"3*cos(x + x^2)*x^3 + x*cos(x + x^2) + 2*cos(x + x^2)*x^2\n";

    cout<<fraction_(3*(xS+pow_(xS,2)),9*xS);
    cout<<"(1/3*(x + x^2))/x\n";
    cout<<fraction_((xS+pow_(xS,2)),9*xS);
    cout<<"(1/9*(x + x^2))/x\n";
    cout<<pow_(xS/(xS+pow_(xS,2)),-3*pow_(xS,3));
    cout<<"((x + x^2)/x)^(3*x^3)\n";
    cout<<pow_(fraction_(3*(xS+pow_(xS,2)),9*xS),-2);
    cout<<"(x/(1/3*(x + x^2)))^2\n";

    toFactor = xS*cos_(xS*xS+xS) + 2*xS*xS*cos_(xS*xS+xS) + 3*xS*xS*xS*cos_(xS+xS*xS);
    toFactor = toFactor.factor();
    toFactor.print();
    cout<<"cos(x^2 + x)*(1 + 3*x^2 + 2*x)*x\n";
    toFactor = toFactor.full_factor();
    toFactor.print();
    cout<<"x*cos((1 + x)*x)*(1 + 2*x + 3*x^2)\n";

    toFactor = pow_(xS,2)+cfraction_(3,4)*pow_(xS,4);
    toFactor = toFactor.factor();
    toFactor.print();
    cout<<"(1 + 3/4*x^2)*x^2\n";
    
    toFactor = pow_(xS,fraction_(1,3))+3*pow_(xS,fraction_(4,3));
    toFactor.print();
    toFactor = toFactor.factor();
    toFactor.print();
    cout<<"(1 + 3*x)*x^(1/3)\n";

    toFactor = pow_(xS,-1)+fraction_(1,xS);
    toFactor = toFactor.factor();
    toFactor.print();
    cout<<"x^(-1) + 1/x\n";
    
    toFactor = pow_(fraction_(1,xS),-1)+xS;
    toFactor = toFactor.factor();
    toFactor.print();
    cout<<"2*x\n";
    
    toFactor = pow_(xS,2)+pow_(xS,cfraction_(1,3));
    toFactor = toFactor.factor();
    toFactor.print();
    cout<<"x^2 + x^(1/3)\n";

    toFactor = Symbol(1)/0;
    toFactor.print();
    cout<<"inf = 0\n";

    toFactor = fraction_(1,0);
    toFactor.print();
    cout<<"inf = 0\n";

    toFactor = cfraction_(3,0);
    toFactor.print();
    cout<<"inf = 0\n";

    toFactor = xS*cos_(xS*xS+xS) + 2*xS*xS*cos_(xS*xS+xS) + 3*xS*xS*xS*cos_(xS+xS*xS);
    toFactor = toFactor.replace(cos_(xS*xS+xS),sin_(xS*xS+xS));
    toFactor = toFactor.replace(xS,yS);
    toFactor.print();
    cout<<"y*sin(y^2 + y) + 2*sin(y^2 + y)*y^2 + 3*sin(y^2 + y)*y^3\n";

    xS.clear();
    yS.clear();
    Symbol z = (xS+Symbol(i_)*yS)*(xS+Symbol(i_)*yS);
    xS = 1;
    yS = 2;
    //cout<<z.evaluateScalar()<<endl;
    z = z.develop();
    cout<<"(-3) + 4*i\n";
    z = z.evaluate();
    cout<<"Real part of z = "<<z.getRealPart();
    cout<<"Real part of z = -3\n";
    cout<<"Imaginary part = "<<z.getImaginaryPart();
    cout<<"Imaginary part = 4\n";
    cout<<"Modulus of z   = "<<z.getComplexModulus();
    cout<<"Modulus of z   = 5\n";
    cout<<"Argument of z  = "<<z.getComplexArgument().evaluate();
    cout<<"Argument of z  = 2.214297436\n";
    z = xS+yS*2*Symbol(i_);
    z.print();
    cout<<"x + 2*i*y\n";
    cout<<"Real part of z = "<<z.getRealPart();
    cout<<"Real part of z = x\n";
    cout<<"Imaginary part = "<<z.getImaginaryPart();
    cout<<"Imaginary part = 2*y\n";
    cout<<"Modulus of z   = "<<z.getComplexModulus();
    cout<<"Modulus of z   = (x^2 + (2*y)^2)^0.5\n";
    cout<<"Argument of z  = "<<z.getComplexArgument();
    cout<<"Argument of z  = Angle(2*y, x)\n";
    (Symbol(i_)*Symbol(i_)).print();
    cout<<"-1\n";
    pow_(Symbol(i_),3).print();
    cout<<"(-1)*i\n";
    pow_(Symbol(i_),4).print();
    cout<<"1\n";
    pow_(Symbol(i_),5).print();
    cout<<"i\n";
    pow_(Symbol(i_),6).print();
    cout<<"-1\n";

    cout<<"cos(0) = "; cos_(Symbol(0)).print();
    cout<<"cos(Symbol(pi_)/6) = "; cos_(Symbol(pi_)/6).print();
    cout<<"cos(Symbol(pi_)/4) = "; cos_(Symbol(pi_)/4).print();
    cout<<"cos(Symbol(pi_)/3) = "; cos_(Symbol(pi_)/3).print();
    cout<<"cos(Symbol(pi_)/2) = "; cos_(Symbol(pi_)/2).print();
    cout<<"cos(2*Symbol(pi_)/3) = "; cos_(2*Symbol(pi_)/3).print();
    cout<<"cos(3*Symbol(pi_)/4) = "; cos_(3*Symbol(pi_)/4).print();
    cout<<"cos(5*Symbol(pi_)/6) = "; cos_(5*Symbol(pi_)/6).print();
    cout<<"cos(Symbol(pi_)) = "; cos_(Symbol(Symbol(pi_))).print();
    cout<<endl;

    cout<<"sin(0) = "; sin_(Symbol(0)).print();
    cout<<"sin(Symbol(pi_)/6) = "; sin_(Symbol(pi_)/6).print();
    cout<<"sin(Symbol(pi_)/4) = "; sin_(Symbol(pi_)/4).print();
    cout<<"sin(Symbol(pi_)/3) = "; sin_(Symbol(pi_)/3).print();
    cout<<"sin(Symbol(pi_)/2) = "; sin_(Symbol(pi_)/2).print();
    cout<<"sin(2*Symbol(pi_)/3) = "; sin_(2*Symbol(pi_)/3).print();
    cout<<"sin(3*Symbol(pi_)/4) = "; sin_(3*Symbol(pi_)/4).print();
    cout<<"sin(5*Symbol(pi_)/6) = "; sin_(5*Symbol(pi_)/6).print();
    cout<<"sin(Symbol(pi_)) = "; sin_(Symbol(Symbol(pi_))).print();
    cout<<endl;

    cout<<"tan(0) = "; tan_(Symbol(0)).print();
    cout<<"tan(Symbol(pi_)/6) = "; tan_(Symbol(pi_)/6).print();
    cout<<"tan(Symbol(pi_)/4) = "; tan_(Symbol(pi_)/4).print();
    cout<<"tan(Symbol(pi_)/3) = "; tan_(Symbol(pi_)/3).print();
    cout<<"tan(Symbol(pi_)/2) = "; tan_(Symbol(pi_)/2).print();
    cout<<"tan(2*Symbol(pi_)/3) = "; tan_(2*Symbol(pi_)/3).print();
    cout<<"tan(3*Symbol(pi_)/4) = "; tan_(3*Symbol(pi_)/4).print();
    cout<<"tan(5*Symbol(pi_)/6) = "; tan_(5*Symbol(pi_)/6).print();
    cout<<"tan(Symbol(pi_)) = "; tan_(Symbol(Symbol(pi_))).print();
    cout<<endl;

    (xS^4).print();

    Symbol F("F"), G("G"), H("H");

    ((F+cos_(G))*H+H*(F+cos_(G))).print();
    cout<<"2*(F + cos(G))*H\n";
    G.setCommutable(false);
    ((F+cos_(G))*H+H*(F+cos_(G))).print();
    cout<<"2*(F + cos(G))*H\n";
    H.setCommutable(false);
    ((F+cos_(G))*H+H*(F+cos_(G))).print();
    cout<<"(F + cos(G))*H + H*(F + cos(G))\n";
    yS = ((F+cos_(G))*H+H*(F+cos_(G)));
    yS = yS.full_develop();
    yS.print();
    cout<<"H*cos(G) + 2*H*F + cos(G)*H\n";
    
    Symbol taylor;
    taylor = Taylor(cos_(xS), xS, 8);
    taylor.print();
    cout<<"1 + ((-1)*x^2)/2 + x^4/4! + ((-1)*x^6)/6! + x^8/8!\n";

    taylor = Taylor(pow_(4*xS,yS),yS,2);
    taylor = taylor - 1;
    taylor = taylor.full_factor();
    //full_develop(taylor);
    taylor.print();
    cout<<"y*log(4*x) + (y^2*log(4*x)^2)/2\n";

    yS.clear();
    xS = factorial_(yS);
    xS.print();
    cout<<"y!\n";
    xS.derive(yS).print();
    cout<<"0\n";
    (1/xS).print();
    cout<<"1/y!\n";
    yS = 5;
    yS = yS + 2;
    xS = factorial_(yS);
    xS.evaluate().print();
    cout<<"5040\n";
    yS.clear();
    yS = 5.2;
    xS = factorial_(yS);
    xS.evaluate().print();
    cout<<"Warning: argument of Factorial function not integer! Replacing by the rounded value.\n";
    cout<<"120\n";
    cout.precision(15);

    Symbol pi_sum("my_pi");
    pi_sum = 0;
    int N = 10;
    for (Symbol i=0; i.evaluateScalar()<N; i=i+1)
    {
        pi_sum = pi_sum + (pow_(factorial_(i),2)*pow_(2,i+1)/factorial_(2*i+1));
    }
    cout<<"Calculated pi to the order "<<N<<". pi = "<<pi_sum.evaluateScalar()<<endl;
    cout<<"Calculated pi to the order 10. pi = 3.14057816968034\n";

    xS.setName("x");
    yS.setName("y");
    xS.clear();
    yS.clear();
    Refresh((3*xS*pow_(yS,2)/(xS*yS*2.4))).print();

    xS = derivative_(cos_(xS)*sin_(xS), xS, 4);
    xS.print();
    xS.evaluate().print();

    xS.clear();
    yS = xS + 4*xS*xS + 3 + pow_(xS,3)*cos_(xS)+H*sin_(G)*pow_(xS,5);
    yS = polynomial_(yS, xS);
    yS.print();
    yS.derive(xS).print();
    yS.derive(yS).print();
    
    yS.print();
    cout<<"yS+yS = ";
    (yS+yS).print();
    cout<<"yS*yS = ";
    (yS*yS).print();
    /*shared_ptr<Abstract> foo = (yS*yS).getAbstract();
    foo->print();
    for (int i=0; i<foo->getNArgs(); i++)
    {
        foo->getArgument(i)->print();
        cout<<"TYPE = "<<foo->getArgument(i)->getType()<<endl;
    }

    string gg;
    cin>>gg;*/

    polynomial_(2,xS).print();
    cout<<"3+4x^4+2yS = ";
    (2*yS).print();
    (polynomial_(xS+xS*xS,xS)*2).print();
    yS = xS + 4*xS*xS + 3 + pow_(xS,3)*cos_(xS)+H*sin_(G)*pow_(xS,5);
    yS = polynomial_(yS, H);
    yS.print();
    yS.derive(xS).print();
    yS.derive(yS).print();

    yS = Symbol(pi_)/2 +Symbol(i_)*log_(pow_(1-pow_(xS,2), Symbol(1)/2)+Symbol(i_)*xS);
    yS.print();
    yS = Taylor(yS,xS,4);
    yS.print();

    xS.clear();
    Symbol pol1("P1"), pol2("P2");
    pol2 = polynomial_(xS+pow_(F,Symbol(1)/2),xS);
    pol2.print();
    sqrt_(F).print();
    pow_(F,Symbol(1)/2).print();
    pol1 = polynomial_(xS*xS-1,xS);
    pol2 = polynomial_(xS+1,xS);
    cout<<"(x^2 - 1)/(x + 1) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(xS*xS-1,xS);
    pol2 = polynomial_(xS-1,xS);
    cout<<"(x^2 - 1)/(x - 1) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(xS*xS-F,xS);
    pol2 = polynomial_(xS+F,xS);
    cout<<"(x^2 - F)/(x + F) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(xS*xS-pow_(F,2),xS);
    pol2 = polynomial_(xS+F,xS);
    cout<<"(x^2 - F^2)/(x + F) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(xS*xS-F,xS);
    pol2 = polynomial_(xS+pow_(F,Symbol(1)/2),xS);
    cout<<"(x^2 - F)/(x + sqrt(F)) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(12*pow_(xS,5)+8*pow_(xS,4)+56*pow_(xS,3)+24*xS*xS+60*xS,xS);
    pol2 = polynomial_(3*xS*xS+2*xS+5,xS);
    cout<<"(12x^5 - 8x^4 + 56x^3 + 24x^2 + 60x)/(3x^2 + 2x + 5) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(xS*xS+2*F*xS+F*F+F*G+xS*G,xS);
    pol2 = polynomial_(xS+F,xS);
    cout<<"(x^2 + 2F*x + F^2 + FG + G*x)/(x+F) = ";pol1.polynomialDivision(pol2).print();
    pol1 = polynomial_(xS*xS+2*xS+1,xS);
    cout<<"x^2 + 2x + 1 = ";pol1.polynomialFactorization().print();
    pol1 = polynomial_(6*xS*xS-13*xS-5,xS);
    cout<<"6x^2 - 13x - 5 = ";pol1.polynomialFactorization().print();
    //pol1.polynomialFactorization().printExplicit();
    Refresh(pol1.polynomialFactorization()).print();
    pol1 = polynomial_(xS*xS-xS-1,xS);
    cout<<"x^2 - x - 1 = ";pol1.polynomialFactorization().print();

    yS.clear();
    cout<<cos_(xS).getParity(xS)<<endl;
    cout<<sin_(xS).getParity(xS)<<endl;
    cout<<exp_(xS).getParity(xS)<<endl;
    cout<<log_(xS).getParity(xS)<<endl;
    cout<<tan_(xS).getParity(xS)<<endl;
    cout<<cosh_(xS).getParity(xS)<<endl;
    cout<<sinh_(xS).getParity(xS)<<endl;
    cout<<polynomial_(8*yS*xS+15*pow_(yS,2)*pow_(xS,3),xS).getParity(xS)<<endl;
    cout<<(8*yS*xS+15*pow_(yS,2)*pow_(xS,3)).getParity(xS)<<endl;
    cout<<fraction_(3+xS*xS,pow_(xS,4)+5).getParity(xS)<<endl;



    Symbol eps("eps");
    Symbol d("d");
    Symbol I13("I(1,3)");
    Symbol Delta("Delta");
    Symbol pi("pi");
    Symbol gammaE("gammaE");

    I13 = d/4*1/pow_(4*pi,d/2)*pow_(Delta,-2+d/2);
    I13.print();
    I13 = I13.replace(d,4-2*eps);
    I13.print();
    I13 = Taylor(I13,eps,1)*(1/eps-gammaE);
    I13 = I13.develop();
    Refresh(I13);
    I13.print();
    I13 = I13.factor(1/eps);
    I13 = I13.factor(eps);
    Refresh(I13);
    I13.print();

    I13 = (xS+3*yS)*(3*yS*pow_(xS,2)+xS)*(F+G*xS+H*xS);
    I13 = (xS+2*yS*xS*xS)*(1+xS+xS*xS);
    I13 = I13.develop();
    I13 = I13.factor(pow_(xS,5));
    I13 = I13.factor(pow_(xS,4));
    I13 = I13.factor(pow_(xS,3));
    I13 = I13.factor(pow_(xS,2));
    I13 = I13.factor(pow_(xS,1));
    Refresh(I13);
    I13.print();

    Symbol index("i");
    Symbol jndex("j");
    Symbol vectorialExpression_i = index;
    Symbol vec1 = vector_(10, vectorialExpression_i, index);
    Symbol vec2 = vector_(10, xS^vectorialExpression_i, index);
    vec1.print();
    vec2.print();
    (vec1+vec2).print();
    (vec1*vec2).print();
    (vec1-vec2).print();
    polynomial_(dot(vec1, vec2), xS).print();

    Symbol mat1 = matrix_(3,3,3*index+jndex,index,jndex);
    Symbol mat2 = matrix_(3,3,index+xS*jndex,index,jndex);
    mat1.print();
    mat2.print();
    (mat1+mat2).print();
    (mat1*mat2).print();
    dot(mat1,mat2).print();
    dot(mat1,vec2).print();

    N = 5;
    vec1 = vector_(N, xS^(1-index),index);
    mat1 = matrix_(N,N,index+jndex*(xS^jndex),index,jndex);
    vec2 = (xS^N)*dot(mat1,vec1);
    shared_ptr<Abstract> fooAbstract = vec2.getAbstract();
    vec2 = polynomial_(vec2.full_develop(), xS);
    vec2.print();
    cout<<vec2.getType()<<endl;

    vector<int> shape(3,3);
    Symbol tensor = Symbol(tensor_(shape));
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            for (int k=0; k<3; k++)
            {
                tensor.setArgument((int)(i!=j and i!=k and j!=k)*((int)((i+1)%3==j)*2-1),i,j,k);
            }
    tensor.print();
    tensor[0][0][1].print();
    tensor[0][1][2].print();
    tensor[0][2][1].print();
    tensor[1][2][0].print();
    tensor[1][0][2].print();

    Symbol zS("z");
    Symbol Ax("Ax"), Ay("Ay"), Az("Az");
    Symbol Bx("Bx"), By("By"), Bz("Bz");
    vec1 = vector_(3);
    vec1.setArgument(Ax,0);
    vec1.setArgument(Ay,1);
    vec1.setArgument(Az,2);
    vec2 = vector_(3);
    vec2.setArgument(Bx,0);
    vec2.setArgument(By,1);
    vec2.setArgument(Bz,2);
    dot(dot(tensor,vec2),vec1).print(); // Eps_ijk A_j B_k = ( Eps_ijk B_k ) A_j = dot(dot(Eps, B), A)

    tensor = matrix_(2,2);
    tensor.setArgument(xS,0,0);
    tensor.setArgument(xS,1,1);
    tensor.setArgument(yS,0,1);
    tensor.setArgument(zS,1,0);
    tensor.determinant().print();

    eps = Symbol(tensor_(vector<int>(2,2)));
    for (int i=0; i<2; i++)
    {
        for (int j=0; j<2; j++)
        {
            if (i != j) {
                if (i == 0)
                    eps.setArgument(1,i,j);
                else
                    eps.setArgument(-1,i,j);
            }
        }
    }
    yS = eps;
    eps.print();
    for (int i=0; i<2; i++)
    {
        yS = dot(tensor, yS)[1-i];
    }
    cout<<"det = ";
    (-1*yS).develop().print();

    tensor.inverseMatrix().print();

    tensor = matrix_(3,3);
    tensor.setArgument(1,1,1);
    tensor.setArgument(-1,2,2);

    mat1 = matrix_(3,3);
    mat1.setArgument(1,0,0);
    mat1.setArgument(-1,1,0);
    mat1.setArgument(1,1,1);
    mat1.setArgument(-1,2,1);
    mat1.setArgument(1,2,2);

    mat2 = mat1.inverseMatrix();

    tensor.print();
    mat1.print();
    mat2.print();

    tensor = dot(dot(mat2,tensor),mat1);
    tensor.print();

    Symbol lambda("lambda");
    eps = matrix_(3,3);
    eps.setArgument(1,0,0);
    eps.setArgument(1,1,1);
    eps.setArgument(1,2,2);
    (tensor-lambda*eps).print();
    (tensor-lambda*eps).determinant().print();

    N = 10;
    eps = matrix_(N,N);
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            eps.setArgument(i*j/(i+1+j)+i*i*j/(1+i+j)+i*j*j/(1+i+j)+i*i*j*j/(1+i+j)+pow(-1,i+j)*(i+j*1./2)+i*i-j*j+i*j*1./10 +i*i*i/(1.+j)+j*j*j/(1.+i),i,j);
    eps.setArgument(5,2,2);
    eps.print();
    eps.determinant().print();
    eps = dot(eps,eps.inverseMatrix());
    eps.print();
    cout<<"Mean squared error = ";
    for (int i=0; i<N; i++)
        eps.setArgument(1-eps[i][i],i,i);
    eps = eps*eps;
    eps.print();
    cout<<eps.getAbstract()->getSum()/(N*N)<<endl;

    eps = matrix_(3,3);
    Symbol t("t");
    xS.clear(); 
    yS.clear();
    z.clear();

    eps.setArgument(xS,{0,0});
    eps.setArgument(zS,{0,2});
    eps.setArgument(xS,{1,1});
    eps.setArgument(t,{1,2});
    eps.setArgument(zS,{2,0});
    eps.setArgument(yS,{2,2});
    Simplify(eps.determinant()).print();
    eps.inverseMatrix().print();
    dot(eps, eps.inverseMatrix()).print();
    cout<<"Simplify:  \n";
    eps = Simplify(dot(eps, eps.inverseMatrix()));
    eps.print();

    eps = matrix_(2,2);
    eps.setArgument(1,{0,0});
    eps.setArgument(-3,{0,1});
    eps.setArgument(1,{1,0});
    eps.setArgument(-2,{1,1});
    Symbol vecvec = vector_(2);
    vecvec.setArgument(-20,0);
    vecvec.setArgument(2,1);
    (dot(eps.inverseMatrix(), vecvec)).print();
    
    tensor = tensor-lambda*eps;

    eps = Symbol(tensor_(vector<int>(3,3)));
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            for (int k=0; k<3; k++)
            {
                if (i != j and j != k and i != k)
                {
                    if ((i+1)%3 == j)
                        eps.setArgument(1,i,j,k);
                    else 
                        eps.setArgument(-1,i,j,k);
                }
            }
        }
    }
    yS = eps;
    for (int i=0; i<3; i++)
    {
        yS = dot(tensor, yS)[2-i];
    }
    (pow(-1,3/2)*yS).print();


    vec1.print();
    vec2.print();
    mat1 = tensor_dot(vec1,vec2);
    mat1.print();

    shared_ptr<Abstract> foo = mat1.getAbstract();
    foo->getArgument(-1)->print();
    foo->getArgument({-1,1})->print();
    foo->getArgument({1,-1})->print();

    foo->trace()->print();
    foo->trace(0,0)->print();
    foo->trace(1,1)->print();
    foo->trace(0,1)->print();
    foo->trace(1,0)->print();
    foo->trace(0,2)->print();

    shape = vector<int>(3,3);
    eps = Symbol(tensor_(shape));
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            for (int k=0; k<3; k++)
            {
                eps.setArgument((int)(i!=j and i!=k and j!=k)*((int)((i+1)%3==j)*2-1),i,j,k);
            }

    tensor = tensor_dot(tensor_dot(eps, vec1), vec2);
    tensor = tensor.trace(1,3);
    tensor = tensor.trace(1,2);
    tensor.print();

    mat1.print();
    (mat1*mat1).print();
    mat1.transpose().print();
    mat1.symmetrise().print();
    mat1.antisymmetrise().print();
    Refresh(mat1.symmetrise() + mat1.antisymmetrise()).print();
    Refresh(mat1.antisymmetrise() + mat1.antisymmetrise().transpose()).print();

    Symbol F_munu("F_munu");
    F_munu = Symbol(tensor_(vector<int>(2,4)));
    F_munu.print();

    Symbol E("E");
    Symbol Ex("Ex"), Ey("Ey"), Ez("Ez");
    E = vector_(3);
    E.setArgument(Ex,0);
    E.setArgument(Ey,1);
    E.setArgument(Ez,2);

    Symbol B("B");
    B = vector_(3);
    B.setArgument(Bx,0);
    B.setArgument(By,1);
    B.setArgument(Bz,2);
    tensor = tensor_dot(eps,B).trace(2,3);

    for (int i=0; i<4; i++)
    {
        if (i > 0)
        {
            F_munu.setArgument(-2*E[i-1], 0, i);
            for (int j=i; j<4; j++)
                F_munu.setArgument(2*tensor[i-1][j-1],i,j);
        }
    }
    F_munu = F_munu.antisymmetrise();
    F_munu.print();

    Symbol d_mu("d_mu");
    d_mu = vector_(4);
    Symbol tS("t");
    yS.clear();
    xS.clear();
    zS.clear();
    d_mu.setArgument(derivative_(tS),0);
    d_mu.setArgument(derivative_(xS),1);
    d_mu.setArgument(derivative_(yS),2);
    d_mu.setArgument(derivative_(zS),3);
    tensor = tensor_dot(d_mu,F_munu);
    d_mu.print();
    tensor.print();
    tensor.trace(0,1).print();

    eps = Symbol(tensor_(vector<int>(4,4)));
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            for (int k=0; k<4; k++)
            {
                for (int l=0; l<4; l++)
                {
                    if (i!=j and i!=k and i!=l and j!=k and j!=l and k!=l)
                    {
                        int _i(i), _j(j), _k(k);
                        int permut = 1;
                        if (i != 0)
                        {
                            permut *= -1;
                            if (_j == 0)
                                _j = _i;
                            if (_k == 0)
                                _k = _i;
                        }
                        if (_j != 1)
                        {
                            permut *= -1;
                            if (_k == 1)
                                _k = _j;
                        }
                        if (_k != 2)
                            permut *= -1;

                        vector<int> indices(4);
                        indices[0] = i;
                        indices[1] = j;
                        indices[2] = k;
                        indices[3] = l;
                        eps.setArgument(permut, indices);
                    }
                }
            }
        }
    }
    eps.print();
    tensor = tensor_dot(tensor_dot(eps,d_mu),F_munu);
    tensor.print();
    tensor = tensor.trace(1,4);
    tensor = tensor.trace(1,3);
    tensor = tensor.trace(1,2);
    tensor.print();
    (tensor/2).develop().print();

    /*Index i("i"), j("j"), k("k");
    itensor_("A",{i,j}).print();
    itensor_("A",i).print();
    itensor_("A",{i}).print();
    itensor_("A",{}).print();

    Symbol A_ij, B_ij, A_ji;
    A_ij = itensor_("A",{i,j});
    A_ji = itensor_("A",{j,i});
    B_ij = itensor_("B",{i,j});

    (A_ij+A_ij).print();
    (A_ij-A_ji).print();
    vector<Index> indices = (A_ij-A_ji).getAbstract()->getIndexStructure();
    cout<<"    -> structure: ";
    for (size_t i=0; i<indices.size(); i++)
        indices[i].print();
    cout<<endl;
    (A_ij+B_ij).print();
    indices = (A_ij+B_ij).getAbstract()->getIndexStructure();
    cout<<"    -> structure: ";
    for (size_t i=0; i<indices.size(); i++)
        indices[i].print();
    cout<<endl;
    (A_ij-A_ij).print();
    indices = (A_ij-A_ij).getAbstract()->getIndexStructure();
    cout<<"    -> structure: ";
    for (size_t i=0; i<indices.size(); i++)
        indices[i].print();
    cout<<endl;

    cout<<"Test structures\n";
    Symbol eps_ijk = itensor_("eps", {i,j,k});
    cout<<A_ij.checkIndexStructure({i,j})<<endl;
    cout<<A_ij.checkIndexStructure({j,i})<<endl;
    cout<<A_ji.checkIndexStructure({i,j})<<endl;
    cout<<eps_ijk.checkIndexStructure({k,i,j})<<endl;
    cout<<eps_ijk.checkIndexStructure({j,i})<<endl;
    cout<<A_ij.checkIndexStructure({k,i})<<endl;

    eps_ijk = itensor_("eps", {i,j,k});
    eps_ijk.print();
    foo = eps_ijk.getAbstract();
    foo->contractIndices(0,1);
    eps_ijk.setAbstract(foo);
    eps_ijk.print();
    eps_ijk = itensor_("eps", {i,j,k});
    foo = eps_ijk.getAbstract();
    foo->contractIndices(0,2);
    eps_ijk.setAbstract(foo);
    eps_ijk.print();
    eps_ijk = itensor_("eps", {i,i,j});
    eps_ijk.print();
    set<pair<int,int> > pair_ = eps_ijk.getAbstract()->getContractedPair();
    for (auto it=pair_.begin(); it!=pair_.end(); ++it)
        cout<<"   -pair "<<(*it).first<<"<->"<<(*it).second<<endl;
    eps_ijk = itensor_("eps", {i,i,i});
    eps_ijk.print();
    pair_ = eps_ijk.getAbstract()->getContractedPair();
    for (auto it=pair_.begin(); it!=pair_.end(); ++it)
        cout<<"   -pair "<<(*it).first<<"<->"<<(*it).second<<endl;

    Symbol gamma, psi, psSymbol(i_)bar;
    Index alpha("\\alpha",4);
    Index beta("\\beta",4);
    Index delta("\\delta",4);
    Index epsilon("\\epsilon",4);
    Index mu("mu", 4);
    psi = itensor_("\\psi", {alpha});
    psSymbol(i_)bar = itensor_("\\bar{\\psi}", {beta});
    gamma = itensor_("gamma", {mu,delta,epsilon});

    (psSymbol(i_)bar*2*gamma*xS*psi).print(); */

    if (everythingOK) cout<<"Everything is ok for the diagnostic. Well done !\n";
    else cout<<"Problems occured during the run... Please work a little bit harder !\n";

    return 0;
}
