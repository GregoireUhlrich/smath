#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "abstract.h"
#include "variable.h"
#include "operations.h"
#include "mathFunctions.h"
#include "support.h"

class AbstractVectorial: public Abstract{

    protected:

    int dim;
    int nArgs;
    std::vector<Expr > argument;
    std::vector<int> shape;

    public:

    AbstractVectorial();
    ~AbstractVectorial(){};

    void print(int mode=0) const override;

    std::string printLaTeX(int mode=0) const override;

    Expr evaluate() override;

    int getDim() const { return dim;}

    PrimaryType getPrimaryType() const { return VECTORIAL;}

    int getNArgs(int axis=0) const override;

    const Expr& getArgument(int iArg=0) const override;

    Expr getArgument(const std::initializer_list<int>& indices) const override;

    Expr getArgument(const std::vector<int>& indices) const override;

    const std::vector<Expr >& getVectorArgument() const override;

    std::vector<int> getShape() const;

    void setArgument(const Expr& t_abstract, int iArg=0) override;

    void setArgument(const Expr& t_abstract, const std::initializer_list<int>& indices) override;

    void setArgument(const Expr& t_abstract, const std::vector<int>& indices) override;

    void setVectorArgument(const std::vector<Expr >& t_argument) override;

    bool matchShape(const Expr& t_abstract, bool exact=false) const override;

    bool exactMatchShape(const Expr& t_abstract) const;

    Expr getSum() const;

    Expr getProduct() const;

    Expr getSubVectorial(const std::vector<int>& exceptions) const;

    Expr getVectorialModulus() const;

    Expr dot(const Expr& t_abstract) const;

    Expr addition_own(const Expr& t_abstract) const override;

    Expr multiplication_own(const Expr& t_abstract) const override;

    Expr tensor_dot(const Expr& t_abstract) const;

    Expr trace(int axis1, int axis2) const;

    Expr develop(bool full=false) const;

    Expr factor(bool full=false) const;

    Expr factor(const Expr& t_abstract, bool full=false) const;

    bool operator==(const Expr& t_abstract) const;
};

class Vector: public AbstractVectorial{

    public:

    Vector();

    Vector(int t_nElements);

    Vector(int t_nElements, const Expr& t_abstract, const Expr& index);

    Vector(const std::vector<Expr >& t_argument);

    ~Vector(){};

    Type getType() const { return VECTOR;}

    Expr getSubVectorial(int iExcept) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

Expr _vector_(int t_nElements);

Expr vector_(int t_nElements,const Expr& t_abstract, const Expr& index);

Expr vector_(const std::vector<Expr >& t_argument);

class Matrix: public AbstractVectorial{

    public:

    Matrix();

    Matrix(int t_nArgs);

    Matrix(int t_x_nArgs, int t_y_nArgs);

    Matrix(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y);

    Matrix(const std::vector<Expr >& t_argument);

    ~Matrix(){};

    Type getType() const { return MATRIX;}

    Expr determinant() const;

    Expr trace() const;

    Expr transpose() const;

    Expr transposedCoMatrix() const;

    Expr inverseMatrix() const;

    Expr symmetrise() const;

    Expr antisymmetrise() const;

    Expr getSubVectorial(int iExcept, int jExcept) const;

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

Expr _matrix_(int t_nArgs);

Expr _matrix_(int t_x_nArgs, int t_y_nArgs);

Expr matrix_(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y);

Expr matrix_(const std::vector<Expr >& t_argument);

class HighDTensor: public AbstractVectorial{

    public:

    HighDTensor();

    HighDTensor(const std::vector<int>& shape);

    HighDTensor(const std::vector<Expr >& t_argument);

    ~HighDTensor(){};

    Type getType() const { return HIGHDTENSOR;}

    bool operator>(const Expr& t_abstract) const;

    bool operator<(const Expr& t_abstract) const;
};

Expr highDTensor(const std::vector<int>& shape);

Expr highDTensor_(const std::vector<Expr >& t_argument);

Expr tensor_(const std::vector<int>& shape);

#endif
