#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Primitive::Primitive(PrimitiveType primitiveType) :
    Primitive(primitiveType, nullptr, nullptr, nullptr)
{
}

Primitive::Primitive(PrimitiveType primitiveType, std::shared_ptr<VertexFormat> vertexFormat, std::shared_ptr<VertexGroup> vertexGroup, std::shared_ptr<IndexBuffer> indexBuffer) :
    mPrimitiveType(primitiveType),
    mVertexFormat(vertexFormat),
    mVertexGroup(vertexGroup),
    mIndexBuffer(indexBuffer)
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
    return mPrimitiveType;
}

/************************************************************************/
/* Bounding Box Management                                              */
/************************************************************************/
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

/************************************************************************/
/* Vertex Buffer Management                                             */
/************************************************************************/
const VertexFormat *
Primitive::GetVertexFormat() const
{
    return mVertexFormat.get();
}

std::shared_ptr<VertexFormat>
Primitive::GetVertexFormat()
{
    return mVertexFormat;
}

const VertexGroup *
Primitive::GetVertexGroup() const
{
    return mVertexGroup.get();
}

std::shared_ptr<VertexGroup>
Primitive::GetVertexGroup()
{
    return mVertexGroup;
}

size_t
Primitive::GetVertexNum() const
{
    return mVertexGroup->GetElementNum();
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
Primitive::GetIndexBuffer()
{
    return mIndexBuffer;
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Primitive::CopyTo(Primitive *lhs)
{
    lhs->mPrimitiveType = mPrimitiveType;
    lhs->mBoundingBox = mBoundingBox;
    lhs->mVertexFormat = mVertexFormat;
    lhs->mVertexGroup = mVertexGroup;
    lhs->mIndexBuffer = mIndexBuffer;
}

}
