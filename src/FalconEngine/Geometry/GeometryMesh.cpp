#include <FalconEngine/Geometry/GeometryMesh.h>

namespace FalconEngine {
namespace Geometry {

/* static */ GeometryMeshVertexData GeometryMesh::LoadVertexes(std::wstring filename)
{
    using arma::uword;

    std::ifstream vertexFile(filename);

    if (!vertexFile.good())
    {
        using std::runtime_error;
        throw runtime_error("vertex file doest not exist.");
    }

    int vertexNum;
    int vertexRowNum;
    int vertexColNum;

    // Get the dimension of the vertex matrix
    vertexFile >> vertexNum >> vertexRowNum >> vertexColNum;

    auto vertexData = GeometryMeshVertexData(vertexNum, vertexRowNum, vertexColNum);

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
        vertexData.Vertexes->push_back(Math::Vector3(vertexX, vertexY, vertexZ));
    }

    return vertexData;
}

/* static */ GeometryMeshIndexData GeometryMesh::LoadIndexes(std::wstring filename)
{
    using arma::uword;

    std::ifstream indexFile(filename);

    if (!indexFile.good())
    {
        using std::runtime_error;
        throw runtime_error("index file doest not exist.");
    }

    int indexNum;
    int indexRowNum;
    int indexColNum;

    // Get the dimension of the point matrix
    indexFile >> indexNum >> indexRowNum >> indexColNum;

    auto indexData = GeometryMeshIndexData(indexNum, indexRowNum, indexColNum);

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
        indexData.Indexes->push_back(Math::Index(indexA, indexB, indexC));
    }

    return indexData;
}

GeometryMesh::GeometryMesh()
{
}

/* virtual */ GeometryMesh::~GeometryMesh()
{
}

/* virtual */ void GeometryMesh::LoadMesh(std::initializer_list<std::wstring> fileNames)
{
    auto vertexData = LoadVertexes(*fileNames.begin());
    auto indexData = LoadIndexes(*(fileNames.begin() + 1));

    // TODO
    //if (vertexData.VertexNum != indexData.IndexNum)
    //{
    //    throw std::runtime_error("mesh file is invalid: index number is not equal to vertex number.");
    //}

    m_Vertexes.reset(vertexData.Vertexes);
    m_Indexes.reset(indexData.Indexes);
}

}
}