#include <FalconEngine/Graphics/Renderers/Primitives.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Primitives, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitives::Primitives(PrimitiveType primitiveType) :
    Primitives(primitiveType, nullptr)
{
}

Primitives::Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat) :
    Primitives(primitiveType, vertexFormat, nullptr)
{
}

Primitives::Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, IndexBufferSharedPtr indexBuffer) :
    mPrimitiveType(primitiveType),
    mVertexFormat(vertexFormat),
    mIndexBuffer(indexBuffer),
    mVertexNum(0)
{
    // NOTE(Wuxiang): Both vertex format and index buffer is allowed to be null
    // here. But they should be initialized in the derived class's constructor.
}

Primitives::~Primitives()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
PrimitiveType
Primitives::GetPrimitiveType() const
{
    return mPrimitiveType;
}

const VertexFormat *
Primitives::GetVertexFormat() const
{
    return mVertexFormat.get();
}

const IndexBuffer *
Primitives::GetIndexBuffer() const
{
    return mIndexBuffer.get();
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
Primitives::SetPrimitiveNum()
{
    if (mVertexNum == 0)
    {
        ThrowRuntimeException("Vertex number is 0.");
    }
}

void
Primitives::SetVertexNum(int vertexNum)
{
    if (vertexNum == 0)
    {
        ThrowRuntimeException("Vertex number is 0.");
    }

    mVertexNum = vertexNum;
}

}
