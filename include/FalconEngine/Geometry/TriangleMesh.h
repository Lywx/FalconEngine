#pragma once

#include <fstream>
#include <memory>

#include <armadillo>

#include <FalconEngine/Geometry/Mesh.h>
#include <FalconEngine/Math/Vector3d.h>
#include <FalconEngine/Math/Vector3f.h>

namespace FalconEngine {

typedef Vector3d                            TriangleIndex;
typedef std::vector<TriangleIndex>          TriangleIndexList;
typedef std::shared_ptr<TriangleIndexList>  TriangleIndexListPtr;

typedef Vector3f                            TriangleVertex;
typedef std::vector<TriangleVertex>         TriangleVertexList;
typedef std::shared_ptr<TriangleVertexList> TriangleVertexListPtr;

//@Summary: stores all the vertex data loaded from a vertex file.
struct TriangleVertexData
{
    TriangleVertexData(int vertexNum, int vertexRowNum, int vertexColNum);

    int                   VertexNum;
    int                   VertexRowNum;
    int                   VertexColNum;
    TriangleVertexListPtr VertexList;
};

typedef std::shared_ptr<TriangleVertexData> TriangleVertexDataPtr;

//@Summary: stores all the index data loaded from an index file.
struct TriangleIndexData
{
    TriangleIndexData(int indexNum, int indexRowNum, int indexColNum);

    int                  IndexNum;
    int                  IndexRowNum;
    int                  IndexColNum;
    TriangleIndexListPtr IndexList;
};

typedef std::shared_ptr<TriangleIndexData> TriangleIndexDataPtr;

class TriangleMesh : public Mesh
{
public:
    TriangleMesh();
    virtual ~TriangleMesh();

    size_t                VertexSize() const;
    Vector3f&             VertexFront() const;
    TriangleVertexListPtr VertexListPtr() const;

    size_t                IndexSize() const;
    TriangleIndex&        IndexFront() const;
    TriangleIndexListPtr  IndexListPtr() const;

    virtual void          LoadMesh(std::initializer_list<std::wstring> fileNames)
    override;

private:
    TriangleVertexDataPtr LoadVertexes(std::wstring filename);
    TriangleIndexDataPtr  LoadIndexes(std::wstring filename);

    TriangleVertexListPtr m_vertexList;
    TriangleIndexListPtr  m_indexList;
};

typedef std::shared_ptr<TriangleMesh> TriangleMeshPtr;

#include "TriangleMesh.inl"

}