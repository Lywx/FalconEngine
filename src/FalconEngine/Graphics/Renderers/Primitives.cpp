#include <FalconEngine/Graphics/Renderers/Primitives.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Primitives, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitives::Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat) :
    Primitives(primitiveType, vertexFormat, nullptr, nullptr)
{
}

Primitives::Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer) :
    mPrimitiveType(primitiveType),
    mVertexGroup(vertexGroup),
    mVertexFormat(vertexFormat),
    mIndexBuffer(indexBuffer)
{
    // NOTE(Wuxiang): All vertex buffer format, vertex format and index buffer is
    // allowed to be null here. But they should be initialized in the derived
    // class's constructor.
}

Primitives::~Primitives()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
Primitives::SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
{
    if (mVertexGroup->ContainVertexBuffer(bindingIndex, vertexBuffer))
    {
        ThrowRuntimeException("It is not allowed to reset vertex buffer's offset or stride.");
    }
    else
    {
        mVertexGroup->SetVertexBuffer(bindingIndex, vertexBuffer, offset, stride);
    }
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
Primitives::SetPrimitiveNum()
{
}

}
