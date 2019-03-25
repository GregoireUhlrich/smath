#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "abstract.h"
#include "equation.h"

class Property{

    protected:

    Equation eq;

    public:

    Property();
    Property(const Equation& t_eq);
    Property(const Expr& leftHandSide, const Expr& rightHandSide);
    //Property(const Property& p) = delete;
    //Property& operator=(const Property& p) = delete;
    ~Property(){};

    Expr apply(const Expr& expr) const;
};

class PropertyList{

    protected:

        // Singleton class
    static PropertyList* self;
    std::vector<Property> props;

    private:

    PropertyList();
    ~PropertyList();

    public:

    static PropertyList* Construct();
    void addProperty(const Property& property);
    void removeProperty(const Property& property);

    friend std::ostream& operator<<(std::ostream& fout, const PropertyList& prop);
};

PropertyList* PropertyList::self = nullptr;
static PropertyList* PROPERTIES = PropertyList::Construct();

#endif
