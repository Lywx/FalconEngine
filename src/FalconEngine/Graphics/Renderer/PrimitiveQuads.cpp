#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitiveQuads, PrimitiveTriangles);
FALCON_ENGINE_RTTI_IMPLEMENT_EXPORT(PrimitiveQuads);

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
