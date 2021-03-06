/*! \file vector.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Objects handling vectors, matrices and higher-dimensional tensors.
 */
#ifndef Vector_H_INCLUDED
#define Vector_H_INCLUDED

#include "abstract.h"

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

    smType::PrimaryType getPrimaryType() const override{
        return smType::Vectorial;
    }

    int getNArgs(int axis=0) const override;

    iter begin() override;
    const_iter begin() const override
    {
        return argument.begin();
    }

    iter end() override;
    const_iter end() const override
    {
        return argument.end();
    }

    Expr getArgument(int iArg=0) const override;

    Expr getArgument(const std::initializer_list<int>& indices) const override;

    Expr getArgument(const std::vector<int>& indices) const override;

    const std::vector<Expr >& getVectorArgument() const override;

    std::vector<int> getShape() const override;

    void setArgument(const Expr& expr, int iArg=0) override;

    void setArgument(const Expr& expr,
                     const std::initializer_list<int>& indices) override;

    void setArgument(const Expr& expr,
                     const std::vector<int>& indices) override;

    void setVectorArgument(const std::vector<Expr >& t_argument) override;

    bool matchShape(const Expr& expr, bool exact=false) const override;

    bool exactMatchShape(const Expr& expr) const;

    Expr getSum() const override;

    Expr getProduct() const override;

    Expr getSubVectorial(const std::vector<int>& exceptions) const override;

    Expr getVectorialModulus() const override;

    Expr dot(const Expr& expr) const override;

    Expr addition_own(const Expr& expr) const override;

    Expr multiplication_own(const Expr& expr, bool side=1) const override;

    Expr tensor_dot(const Expr& expr) const override;

    Expr trace(int axis1, int axis2) const override;

    Expr develop(bool full=false) override;

    Expr factor(bool full=false) override;

    Expr factor(const Expr& expr, bool full=false) override;

    bool operator==(const Expr& expr) const override;

    Expr& operator[](int iArg) override;

    Expr operator[](int iArg) const override;
};

class Vector: public AbstractVectorial{

    public:

    Vector();

    explicit Vector(int t_nElements);

    Vector(int t_nElements, const Expr& expr, const Expr& index);

    explicit Vector(const std::vector<Expr >& t_argument);

    ~Vector(){};

    smType::Type getType() const override { return smType::Vector;}

    using AbstractVectorial::getSubVectorial;
    Expr getSubVectorial(int iExcept) const override;

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
};

Expr _vector_(int t_nElements);

Expr vector_(int t_nElements,const Expr& expr, const Expr& index);

Expr vector_(const std::vector<Expr >& t_argument);

Expr vector_(const std::initializer_list<Expr>& t_argument);

class Matrix: public AbstractVectorial{

    public:

    Matrix();

    explicit Matrix(int t_nArgs);

    Matrix(int t_x_nArgs, int t_y_nArgs);

    Matrix(int t_x_nArgs, int t_y_nArgs,
           const Expr& expr, 
           const Expr& index_x, const Expr& index_y);

    explicit Matrix(const std::vector<Expr >& t_argument);

    ~Matrix(){};

    smType::Type getType() const override {
       return smType::Matrix;
    }

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

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
};

Expr _matrix_(int t_nArgs);

Expr _matrix_(int t_x_nArgs, int t_y_nArgs);

Expr matrix_(int t_x_nArgs, int t_y_nArgs,
             const Expr& expr,
             const Expr& index_x, const Expr& index_y);

Expr matrix_(const std::vector<Expr >& t_argument);

Expr matrix_(const std::initializer_list<std::initializer_list<Expr> >&
        t_matrix);

class HighDTensor: public AbstractVectorial{

    public:

    HighDTensor();

    explicit HighDTensor(const std::vector<int>& shape);

    explicit HighDTensor(const std::vector<Expr >& t_argument);

    ~HighDTensor(){};

    smType::Type getType() const override { return smType::HighDTensor;}

    bool operator>(const Expr& expr) const override;

    bool operator<(const Expr& expr) const override;
};

Expr highDTensor(const std::vector<int>& shape);

Expr highDTensor_(const std::vector<Expr >& t_argument);

Expr tensor_(const std::vector<int>& shape);

#endif
