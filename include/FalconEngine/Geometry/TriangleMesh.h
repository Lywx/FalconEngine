#pragma once

#include <fstream>
#include <memory>

#include <armadillo>

#include <FalconEngine/Math/Vector3f.h>

namespace FalconEngine {

struct TriangleIndex
{
    int A;
    int B;
    int C;

    TriangleIndex(int a, int b, int c)
    {
        A = a;
        B = b;
        C = c;
    }
};

typedef std::vector<TriangleIndex>          TriangleIndexList;
typedef std::shared_ptr<TriangleIndexList>  TriangleIndexListPtr;
typedef std::vector<Vector3f>               TriangleVertexList;
typedef std::shared_ptr<TriangleVertexList> TriangleVertexListPtr;

//@Summary: stores all the vertex data loaded from a vertex file.
struct TriangleVertexData
{
    TriangleVertexData(int vertexNum, int vertexRowNum, int vertexColNum) :
        VertexNum(vertexNum),
        VertexRowNum(vertexRowNum),
        VertexColNum(vertexColNum),
        VertexList(std::make_shared<TriangleVertexList>())
    {
        VertexList->reserve(vertexNum);
    }

    int                   VertexNum;
    int                   VertexRowNum;
    int                   VertexColNum;
    TriangleVertexListPtr VertexList;
};

// Stores all the index data loaded from an index file.
struct TriangleIndexData
{
    int                           IndexNum;
    int                           IndexRowNum;
    int                           IndexColNum;
    TriangleIndexListPtr          IndexList;

    TriangleIndexData(int indexNum, int indexRowNum, int indexColNum) :
        IndexNum(indexNum),
        IndexRowNum (indexRowNum),
        IndexColNum(indexColNum),
        IndexList(std::make_shared<TriangleIndexList>())
    {
        IndexList->reserve(indexNum);
    }
};

class TriangleMesh
{
public:

    TriangleMesh();
    virtual ~TriangleMesh();

    TriangleVertexListPtr Vertexes() const { return m_vertexes; }
    size_t                VertexSize() const { return m_vertexes->size(); }
    Vector3f&             VertexFront() const { return m_vertexes->front(); }

    TriangleIndexListPtr Indexes() const { return m_indexes; }
    size_t               IndexSize() const { return m_indexes->size(); }
    TriangleIndex&       IndexFront() const { return m_indexes->front(); }

    void               LoadMesh(std::initializer_list<std::wstring> fileNames);

private:
    TriangleVertexData LoadVertexes(std::wstring filename);
    TriangleIndexData  LoadIndexes(std::wstring filename);

    TriangleVertexListPtr m_vertexes;
    TriangleIndexListPtr  m_indexes;
};

}
