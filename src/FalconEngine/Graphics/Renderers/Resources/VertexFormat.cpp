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

// ReSharper disable once CppNotAllPathsReturnValue
int
VertexFormat::GetVertexAttributeStride() const
{
    if (mVertexAttributeFinished)
    {
        return mVertexAttributeOffset;
    }
    else
    {
        ThrowRuntimeException("Vertex attribute has not finished initialization.");
    }
}

void
VertexFormat::PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex)
{
    if (attributeLocation != mVertexAttributeVector.size())
    {
        // NOTE(Wuxiang): It is not supported for out of order attribute registration.
        FALCON_ENGINE_NOT_SUPPORT();
    }

    if (mVertexAttributeFinished)
    {
        ThrowRuntimeException("Vertex attribute has finished initialization.");
    }

    // NOTE(Wuxiang): mVertexAttributeOffset is summed
    mVertexAttributeVector.push_back(VertexAttribute(attributeLocation, attributeName, attributeType, attributeNormalized, mVertexAttributeOffset, attributeBindingIndex));
    mVertexAttributeOffset += VertexAttributeSize[int(mVertexAttributeVector.back().mType)];
}

void
VertexFormat::FinishVertexAttribute()
{
    mVertexAttributeFinished = true;
}

}
