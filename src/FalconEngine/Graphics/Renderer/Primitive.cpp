#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Primitive, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitive::Primitive(PrimitiveType primitiveType) :
    Primitive(primitiveType, nullptr, nullptr)
{
}

Primitive::Primitive(PrimitiveType primitiveType, std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) :
    mPrimitiveType(primitiveType),
    mVertexBuffer(vertexBuffer),
    mIndexBuffer(indexBuffer)
{
    // NOTE(Wuxiang): All vertex buffer and index buffer is allowed to be null
    // here. But they should be initialized in the derived class's constructor.
}

Primitive::~Primitive()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
Primitive::CopyTo(Primitive *lhs)
{
    lhs->mBoundingBox = mBoundingBox;
    lhs->mPrimitiveType = mPrimitiveType;

    lhs->mVertexBuffer = mVertexBuffer;
    lhs->mIndexBuffer = mIndexBuffer;
}

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
Primitive::SetBoundingBox(std::shared_ptr<BoundingBox> boundingBox)
{
    FALCON_ENGINE_CHECK_NULLPTR(boundingBox);

    mBoundingBox = boundingBox;
}

void
Primitive::SetVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    mVertexBuffer = vertexBuffer;
}

size_t
Primitive::GetVertexNum() const
{
    return mVertexBuffer->GetElementNum();
}

const IndexBuffer *
Primitive::GetIndexBuffer() const
{
    return mIndexBuffer.get();
}

void
Primitive::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    mIndexBuffer = indexBuffer;
}

const VertexBuffer *
Primitive::GetVertexBuffer() const
{
    return mVertexBuffer.get();
}

std::shared_ptr<VertexBuffer>
Primitive::GetVertexBuffer()
{
    return mVertexBuffer;
}

}
