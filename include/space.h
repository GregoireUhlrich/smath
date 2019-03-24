#ifndef SPACE_H_INCLUDED
#define SPACE_H_INCLUDED

#include "indicial.h"
#include "vector.h"

// Only using Space* type. Non-copyable class, One space corresponds to only
// one instance --> comparison of spaces <==> comparison of pointers.
class Space{

    private:

    std::string name;
    int dim;
    bool signedIndex;

    public:

    const IndicialParent metric;

    Space() = delete;
    Space(const Space&) = delete;
    Space(const std::string& t_name, int t_dim);
    Space(const std::string& t_name, int t_dim, 
          const std::string& name_metric, const Expr& t_metric);
    ~Space(){};

    std::string getName() const;
    int getDim() const;
    bool getSignedIndex() const;

    Space& operator=(const Space&) = delete;
};

///////////////////////////////////////////////////
//// Inline functions
///////////////////////////////////////////////////

inline Space::Space(const std::string& t_name, int t_dim)
    :name(t_name), dim(t_dim), signedIndex(false) 
{}

//Space with metric
inline Space::Space(const std::string& t_name, int t_dim,
        const std::string& name_metric, const Expr& t_metric)
    :name(t_name), dim(t_dim), signedIndex(true),
    metric(name_metric, this, t_metric) 
{}

inline std::string Space::getName() const {
    return name;
}

inline int Space::getDim() const {
    return dim;
}

inline bool Space::getSignedIndex() const {
    return signedIndex;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////


static const Space Euclid_R("R", 1);
static const Space Euclid_R2("R2", 2);
static const Space Euclid_R3("R3", 3);
static const Space Euclid_R4("R4", 4);
static const Space Minkowski("R1,3",4,"g",matrix_({{int_(-1),ZERO,ZERO,ZERO},
                                              {ZERO,ONE,ZERO,ZERO},
                                              {ZERO,ZERO,ONE,ZERO},
                                              {ZERO,ZERO,ZERO,ONE}}));
        
#endif
