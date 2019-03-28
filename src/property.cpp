#include "property.h"
#include "equation.h"
#include "indicial.h"

using namespace std;

PropertyList::PropertyList(): props(vector<Equation>(0)){}

PropertyList::~PropertyList()
{}

void PropertyList::addProperty(const Equation& property)
{
    vector<Expr> BB = property.getBuildingBlocks();
    const size_t size = props.size();
    for (const auto& bb : BB) {
        Equation newProp = property;
        newProp.isolate(bb);
        if (newProp != property) {
            newProp.setBuildingBlocks(vector<Expr>(1,bb));
            props.push_back(newProp);
            bb->addProperty(new Equation(props[props.size()-1]));
        }
    }
    if (size == props.size()) {
        props.push_back(property);
        for (const auto& bb : property.getBuildingBlocks())
            bb->addProperty(new Equation(props[props.size()-1]));
    }
}

void PropertyList::removeProperty(const Equation& property)
{ 
    vector<Expr> BB = property.getBuildingBlocks();
    for (const auto& bb : BB) {
        Equation newProp = property;
        newProp.isolate(bb);
        if (newProp != property) {
            bb->removeProperty(new Equation(props[props.size()-1]));
            for (auto iter=props.begin(); iter!=props.end(); ++iter)
                if (*iter == newProp)
                    props.erase(iter);
        }
    }
}

vector<Expr> PropertyList::apply(const Expr& expr) const
{
    const vector<Expr>& buildingBlocks = listBuildingBlocks(expr);
    if (buildingBlocks.size() == 0)
        return vector<Expr>(0);

    vector<Expr> res(0);
    for (const auto& bb : buildingBlocks) {
        vector<Equation*> propsToApply = bb->getProperties();
        for (const auto& p : propsToApply) {
            Expr foo = expr->findSubExpression(p->getLHS(), p->getRHS());
            if (*foo != expr)
                res.push_back(foo);
        }
    }

    return res;
}

ostream& operator<<(ostream& fout, const PropertyList& props)
{
    for (const auto& p : props.props)
        cout<<p<<endl;

    return fout;
}
