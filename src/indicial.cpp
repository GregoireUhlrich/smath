#include "indicial.h"
#include "error.h"
#include "space.h"
#include "equation.h"
#include "variable.h"
#include "comparison.h"
#include "commutation.h"

using namespace std;

void nameTensor(const string& name, Expr& tensor, bool first)
{
    if (tensor->getPrimaryType() != smType::Vectorial)
        callError(smError::UndefinedBehaviour,
                "nameTensor(const string&, Expr&)");
    if (tensor->getDim() == 1) {
        if (first)
            for (iter arg=tensor->begin(); arg!=tensor->end(); ++arg) {
                ostringstream sout;
                sout<<distance(tensor->begin(), arg);
                (*arg) = var_(name+"_"+sout.str());
            }
        else
            for (iter arg=tensor->begin(); arg!=tensor->end(); ++arg) {
                ostringstream sout;
                sout<<distance(tensor->begin(), arg);
                (*arg) = var_(name+","+sout.str()+"}");
            }
    }
    else {
        if (first)
            for (iter arg=tensor->begin(); arg!=tensor->end(); ++arg) {
                ostringstream sout;
                sout<<distance(tensor->begin(), arg);
                nameTensor(name+"_{"+sout.str(), *arg, false);
            }
        else
            for (iter arg=tensor->begin(); arg!=tensor->end(); ++arg) {
                ostringstream sout;
                sout<<distance(tensor->begin(), arg);
                nameTensor(name+","+sout.str(), *arg, false);
            }
    }
}

Expr generateTensor(const string& name, const vector<const Space*>& spaces)
{
    vector<int> shape(0);
    for (const auto& s : spaces)
        shape.push_back(s->getDim());

    Expr tensor = tensor_(shape);
    nameTensor(name, tensor);
    tensor->print();

    return tensor;
}

///////////////////////////////////////////////////
/*************************************************/
// Class IndicialParent                        //
/*************************************************/
///////////////////////////////////////////////////

IndicialParent::IndicialParent(): name(""), commutable(true), dim(0), 
    space(vector<const Space*>(0)), symmetry(), fullySymmetric(false),
    fullyAntiSymmetric(false), valued(false)
{}

IndicialParent::IndicialParent(const string& t_name): name(t_name),
    commutable(true), dim(0), space(vector<const Space*>(0)), symmetry(),
    fullySymmetric(false), fullyAntiSymmetric(false), valued(false)
{}

IndicialParent::IndicialParent(const string& t_name,
                               const Space* t_space)
    :name(t_name), commutable(true), dim(1), space(vector<const Space*>(1,t_space)),
    symmetry(), fullySymmetric(false), fullyAntiSymmetric(false), valued(false)
{
    tensor = generateTensor(name,space);
}

IndicialParent::IndicialParent(const string& t_name,
                               const std::initializer_list<const Space*> t_space)
    :name(t_name), commutable(true), dim(t_space.size()), space(t_space),
    symmetry(), fullySymmetric(false), fullyAntiSymmetric(false), valued(false)
{
    tensor = generateTensor(name,space);
}

IndicialParent::IndicialParent(const string& t_name,
                               const Space* t_space,
                               const Expr& t_tensor)
    :name(t_name), commutable(true), dim(2), space(vector<const Space*>(2,t_space)),
    symmetry(), fullySymmetric(true), fullyAntiSymmetric(false), valued(true)
{
    if (t_tensor->getType() != smType::Matrix
            or t_tensor->getShape() != vector<int>(2,t_space->getDim())) {
        callError(smError::InvalidIndicialParent,
                "IndicialParent(const string&, const Space*, const Expr&)");
    }
    tensor = t_tensor;
}


string IndicialParent::getName() const {
    return name;
}

bool IndicialParent::getCommutable() const {
    return commutable;
}

int IndicialParent::getDim() const {
    return dim;
}

bool IndicialParent::getFullySymmetric() const {
    return fullySymmetric;
}
bool IndicialParent::getFullyAntiSymmetric() const {
    return fullyAntiSymmetric;
}

vector<Permutation> IndicialParent::getPermutation() const {
    return symmetry.getPermutation();
}

void IndicialParent::setName(const std::string& t_name) {
    name = t_name;
}
void IndicialParent::setCommutable(bool t_commutable) {
    commutable = t_commutable;
}

void IndicialParent::setFullySymmetric() {
    fullySymmetric = true;
    fullyAntiSymmetric = false;
}
void IndicialParent::setFullyAntiSymmetric() {
    fullySymmetric = false;
    fullyAntiSymmetric = true;
}
void IndicialParent::addSymmetry(int i1, int i2)
{
    if (fullySymmetric) 
        return;
    if (fullyAntiSymmetric) 
        fullyAntiSymmetric = false;

    if (i1 < 0 or i2 < 0 or 
        i1 >= dim or i2 >= dim)
        callError(smError::OutOfBounds,"IndicialParent::addSymmetry(int i1, int i2)",
                (i1<0 or i1>=dim) ? i1 : i2);
}
void IndicialParent::addAntiSymmetry(int i1, int i2)
{
    if (fullyAntiSymmetric) return;
    if (fullySymmetric) fullySymmetric = false;
    if (i1 < 0 or i2 < 0 or 
        i1 >= dim or i2 >= dim)
        callError(smError::OutOfBounds,"ITensor::addAntiSymmetry(int i1, int i2)",
                (i1<0 or i1>=dim) ? i1 : i2);
}

const vector<Equation*>& IndicialParent::getProperties() const
{
    return props;
}

void IndicialParent::addProperty(Equation* property)
{
    for (const auto& p : props)
        if (*p == *property)
            return;
    props.push_back(property);
}

void IndicialParent::removeProperty(Equation* property)
{
    auto p = find(props.begin(), props.end(), property);
    if (p != props.end())
        props.erase(p);
}

void IndicialParent::setSymmetry(const Symmetry& t_symmetry)
{
    if (t_symmetry.getDim() != dim)
        callError(smError::BadSymmetry,
                "IndicialParent::setSymmetry(const Symmetry& t_symmetry)");
    symmetry = t_symmetry;
    fullySymmetric = false;
    fullyAntiSymmetric = false;
}

Expr IndicialParent::operator()(const Idx& index)
{
    if (dim != 1)
        callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Idx>& indices) const");
    if (index->getSpace() != space[0])
            callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Idx>& indices) const");

    Idx copyIndex = make_shared<Index>(*index);
    return make_shared<ITensor>(name, commutable, copyIndex, this);
}

Expr IndicialParent::operator()(const initializer_list<Idx>& indices)
{
    if (indices.size() != (size_t)dim) {
        callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Idx>& indices) const");
    }
    for (auto index=indices.begin(); index!=indices.end(); ++index)
        if ((*index)->getSpace() != space[distance(indices.begin(), index)])
            callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Idx>& indices) const");

    vector<Idx> copyIndices(0);
    for (const auto& index : indices)
        copyIndices.push_back(make_shared<Index>(*index));

    return make_shared<ITensor>(name, commutable, copyIndices, this);
}


////////////////////////////////////////////////////
///*************************************************/
// Class AbstractIndicial                          //
///*************************************************/
/////////////////////////////////////////////////////

AbstractIndicial::AbstractIndicial(): AbstractBuildingBlock() 
{}

AbstractIndicial::AbstractIndicial(const string& t_name)
    :AbstractBuildingBlock(t_name)
{}

AbstractIndicial::AbstractIndicial(const IndexStructure& t_index)
    :AbstractBuildingBlock(), index(t_index)
{}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const IndexStructure& t_index)
    :AbstractBuildingBlock(t_name), index(t_index)
{}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const Idx& t_index)
    :AbstractBuildingBlock(t_name), nIndices(1), index(vector<Idx>(1,t_index))
{}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const vector<Idx>& indices)
    :AbstractBuildingBlock(t_name), nIndices(indices.size()), index(indices)
{}

bool AbstractIndicial::compareWithDummy(const Expr& expr,
        map<Index,Index>& constraints) const
{
    if (name != expr->getName())
        return false;
    return index.compareWithDummy(expr->getIndexStructure(), constraints);
}

///////////////////////////////////////////////////
/*************************************************/
// Class ITensor                                 //
/*************************************************/
///////////////////////////////////////////////////

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const Idx& t_index,
                 IndicialParent *const t_parent)
    :AbstractIndicial(t_name, t_index), contractions(vector<Abstract*>(1)),
    parent(t_parent)
{
    commutable = t_commutable;
}

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const vector<Idx>& indices,
                 IndicialParent *const t_parent)
    :AbstractIndicial(t_name, indices), 
    contractions(vector<Abstract*>(indices.size())),
    parent(t_parent)
{
    commutable = t_commutable;
}

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const IndexStructure& indices,
                 IndicialParent *const t_parent)
    :AbstractIndicial(t_name, indices), 
    contractions(vector<Abstract*>(indices.getNIndices())),
    parent(t_parent)
{
    commutable = t_commutable;
}

// Constructor crashes if expr is not an ITensor
ITensor::ITensor(const Abstract*& expr)
    :ITensor(expr->getName(), expr->getCommutable(),
            expr->getIndexStructure(), expr->getParent())
{
    commutable = expr->getCommutable();
}


// Constructor crashes if expr is not an ITensor
ITensor::ITensor(const Expr& expr)
    :AbstractIndicial(expr->getName(), expr->getIndexStructure()),
    parent(expr->getParent())
{
    commutable = expr->getCommutable();
}

Idx ITensor::getIndex(int i) const
{
    if (i >= 0 and i < index.getNIndices()) 
        return index[i];
    callError(smError::OutOfBounds,"ITensor::getIndex(int i) const",i);
    return make_shared<Index>();
}

IndicialParent* ITensor::getParent() const {
    return parent;
}

const std::vector<Equation*>& ITensor::getProperties() const
{
    return parent->getProperties();
}

void ITensor::addProperty(Equation* property)
{
    parent->addProperty(property);
}

void ITensor::removeProperty(Equation* property) 
{
    parent->removeProperty(property);
}

bool ITensor::checkIndexStructure(const vector<Idx>& t_indices) const
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)t_indices.size()) 
        return false;
    vector<int> indicesLeft(nIndices);
    for (int i=0; i<nIndices;i++) 
        indicesLeft[i] = i;

    for (int i=0; i<nIndices; i++) {
        if (index[i]->getFree()) {
            bool matched = 0;
            for (size_t j=0; j<indicesLeft.size(); j++) {
                Idx foo = t_indices[indicesLeft[j]];
                if (not foo->getFree() or *index[i] == *foo) {
                    indicesLeft.erase(indicesLeft.begin()+j);
                    matched = 1;
                    break;
                }
            }
            if (!matched) 
                return false;
        }
    }
    return true;
}

bool ITensor::checkIndexStructure(
        const initializer_list<Idx>& t_indices) const 
{
    return checkIndexStructure(vector<Idx>(t_indices.begin(), t_indices.end()));
}

bool ITensor::replaceIndex(const Idx& indexToReplace,
                            const Idx& newIndex)
{
    for (int i=0; i!=nIndices; ++i)
        if (*index[i] == *indexToReplace) {
            index[i] = newIndex;
            return true;
        }

    return false;
}

void ITensor::setIndexStructure(const IndexStructure& t_index)
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)t_index.getNIndices())
        callWarning(smError::InvalidDimension,
                "ITensor::setIndexStructure(const std::vector<Index>&)",
                t_index.getNIndices());
    else 
        index = IndexStructure(t_index);
}

Expr ITensor::applyPermutation(const Permutation& permutation) const
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)permutation.getSize())
        callWarning(smError::InvalidDimension,
                "ITensor::applyPermutation(const vector<int>& permutations) const",
                permutation.getSize());
    else {
        IndexStructure newIndex(nIndices);
        for (int i=0; i!=nIndices; ++i)
            newIndex[i] = index[permutation[i]];
        Expr res = make_shared<ITensor>(*this);
        res->setIndexStructure(newIndex);
        return res;
    }

    return ZERO;
}

vector<Expr> ITensor::getPermutations() const
{
    vector<Expr> res(1,Copy(this));
    if (parent->getFullySymmetric() or parent->getFullyAntiSymmetric()) {
        const int nIndices = index.getNIndices();
        Permutation initPerm(nIndices);
        for (int i=0; i!=nIndices; ++i)
            initPerm[i] = i;
        vector<Permutation > perm = permutations(initPerm);
        res = vector<Expr>(0);
        bool getSign = parent->getFullyAntiSymmetric();
        for (size_t i=0; i!=perm.size(); ++i)
            if (getSign)
                res.push_back(int_(perm[i].getSign())
                        *applyPermutation(perm[i]));
            else
                res.push_back(applyPermutation(perm[i]));

        return res;
    }
    vector<Permutation> perm = parent->getPermutation();
    res.clear();
    for (size_t i=0; i!=perm.size(); ++i) {
        res.push_back(applyPermutation(perm[i]));
        if (perm[i].getSymmetry() == -1)
            res[i] = -1*res[i];
    }

    return res;
}

void ITensor::print(int mode) const
{
    const int nIndices = index.getNIndices();
    cout<<name;
    if (nIndices > 0) {
        cout<<"_";
        if (nIndices > 1) {
            cout<<"{";
            for (int i=0; i<nIndices; i++)
                index[i]->print();
            cout<<"}";
        }
        else 
            index[0]->print();
    }
    if (mode == 0)
        cout<<endl;
}

string ITensor::printLaTeX(int mode) const
{
    const int nIndices = index.getNIndices();
    ostringstream sout;
    sout<<name;
    if (nIndices > 0) {
        sout<<"_";
        if (nIndices > 1) {
            sout<<"{";
            for (int i=0; i<nIndices; i++)
                index[i]->print();
            sout<<"}";
        }
        else 
            index[0]->print();
    }
    if (mode == 0)
        sout<<endl;

    return sout.str();
}

Expr ITensor::evaluate()
{
    cout<<"Warning: evaluate function for ITensor not yet implemented.\n";
    return ZERO;
}

bool ITensor::operator==(const Expr& expr) const
{
    if (expr->getName() == smComparator::dummyName) 
        return expr->operator==(DummyCopy(this));
    if (expr->getType() != smType::ITensor) 
        return false;

    if (name != expr->getName()) 
        return false;

    return index.exactMatch(expr->getIndexStructure());
}

///////////////////////////////////////////////////
/*************************************************/
// Class ITimes                                  //
/*************************************************/
///////////////////////////////////////////////////

ITimes::ITimes(): Times(){}

ITimes::ITimes(const vector<Expr>& t_argument, bool explicitTimes)
    :Times(t_argument, explicitTimes)
{
    selfCheckIndexStructure();
}

ITimes::ITimes(const Expr& leftOperand, const Expr& rightOperand, 
               bool explicitTimes)
    :Times(leftOperand, rightOperand, explicitTimes)
{
    selfCheckIndexStructure();
}

bool ITimes::isIndexed() const
{
    return true;
}

IndexStructure ITimes::getIndexStructure() const
{
    IndexStructure structure;
    for (const auto& s : indexArgument)
        structure += s;

    return structure;
}

void ITimes::selfCheckIndexStructure()
{
    // Check the indexStructure of a product and apply Einstein's convention
    // in the case of a repeated index. This algorithm is O(N^2) with N the
    // total number of indices in the product (check for each index if it is
    // present elsewhere.

    //For each argument
    for (iter arg=argument.begin(); arg!=argument.end(); ++arg) {
        // We get its structure in fooStruct
        IndexStructure fooStruct = (*arg)->getIndexStructure();
        if ((*arg)->isIndexed()) {
            // Now we check for each new index if it is present before in
            // the structure, in which case we contract it
            // (Einstein's convention).
            // For each new index: 
            for (int k=0; k!=fooStruct.getNIndices(); ++k) {
                //For each former structure (former arguments)
                for (size_t i=0; i!=indexArgument.size(); ++i) {
                    const int nIndices = indexArgument[i].getNIndices();
                    bool breakValue = false;
                    // For each index in the structure
                    for (int j=0; j!=nIndices; ++j) {
                        // If the index is already present
                        if (*indexArgument[i][j] == *fooStruct[k]
                                and fooStruct[k]->getFree()) {
                            indexArgument[i][j]->testContraction(*fooStruct[k]);
                            breakValue = true;
                            break;
                        }
                    }
                    if (breakValue)
                        break;
                }
            }
            // We add fooStruct to the vector of structures
        }
        indexArgument.push_back(fooStruct);
    }
}
void ITimes::leftInsert(const Expr& expr)
{
    // If not numerical, we search for a similar term
    int max = nArgs;
    Expr term, exponent;
    getExponentStructure(expr, term, exponent);
    for (int i=0; i<nArgs; i++) {
        // We do not merge indicial expressions
        // Ai.Ai does not give (Ai)^2
        if (argument[i]->isIndexed())
            continue;
        Expr term2, exponent2;
        getExponentStructure(argument[i], term2, exponent2);
        if (*Commutation(expr, argument[i]) == ZERO) {
            // If we found the right term, it's done
            if (*term == term2) {
                argument[i] = pow_(term, exponent->addition_own(exponent2));
                if (*argument[i] == ONE) {
                    argument.erase(argument.begin()+i);
                    --nArgs;
                }
                return;
            }
        }
        else if (*term == term2) {
            argument[i] = pow_(term, exponent->addition_own(exponent2));
            if (*argument[i] == ONE) {
                argument.erase(argument.begin()+i);
                --nArgs;
            }
            return;
        }
        else {
            // max is the position not reachable because of commutation not trivial
            max = i;
            break;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    for (int i=0; i<max; i++) 
        if (expr < argument[i] or *Commutation(expr, argument[i]) != ZERO) {
            ++nArgs;
            argument.insert(argument.begin()+i, expr);
            return;
        }

    // no term is more complicated than expr, we put it at the end
    argument.insert(argument.begin()+max, expr);
    ++nArgs;
}
void ITimes::rightInsert(const Expr& expr)
{
    // If not numerical, we search for a similar term
    int max = -1;
    Expr term, exponent;
    getExponentStructure(expr, term, exponent);
    for (int i=nArgs-1; i>=0; --i) {
        // We do not merge indicial expressions
        // Ai.Ai does not give (Ai)^2
        if (argument[i]->isIndexed())
            continue;
        Expr term2, exponent2;
        getExponentStructure(argument[i], term2, exponent2);
        if (*Commutation(expr, argument[i]) == ZERO) {
            // If we found the right term, it's done
            if (*term == term2) {
                argument[i] = pow_(term, exponent->addition_own(exponent2));
                if (*argument[i] == ONE) {
                    argument.erase(argument.begin()+i);
                    --nArgs;
                }
                return;
            }
        }
        else if (*term == term2) {
            argument[i] = pow_(term, exponent->addition_own(exponent2));
            if (*argument[i] == ONE) {
                argument.erase(argument.begin()+i);
                --nArgs;
            }
            return;
        }
        else {
            // max is the position not reachable because of commutation not trivial
            max = i;
            break;
        }
    }

    // No term corresponds, we order correctly the new term in the sum
    for (int i=nArgs-1; i>max; --i)  {
        if (expr > argument[i] or *Commutation(expr, argument[i]) != ZERO) {
            ++nArgs;
            argument.insert(argument.begin()+i+1, expr);
            return;
        }
    }

    // no term is more complicated than expr, we put it at the end
    argument.insert(argument.begin()+max+1, expr);
    ++nArgs;
}

bool ITimes::mergeTerms()
{
    bool simplified = false;
    nArgs = argument.size();
    for (int i=0; i<nArgs; i++) {
        if (argument[i]->getType() == smType::Times) { 
            vector<shared_ptr<Abstract> > t_argument =
                argument[i]->getVectorArgument();

            for (int j=i-1; j>=0; --j)
                t_argument.insert(t_argument.begin(),argument[j]);
            for (int j=i+1; j<nArgs; ++j)
                t_argument.push_back(argument[j]);
            nArgs += argument[i]->getNArgs()-1;
            i += argument[i]->getNArgs()-1;
            argument = t_argument;
        }
    }
    bool numericalFactor = (argument[0]->getPrimaryType() == smType::Numerical);
    for (int i=numericalFactor; i<nArgs; i++) {
        if (argument[i]->getPrimaryType() == smType::Numerical) {
            if (!numericalFactor) {
                shared_ptr<Abstract> foo = argument[i];
                argument.erase(argument.begin()+i);
                argument.insert(argument.begin(),foo);
                numericalFactor = true;
                i--;
            }
            else {
                argument[0] = argument[0]->multiplication_own(argument[i]);
                argument.erase(argument.begin()+i);
                nArgs--;
                i--;
            }
        }
    }
    if (numericalFactor and argument[0]->evaluateScalar()==1 and nArgs > 1) {
        argument.erase(argument.begin());
        nArgs--;
    }
    else if (numericalFactor and argument[0]->evaluateScalar()==0) {
        argument = vector<shared_ptr<Abstract>>(1);
        argument[0] = ZERO;
        nArgs = 1;
        return false;
    }
    shared_ptr<Abstract> term, term2;
    shared_ptr<Abstract> factor, factor2;
    bool matched;
    for (int i=numericalFactor; i<nArgs-1; i++) {
        // We do not merge indicial expressions
        // Ai.Ai does not give (Ai)^2
        if (argument[i]->isIndexed())
            continue;
        factor = ONE;
        if (argument[i]->getType() == smType::Pow) { //Pow 
            term = argument[i]->getArgument(1);
            if (term->getPrimaryType() == smType::Numerical) {
                factor = term;
                term = argument[i]->getArgument();
            }
            else 
                term = argument[i];
        }
        else term = argument[i];
        for (int j=i+1; j<nArgs; j++) {
            if(*Commutation(argument[i], argument[j]) != ZERO)
                break;
            factor2 = ONE;
            if (argument[j]->getType() == smType::Pow) {  //Pow
                term2 = argument[j]->getArgument(1);
                if (term2->getPrimaryType() == smType::Numerical) {
                    factor2 = term2;
                    term2 = argument[j]->getArgument();
                }
                else 
                    term2 = argument[j];
            }
            else term2 = argument[j];
            if (*term==term2) {
                factor = factor->addition_own(factor2);
                matched = true;
                argument.erase(argument.begin()+j);
                j--;
                nArgs--;
            }
        }
        if (matched) {
            argument[i] = pow_(term, factor);
            if (*argument[i] == ONE and nArgs > 1){
                argument.erase(argument.begin()+i);
                --i;
                --nArgs;
            }
            simplified = true;
        } 
    }

    orderTerms();
    return simplified;
}

bool ITimes::operator==(const Expr& expr) const
{
    if (expr->getName() == smComparator::dummyName) 
        return expr->operator==(DummyCopy(this));
    if (nArgs == 1)
        return *argument[0]==expr;
    if (expr->getType() != smType::Times)
        return false;
    if (nArgs != expr->getNArgs())
        return false;

    vector<int> indicesLeft(nArgs);
    for (int i=0; i<nArgs;i++)
        indicesLeft[i] = i;

    Expr foo;
    map<Index,Index> constraints;
    bool checkIndexExpressions = false;
    if (isIndexed()) 
        checkIndexExpressions = true;
    for (int i=0; i<nArgs; i++) {
        bool matched = false;
        for (size_t j=0; j<indicesLeft.size(); j++) {
            foo = expr->getArgument(indicesLeft[j]);
            if (!argument[i]-> getCommutable() and
                !foo->getCommutable() and
                *argument[i]!=foo)
                if (argument[i]->getType() != smType::ITensor 
                        or foo->getType() != smType::ITensor
                        or foo->getName() != argument[i]->getName())
                    break;
            if ((not checkIndexExpressions
                        or not (argument[i]->getType() == smType::ITensor))
                    and *argument[i] == foo) {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = true;
                break;
            }
            else if (checkIndexExpressions 
                and argument[i]->getType() == smType::ITensor
                and foo->getType() == smType::ITensor)  {

                if (argument[i]->compareWithDummy(foo, constraints)) {
                    indicesLeft.erase(indicesLeft.begin()+j);
                    matched = true;
                    break;
                }
            }
            
        }
        if (not matched) return false;
    }

    if (checkIndexExpressions and not constraints.empty()) 
        for (auto it=constraints.begin(); it!=constraints.end(); ++it)
            if (it->first != it->second)
                return false;

    return true;
}

bool ITimes::partialComparison(const Expr& expr) const
{
    if (expr->getName() == WHATEVER->getName())
        return true;
    if (nArgs == 1)
        return *argument[0]==expr;
    if (expr->getType() != smType::Times)
        return false;

    int t_nArgs = expr->getNArgs();
    vector<int> indicesLeft(t_nArgs);
    for (int i=0; i<t_nArgs;i++)
        indicesLeft[i] = i;

    Expr foo;
    map<Index,Index> constraints;
    bool checkIndexExpressions = false;
    if (isIndexed()) 
        checkIndexExpressions = true;
    for (int i=0; i<nArgs; i++) {
        bool matched = false;
        for (size_t j=0; j<indicesLeft.size(); j++) {
            foo = expr->getArgument(indicesLeft[j]);
            if (!argument[i]-> getCommutable() and
                !foo->getCommutable() and
                *argument[i]!=foo)
                if (argument[i]->getType() != smType::ITensor 
                        or foo->getType() != smType::ITensor
                        or foo->getName() != argument[i]->getName())
                    break;
            if ((not checkIndexExpressions
                        or not (argument[i]->getType() == smType::ITensor))
                    and *argument[i] == foo) {
                indicesLeft.erase(indicesLeft.begin()+j);
                matched = true;
                break;
            }
            else if (checkIndexExpressions 
                and argument[i]->getType() == smType::ITensor
                and foo->getType() == smType::ITensor)  {

                if (argument[i]->compareWithDummy(foo, constraints)) {
                    indicesLeft.erase(indicesLeft.begin()+j);
                    matched = true;
                    break;
                }
            }
            
        }
        if (not matched)
            return false;
        else if (indicesLeft.size() == 0)
            break;
    }

    // If there is some constraints on dummy indices left (we found only 
    // one dummy of the pair), we check that there are the same.
    // Ex: A_i.B_%j != A_i.B_%k but A_i.B_%j == A_i.B_%j
    if (checkIndexExpressions and not constraints.empty()) 
        for (auto it=constraints.begin(); it!=constraints.end(); ++it)
            if (it->first != it->second)
                return false;

    return true;
}
