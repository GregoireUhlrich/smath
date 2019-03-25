#include "property.h"
#include "indicial.h"

using namespace std;

Property::Property(): eq(){}

Property::Property(const Equation& t_eq): eq(t_eq)
{
    if (eq.getType() != smEquation::Equal)
        callError(smError::BadPropertySetting,
                "Property::Property(const Equation&)",
                eq.getType());

    eq.makeLHSimple();
}

Property::Property(const Expr& leftHandSide, const Expr& rightHandSide)
    :Property(Equation(leftHandSide, rightHandSide)){}

Expr Property::apply(const Expr& expr) const
{
    // To implement
   return expr; 
}


PropertyList::PropertyList(): props(vector<Property>(0)){}

PropertyList::~PropertyList()
{}

PropertyList* PropertyList::Construct()
{
    if (not self)
        return new PropertyList();
    else
        return self;
}

void PropertyList::addProperty(const Property& property)
{
    props.push_back(property);
}

void PropertyList::removeProperty(const Property& property)
{
}
