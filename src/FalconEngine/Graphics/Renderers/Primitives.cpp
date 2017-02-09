#include <FalconEngine/Graphics/Renderers/Primitives.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Primitives, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitives::Primitives(PrimitiveType primitiveType) :
    Primitives(primitiveType, nullptr, nullptr)
{
}

Primitives::Primitives(PrimitiveType primitiveType, VertexBufferSharedPtr vertexBuffer, IndexBufferSharedPtr indexBuffer) :
    mPrimitiveType(primitiveType),
    mVertexBuffer(vertexBuffer),
    mIndexBuffer(indexBuffer)
{
}

Primitives::~Primitives()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const
PrimitiveType Primitives::GetPrimitiveType() const
{
    return mPrimitiveType;
}

const VertexBuffer *
Primitives::GetVertexBuffer() const
{
    return mVertexBuffer.get();
}

const IndexBuffer *
Primitives::GetIndexBuffer() const
{
    return mIndexBuffer.get();
}

}
