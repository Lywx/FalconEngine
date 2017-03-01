#include <FalconEngine/Graphics/Renderer/VisualQuads.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualQuads, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualQuads::VisualQuads(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup) :
    VisualTriangles(vertexFormat, vertexGroup, nullptr)
{
}

VisualQuads::~VisualQuads()
{
}

}
