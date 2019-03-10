#include "vector.h"

using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class AbstractVectorial                       //
/*************************************************/
///////////////////////////////////////////////////

AbstractVectorial::AbstractVectorial(): Abstract()
{
    commutable = false;
    dim = 0;
    nArgs = 0;
    argument = vector<Expr >(0);
    shape = vector<int>(0);
}

void AbstractVectorial::print(int mode) const
{
    if (mode == 0)
    {
        if (name != "") 
            cout<<name<<" = ";
        if (dim == 1) 
            cout<<"Vec";
        else if (dim == 2) 
            cout<<"Mat";
        else 
            cout<<"Tensor";
    }
    cout<<"{";
    for (int i=0; i<nArgs; i++) {
        argument[i]->print(1);
        if (i < nArgs-1) {
            cout<<" , ";
            if (mode == 0 and dim == 2) 
                cout<<"\n    ";
            if (mode == 0 and dim == 3) 
                cout<<"\n       ";
            if (mode == 0 and dim > 3) {
                for (int j=0; j<dim+1-3; j++)
                    cout<<endl;
                cout<<"       ";
            }
        }
    }
    cout<<"}";
    if (mode == 0) 
        cout<<endl;
}

string AbstractVectorial::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0) {
        if (name != "") 
            sout<<name<<" = ";
        if (dim == 1) 
            sout<<"Vec";
        else if (dim == 2) 
            sout<<"Mat";
        else 
            sout<<"Tensor";
    }
    sout<<"{ ";
    for (int i=0; i<nArgs; i++) {
        argument[i]->print(1);
        if (i < nArgs-1)
            sout<<" , ";
    }
    sout<<"}";
    if (mode == 0) 
        sout<<endl;

    return sout.str();
}

Expr AbstractVectorial::evaluate()
{
    if (dim == 0) 
        return ZERO;
    if (nArgs > 0) {
        Expr foo = tensor_(getShape());
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->evaluate(),i);

        return foo;
    }
    else 
        return ZERO;
}
        

int AbstractVectorial::getNArgs(int axis) const
{
    if (axis >= dim or axis < 0) {
        cout<<"Warning: axis "<<axis<<" out of bounds of the vectorial expr.\n";
        return 0;
    }
    if (axis == 0) 
        return nArgs;
    if (nArgs == 0) 
        return 0;

    return argument[0]->getNArgs(axis-1);
}

iter AbstractVectorial::begin()
{
    return argument.begin();
}

iter AbstractVectorial::end()
{
    return argument.end();
}

Expr AbstractVectorial::getArgument(int iArg) const
{
    if (iArg >= 0 and iArg < nArgs)
        return argument[iArg];
    else if (iArg == -1)
        return Copy(this);
    print();
    callError(smError::OutOfBounds,
            "AbstractVectorial::getArgument(int iArg) const",iArg);

    return ZERO;
}

Expr AbstractVectorial::getArgument(const initializer_list<int>& indices) const
{
    vector<int> indices_vec(indices.begin(), indices.end());
    return getArgument(indices_vec);
}

Expr AbstractVectorial::getArgument(const vector<int>& indices) const
{
    const int size = indices.size();
    if (size > dim or size == 0) {
        callWarning(smError::InvalidDimension,
                "AbstractVectorial::getArgument",size);
        return ZERO;
    }
    else if (size == 1)
        return getArgument(indices[0]);
    vector<int> shape = getShape();
    vector<int>::const_iterator it;
    // All dimensions with index -1 keep their size (we take all indices)
    for (it=indices.begin(); it!=indices.end(); ++it)
        if (*it != -1)
            shape[distance(indices.begin(),it)] = 1;
    // We suppress dimensions of size 1
    for (size_t i=0; i!=shape.size(); ++i) {
        if (shape[i] == 1) {
            shape.erase(shape.begin()+i);
            --i;
        }
    }

    Expr foo = tensor_(shape);
    int index = indices[0];
    // new indices with which we call recursively getArgument (we suppress the first)
    vector<int> newIndices(indices.begin()+1,indices.end());
    if (dim > 1) {
        if (index == -1)
            for (int i=0; i<nArgs; i++)
                foo->setArgument(argument[i]->getArgument(newIndices),i);
        else
            foo = argument[index]->getArgument(newIndices);
    }
    else {
        if (index == -1)
            for (int i=0; i<nArgs; i++)
                foo->setArgument(argument[i],i);
        else
            foo = argument[index];
    }

    return foo;
}

const vector<Expr >& AbstractVectorial::getVectorArgument() const
{
    return argument;
}

vector<int> AbstractVectorial::getShape() const
{
    return shape;
}

void AbstractVectorial::setArgument(const Expr& expr, int iArg)
{
    if (iArg < nArgs and dim == 1+expr->getDim())
        argument[iArg] = expr;
    else
        cout<<"Warning: index "<<iArg<<" out of bound of vectorial expr.\n";
}

void AbstractVectorial::setVectorArgument(const vector<Expr >& t_argument)
{
    if (t_argument.size() > 0) {
        if (t_argument[0]->getDim() != dim-1)
            cout<<"Warning: wrong dimension in setVectorArgument in AbstractVectorial.\n";
        else {
            argument = t_argument;
            nArgs = argument.size();
        }
    }
    else {
        nArgs = 0;
        argument = t_argument;
    }
}

void AbstractVectorial::setArgument(const Expr& expr,
                                    const initializer_list<int>& indices)
{
    setArgument(expr, vector<int>(indices.begin(), indices.end()));
}

void AbstractVectorial::setArgument(const Expr& expr,
                                    const vector<int>& indices)
{
    const int size = indices.size();
    if (size == 0 or size > dim) {
        callWarning(smError::InvalidDimension,
"AbstractVectorial::setArgument(const Expr&, const vector<int>&)",size);
        return;
    }
    if (size == 1)
        argument[indices[0]] = expr;
    else
        argument[indices[0]]->setArgument(expr,
                vector<int>(indices.begin()+1,indices.end()));
}

bool AbstractVectorial::matchShape(const Expr& expr, bool exact) const
{
    if (exact) 
        return exactMatchShape(expr);
    if (dim == 0 or expr->getDim() == 0) 
        return true;

    // if no object of dimension 0, we test the matching of the last 
    // dimension of this and the first of expr (for a dot product)
    return (getNArgs(dim-1) == expr->getNArgs(0));
}

bool AbstractVectorial::exactMatchShape(const Expr& expr) const
{
    int t_dim = expr->getDim();
    if (dim == 0 or t_dim == 0) 
        return true;
    if (dim != t_dim) 
        return false;
    vector<int> shape1(getShape()), shape2(expr->getShape());
    if (shape1.size() != shape2.size()) 
        return false;
    for (size_t i=0; i<shape1.size(); i++)
        if (shape1[i] != shape2[i])
            return false;

    return true;
}

Expr AbstractVectorial::getSum() const
{
    if (dim == 1)
        return plus_(argument);
    else {
        vector<Expr > intermediateSums(nArgs);
        for (int i=0; i<nArgs; i++)
            intermediateSums[i] = argument[i]->getSum();

        return plus_(intermediateSums);
    }
}

Expr AbstractVectorial::getProduct() const
{
    if (dim == 1)
        return times_(argument);
    else {
        vector<Expr > intermediateProducts(nArgs);
        for (int i=0; i<nArgs; i++)
            intermediateProducts[i] = argument[i]->getProduct();
        
        return times_(intermediateProducts);
    }
}

Expr AbstractVectorial::getSubVectorial(const vector<int>& exceptions) const
{
    if ((int)exceptions.size() != dim) {
        cout<<"Warning: taking subVectorial with wrong number of dimensions.\n";
        return ZERO;
    }
    vector<int> shape = getShape();
    for (int i=0; i<dim; i++)
        --shape[i];
    Expr foo = tensor_(shape);
    if (dim > 1) {
        vector<int> newExceptions(exceptions);
        newExceptions.erase(newExceptions.begin());
        int i=0; 
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i) {
            if (i == exceptions[0])
                ++i;
            *arg = argument[i]->getSubVectorial(newExceptions);
        }
    }
    else {
        int i=0;
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i) {
            if (i == exceptions[0])
                ++i;
            *arg = argument[i];
        }
    }

    return foo;
}

Expr AbstractVectorial::getVectorialModulus() const
{
    Expr sum = ZERO;
    if (dim == 1) {
        vector<Expr > intermediateResults(nArgs);
        for (int i=0; i<nArgs; i++)
            intermediateResults[i] = pow_(argument[i], int_(2));

        return sqrt_(plus_(intermediateResults));
    }
    vector<Expr > intermediateResults(nArgs);
    for (int i=0; i<nArgs; i++)
        intermediateResults[i] = argument[i]->getVectorialModulus();

    return sqrt_(plus_(intermediateResults));
}

Expr AbstractVectorial::dot(const Expr& expr) const
{
    int t_dim = expr->getDim();
    if (t_dim == 0) {
        Expr foo = Copy(this);
        if (dim == 1) {
            int i=0;
            for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
                *arg = times_(argument[i], expr);
            return foo;
        }
        int i=0;
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
            *arg = argument[i]->dot(expr);
        return foo;
    }
    else {
        vector<int> shape2(expr->getShape());
        vector<int> newShape(dim+shape2.size()-2);
        if (shape[dim-1] != shape2[0]) {
            cout<<"Warning: shapes do not match in dot product.\n";
            return ZERO;
        }
        for (int i=0; i<dim-1; i++)
            newShape[i] = shape[i];
        for (size_t j=dim-1; j<newShape.size(); j++)
            newShape[j] = shape2[2+j-dim];

        Expr foo = tensor_(newShape);
        vector<Expr> vec(nArgs);
        if (dim == 1) {
            int i=0;
            for (iter arg=expr->begin(); arg!=expr->end(); ++arg, ++i)
                vec[i] = times_(argument[i], *arg);
            for (int i=0; i<nArgs; i++)
                foo = plus_(foo, times_(argument[i],(*expr)[i]));
            foo = plus_(vec);
        }
        else {
            for (int i=0; i<nArgs; ++i)
                vec[i] = argument[i]->dot(expr);
            for (int i=0; i<nArgs; i++)
                foo->setArgument(argument[i]->dot(expr), i);
            foo = highDTensor_(vec);
        }

        return foo;
    }
}

Expr AbstractVectorial::addition_own(const Expr& expr) const
{
    if (!exactMatchShape(expr)) {
        cout<<"Warning: shapes do not match in addition_own.\n";
        return ZERO;
    }
    Expr foo = tensor_(getShape());
    if (expr->getDim() == 0) {
        if (dim == 1) {
            int i=0;
            for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
                *arg = plus_(expr, argument[i]);
            return foo;
        }
        int i=0;
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
            *arg = argument[i]->addition_own(expr);
        return foo;
    }
    if (dim == 1) {
        int i=0;
        iter arg2=expr->begin();
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++arg2, ++i)
            *arg = plus_(argument[i], *arg2);
    }
    else {
        int i=0;
        iter arg2=expr->begin();
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++arg2, ++i)
            *arg = argument[i]->addition_own(*arg2);
    }

    return foo;
}

Expr AbstractVectorial::multiplication_own(const Expr& expr) const
{
    if (!exactMatchShape(expr)) {
        cout<<"Warning: shapes do not match in multiplication_own.\n";
        return ZERO;
    }
    Expr foo = tensor_(getShape());
    if (expr->getDim() == 0) {
        if (dim == 1) {
            int i=0;
            for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
                *arg = times_(expr, argument[i]);

            return foo;
        }
        int i=0;
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
            *arg = argument[i]->multiplication_own(expr);

        return foo;
    }
    if (dim == 1) {
        int i=0;
        iter arg2 = expr->begin();
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++arg2, ++i)
            *arg = times_(argument[i],*arg2);
    }
    else {
        int i=0;
        iter arg2 = expr->begin();
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++arg2, ++i)
            *arg = argument[i]->multiplication_own(*arg2);
    }

    return foo;
}

Expr AbstractVectorial::tensor_dot(const Expr& expr) const
{
    if (expr->getDim() == 0)
        return multiplication_own(expr);
    vector<int> shape = getShape();
    vector<int> shape2 = expr->getShape();
    shape.insert(shape.end(), shape2.begin(), shape2.end());
    Expr foo = tensor_(shape);
    if (dim > 1)  {
        int i=0;
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
            *arg = argument[i]->tensor_dot(expr);
    }
    else  {
        int i=0;
        for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
            *arg = expr->multiplication_own(argument[i]);
    }
    
    return foo;
}

Expr AbstractVectorial::trace(int axis1, int axis2) const
{
    if (axis1 > dim or axis2 > dim) {
        cout<<"Warning: taking trace of axis out of scope.\n";
        return ZERO;
    }
    vector<int> newShape = shape;
    for (int i=0; i<dim; i++)
        if (i == axis1 or i == axis2)
            newShape[i] = 1;
    for (size_t i=0; i<newShape.size(); i++) {
        if (newShape[i] == 1) {
            newShape.erase(newShape.begin()+i);
            i--;
        }
    }

    Expr foo = tensor_(newShape);
    vector<int> indices(dim, -1);
    if (axis1 == axis2) {
        for (int i=0; i<shape[axis1]; i++) {
            indices[axis1] = i;
            foo = plus_(foo, getArgument(indices));
        }

        return foo;
    }
    if (shape[axis1] != shape[axis2]) {
        cout<<"Warning: taking trace of non-equivalent dimensions.\n";
        return ZERO;
    }
    if (axis2 < axis1) {
        int foo = axis1;
        axis1 = axis2;
        axis2 = foo;
    }
    for (int i=0; i<shape[axis1]; i++) {
        indices[axis1] = i;
        indices[axis2] = i;
        foo = plus_(foo, getArgument(indices));
    }

    return foo;
}

Expr AbstractVectorial::develop(bool full)
{
    Expr foo = tensor_(getShape());
    int i=0;
    for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
        *arg = argument[i]->develop(full);

    return foo;
}

Expr AbstractVectorial::factor(bool full)
{
    Expr foo = tensor_(getShape());
    int i=0;
    for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
        *arg = argument[i]->factor(full);

    return foo;
}

Expr AbstractVectorial::factor(const Expr& expr, bool full)
{
    Expr foo = tensor_(getShape());
    int i=0;
    for (iter arg=foo->begin(); arg!=foo->end(); ++arg, ++i)
        *arg = argument[i]->factor(expr, full);

    return foo;
}

bool AbstractVectorial::operator==(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (dim != expr->getDim() or nArgs != expr->getNArgs()) 
        return false;
    int i=0;
    for (iter arg=expr->begin(); arg!=expr->end(); ++arg, ++i)
        if (*argument[i] != *arg)
            return false;

    return true;
}

Expr AbstractVectorial::operator[](int iArg)
{
    if (iArg < 0 or iArg >= nArgs) {
        print();
        callError(smError::OutOfBounds,
                "AbstractVectorial::operator[](int iArg)", iArg);
    }
    return argument[iArg];
}

///////////////////////////////////////////////////
/*************************************************/
// Class Vector                                  //
/*************************************************/
///////////////////////////////////////////////////

Vector::Vector(): AbstractVectorial()
{
    dim = 1;
    shape = vector<int>(1,0);
}

Vector::Vector(int t_nElements): Vector()
{
    nArgs = t_nElements;
    argument = vector<Expr >(nArgs,ZERO);
    shape = vector<int>(1,nArgs);
}

Vector::Vector(int t_nElements, const Expr& expr, const Expr& index): Vector()
{
    if (expr->getDim() > 0) {
        print();
        callError(smError::ElementSequence,
                "Vector::Vector(int, const Expr&, const Expr&)");
    }
    else {
        nArgs = t_nElements;
        argument = vector<Expr >(nArgs, expr);
        if (index->getType() == smType::Variable)
            for (iter it=argument.begin(); it!=argument.end(); ++it)
                *it = Replace(*it,index,int_(distance(argument.begin(),it)));
        shape = vector<int>(1,nArgs);
    }
}

Vector::Vector(const vector<Expr >& t_argument): Vector()
{
    int dimOk = true;
    for (const_iter it=t_argument.begin(); it!=t_argument.end(); ++it) {
        if ((*it)->getDim() != 0) {
            dimOk = false;
            break;
        }
    }
    if (!dimOk) {
        print();
        callError(smError::ElementSequence,
                "Vector::Vector(const vector<Expr >& t_argument)");
    }
    else {
        argument = t_argument;
        nArgs = argument.size();
        shape = vector<int>(1,nArgs);
    }
}

Expr Vector::getSubVectorial(int iExcept) const
{
    if (nArgs == 2) 
        return argument[1-iExcept];
    Expr foo = _vector_(nArgs-1);
    for (int i=0; i<nArgs; i++) {
        if (i < iExcept)
            foo->setArgument(argument[i],i);
        else if (i > iExcept)
            foo->setArgument(argument[i],i-1);
    }

    return foo;
}

Expr _vector_(int t_nElements)
{
    return make_shared<Vector>(t_nElements);
}

Expr vector_(int t_nElements,const Expr& expr, const Expr& index)
{
    return make_shared<Vector>(t_nElements, expr, index);
}

Expr vector_(const vector<Expr >& t_argument)
{
    return make_shared<Vector>(t_argument);
}

///////////////////////////////////////////////////
/*************************************************/
// Class Matrix                                  //
/*************************************************/
///////////////////////////////////////////////////

Matrix::Matrix(): AbstractVectorial()
{
    dim = 2;
    shape = vector<int>(2,0);
}

Matrix::Matrix(int t_nArgs): Matrix()
{
    nArgs = t_nArgs;
    argument = vector<Expr >(nArgs, make_shared<Vector>(nArgs));
    shape = vector<int>(2,nArgs);
}

Matrix::Matrix(int t_x_nArgs, int t_y_nArgs): Matrix()
{
    nArgs = t_x_nArgs;
    argument = vector<Expr >(nArgs);
    for (auto& arg : argument)
        arg = make_shared<Vector>(t_y_nArgs);
    shape = vector<int>(2);
    shape[0] = t_x_nArgs;
    shape[1] = t_y_nArgs;
}

Matrix::Matrix(int t_x_nArgs, int t_y_nArgs,
               const Expr& expr,
               const Expr& index_x, const Expr& index_y)
    :Matrix()
{
    if (expr->getDim() != 0) {
        print();
        callError(smError::ElementSequence,
            "Matrix::Matrix(int, int, const Expr&, const Expr&, const Expr&)");
    }
    else {
        nArgs = t_x_nArgs;
        argument = vector<Expr >(nArgs);
        Expr foo;
        for (iter it=argument.begin(); it!=argument.end(); ++it) {
            foo = Replace(expr, index_x, int_(distance(argument.begin(),it)));
            *it = make_shared<Vector>(t_y_nArgs,foo,index_y);
        }
        shape = vector<int>(2);
        shape[0] = t_x_nArgs;
        shape[1] = t_y_nArgs;
    }
}

Matrix::Matrix(const vector<Expr >& t_argument): Matrix()
{
    int dimOk = true;
    for (const auto& x: t_argument) {
        if (x->getDim() != 1) {
            dimOk = false;
            break;
        }
    }
    if (!dimOk) {
        print();
        callError(smError::ElementSequence,
                "Matrix::Matrix(const vector<Expr >& t_argument): Matrix()");
    }
    else {
        argument = t_argument;
        nArgs = argument.size();
        shape = vector<int>(2);
        shape[0] = nArgs;
        if (nArgs > 0) shape[1] = argument[0]->getNArgs();
        else           shape[1] = 0;
    }
}

Expr Matrix::getSubVectorial(int iExcept, int jExcept) const
{
    vector<int> newShape = shape;
    newShape[0]--;
    newShape[1]--;
    if (newShape[0] == 1) 
        return argument[1-iExcept]->getSubVectorial(jExcept);
    Expr foo = tensor_(newShape);
    for (int i=0; i<nArgs; i++) {
        if (i < iExcept)
            foo->setArgument(argument[i]->getSubVectorial(jExcept),i);
        else if (i > iExcept)
            foo->setArgument(argument[i]->getSubVectorial(jExcept),i-1);
    }
    return foo;
}

Expr Matrix::determinant() const
{
    if (nArgs != argument[0]->getNArgs()) {
        cout<<"Warning: taking determinant of non-square matrix.\n";
        return ZERO;
    }

    // Former algo in N!
    
    /*
    Expr foo = ZERO;
    if (nArgs > 2 and argument[0]->getNArgs() > 2) 
        for (int i=0; i<nArgs; i++)
            foo = plus_(foo,
                        times_(argument[i]->getArgument(0),
                               times_(int_(pow(-1,i)),
                                      getSubVectorial(i,0)->determinant())));    
    else 
        for (int i=0; i<nArgs; i++)
            foo = plus_(foo,
                        times_(argument[i]->getArgument(0),
                               times_(int_(pow(-1,i)),
                                      getSubVectorial(i,0))));    
    */
   

    // New algo in N^3
    Expr copy = DeepCopy(this);
    const int n = nArgs;
    const int m = argument[0]->getNArgs();
    int h = 0;
    int k = 0;
    int pivot = n-1;
    int sign = 1;
    iter arg_h = copy->begin();
    while (h < n and k < m) {
        if ((*arg_h)->getArgument(k) == ZERO) {
            if (pivot == h)
                return ZERO;
            Expr foo = copy->getArgument(pivot);
            copy->setArgument(*arg_h, pivot);
            *arg_h = foo;
            --pivot;
            sign *= -1;
        }
        else {
            pivot = n-1;
            for (iter arg_i=1+arg_h; arg_i!=copy->end(); ++arg_i) {
                Expr f = fraction_((*arg_i)->getArgument(k),
                                   (*arg_h)->getArgument(k));
                (*arg_i)->setArgument(ZERO,k);
                for (int j=k+1; j<m; ++j)
                    (*arg_i)->setArgument(minus_((*arg_i)->getArgument(j),
                                times_((*arg_h)->getArgument(j),f)),j);
            }
            ++h;
            ++arg_h;
            ++k;
        }
    };
    vector<Expr> vec(nArgs);
    int i=0;
    for (iter arg=copy->begin(); arg!=copy->end(); ++arg, ++i) {
        vec[i] = (*arg)->getArgument(i);
    }
//    cout<<"Det à moi: "; foo->print();
//    cout<<"new Det: "; times_(vec)->print();
//    if (*foo != times_(vec))
//    {
//        cout<<"DIFFERENCE IN "; print();
//    }


    return times_(int_(sign),times_(vec));
}

Expr Matrix::trace() const
{
    if (nArgs != argument[0]->getNArgs()) {
        cout<<"Warning: taking the trace of non-square matrix.\n";
        return ZERO;
    }
    vector<Expr> vec(nArgs);
    for (int i=0; i<nArgs; i++)
        vec[i] = argument[i]->getArgument(i);

    return plus_(vec);
}

Expr Matrix::transpose() const
{
    vector<int> newShape(shape);
    int fooInt = newShape[0];
    newShape[0] = newShape[1];
    newShape[1] = fooInt;
    Expr foo = tensor_(newShape);
    int j=0;
    for (iter arg_i=foo->begin(); arg_i!=foo->end(); ++arg_i, ++j) {
        int i=0;
        for (iter arg_j=(**arg_i).begin(); arg_j!=(**arg_i).end(); ++arg_j, ++i)
            *arg_j = argument[i]->getArgument(j);
    }

    return foo;
}

Expr Matrix::transposedCoMatrix() const
{
    Expr foo = tensor_(getShape());
    if (nArgs > 2 and argument[0]->getNArgs() > 2) 
        for (int i=0; i<nArgs; i++)
            for (int j=0; j<argument[0]->getNArgs(); j++)
                foo->setArgument(times_(getSubVectorial(i,j)->determinant(),
                                        int_(pow(-1,i+j))),{j,i});
    else 
        for (int i=0; i<nArgs; i++) 
            for (int j=0; j<argument[0]->getNArgs(); j++) 
                foo->setArgument(times_(getSubVectorial(i,j),
                                        int_(pow(-1,i+j))),{j,i});

    return foo;
}

Expr Matrix::inverseMatrix() const
{
    Expr det = determinant();
    if (det->getPrimaryType() == smType::Numerical
            and det->evaluateScalar() == 0) {
        cout<<"Warning: inverting matrix that has dete = 0.\n";
        return ZERO;
    }

    return times_(fraction_(int_(1),det),transposedCoMatrix());
}

Expr Matrix::symmetrise() const
{
    Expr foo = _cfraction_(1,2);
    return plus_(times_(foo,Copy(this)),times_(foo,transpose()));
}

Expr Matrix::antisymmetrise() const
{
    Expr foo = _cfraction_(1,2);
    return minus_(times_(foo,Copy(this)),times_(foo,transpose()));
}

Expr _matrix_(int t_nArgs)
{
    return make_shared<Matrix>(t_nArgs);
}

Expr _matrix_(int t_x_nArgs, int t_y_nArgs)
{
    return make_shared<Matrix>(t_x_nArgs, t_y_nArgs);
}

Expr matrix_(int t_x_nArgs, int t_y_nArgs,
             const Expr& expr,
             const Expr& index_x, const Expr& index_y)
{
    return make_shared<Matrix>(t_x_nArgs, t_y_nArgs, expr, index_x, index_y);
}

Expr matrix_(const vector<Expr >& t_argument)
{
    return make_shared<Matrix>(t_argument);
}

///////////////////////////////////////////////////
/*************************************************/
// Class HighDTensor                             //
/*************************************************/
///////////////////////////////////////////////////

HighDTensor::HighDTensor(): AbstractVectorial()
{
    shape = vector<int>(0);
}

HighDTensor::HighDTensor(const vector<int>& t_shape): AbstractVectorial()
{
    shape = t_shape;
    dim = shape.size();
    if(dim > 0) {
        nArgs = shape[0];
        vector<int> newShape(shape.begin()+1, shape.end());
        if (dim > 1) {
            argument = vector<Expr >(nArgs);
            for (auto& arg : argument)
                arg = tensor_(newShape);
        }
        else argument = vector<Expr >(nArgs, ZERO);
    }
    else argument = vector<Expr >(0);
}

HighDTensor::HighDTensor(const vector<Expr >& t_argument)
{
    nArgs = t_argument.size();
    shape = vector<int>(1,nArgs);
    if (nArgs > 0) {
        argument = t_argument;
        dim = 1+argument[0]->getDim();
        if (dim > 1) {
            vector<int> followingShape = argument[0]->getShape();
            shape.insert(shape.end(),
                         followingShape.begin(), followingShape.end());
        }
    }
    else {
        argument = vector<Expr >(0);
        nArgs = 0;
        dim = 0;
    }
}

Expr highDTensor_(const vector<int>& shape)
{
    return make_shared<HighDTensor>(shape);
}

Expr highDTensor_(const vector<Expr >& t_argument)
{
    if (t_argument.size() == 0)
        return ZERO;
    switch (t_argument[0]->getDim()) {

        case 0:
        return vector_(t_argument);
        break;

        case 1:
        return matrix_(t_argument);
        break;

        default:
        return make_shared<HighDTensor>(t_argument);
    }
}

Expr tensor_(const std::vector<int>& shape)
{
    switch(shape.size())
    {
        case 0:
        return ZERO;
        break;

        case 1:
        return _vector_(shape[0]);
        break;

        case 2:
        return _matrix_(shape[0],shape[1]);
        break;

        default:
        return highDTensor_(shape);
    }
}
