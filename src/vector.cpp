#include "vector.h"

using namespace std;

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
        if (name != "") cout<<name<<" = ";
        if (dim == 1) cout<<"Vec";
        else if (dim == 2) cout<<"Mat";
        else cout<<"Tensor";
    }
    cout<<"{";
    for (int i=0; i<nArgs; i++)
    {
        argument[i]->print(1);
        if (i < nArgs-1)
        {
            cout<<" , ";
            if (mode == 0 and dim == 2) cout<<"\n    ";
            if (mode == 0 and dim == 3) cout<<"\n       ";
            if (mode == 0 and dim > 3)
            {
                for (int j=0; j<dim+1-3; j++)
                    cout<<endl;
                cout<<"       ";
            }
        }
    }
    cout<<"}";
    if (mode == 0) cout<<endl;
}

string AbstractVectorial::printLaTeX(int mode) const
{
    ostringstream sout;
    if (mode == 0)
    {
        if (name != "") sout<<name<<" = ";
        if (dim == 1) sout<<"Vec";
        else if (dim == 2) sout<<"Mat";
        else sout<<"Tensor";
    }
    sout<<"{ ";
    for (int i=0; i<nArgs; i++)
    {
        argument[i]->print(1);
        if (i < nArgs-1)
            sout<<" , ";
    }
    sout<<"}";
    if (mode == 0) sout<<endl;

    return sout.str();
}

Expr AbstractVectorial::evaluate()
{
    if (dim == 0) return ZERO;
    if (nArgs > 0)
    {
        Expr foo = tensor_(getShape());
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->evaluate(),i);
        return foo;
    }
    else return ZERO;
}
        

int AbstractVectorial::getNArgs(int axis) const
{
    if (axis >= dim or axis < 0)
    {
        cout<<"Warning: axis "<<axis<<" out of bounds of the vectorial expression.\n";
        return 0;
    }
    if (axis == 0) return nArgs;
    if (nArgs == 0) return 0;
    return argument[0]->getNArgs(axis-1);
}

Expr AbstractVectorial::getArgument(int iArg) const
{
    if (iArg >= 0 and iArg < nArgs)
        return argument[iArg];
    else if (iArg == -1)
        return Copy(this);
    print();
    callError(smError::OutOfBounds, "AbstractVectorial::getArgument(int iArg) const",iArg);
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
    if (size > dim or size == 0)
    {
        callWarning(smError::InvalidDimension,"AbstractVectorial::getArgument",size);
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

void AbstractVectorial::setArgument(const Expr& t_abstract, int iArg)
{
    if (iArg < nArgs and dim == 1+t_abstract->getDim())
        argument[iArg] = t_abstract;
    else
        cout<<"Warning: index "<<iArg<<" out of bound of vectorial expression.\n";
}

void AbstractVectorial::setVectorArgument(const vector<Expr >& t_argument)
{
    if (t_argument.size() > 0)
    {
        if (t_argument[0]->getDim() != dim-1)
        {
            cout<<"Warning: wrong dimension in setVectorArgument in AbstractVectorial.\n";
        }
        else
        {
            argument = t_argument;
            nArgs = argument.size();
        }
    }
    else
    {
        nArgs = 0;
        argument = t_argument;
    }
}

void AbstractVectorial::setArgument(const Expr& t_abstract, const initializer_list<int>& indices)
{
    setArgument(t_abstract, vector<int>(indices.begin(), indices.end()));
}

void AbstractVectorial::setArgument(const Expr& t_abstract, const vector<int>& indices)
{
    const int size = indices.size();
    if (size == 0 or size > dim)
    {
        callWarning(smError::InvalidDimension, "AbstractVectorial::setArgument(const Expr& t_abstract, const vector<int>& indices)", size);
        return;
    }
    if (size == 1)
        argument[indices[0]] = t_abstract;
    else
        argument[indices[0]]->setArgument(t_abstract,vector<int>(indices.begin()+1,indices.end()));
}

bool AbstractVectorial::matchShape(const Expr& t_abstract, bool exact) const
{
    if (exact) return exactMatchShape(t_abstract);
    if (dim == 0 or t_abstract->getDim() == 0) return true;
    // if no object of dimension 0, we test the matching of the last 
    // dimension of this and the first of t_abstract (for a dot product)
    return (getNArgs(dim-1) == t_abstract->getNArgs(0));
}

bool AbstractVectorial::exactMatchShape(const Expr& t_abstract) const
{
    int t_dim = t_abstract->getDim();
    if (dim == 0 or t_dim == 0) return true;
    if (dim != t_dim) return false;
    vector<int> shape1(getShape()), shape2(t_abstract->getShape());
    if (shape1.size() != shape2.size()) return false;
    for (size_t i=0; i<shape1.size(); i++)
        if (shape1[i] != shape2[i])
            return false;
    return true;
}

Expr AbstractVectorial::getSum() const
{
    if (dim == 1)
    {
        return plus_(argument);
    }
    else
    {
        vector<Expr > intermediateSums(nArgs);
        for (int i=0; i<nArgs; i++)
        {
            intermediateSums[i] = argument[i]->getSum();
        }
        return plus_(intermediateSums);
    }
}

Expr AbstractVectorial::getProduct() const
{
    if (dim == 1)
    {
        return times_(argument);
    }
    else
    {
        vector<Expr > intermediateProducts(nArgs);
        for (int i=0; i<nArgs; i++)
            intermediateProducts[i] = argument[i]->getProduct();
        return times_(intermediateProducts);
    }
}

Expr AbstractVectorial::getSubVectorial(const vector<int>& exceptions) const
{
    if ((int)exceptions.size() != dim)
    {
        cout<<"Warning: taking subVectorial with wrong number of dimensions.\n";
        return ZERO;
    }
    vector<int> shape = getShape();
    for (int i=0; i<dim; i++)
        shape[i]--;
    Expr foo = tensor_(shape);
    if (exceptions.size() > 1)
    {
        vector<int> newExceptions(exceptions);
        newExceptions.erase(newExceptions.begin());
        for (int i=0; i<nArgs; i++)
        {
            if (i < exceptions[0])
                foo->setArgument(argument[i]->getSubVectorial(newExceptions),i);
            else if (i > exceptions[0])
                foo->setArgument(argument[i]->getSubVectorial(newExceptions),i-1);
        }
    }
    else
    {
        for (int i=0; i<nArgs; i++)
        {
            if (i < exceptions[0])
                foo->setArgument(argument[i],i);
            else if (i > exceptions[0])
                foo->setArgument(argument[i],i-1);
        }
    }
    return foo;
}

Expr AbstractVectorial::getVectorialModulus() const
{
    Expr sum = ZERO;
    if (dim == 1)
    {
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

Expr AbstractVectorial::dot(const Expr& t_abstract) const
{
    int t_dim = t_abstract->getDim();
    if (dim == 0)
    {
        if (t_dim == 0) return times_(argument[0],(*t_abstract)[0]);
        return t_abstract->dot(Copy(this));
    }
    Expr foo;
    if (t_dim == 0)
    {
        foo = Copy(this);
        if (dim == 1)
        {
            for (int i=0; i<nArgs; i++)
                foo->setArgument(times_(argument[i],t_abstract),i);
            return foo;
        }
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->dot(t_abstract),i);
        return foo;
    }
    else
    {
        vector<int> shape1(getShape()), shape2(t_abstract->getShape());
        vector<int> newShape(shape1.size()+shape2.size()-2);
        if (shape1[shape1.size()-1] != shape2[0])
        {
            cout<<"Warning: shapes do not match in dot product.\n";
            return ZERO;
        }
        for (size_t i=0; i<shape1.size()-1; i++)
            newShape[i] = shape1[i];
        for (size_t j=shape1.size()-1; j<newShape.size(); j++)
            newShape[j] = shape2[2+j-shape1.size()];

        Expr foo = tensor_(newShape);
        if (dim == 1)
        {
            for (int i=0; i<nArgs; i++)
                foo = plus_(foo, times_(argument[i],(*t_abstract)[i]));
        }
        else
        {
            for (int i=0; i<nArgs; i++)
                foo->setArgument(argument[i]->dot(t_abstract), i);
        }
        return foo;
    }
}

Expr AbstractVectorial::addition_own(const Expr& t_abstract) const
{
    if (!exactMatchShape(t_abstract))
    {
        cout<<"Warning: shapes do not match in addition_own.\n";
        return ZERO;
    }
    Expr foo = tensor_(getShape());
    if (t_abstract->getDim() == 0)
    {
        if (dim == 1)
        {
            for (int i=0; i<nArgs; i++)
                foo->setArgument(plus_(t_abstract, argument[i]),i);
            return foo;
        }
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->addition_own(t_abstract));
        return foo;
    }
    if (dim == 1)
    {
        for (int i=0; i<nArgs; i++)
            foo->setArgument(plus_(argument[i],(*t_abstract)[i]),i);
    }
    else
    {
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->addition_own((*t_abstract)[i]),i);
    }
    return foo;
}

Expr AbstractVectorial::multiplication_own(const Expr& t_abstract) const
{
    if (!exactMatchShape(t_abstract))
    {
        cout<<"Warning: shapes do not match in multiplication_own.\n";
        return ZERO;
    }
    Expr foo = tensor_(getShape());
    if (t_abstract->getDim() == 0)
    {
        if (dim == 1)
        {
            for (int i=0; i<nArgs; i++)
                foo->setArgument(times_(t_abstract, argument[i]),i);
            return foo;
        }
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->multiplication_own(t_abstract),i);
        return foo;
    }
    if (dim == 1)
    {
        for (int i=0; i<nArgs; i++)
            foo->setArgument(times_(argument[i],(*t_abstract)[i]),i);
    }
    else
    {
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->multiplication_own((*t_abstract)[i]),i);
    }

    return foo;
}

Expr AbstractVectorial::tensor_dot(const Expr& t_abstract) const
{
    if (t_abstract->getDim() == 0)
        return multiplication_own(t_abstract);
    vector<int> shape = getShape();
    vector<int> shape2 = t_abstract->getShape();
    shape.insert(shape.end(), shape2.begin(), shape2.end());
    Expr foo = tensor_(shape);
    if (dim > 1)
    {
        for (int i=0; i<nArgs; i++)
            foo->setArgument(argument[i]->tensor_dot(t_abstract),i);
    }
    else
    {
        for (int i=0; i<nArgs; i++)
            foo->setArgument(t_abstract->multiplication_own(argument[i]),i);
    }
    
    return foo;
}

Expr AbstractVectorial::trace(int axis1, int axis2) const
{
    if (axis1 > dim or axis2 > dim)
    {
        cout<<"Warning: taking trace of axis out of scope.\n";
        return ZERO;
    }
    vector<int> shape = getShape();
    vector<int> newShape = shape;
    for (int i=0; i<dim; i++)
        if (i == axis1 or i == axis2)
            newShape[i] = 1;
    for (size_t i=0; i<newShape.size(); i++)
    {
        if (newShape[i] == 1)
        {
            newShape.erase(newShape.begin()+i);
            i--;
        }
    }

    Expr foo = tensor_(newShape);
    vector<int> indices(dim, -1);
    if (axis1 == axis2)
    {
        for (int i=0; i<shape[axis1]; i++)
        {
            indices[axis1] = i;
            foo = plus_(foo, getArgument(indices));
        }

        return foo;
    }
    if (shape[axis1] != shape[axis2])
    {
        cout<<"Warning: taking trace of non-equivalent dimensions.\n";
        return ZERO;
    }
    if (axis2 < axis1)
    {
        int foo = axis1;
        axis1 = axis2;
        axis2 = foo;
    }
    for (int i=0; i<shape[axis1]; i++)
    {
        indices[axis1] = i;
        indices[axis2] = i;
        foo = plus_(foo, getArgument(indices));
    }

    return foo;
}

Expr AbstractVectorial::develop(bool full)
{
    Expr foo = tensor_(getShape());
    for (int i=0; i<nArgs; i++)
        foo->setArgument(argument[i]->develop(full), i);

    return foo;
}

Expr AbstractVectorial::factor(bool full)
{
    Expr foo = tensor_(getShape());
    for (int i=0; i<nArgs; i++)
        foo->setArgument(argument[i]->factor(full), i);

    return foo;
}

Expr AbstractVectorial::factor(const Expr& t_abstract, bool full)
{
    Expr foo = tensor_(getShape());
    for (int i=0; i<nArgs; i++)
        foo->setArgument(argument[i]->factor(t_abstract,full), i);

    return foo;
}

bool AbstractVectorial::operator==(const Expr& t_abstract) const
{
    if (t_abstract->getName() == WHATEVER->getName()) return true;
    if (dim != t_abstract->getDim() or nArgs != t_abstract->getNArgs()) return false;
    for (int i=0; i<nArgs; i++)
        if (*argument[i] != t_abstract->getArgument(i))
            return false;
    return true;
}

Expr AbstractVectorial::operator[](int iArg)
{
    if (iArg < 0 or iArg >= nArgs) {
        print();
        callError(smError::OutOfBounds, "AbstractVectorial::operator[](int iArg)", iArg);
    }
    return argument[iArg];
}

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

Vector::Vector(int t_nElements, const Expr& t_abstract, const Expr& index): Vector()
{
    if (t_abstract->getDim() > 0) {
        print();
        callError(smError::ElementSequence, "Vector::Vector(int t_nElements, const Expr& t_abstract, const Expr& index): Vector()");
    }
    else {
        nArgs = t_nElements;
        argument = vector<Expr >(nArgs, t_abstract);
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
        callError(smError::ElementSequence, "Vector::Vector(const vector<Expr >& t_argument): Vector()");
    }
    else {
        argument = t_argument;
        nArgs = argument.size();
        shape = vector<int>(1,nArgs);
    }
}

Expr Vector::getSubVectorial(int iExcept) const
{
    if (nArgs == 2) return argument[1-iExcept];
    Expr foo = _vector_(nArgs-1);
    for (int i=0; i<nArgs; i++)
    {
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

Expr vector_(int t_nElements,const Expr& t_abstract, const Expr& index)
{
    return make_shared<Vector>(t_nElements, t_abstract, index);
}

Expr vector_(const vector<Expr >& t_argument)
{
    return make_shared<Vector>(t_argument);
}

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

Matrix::Matrix(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y): Matrix()
{
    if (t_abstract->getDim() != 0) {
        print();
        callError(smError::ElementSequence,"Matrix::Matrix(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y): Matrix()");
    }
    else {
        nArgs = t_x_nArgs;
        argument = vector<Expr >(nArgs);
        Expr foo;
        for (iter it=argument.begin(); it!=argument.end(); ++it) {
            foo = Replace(t_abstract, index_x, int_(distance(argument.begin(),it)));
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
    if (!dimOk)
    {
        print();
        callError(smError::ElementSequence,"Matrix::Matrix(const vector<Expr >& t_argument): Matrix()");
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
    if (newShape[0] == 1) return argument[1-iExcept]->getSubVectorial(jExcept);
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
    if (nArgs != argument[0]->getNArgs())
    {
        cout<<"Warning: taking determinant of non-square matrix.\n";
        return ZERO;
    }
    Expr foo = ZERO;
    if (nArgs > 2 and argument[0]->getNArgs() > 2)
    {
        for (int i=0; i<nArgs; i++)
            foo = plus_(foo, times_(argument[i]->getArgument(0),times_(int_(pow(-1,i)),getSubVectorial(i,0)->determinant())));    
    }
    else
    {
        for (int i=0; i<nArgs; i++)
            foo = plus_(foo, times_(argument[i]->getArgument(0),times_(int_(pow(-1,i)),getSubVectorial(i,0))));    
    }
    return foo;
}

Expr Matrix::trace() const
{
    if (nArgs != argument[0]->getNArgs())
    {
        cout<<"Warning: taking the trace of non-square matrix.\n";
        return ZERO;
    }
    Expr foo = ZERO;
    for (int i=0; i<nArgs; i++)
        foo = plus_(foo, argument[i]->getArgument(i));

    return foo;
}

Expr Matrix::transpose() const
{
    vector<int> newShape(shape);
    int fooInt = newShape[0];
    newShape[0] = newShape[1];
    newShape[1] = fooInt;
    Expr foo = tensor_(newShape);
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            foo->setArgument(getArgument({j,i}),{i,j});

    return foo;
}

Expr Matrix::transposedCoMatrix() const
{
    Expr foo = tensor_(getShape());
    if (nArgs > 2 and argument[0]->getNArgs() > 2) 
        for (int i=0; i<nArgs; i++)
            for (int j=0; j<argument[0]->getNArgs(); j++)
                foo->setArgument(times_(getSubVectorial(i,j)->determinant(),int_(pow(-1,i+j))),{j,i});
    else 
        for (int i=0; i<nArgs; i++) 
            for (int j=0; j<argument[0]->getNArgs(); j++) 
                foo->setArgument(times_(getSubVectorial(i,j),int_(pow(-1,i+j))),{j,i});

    return foo;
}

Expr Matrix::inverseMatrix() const
{
    Expr det = determinant();
    if (det->getPrimaryType() == smType::Numerical and det->evaluateScalar() == 0)
    {
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

Expr matrix_(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y)
{
    return make_shared<Matrix>(t_x_nArgs, t_y_nArgs, t_abstract, index_x, index_y);
}

Expr matrix_(const vector<Expr >& t_argument)
{
    return make_shared<Matrix>(t_argument);
}

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
            shape.insert(shape.end(), followingShape.begin(), followingShape.end());
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
    return make_shared<HighDTensor>(t_argument);
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
