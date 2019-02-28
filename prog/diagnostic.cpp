#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "symbol.h"
#include "simplification.h"
#include "support.h"
#include <chrono>
#include <cmath>
#pragma GCC diagnostic ignored "-Wunused-result"
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

    Symbol WEVER("#");
    WEVER = WHATEVER;

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
    Simplify(Symbol(1)/4*(2*(sin_(x)^2) + 2*((1+sin_(pi_/2-2*x))/2+1))).print();
    cout<<endl;

    cout<<"                                      sin(pi/2 - x) = ";
    Simplify(sin_(pi_/2-x)).print();
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

    Index i("i"), j("j"), k("k");
    Symbol eps_ijk = itensor_("eps", {i,j,k});
    Expr foo = eps_ijk.getAbstract();
    foo->addSymmetry(0,1);
    foo->addAntiSymmetry(1,2);
    vector<Expr> vecExpr = foo->getPermutations();
    for (size_t i=0; i<vecExpr.size(); i++)
    {
        cout<<"Permutation "<<i+1<<": ";
        vecExpr[i]->print();
    }
    foo->setFullySymmetric();
    vecExpr = foo->getPermutations();
    for (size_t i=0; i<vecExpr.size(); i++)
    {
        cout<<"Permutation "<<i+1<<": ";
        vecExpr[i]->print();
    }

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
