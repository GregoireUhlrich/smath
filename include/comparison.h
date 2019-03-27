#ifndef COMPARISON_H_INCLUDED
#define COMPARISON_H_INCLUDED

#include "abstract.h"
#include "variable.h"
#include "supportIndicial.h"

class Arbitrary: public AbstractLiteral{

    public:

    explicit Arbitrary(int n);
    ~Arbitrary(){};

    smType::Type getType() const override;
    void print(int mode=0) const override;
    std::string printLaTeX(int mode=0) const override;
    Expr evaluate() override;

    int getNum() const override;

    bool operator==(const Expr& expr) const override;
    bool operator<(const Expr& expr) const override;
    bool operator>(const Expr& expr) const override;


    private:

    int number;
};

class smComparator{

    public:

    static Expr dummy(int n);

    static bool compare(const Expr& expr, const constExpr& dummy);
    static bool dummyComparison(const Expr& expr, const Expr& dummyExpr);

    static void clear();

    public:

    static std::string dummyName;

    private:

    static bool dummyComparisonActive;

    static std::map<int,Expr> arbitrary;
    static std::map<int,Expr> correspondance;

};

#endif
