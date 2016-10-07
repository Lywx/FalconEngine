#include <FalconEngine/Geometry/TriangleMesh.h>

namespace FalconEngine {

/************************************************************************/
/* TriangleVertexData Members                                           */
/************************************************************************/
TriangleVertexData::TriangleVertexData(int vertexNum, int vertexRowNum,
                                       int vertexColNum) :
    VertexNum(vertexNum),
    VertexRowNum(vertexRowNum),
    VertexColNum(vertexColNum),
    VertexList(std::make_shared<TriangleVertexList>())
{
    VertexList->reserve(vertexNum);
}


/************************************************************************/
/* TriangleIndexData Members                                            */
/************************************************************************/
TriangleIndexData::TriangleIndexData(int indexNum, int indexRowNum,
                                     int indexColNum) :
    IndexNum(indexNum),
    IndexRowNum (indexRowNum),
    IndexColNum(indexColNum),
    IndexList(std::make_shared<TriangleIndexList>())
{
    IndexList->reserve(indexNum);
}

/************************************************************************/
/* TriangleMesh Members                                                 */
/************************************************************************/

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TriangleMesh::TriangleMesh() :
    m_vertexList(nullptr),
    m_indexList(nullptr)
{
}

/* virtual */ TriangleMesh::~TriangleMesh()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

void TriangleMesh::LoadMesh(std::initializer_list<std::wstring> fileNames)
{
    auto fileNameItr = fileNames.begin();

    auto vertexDataPtr = LoadVertexes(*fileNameItr);
    auto indexDataPtr = LoadIndexes(*(fileNameItr + 1));

    // This is based on common partition semantics in computational electromagnetism
    if (vertexDataPtr->VertexNum != indexDataPtr->IndexNum)
    {
        throw std::runtime_error("Mesh file is invalid: index number is not equal to vertex number.");
    }

    m_vertexList = vertexDataPtr->VertexList;
    m_indexList = indexDataPtr->IndexList;
}

TriangleVertexDataPtr TriangleMesh::LoadVertexes(std::wstring filename)
{
    using arma::uword;

    std::ifstream vertexFile(filename);

    if (!vertexFile.good())
    {
        throw std::runtime_error("Vertex file doest not exist.");
    }

    int vertexNum;
    int vertexRowNum;
    int vertexColNum;

    // Get the dimension of the vertex matrix
    vertexFile >> vertexNum >> vertexRowNum >> vertexColNum;

    auto vertexDataPtr = std::make_shared<TriangleVertexData>(vertexNum,
                         vertexRowNum,
                         vertexColNum);

    // Iterates column by column like this:
    // 0         4.0000    8.0000   12.0000
    // 1.0000    5.0000    9.0000   13.0000
    // 2.0000    6.0000   10.0000   14.0000
    // 3.0000    7.0000   11.0000   15.0000
    int   vertexIndex;
    float vertexX;
    float vertexY;
    float vertexZ;

    for (auto i = 0; i < vertexNum; ++i)
    {
        vertexFile >> vertexIndex >> vertexX >> vertexY >> vertexZ;
        vertexDataPtr->VertexList->push_back(Vector3f(vertexX, vertexY, vertexZ));
    }

    return vertexDataPtr;
}

TriangleIndexDataPtr TriangleMesh::LoadIndexes(std::wstring filename)
{
    using arma::uword;

    std::ifstream indexFile(filename);

    if (!indexFile.good())
    {
        throw std::runtime_error("Index file doest not exist.");
    }

    int indexNum;
    int indexRowNum;
    int indexColNum;

    // Get the dimension of the point matrix
    indexFile >> indexNum >> indexRowNum >> indexColNum;

    auto indexDataPtr = std::make_shared<TriangleIndexData>(indexNum, indexRowNum,
                        indexColNum);

    // Iterates column by column like this:
    // 0    4    8    12
    // 1    5    9    13
    // 2    6    10   14
    // 3    7    11   15
    int indexIndex;
    int indexA;
    int indexB;
    int indexC;

    for (auto i = 0; i < indexNum; ++i)
    {
        indexFile >> indexIndex >> indexA >> indexB >> indexC;
        indexDataPtr->IndexList->push_back(TriangleIndex(indexA, indexB, indexC));
    }

    return indexDataPtr;
}

}