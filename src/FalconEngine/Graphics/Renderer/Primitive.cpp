#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitive::Primitive(PrimitiveType type) :
    Primitive(type, nullptr, nullptr, nullptr)
{
}

Primitive::Primitive(PrimitiveType type,
                     const std::shared_ptr<VertexFormat>& vertexFormat,
                     const std::shared_ptr<VertexGroup>& vertexGroup,
                     const std::shared_ptr<IndexBuffer>& indexBuffer) :
    mType(type),
    mAabb(),
    mVertexFormat(vertexFormat),
    mVertexGroup(vertexGroup),
    mVertexOffset(0),
    mIndexBuffer(indexBuffer),
    mIndexOffset(0)
{
    // NOTE(Wuxiang): All vertex format, vertex group and index buffer is allowed to be null
    // here. But they should be initialized in the derived class's constructor.
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
    return mType;
}

/************************************************************************/
/* Bounding Box Management                                              */
/************************************************************************/
const Aabb *
Primitive::GetAabb() const
{
    return mAabb.get();
}

void
Primitive::SetAabb(const Aabb& aabb)
{
    mAabb = std::make_shared<Aabb>(aabb);
}

/************************************************************************/
/* Vertex Buffer Management                                             */
/************************************************************************/
const VertexFormat *
Primitive::GetVertexFormat() const
{
    return mVertexFormat.get();
}

std::shared_ptr<const VertexFormat>
Primitive::GetVertexFormat()
{
    return mVertexFormat;
}

const VertexGroup *
Primitive::GetVertexGroup() const
{
    return mVertexGroup.get();
}

std::shared_ptr<const VertexGroup>
Primitive::GetVertexGroup()
{
    return mVertexGroup;
}

int
Primitive::GetVertexNum() const
{
    return mVertexGroup->GetVertexNum();
}

int
Primitive::GetVertexOffset() const
{
    return mVertexOffset;
}

void
Primitive::SetVertexOffset(int vertexOffset)
{
    mVertexOffset = vertexOffset;
}

/************************************************************************/
/* Index Buffer Management                                              */
/************************************************************************/
const IndexBuffer *
Primitive::GetIndexBuffer() const
{
    return mIndexBuffer.get();
}

std::shared_ptr<IndexBuffer>
Primitive::GetIndexBufferSp()
{
    return mIndexBuffer;
}

int
Primitive::GetIndexOffset() const
{
    return mIndexOffset;
}

void
Primitive::SetIndexOffset(int indexOffset)
{
    mIndexOffset = indexOffset;
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Primitive::CopyTo(Primitive *lhs)
{
    lhs->mType = mType;
    lhs->mAabb = mAabb;

    lhs->mVertexFormat = mVertexFormat;
    lhs->mVertexGroup = mVertexGroup;
    lhs->mVertexOffset = mVertexOffset;

    lhs->mIndexBuffer = mIndexBuffer;
    lhs->mIndexOffset = mIndexOffset;
}

}
