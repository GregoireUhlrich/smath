#include "symbol.h"
#include <iostream>

using namespace std;

/* Already implemented in symbol.cpp
(and better)
Symbol scalarDot(Symbol A, Symbol B)
{
    return (A[0]*B[0]
           +A[1]*B[1]
           +A[2]*B[2]);
}
*/

Symbol crossDot(Symbol A, Symbol B)
{
    return vector_(
            {A[1]*B[2]-A[2]*B[1],
             A[2]*B[0]-A[0]*B[2],
             A[0]*B[1]-A[1]*B[0]});
}

int main(){

    // Creating elementary variables
    Symbol x("x"), y("y"), z("z");
    x.setElementary(true);
    y.setElementary(true);
    z.setElementary(true);

    // Symbols that will be contained in two 3-vectors A and B
    Symbol Ax("Ax"), Ay("Ay"), Az("Az"),
           Bx("Bx"), By("By"), Bz("Bz");

    // Vectors A and B
    Symbol A("A"), B("B");
    A = vector_({Ax,Ay,Az});
    B = vector_({Bx,By,Bz});

    // Cartesian derivative in 3D
    Symbol Nabla("D");
    Nabla = vector_({derivative_(x),
                     derivative_(y),
                     derivative_(z)});

    // Verifying the equation:
    // D^(A^B) = A(D.B) - (A.D)B + A(D.B) - B(D.A) 
    // in 3D (^ stands for crossProduct and D for the \nabla operator.
    Symbol leftHandSide = crossDot(Nabla, crossDot(A,B));
    Symbol rightHandSide = (scalarDot(B,Nabla)*A - scalarDot(A,Nabla)*B
                          + A*scalarDot(Nabla,B) - B*scalarDot(Nabla,A));

    cout<<"Result of D^(A^B) - (A(D.B) - (A.D)B + A(D.B) - B(D.A)) (== 0):\n\n";
    // Printing the difference (should be 0)
    cout<<"Bare expression:\n";
    (leftHandSide - rightHandSide).print();
    // Evaluating (to apply Leibniz rules for derivatives)
    cout<<"Applying Leibniz rule (evaluate):\n";
    (leftHandSide.evaluate()-rightHandSide).print();
    // Developing 
    cout<<"Developing:\n";
    (leftHandSide.evaluate()-rightHandSide).full_develop().print();

    // Rotationnal in spherical coordinates
    Symbol r("r"), theta("theta"), phi("phi");
    // Here for r and theta derivatives, a term is present in the derivative already
    // (r^2 and sin(theta)) but the dereivative must stay empty to apply to a function
    // on the right. To create an empty derivative with an argument, we must call
    // derivative_() with 4 argument: 
    // Argument of derivative, variable, order of derivative, boolean that tells if the 
    // derivative must stay empty (true her)
    Nabla = vector_({1/(r^2)*derivative_(r^2,r,1,true),
                     1/(r*sin_(theta))*derivative_(sin_(theta),theta,1,true),
                     1/(r*sin_(theta))*derivative_(phi)});

    cout<<"\n\nRotationnal in spherical coordinates:\n";
    scalarDot(Nabla,A).print();

    Symbol a("a"), b("b"), c("c"), d("d");
    Symbol lambda("lambda");
    Symbol M = matrix_({{a,b},
                        {c,d}});

    M.print();
    Id_(2).print();
    (M-lambda*Id_(2)).print();
    (M-lambda*Id_(2)).determinant().print();
    Simplify((M-lambda*Id_(2)).determinant()).print();
    polynomial_(Simplify((M-lambda*Id_(2)).determinant()), lambda).print();
    Symbol poly = polynomial_(Simplify((M-lambda*Id_(2)).determinant()), lambda);
    poly = poly.factor();
    poly.print();
    poly.setArgument(Simplify(poly[0]),0);
    poly.setArgument(Simplify(poly[1]),1);
    poly.print();

    Simplify(a*c/(a+b)+b*c/(a+b)).print();


    return 0;
};
