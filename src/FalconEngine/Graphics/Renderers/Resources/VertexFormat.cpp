#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VertexFormat, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexFormat::VertexFormat() :
    mVertexAttributeOffset(0)
{
}

VertexFormat::~VertexFormat()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VertexFormat::PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex)
{
    if (attributeLocation != mVertexAttributeVector.size())
    {
        ThrowRuntimeException("It is not supported for out of order attribute registration.");
    }

    // NOTE(Wuxiang): mVertexAttributeOffset is summed
    mVertexAttributeVector.push_back(VertexAttribute(attributeLocation, attributeName, attributeType, attributeNormalized, mVertexAttributeOffset, attributeBindingIndex));
    mVertexAttributeOffset += VertexAttributeSize[int(mVertexAttributeVector.back().mType)];
}

int
VertexFormat::GetVertexAttributeNum() const
{
    return int(mVertexAttributeVector.size());
}

VertexAttribute&
VertexFormat::GetVertexAttribute(int attributeIndex)
{
    return mVertexAttributeVector.at(attributeIndex);
}

void
VertexFormat::PushVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
{
    mVertexRecordVector.push_back(VertexRecord(vertexBuffer, bindingIndex, offset, stride));
}

}
