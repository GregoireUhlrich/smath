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

    int getDim() const override { return dim;}

    PrimaryType getPrimaryType() const override { return VECTORIAL;}

    int getNArgs(int axis=0) const override;

    Expr getArgument(int iArg=0) const override;

    Expr getArgument(const std::initializer_list<int>& indices) const override;

    Expr getArgument(const std::vector<int>& indices) const override;

    const std::vector<Expr >& getVectorArgument() const override;

    std::vector<int> getShape() const override;

    void setArgument(const Expr& t_abstract, int iArg=0) override;

    void setArgument(const Expr& t_abstract, const std::initializer_list<int>& indices) override;

    void setArgument(const Expr& t_abstract, const std::vector<int>& indices) override;

    void setVectorArgument(const std::vector<Expr >& t_argument) override;

    bool matchShape(const Expr& t_abstract, bool exact=false) const override;

    bool exactMatchShape(const Expr& t_abstract) const;

    Expr getSum() const override;

    Expr getProduct() const override;

    Expr getSubVectorial(const std::vector<int>& exceptions) const override;

    Expr getVectorialModulus() const override;

    Expr dot(const Expr& t_abstract) const override;

    Expr addition_own(const Expr& t_abstract) const override;

    Expr multiplication_own(const Expr& t_abstract) const override;

    Expr tensor_dot(const Expr& t_abstract) const override;

    Expr trace(int axis1, int axis2) const override;

    Expr develop(bool full=false) override;

    Expr factor(bool full=false) override;

    Expr factor(const Expr& t_abstract, bool full=false) override;

    bool operator==(const Expr& t_abstract) const override;

    Expr operator[](int iArg) override;
};

class Vector: public AbstractVectorial{

    public:

    Vector();

    explicit Vector(int t_nElements);

    Vector(int t_nElements, const Expr& t_abstract, const Expr& index);

    explicit Vector(const std::vector<Expr >& t_argument);

    ~Vector(){};

    Type getType() const override { return VECTOR;}

    using AbstractVectorial::getSubVectorial;
    Expr getSubVectorial(int iExcept) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

Expr _vector_(int t_nElements);

Expr vector_(int t_nElements,const Expr& t_abstract, const Expr& index);

Expr vector_(const std::vector<Expr >& t_argument);

class Matrix: public AbstractVectorial{

    public:

    Matrix();

    explicit Matrix(int t_nArgs);

    Matrix(int t_x_nArgs, int t_y_nArgs);

    Matrix(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y);

    explicit Matrix(const std::vector<Expr >& t_argument);

    ~Matrix(){};

    Type getType() const override { return MATRIX;}

    Expr determinant() const override;

    using AbstractVectorial::trace;
    Expr trace() const override;

    Expr transpose() const override;

    Expr transposedCoMatrix() const;

    Expr inverseMatrix() const override;

    Expr symmetrise() const override;

    Expr antisymmetrise() const override;

    using AbstractVectorial::getSubVectorial;
    Expr getSubVectorial(int iExcept, int jExcept) const override;

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

Expr _matrix_(int t_nArgs);

Expr _matrix_(int t_x_nArgs, int t_y_nArgs);

Expr matrix_(int t_x_nArgs, int t_y_nArgs, const Expr& t_abstract, const Expr& index_x, const Expr& index_y);

Expr matrix_(const std::vector<Expr >& t_argument);

class HighDTensor: public AbstractVectorial{

    public:

    HighDTensor();

    explicit HighDTensor(const std::vector<int>& shape);

    explicit HighDTensor(const std::vector<Expr >& t_argument);

    ~HighDTensor(){};

    Type getType() const override { return HIGHDTENSOR;}

    bool operator>(const Expr& t_abstract) const override;

    bool operator<(const Expr& t_abstract) const override;
};

Expr highDTensor(const std::vector<int>& shape);

Expr highDTensor_(const std::vector<Expr >& t_argument);

Expr tensor_(const std::vector<int>& shape);

#endif
