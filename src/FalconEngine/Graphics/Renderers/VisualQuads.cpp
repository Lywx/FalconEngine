#include <FalconEngine/Graphics/Renderers/VisualQuads.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualQuads, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualQuads::VisualQuads(VertexBufferSharedPtr vertexBuffer)
    : Visual(PrimitiveType::Triangle, vertexBuffer, nullptr)
{
}

VisualQuads::~VisualQuads()
{
}

}
