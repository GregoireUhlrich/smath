#include "indicial.h"
#include "error.h"

using namespace std;

///////////////////////////////////////////////////
/*************************************************/
// Class IndicialParent                        //
/*************************************************/
///////////////////////////////////////////////////

IndicialParent::IndicialParent(): name(""), commutable(true), dim(0), 
    space(vector<const Space*>(0)), symmetry(), fullySymmetric(false),
    fullyAntiSymmetric(false)
{}

IndicialParent::IndicialParent(const string& t_name): name(t_name),
    commutable(true), dim(0), space(vector<const Space*>(0)), symmetry(),
    fullySymmetric(false), fullyAntiSymmetric(false)
{}

IndicialParent::IndicialParent(const string& t_name,
                               const std::initializer_list<const Space*> t_space)
    :name(t_name), commutable(true), dim(t_space.size()), space(t_space),
    symmetry(), fullySymmetric(false), fullyAntiSymmetric(false)
{}

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

Expr IndicialParent::operator()(const Index& index) const
{
    if (dim != 1)
        callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Index>& indices) const");
    if (index.getSpace() != space[0])
            callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Index>& indices) const");

    return make_shared<ITensor>(name, commutable, index, this);
}

Expr IndicialParent::operator()(const initializer_list<Index>& indices) const
{
    if (indices.size() != (size_t)dim) {
        callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Index>& indices) const");
    }
    for (auto index=indices.begin(); index!=indices.end(); ++index)
        if (index->getSpace() != space[distance(indices.begin(), index)])
            callError(smError::InvalidITensor, 
    "IndicialParent::operator()(const initializer_list<Index>& indices) const");

    return make_shared<ITensor>(name, commutable, indices, this);
}


////////////////////////////////////////////////////
///*************************************************/
// Class AbstractIndicial                          //
///*************************************************/
/////////////////////////////////////////////////////

AbstractIndicial::AbstractIndicial(): AbstractScalar() 
{}

AbstractIndicial::AbstractIndicial(const string& t_name)
    :AbstractScalar(t_name)
{}

AbstractIndicial::AbstractIndicial(const IndexStructure& t_index)
    :AbstractScalar(), index(t_index)
{}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const Index& t_index)
    :AbstractScalar(t_name), nIndices(1), index(vector<Index>(1,t_index))
{}

AbstractIndicial::AbstractIndicial(const string& t_name,
                                   const initializer_list<Index>& indices)
    :AbstractScalar(t_name), nIndices(indices.size()), index(indices)
{}

///////////////////////////////////////////////////
/*************************************************/
// Class ITensor                                 //
/*************************************************/
///////////////////////////////////////////////////

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const Index& t_index,
                 const IndicialParent* t_parent)
    :AbstractIndicial(t_name, t_index), parent(t_parent)
{
    commutable = t_commutable;
}

ITensor::ITensor(const string& t_name,
                 bool t_commutable,
                 const initializer_list<Index>& indices,
                 const IndicialParent* t_parent)
    :AbstractIndicial(t_name, indices), parent(t_parent)
{
    commutable = t_commutable;
}

// Constructor crashes if expr is not an ITensor
ITensor::ITensor(const Abstract*& expr): parent(expr->getParent())
{
    name = expr->getName();
    commutable = expr->getCommutable();
    nIndices = expr->getNIndices();
    index = expr->getIndexStructure();
}

// Constructor crashes if expr is not an ITensor
ITensor::ITensor(const Expr& expr): parent(expr->getParent())
{
    name = expr->getName();
    commutable = expr->getCommutable();
    nIndices = expr->getNIndices();
    index = expr->getIndexStructure();
}

Index ITensor::getIndex(int i) const
{
    if (i >= 0 and i < index.getNIndices()) 
        return index[i];
    callError(smError::OutOfBounds,"ITensor::getIndex(int i) const",i);
    return Index();
}

const IndicialParent* ITensor::getParent() const {
    return parent;
}

bool ITensor::checkIndexStructure(const vector<Index>& t_indices) const
{
    const int nIndices = index.getNIndices();
    if (nIndices != (int)t_indices.size()) 
        return false;
    vector<int> indicesLeft(nIndices);
    for (int i=0; i<nIndices;i++) 
        indicesLeft[i] = i;

    for (int i=0; i<nIndices; i++) {
        if (index[i].getFree()) {
            bool matched = 0;
            for (size_t j=0; j<indicesLeft.size(); j++) {
                Index foo = t_indices[indicesLeft[j]];
                if (not foo.getFree() or index[i] == foo) {
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
        const initializer_list<Index>& t_indices) const 
{
    return checkIndexStructure(vector<Index>(t_indices.begin(), t_indices.end()));
}

bool ITensor::contractIndex(const Index& indexToContract,
                            const Index& newIndex)
{
    for (int i=0; i!=nIndices; ++i)
        if (index[i] == indexToContract) {
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
        for (size_t i=0; i!=perm.size(); ++i)
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
                index[i].print();
            cout<<"}";
        }
        else 
            index[0].print();
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
                index[i].print();
            sout<<"}";
        }
        else 
            index[0].print();
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

    const int nIndices = index.getNIndices();
    if (name != expr->getName() or nIndices != expr->getNIndices()) 
        return false;

    return index.compareWithDummy(expr->getIndexStructure());
}

Indexed::Indexed(): AbstractIndicial(), expression(ZERO){}

Indexed::Indexed(const Expr& t_expression)
    :AbstractIndicial(t_expression->getName()), expression(t_expression)
{
    IndexStructure structure;
    vector<IndexStructure> structureVec(0);
    switch(expression->getType()) {

        case smType::Plus:
        structure = expression->getArgument()
            ->getIndexStructure();
        for (const_iter arg = t_expression->begin()+1;
                arg!=t_expression->end(); ++arg)
            if (structure != (*arg)->getIndexStructure())
                callError(smError::InvalidIndicialSum,
                        "Indexed::Indexed(const Expr& t_expression)");
        nIndices = structure.getNIndices();
        index = structure;

        break;

        case smType::Times:

        // Check the indexStructure of a product and apply Einstein's convention
        // in the case of a repeated index. This algorithm is O(N^2) with N the
        // total number of indices in the product (check for each index if it is
        // present elsewhere.

        //Structure of each argument in a vector
        //For each argument
        for (iter arg=t_expression->begin();
                arg!=t_expression->end(); ++arg) {
            if ((*arg)->isIndexed()) {
                // We get its structure in fooStruct
                IndexStructure fooStruct = (*arg)->getIndexStructure();
                // Now we check for each new index if it is present before in
                // the structure, in which case we contract it
                // (Einstein's convention).
                // For each new index: 
                for (int k=0; k!=fooStruct.getNIndices(); ++k) {
                    //For each former structureVec (former arguments)
                    for (size_t i=0; i!=structureVec.size(); ++i) {
                        const int nIndices = structureVec[i].getNIndices();
                        bool breakValue = false;
                        // For each index in the structureVec
                        for (int j=0; j!=nIndices; ++j) {
                            // If the index is already present
                            if (structureVec[i][j] == fooStruct[k]
                                    and fooStruct[k].getFree()) {
                                structureVec[i][j].setFree(false);
                                // We replace fooStruct[k] (not contracted)
                                // by structureVec[i][j] (contracted).
                                // If the contraction is not valid, we raise an 
                                // error.
                                if (not t_expression->getArgument(i)
                                        ->contractIndex(fooStruct[k],
                                                        structureVec[i][j]))
                                    callError(smError::BadContraction,
                                            "Times::selfCheckIndexStructure()",
                                            fooStruct[k]);
                                if (not (*arg)->contractIndex(fooStruct[k],
                                                              structureVec[i][j]))
                                    callError(smError::BadContraction,
                                            "Times::selfCheckIndexStructure()",
                                            fooStruct[k]);

                                fooStruct[k].setFree(false);
                                breakValue = true;
                                break;
                            }
                        }
                        if (breakValue)
                            break;
                    }
                }
                // We add fooStruct to the vector of structureVecs
                structureVec.push_back(fooStruct);
            }
        }
        for (const auto& struc : structureVec)
            index = index+struc;
        nIndices = index.getNIndices();
        break;

        default:
        cout<<"nothing\n";
    }
}

smType::PrimaryType Indexed::getPrimaryType() const
{
    return expression->getPrimaryType();
}

smType::Type Indexed::getType() const
{
    return expression->getType();
}

void Indexed::print(int mode) const
{
    expression->print();
}

string Indexed::printLaTeX(int mode) const
{
    return expression->printLaTeX(mode);
}

Expr Indexed::evaluate() 
{
    return expression->evaluate();
}

Expr Indexed::getArgument(int iArg) const
{
    return expression->getArgument();
}

void Indexed::setArgument(const Expr& t_argument, int iArg)
{
    expression->setArgument(t_argument, iArg);
}
