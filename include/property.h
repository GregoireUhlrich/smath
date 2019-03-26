#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "abstract.h"
#include "equation.h"

class PropertyList{

    protected:

    std::vector<Equation> props;

    public:

    PropertyList();
    ~PropertyList();

    void addProperty(const Equation& property);
    void removeProperty(const Equation& property);

    std::vector<Expr> apply(const Expr& expr) const;

    friend std::ostream& operator<<(std::ostream& fout, const PropertyList& prop);
};

static PropertyList PROPERTIES = PropertyList();

#endif
