#include "indicial.h"
#include "error.h"
#include "space.h"

using namespace std;

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
{}

IndicialParent::IndicialParent(const string& t_name,
                               const std::initializer_list<const Space*> t_space)
    :name(t_name), commutable(true), dim(t_space.size()), space(t_space),
    symmetry(), fullySymmetric(false), fullyAntiSymmetric(false), valued(false)
{}

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

void IndicialParent::setSymmetry(const Symmetry& t_symmetry)
{
    if (t_symmetry.getDim() != dim)
        callError(smError::BadSymmetry,
                "IndicialParent::setSymmetry(const Symmetry& t_symmetry)");
    symmetry = t_symmetry;
    fullySymmetric = false;
    fullyAntiSymmetric = false;
}

Expr IndicialParent::operator()(const Idx& index) const
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

Expr IndicialParent::operator()(const initializer_list<Idx>& indices) const
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
                 const IndicialParent* t_parent)
    :AbstractIndicial(t_name, t_index), contractions(vector<Abstract*>(1)),
    parent(t_parent)
{
    commutable = t_commutable;
}

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const vector<Idx>& indices,
                 const IndicialParent* t_parent)
    :AbstractIndicial(t_name, indices), 
    contractions(vector<Abstract*>(indices.size())),
    parent(t_parent)
{
    commutable = t_commutable;
}

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const IndexStructure& indices,
                 const IndicialParent* t_parent)
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

const IndicialParent* ITensor::getParent() const {
    return parent;
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
    if (expr->getName() == WHATEVER->getName()) 
        return true;
    if (expr->getType() != smType::ITensor) 
        return false;

    if (name != expr->getName()) 
        return false;

    return index.exactMatch(expr->getIndexStructure());
}
