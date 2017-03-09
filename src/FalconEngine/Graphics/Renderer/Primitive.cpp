#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Primitive, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitive::Primitive(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat) :
    Primitive(primitiveType, vertexFormat, nullptr, nullptr)
{
}

Primitive::Primitive(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer) :
    mPrimitiveType(primitiveType),
    mVertexGroup(vertexGroup),
    mVertexFormat(vertexFormat),
    mIndexBuffer(indexBuffer)
{
    // NOTE(Wuxiang): All vertex buffer format, vertex format and index buffer is
    // allowed to be null here. But they should be initialized in the derived
    // class's constructor.
}

Primitive::~Primitive()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
PrimitiveType
Primitive::GetPrimitiveType() const
{
    return mPrimitiveType;
}

const BoundingBox *
Primitive::GetBoundingBox() const
{
    return mBoundingBox.get();
}

void
Primitive::SetBoundingBox(BoundingBoxSharedPtr boundingBox)
{
    FALCON_ENGINE_CHECK_NULLPTR(boundingBox);

    mBoundingBox = boundingBox;
}

size_t
Primitive::GetVertexNum() const
{
    return mVertexGroup->GetVertexNum();
}

const VertexFormat *
Primitive::GetVertexFormat() const
{
    return mVertexFormat.get();
}

void
Primitive::SetVertexFormat(VertexFormatSharedPtr vertexFormat)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexFormat);

    mVertexFormat = vertexFormat;
}

const IndexBuffer *
Primitive::GetIndexBuffer() const
{
    return mIndexBuffer.get();
}

void
Primitive::SetIndexBuffer(IndexBufferSharedPtr indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    mIndexBuffer = indexBuffer;
}

const VertexGroup *
Primitive::GetVertexGroup() const
{
    return mVertexGroup.get();
}

void
Primitive::SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    if (mVertexGroup->ContainVertexBuffer(bindingIndex, vertexBuffer))
    {
        // NOTE(Wuxiang): It is not allowed to reset vertex buffer's offset or stride.
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
    else
    {
        mVertexGroup->SetVertexBuffer(bindingIndex, vertexBuffer, offset, stride);
    }
}

}
