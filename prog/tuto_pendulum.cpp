#include <iostream>
#include "symbol.h"

using namespace std;

int main() {

    cout<<"Simple pendulum: \n\n:";

    // Creating constants (the true argument says that it is not a
    // variable but a constant)
    Symbol m("m",true), l("l",true), g("g",true);
    Symbol lambda("lambda",true);

    // Time
    Symbol t("t");

    // Position and velocity variables
    Symbol r("r"), theta("theta");
    Symbol rp("rp"), thetap("thetap");

    // Elementary variables: set no dependency
    r.setElementary(true);
    rp.setElementary(true);
    theta.setElementary(true);
    thetap.setElementary(true);

    // And depend on t
    r.addDependency(t);
    theta.addDependency(t);
    rp.addDependency(t);
    thetap.addDependency(t);

    // Vectors containing (r,theta) and (dr/dt, dtheta/dt)
    Symbol q("q"), qp("qp");
    q = vector_({r,theta});
    qp = vector_({rp, thetap});

    // Lagrangian
    Symbol Lagrangian("L");

    // Kinetic and Potential energies
    Symbol T("T"), V("V");

    // Kinetic energy in polar coordinates
    T = m/2*((rp^2) + ((r*thetap)^2));

    // Gravitationnal potential
    V = m*g*l*cos_(theta);
    cout<<"Kinetic energy:\n";
    T.print();
    cout<<"Potential energy:\n";
    V.print();

    //Lagrangian with constraint r := l
    cout<<"\nLagrangian:\n";
    Lagrangian = T - V - lambda*(r-l);
    Lagrangian.print();

    cout<<"\nEuler-Lagrange equations, steps of calculation:\n";

    Symbol Euler_Lagrange;
    // Euler-Lagrange equations
    Euler_Lagrange = derivative_(derivative_(Lagrangian,qp),t) - derivative_(Lagrangian,q);
    Euler_Lagrange.print();
    
    // Different steps of calculation
    Euler_Lagrange = Euler_Lagrange.evaluate(); // evaluates derivatives (and derivatives of products)
    Euler_Lagrange.print();

    Euler_Lagrange = Simplify(Euler_Lagrange); // Simplifies
    Euler_Lagrange.print();

    // Recover the expression of velocities as derivatives of positions
    Euler_Lagrange = Euler_Lagrange.replace(rp, derivative_(r,t)); 
    Euler_Lagrange = Euler_Lagrange.replace(thetap, derivative_(theta,t));
    Euler_Lagrange.print();

    // With the condition r = l, we can replace r by l in Euler_Lagrange
    Euler_Lagrange = Euler_Lagrange.replace(r,l);
    // We refresh the expression (r is replaced be we have to reevaluate
    // the expression, in particular derivatives)
    Euler_Lagrange = DeepRefresh(Euler_Lagrange);
    Euler_Lagrange.print();

    // Taking final equations, and dividing by constants to isolate what we want
    // (not yet automatic). After the division, we can either develop explicitely
    // or call the Simplify method that do it automatically.
    Symbol eq1 = Euler_Lagrange[0];
    Symbol eq2 = Euler_Lagrange[1];
    cout<<"eq1 = "; (eq1/m).develop().print();
    cout<<"eq2 = "; Simplify(eq2/(l*l*m)).print();

    cout<<"\n----> We get : d^2/dt^2(theta) = -g/l*sin(theta) (Evolution equation of the pendulum)\n";
    cout<<"                r(dtheta/dt)^2 = lambda/m        (Angular momentum).\n";


    return 0;
}
