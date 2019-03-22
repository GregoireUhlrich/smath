#include "symbol.h"
#include "equation.h"
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
    // Only one arg: it is the variable, the derivative is empty (will apply on arguments on the right)
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


    // Diagonalisation of 2x2 matrix [[a,b],[c,d]]
    // Very pedestrian way: no function is dedicated to this task, so we just do 
    // all steps "by hand". It then needs (and shows) a few useful manipulations.
    cout<<"\n\nDiagonalisation of 2*2 general matrix:\n";
    Symbol a("a"), b("b"), c("c"), d("d");
    a.setAllDependencies(false);
    b.setAllDependencies(false);
    c.setAllDependencies(false);
    d.setAllDependencies(false);

    Symbol lambda("lambda");
    Symbol M = matrix_({{a,b},
                        {c,d}});
    M.print();
    (M-lambda*Id_(2)).print();
    (M-lambda*Id_(2)).determinant().print();
    

    cout<<"Polynomial:\n";
    Simplify((M-lambda*Id_(2)).determinant()).print();

    cout<<"Factored polynomial:\n";
    Symbol poly = polynomial_(Simplify((M-lambda*Id_(2)).determinant()), lambda);
    poly = poly.factor();
    poly.print();

    // We take regular expressions (to manipulate sums and not polynomials)
    Symbol root1 = -(poly[0]-lambda).getRegularExpression();
    Symbol root2 = -(poly[1]-lambda).getRegularExpression();

    cout<<"Roots:\n";
    root1.print();
    root2.print();
    cout<<endl;

    // Eigen vectors s.t. M.u = lambda.u
    cout<<"Searching eigen vectors:\n";
    cout<<"\nRoot 1:\n";
    Symbol u = vector_({x,y});
    leftHandSide = dot(M,u);
    rightHandSide = root1*u;

    Symbol eq1 = (leftHandSide - rightHandSide)[0];
    Symbol eq2 = (leftHandSide - rightHandSide)[1];

    cout<<"Equations to solve:\n";
    eq1.print();
    eq2.print();

    // Seeing the above result, we manually isolate x and y in the equations
    eq1 = Simplify(eq1).full_develop().factor(x)/b;
    eq2 = Simplify(eq2).full_develop().factor(y)/c;

    cout<<"Isolating x and y:\n";
    eq1.develop().print();
    eq2.develop().print();

    // Example of automatic isolation of x and y:
    cout<<"Automatic transformation of equation:\n";
    Equation auto_eq1(leftHandSide[0], rightHandSide[0]);
    Equation auto_eq2(leftHandSide[1], rightHandSide[1]);
    auto_eq1.isolate(y);
    auto_eq1.simplify();
    auto_eq2.isolate(x);
    auto_eq2.simplify();
    cout<<auto_eq1<<endl;
    cout<<auto_eq2<<endl;
    cout<<endl;

    // We inject the expression y(x) of eq1 in eq2 and check that we found 0=0.
    cout<<"Checking that the two equations are equivalent (should give 0):\n";
    eq2.replace(y,-eq1.derive(x)).print();
    cout<<"Not zero but with simplification:\n";
    Simplify(eq2.replace(y,-x*eq1.derive(x))).print();

    // Expression of the eigenvector
    Symbol eigenVector1 = vector_({1,-eq1.derive(x)});

    // Same thing for root 2.
    cout<<"\nRoot 2:\n";
    leftHandSide = dot(M,u);
    rightHandSide = root2*u;

    eq1 = (leftHandSide - rightHandSide)[0];
    eq2 = (leftHandSide - rightHandSide)[1];

    cout<<"Equations to solve:\n";
    eq1.print();
    eq2.print();

    eq1 = Simplify(eq1).full_develop().factor(x)/b;
    eq2 = Simplify(eq2).full_develop().factor(y)/c;

    cout<<"Isolating x and y:\n";
    eq1.develop().print();
    eq2.develop().print();

    cout<<"Checking that the two equations are equivalent (should give 0):\n";
    eq2.replace(y,-eq1.derive(x)).print();
    cout<<"Not zero but with simplification:\n";
    Simplify(eq2.replace(y,-x*eq1.derive(x))).print();

    Symbol eigenVector2 = vector_({1,-eq1.derive(x)});

    cout<<"Found eigenvectors:\n";
    eigenVector1.print();
    eigenVector2.print();

    Symbol transfert_matrix = Simplify(matrix_({{eigenVector1[0],eigenVector2[0]},
                                               {eigenVector1[1],eigenVector2[1]}}));
    // Diagnoal matrix
    Symbol D = matrix_({{root1,0},
                        {0,root2}});

    // We check that P.D.P^{-1} = M
    Symbol M_prime = dot(dot(transfert_matrix,D),transfert_matrix.inverseMatrix());
    M_prime = M_prime.full_develop();
    cout<<"M = P*D*P^{-1}:\n";
    Simplify(M_prime).print();

    // We check that P^{-1}.M.P = D
    D = dot(dot(transfert_matrix.inverseMatrix(),M_prime),transfert_matrix);
    cout<<"\n  Diagnoal matrix D = P^{-1}*M*P:\n\n";
    D.print();
    // D is in a complicated form: we simply have to develop it.
    D = D.full_develop();
    cout<<"\n\n  Diagonal matrix D = P^{-1}*M*P, developped:\n\n";
    D.print();

    return 0;
};
