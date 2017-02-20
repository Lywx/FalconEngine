#include <FalconEngine/Graphics/Renderers/VisualQuads.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualQuads, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualQuads::VisualQuads(VertexFormatSharedPtr vertexFormat, int vertexNum)
    : VisualTriangles(vertexFormat, vertexNum, nullptr)
{
}

VisualQuads::~VisualQuads()
{
}

}
