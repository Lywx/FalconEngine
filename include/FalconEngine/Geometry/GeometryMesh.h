#pragma once

#include <fstream>

#include <armadillo>

#include <FalconEngine/Graphics/Mesh.h>

namespace FalconEngine {
namespace Geometry {

// Stores all the vertex data loaded from a vertex file.
struct GeometryMeshVertexData
{
    GeometryMeshVertexData(int vertexNum, int vertexRowNum, int vertexColNum)
        : VertexNum(vertexNum)
        , VertexRowNum (vertexRowNum)
        , VertexColNum(vertexColNum)
        , Vertexes(new std::vector<Math::Vector3>())
    {
        Vertexes->reserve(vertexNum);
    }

    int                   VertexNum;
    int                   VertexRowNum;
    int                   VertexColNum;
    Graphics::VertexList *Vertexes;
};

// Stores all the index data loaded from an index file.
struct GeometryMeshIndexData
{
    int                        IndexNum;

    // TODO(Wuxiang): Do I really need this?
    int                        IndexRowNum;
    int                        IndexColNum;

    std::vector<Math::Index> *Indexes;

    GeometryMeshIndexData(int indexNum, int indexRowNum, int indexColNum) :
        IndexNum(indexNum),
        IndexRowNum (indexRowNum),
        IndexColNum(indexColNum),
        Indexes(new std::vector<Math::Index>())
    {
        Indexes->reserve(10);
    }
};

class GeometryMesh : public Graphics::Mesh
{
public:

    static GeometryMeshVertexData LoadVertexes(std::wstring filename);
    static GeometryMeshIndexData LoadIndexes(std::wstring filename);

    GeometryMesh();
    virtual ~GeometryMesh() override;

    virtual void LoadMesh(std::initializer_list<std::wstring> fileNames) override;
};

}
}


