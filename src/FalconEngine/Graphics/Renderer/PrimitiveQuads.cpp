#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitiveQuads, PrimitiveTriangles);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveQuads::PrimitiveQuads(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup) :
    PrimitiveTriangles(vertexFormat, vertexGroup, nullptr)
{
}

PrimitiveQuads::~PrimitiveQuads()
{
}

}
