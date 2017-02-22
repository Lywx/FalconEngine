#include <FalconEngine/Graphics/Scenes/Mesh.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Scenes/Model.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Mesh, VisualTriangles);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Mesh::Mesh(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer) :
    VisualTriangles(vertexFormat, vertexGroup, indexBuffer)
{
}

Mesh::~Mesh()
{
}

}
