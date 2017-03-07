#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexFormat::VertexFormat() :
    mVertexAttributeOffset(0),
    mVertexAttributeFinished(false)
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
    return int(mVertexAttributeList.size());
}

VertexAttribute&
VertexFormat::GetVertexAttribute(int attributeIndex)
{
    return mVertexAttributeList.at(attributeIndex);
}

int
VertexFormat::GetVertexAttributeStride() const
{
    if (mVertexAttributeFinished)
    {
        return mVertexAttributeOffset;
    }
    else
    {
        FALCON_ENGINE_THROW_EXCEPTION("Vertex attribute has not finished initialization.");
    }
}

void
VertexFormat::PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex, int attributeDivision)
{
    if (attributeLocation != mVertexAttributeList.size())
    {
        // NOTE(Wuxiang): It is not supported for out of order attribute registration.
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }

    if (mVertexAttributeFinished)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Vertex attribute has finished initialization.");
    }

    // NOTE(Wuxiang): mVertexAttributeOffset is summed
    mVertexAttributeList.push_back(VertexAttribute(attributeLocation, attributeName, attributeType, attributeNormalized, mVertexAttributeOffset, attributeBindingIndex, attributeDivision));
    mVertexAttributeOffset += VertexAttributeSize[int(mVertexAttributeList.back().mType)];
}

void
VertexFormat::FinishVertexAttribute()
{
    mVertexAttributeFinished = true;
}

}
