#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "symbol.h"
#include "simplification.h"
#include "space.h"
#include "support.h"
#include "equation.h"
#include "property.h"
#include <chrono>
#include <cmath>
#include <fstream>
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
using namespace std;

string convertTime(chrono::duration<double> dur)
{
    double sec = dur.count();
    int hour = floor(sec/3600);
    sec -= 3600*hour;
    int min = floor(sec/60);
    sec -= 60*min;
    ostringstream sout;
    if (hour < 10) sout<<"0";
    sout<<hour<<"h";
    if (min < 10) sout<<"0";
    sout<<min<<"min";
    if (sec < 10) sout<<"0";
    sout<<floor(sec)<<"sec";
    sec = floor((sec-floor(sec))*1000);
    if (sec < 100) sout<<"0";
    if (sec < 10) sout<<"0";
    sout<<sec<<"\".";

    return sout.str();
}

int main(){

    /*Expr variable = make_shared<Variable>("v");
    variable->print();
    Expr developed = variable->develop();
    developed->print();
    *variable = 3;
    //developed = ZERO;
    cout<<variable.use_count()<<endl;
    cout<<developed.use_count()<<endl;
cout<<variable->evaluateScalar()<<" "<<developed->evaluateScalar()<<endl;
    int a;
    cin>>a;*/

    auto start = chrono::system_clock::now();
    std::chrono::duration<double> dur;

    system("bin/old.x");

    Symbol x("x"), y("y"), z("z"), t("t");

    Symbol TTT = ((cos_(x)^2)+(sin_(x)^2));
    TTT.print();
    TTT = Simplify(TTT);
    TTT.print();

    Symbol WEVER("#");
    WEVER = Symbol(WHATEVER);

    cout<<compare("a","x")<<-1<<endl;
    cout<<compare("y","x")<<1<<endl;
    cout<<compare("xi","x")<<1<<endl;
    cout<<compare("x","x")<<0<<endl;
    cout<<compare("X","x")<<1<<endl;
    cout<<compare("Whateverx","Whatever")<<1<<endl;
    cout<<compare("xx","xy")<<-1<<endl;
    cout<<compare("x","Ed")<<1<<endl;

    cout<<"Simplicity tests: \n";
    cout<<((x+1)>x)<<1<<endl;
    cout<<(((x^2)+x) < (x+1))<<0<<endl;
    cout<<(cos_(x)>x)<<1<<endl;
    cout<<((y+1)>(x+1))<<1<<endl;
    cout<<((y+1)|=(x+1))<<0<<endl;
    cout<<((y+1)&=(x+1))<<1<<endl;
    cout<<((x+1)&=(x+1))<<0<<endl;
    cout<<((x+1)|=(1+x))<<1<<endl;
    cout<<(((x^2)*2*cos_(y+1+x)) > x)<<1<<endl;
    cout<<(((x^2)*2*cos_(y+1+x)) < x)<<0<<endl;
    cout<<(x > ((x^2)*2*cos_(y+1+x)))<<0<<endl;
    cout<<(x < ((x^2)*2*cos_(y+1+x)))<<1<<endl;
    cout<<(cos_(x) < sin_(x))<<0<<endl;
    cout<<(cos_(x) <= sin_(x))<<1<<endl;
    cout<<(cos_(x) > sin_(x))<<0<<endl;
    cout<<(cos_(x) >= sin_(x))<<1<<endl;
    cout<<(cos_(x) |= sin_(x))<<1<<endl;
    cout<<(cos_(x) &= sin_(x))<<0<<endl;
    cout<<((1-sin_(x)) < cos_(x))<<0<<endl;
    cout<<((1-(sin_(x)^2)) <= (cos_(x)^2))<<0<<endl;
    cout<<((cos_(x)^(-2)) < (1+(tan_(x)^2)))<<1<<endl;
    cout<<((1+(cos_(y)^2)-(cos_(x)^2))<=((sin_(x)^2)+(cos_(y)^2)))<<0<<endl;
    cout<<(cos_(x)<cos_(-x))<<1<<endl;
    cout<<(x<-x)<<1<<endl;

    cout<<(x^2)*2*cos_(x+1+y)+x+(Symbol(1)/2)*y*y*x*t<<endl;

    cout<<"                                  cos(x)^2+sin(x)^2 = ";
    Simplify((cos_(x)^2)+(sin_(x)^2)).print(); 
    cout<<endl;

    cout<<"                                  cos(y)^2+sin(x)^2 = ";
    Simplify((cos_(y)^2)+(sin_(x)^2)).print(); 
    cout<<endl;

    cout<<"exp(y^2*log(z))*cos(x)^2 + sin(x)^2*exp(y*log(z)*y) = ";
    Simplify(exp_((y^2)*log_(z))*(cos_(x)^2)+(sin_(x)^2)*exp_(log_(z)*y*y)).print();
    cout<<endl;

    cout<<"exp(y^2*log(z))*cos(y)^2 + sin(x)^2*exp(y*log(z)*y) = ";
    Simplify(exp_((y^2)*log_(z))*(cos_(y)^2)+(sin_(x)^2)*exp_(log_(z)*y*y)).print();
    cout<<endl;

    cout<<"                                        1 - 1/(1+y) = ";
    Simplify(1-1/(1+y)).print();
    cout<<endl;

    cout<<"                                        x - 1/(1+y) = ";
    Simplify(x-1/(1+y)).print();
    cout<<endl;

    cout<<"                                       1 + tan(x)^2 = ";
    Simplify (1+(tan_(x)^2)).print();
    cout<<endl;

    cout<<"                                       2 + tan(x)^2 = ";
    Simplify (2+(tan_(x)^2)).print();
    cout<<endl;

    cout<<"                          cos(x)cos(y)-sin(x)sin(y) = ";
    Simplify(cos_(x)*cos_(y)-sin_(x)*sin_(y)).print();
    cout<<endl;

    cout<<"        (1/4)*[2*sin(x)^2 + 2*((1+cos(2*x))/2 + 1)] = ";
    Simplify(Symbol(1)/4*(2*(sin_(x)^2) + 2*((1+cos_(2*x))/2+1))).print();
    cout<<endl;

    cout<<"                      d/dx[ d/dy( sqrt(1 + y^2) ) ] = ";
    Simplify((sqrt_(1+y*y)).derive(y).derive(x)).print();
    cout<<endl;

    cout<<"  (1/4)*[2sin(x)^2 + 2*((1+sin(5*pi/2-2*x))/2 + 1)] = ";
    Simplify(Symbol(1)/4*(2*(sin_(x)^2) + 2*((1+sin_(Symbol(pi_)/2-2*x))/2+1))).print();
    cout<<endl;

    cout<<"                                      sin(pi/2 - x) = ";
    Simplify(sin_(Symbol(pi_)/2-x)).print();
    cout<<endl;

    int N = 3;
    vector<int> vec(N);
    for (int i=0; i<N; i++) vec[i] = i+1;
    vector<vector<int> > perm = permutations(vec);
    for (int i=0; i<perm.size(); i++)
    {
        cout<<"Permutation "<<i+1<<": ";
        for (int j=0; j<perm[i].size(); j++)
            cout<<perm[i][j]<<" ";
        cout<<endl;
    }
/*
    Index i("i"), j("j"), k("k");
    Symbol eps_ijk = itensor_("eps", {i,j,k});
    Expr foo = eps_ijk.getAbstract();
    foo->setFullySymmetric();
    vector<Expr> vecExpr = foo->getPermutations();
    for (size_t i=0; i<vecExpr.size(); i++)
    {
        cout<<"Permutation "<<i+1<<": ";
        vecExpr[i]->print()
ofojeogz
    }*/

    Permutation antiSym1(4,{0,1});
    Permutation antiSym2(4,{2,3});
    Permutation sym(4,{{0,2},{1,3}});

    cout<<antiSym1<<endl;
    cout<<antiSym2<<endl;
    cout<<sym<<endl;
    cout<<(antiSym1*antiSym2*sym)<<endl;
    cout<<antiSym1.getOrder()<<" "<<sym.getOrder()<<endl;
    cout<<Permutation(vector<int>{1,2,3,0}).getOrder()<<endl;
    cout<<Permutation(4,{{0,2,3},{1}})<<endl;

    vector<Permutation> init(3), span;
    init[0] = antiSym1;
    init[1] = antiSym2;
    init[2] = sym;
    span = getSpan(init);
    cout<<span.size()<<" permutations: \n";
    for (int i=0; i<span.size(); ++i)
        cout<<span[i]<<": "<<span[i].getSign()<<endl;

    Symmetry S;
    S.addSymmetry(sym,1);
    S.addSymmetry(antiSym1,-1);
    S.addSymmetry(antiSym2,-1);
    cout<<S<<endl;

    IndicialParent Riemann("R",{&Minkowski, &Minkowski, &Minkowski, &Minkowski});
    Riemann.setSymmetry(S);
    Idx mu = make_shared<Index>("\\mu",&Minkowski);
    Idx nu = make_shared<Index>("\\nu",&Minkowski);
    Idx rho = make_shared<Index>("\\rho",&Minkowski);
    Idx sigma = make_shared<Index>("\\sigma",&Minkowski);
    mu->setFree(false);
    Riemann({mu,nu,rho,sigma})->print();
    vector<Expr> riemannPermutations = Riemann({mu,nu,rho,sigma})->getPermutations();
    cout<<"Riemann Tensor: \n";
    for (size_t i=0; i!= riemannPermutations.size(); ++i) {
        cout<<"    Permutation "<<i+1<<": ";
        riemannPermutations[i]->print();
    }
    
    Symbol beta("beta"), m("m"), gamma("gamma"), E("E"), p("p");
    gamma = 1/sqrt_(1-beta*beta);
    gamma.print();
    sqrt_(1-beta*beta).print();
    (1-beta*beta).print();
    E = gamma*m;
    p = gamma*m*beta;
    E.print();
    p.print();
    m.evaluate().print();
    Taylor(E,beta,10).evaluate().print();
    Taylor(p,beta,10).evaluate().print();


    IndicialParent eps_("eps",{&Euclid_R3,&Euclid_R3,&Euclid_R3});
    S = Symmetry();
    S.addSymmetry(Permutation(3,{0,1}),-1);
    S.addSymmetry(Permutation(3,{1,2}),-1);
    S.addSymmetry(Permutation(3,{0,2}),-1);
    eps_.setSymmetry(S);
    Idx i = make_shared<Index>("i", &Euclid_R3);
    Idx j = make_shared<Index>("j",&Euclid_R3);
    Idx k = make_shared<Index>("k",&Euclid_R3);
    Idx l = make_shared<Index>("l", &Euclid_R3);
    Idx n = make_shared<Index>("n",&Euclid_R3);
    eps_({i,j,k})->print();
    eps_({i,i,j})->print();
    eps_({i,i,i})->print();

    (eps_({i,i,j})+eps_({i,i,j}))->print();
    (eps_({i,j,k})*eps_({i,l,n}))->print();
    
    IndicialParent A_("A",{&Euclid_R3});
    IndicialParent B_("B",{&Euclid_R3});
    IndicialParent C_("C",{&Euclid_R4});
    (eps_({i,j,k})*A_(j)*B_(k) + eps_({i,j,k})*B_(k)*A_(j))->print();
    A_.setCommutable(false);
    B_.setCommutable(false);
    (eps_({i,j,k})*A_(j)*B_(k) + eps_({i,j,k})*B_(k)*A_(j))->print();
    (eps_({i,j,k})*A_(j)*A_(k) + eps_({i,j,k})*B_(k)*A_(j))->print();
    (A_(i)*(eps_({i,j,k}) + B_(i)*A_(j)*A_(k)))->print();
    //(eps_({i,j,k})*C_(j)*B_(k))->print();
    //(eps_({i,j})*A_(i)*B_(j))->print();
    cout<<((x.getAbstract()*A_(i)*A_(i)) == (A_(j)*x.getAbstract()*A_(j)))<<"1"<<endl;
    cout<<((x.getAbstract()*A_(i)*A_(j)) == (A_(j)*x.getAbstract()*A_(k)))<<"0"<<endl;
    cout<<(2*x.getAbstract()*eps_({i,j,j}) == eps_({j,i,j})*x.getAbstract()*2)<<"0"<<endl;
    cout<<(2*x.getAbstract()*eps_({i,j,j}) == eps_({i,k,k})*x.getAbstract()*2)<<"1"<<endl;
    cout<<(2*x.getAbstract()*eps_({i,j,j}) == eps_({i,j,j})*x.getAbstract()*2)<<"1"<<endl;
    j->setFree(false);
    k->setFree(false);
    cout<<(eps_({i,j,k}) == eps_({i,k,j}))<<"0"<<endl;
    j->setFree(true);
    k->setFree(true);
    cout<<(eps_({i,j,k}) == eps_({i,k,j}))<<"0"<<endl;
    cout<<(eps_({i,j,k})*A_(j)*B_(k) == eps_({i,k,j})*B_(j)*A_(k))<<"0"<<endl;
    cout<<(eps_({i,j,k})*A_(j)*B_(k) == eps_({i,k,j})*A_(k)*B_(j))<<"1"<<endl;
    cout<<(eps_({i,j,k})*A_(j)*B_(k) == eps_({i,k,j})*A_(j)*B_(k))<<"0"<<endl;
    B_.setCommutable(true);
    A_.setCommutable(true);
    cout<<(eps_({i,j,k})*A_(j)*B_(k) == eps_({i,k,j})*B_(j)*A_(k))<<"1"<<endl;
    cout<<((eps_({i,j,k})*A_(j)*A_(k) + eps_({i,j,k})*A_(j)*B_(k)) == (eps_({i,j,k})*A_(j)*A_(k) + eps_({i,j,k})*A_(j)*B_(k)))<<"1"<<endl;
    cout<<(-1*eps_({i,j,k}) == -1*eps_({i,j,k}))<<"1"<<endl;
    cout<<((-1*eps_({i,j,k}))*A_(j)*B_(k) == (-1*eps_({i,j,k}))*A_(j)*B_(k))<<"1"<<endl;

    cout<<"eps_ijk + eps_jik = ";
    Simplify(eps_({i,j,k}) + eps_({j,i,k}))->print();
    cout<<"eps_ijk.Aj.Ak + eps_jik.Bk.Aj = ";
    Simplify(eps_({i,j,k})*A_(j)*A_(k) + eps_({i,j,k})*B_(k)*A_(j))->print();


    (derivative_(x,1)*y).print();
    y.getAbstract()->setElementary(false);
    (derivative_(x,1)*y).print();
    (y*derivative_(x,1)).print();
    ((y*derivative_(x,1))*z).print();
    (z.getAbstract())->setElementary(false);
    ((y*derivative_(x,1))*z).print();

    Symbol alpha("alpha",true);

    (derivative_(x,1)*(alpha*y*z+alpha*y*(z^2)*alpha + alpha)).print();
    alpha.setCommutable(false);
    (derivative_(x,1)*(alpha*y*z+alpha*y*(z^2)*alpha + alpha)).print();
    y.setCommutable(false);
    (derivative_(x,1)*(alpha*y*z+alpha*y*(z^2)*alpha + alpha)).print();
    ((derivative_(x,1)*(alpha*y*z+alpha*y*(z^2)*alpha + alpha))*z).develop().print();

    cout<<aInt(13403190123342438)<<"  "<<aInt(2095)<<endl;
    cout<<(aInt(111)+aInt(999))<<endl;
    cout<<(aInt(5392852)+352529)<<endl;
    cout<<(0+aInt(234))<<endl;
    cout<<(aInt(23452)*23059320)<<endl;
    aInt testAINT = aInt(4);
    cout<<testAINT<<endl;
    testAINT = aInt(5);
    cout<<testAINT<<endl;
    testAINT = aInt(6);
    cout<<testAINT<<endl;
    cout<<factorial(aInt(12))<<endl;
    cout<<factorial(aInt(52))<<endl;
    //cout<<factorial(aInt(10000))<<endl;
    
    Equation eq(3*x + y*x*4*cos_(t) + 5, 3*sin_(y)*x - 1);
    cout<<eq<<endl;
    eq.isolate(x);
    cout<<eq<<endl;

    Symbol a("a"), b("b"), c("c"), d("d");
    eq = Equation(exp_(x*(a+1/(1+x)))+b,c);
    cout<<eq<<endl;
    eq.isolate(x);
    eq.replace(c,d+b);
    cout<<eq<<endl;
    eq = Equation(x/(1+x), a);
    cout<<eq<<endl;
    eq.isolate(x);
    cout<<eq<<endl;
    eq = Equation(1/(x^3), a);
    cout<<eq<<endl;
    eq.isolate(x);
    cout<<eq<<endl;

    cout<<Simplify(((x^100)/(100^x)).derive(x))<<endl;
    derivative_(a*b,x,3).evaluate().print();
    derivative_(derivative_(a*b,x,2),x,3).print();
    derivative_(derivative_(a*b,x,2),x,3).evaluate().print();

    Symbol jcoupech = matrix_({{1,0,-1},
                             {2,1,3},
                             {-1,-1,-2}});

    dot(jcoupech.inverseMatrix(), vector_({-1,3,0})).print();

    IndicialParent g = Minkowski.metric;
    mu->setFree(true);
    g({mu,nu})->print();

    IndicialParent X("X",&Minkowski);
    IndicialParent Y("Y",&Minkowski);

    (g({mu,nu})*X({+rho})*Y({+sigma}))->print();
    // error: (X(mu)*g({mu,nu}))->print();
    (X(+mu)*g({mu,nu}))->print();
    (X(+mu)*g({mu,nu})*(X(+nu)+Y(+nu)))->print();
    (X(+mu)*(g({mu,nu})*(X(+nu)+Y(+nu))))->print();

    IndicialParent AS("A", {&Minkowski, &Minkowski});
    AS.setFullyAntiSymmetric();
    cout<<"A_{\\mu\\nu}*g_{\\mu\\nu} = ";
    Simplify(g({mu,nu})*AS({+mu,+nu}))->print();

    cout<<(g({mu,nu}) == g({mu,nu}))<<"1"<<endl;
    cout<<(g({mu,nu}) == g({nu,mu}))<<"0"<<endl;
    cout<<(AS({+mu,+nu})*g({mu,nu}) == AS({+mu,+nu})*g({mu,nu}))<<"1"<<endl;
    cout<<(AS({+mu,+nu})*g({mu,nu}) == AS({+nu,+mu})*g({nu,mu}))<<"1"<<endl;
    cout<<(AS({+mu,+nu})*g({mu,nu}) == AS({+nu,+mu})*g({mu,nu}))<<"0"<<endl;

    Symbol P("P");
    IndicialParent Ricci("R",{&Minkowski,&Minkowski});
    Symbol R("R");
    P = 1/(a-2)*(Symbol(Ricci({mu,nu}))-1/(2*(a-1))*R*Symbol(g({mu,nu})));

    cout<<"P_{mu,nu} = "; P({mu,nu}).print();
    cout<<"P_{rho,sigma} = ";P({rho,sigma}).print();
    cout<<"P_{rho,+sigma} = ";P({rho,+sigma}).print();
    cout<<"P_{mu,+mu} = ";P({mu,+mu}).print();
    // Error: cout<<"P_{mu,nu} = ";P({mu,mu}).print();

    PROPERTIES->addProperty(Equation(derivative_(a.getAbstract(), x.getAbstract())
                                   +derivative_(b.getAbstract(),y.getAbstract())
                                   +derivative_(c.getAbstract(),z.getAbstract()), ZERO));
    PROPERTIES->addProperty(Equation(Riemann({mu,nu,rho,sigma})+Riemann({nu,mu,rho,sigma}), ZERO));

    cout<<*PROPERTIES<<endl;

    return 0;
    /*Symbol i("i"), j("j");
    int N = 200;
    cout<<"Creating matrix\n";
    Symbol M = matrix_(N,N,(cos_(x^i)^2)+(sin_(x^j)^2),i,j);
    cout<<"Summing matrix\n";
    //M.sum().print();
    Simplify(M.sum()).print();

    dur = chrono::system_clock::now() - start;
    cout<<"Execution ti/me: "<<convertTime(dur)<<endl;

    Expr foo = M.sum().getAbstract();
    foo->print();
    cout<<foo->getNArgs()<<endl<<endl;
    int nArgs = foo->getNArgs();
    foo = Replace(foo,x.getAbstract(), ((x^2)-y+cos_(1+z)).getAbstract());
    foo = Replace(foo,z.getAbstract(), ((x^2)-y+cos_(1+z)).getAbstract());

    foo->print();
    N = 1000;

    start = chrono::system_clock::now();
    const int nThread = 5;
    int slice = N/nThread;
    thread tH[nThread];
    for (int i=0; i<nThread; i++)
        tH[i] = thread([&foo,nArgs,slice](){
                for (int j=0; j<slice; j++)
                foo = Refresh(foo);
                });
    cout<<"Waiting end of threads\n";
    for (int i=0; i<nThread; i++)
        tH[i].join();

    dur = chrono::system_clock::now() - start;
    cout<<"Execution time: "<<convertTime(dur)<<endl;


    start = chrono::system_clock::now();
    for (int i=0; i<N; i++)
        foo = Refresh(foo);
    dur = chrono::system_clock::now() - start;
    cout<<"Execution time: "<<convertTime(dur)<<endl;

*/
    
    return 0;
}
