#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexFormat::VertexFormat()
{
}

VertexFormat::~VertexFormat()
{
    FALCON_ENGINE_RENDERER_UNBIND(this);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
VertexFormat::IsVertexAttributeCompatible(std::shared_ptr<VertexFormat> rhs) const
{
    return IsVertexAttributeCompatible(rhs.get());
}

bool
VertexFormat::IsVertexAttributeCompatible(const VertexFormat *rhs) const
{
    FALCON_ENGINE_CHECK_NULLPTR(rhs);

    if (mVertexAttributeList.size() != rhs->mVertexAttributeList.size())
    {
        return false;
    }

    for (size_t attributeIndex = 0; attributeIndex < mVertexAttributeList.size(); ++attributeIndex)
    {
        if (!mVertexAttributeList[attributeIndex].IsCompatible(mVertexAttributeList[attributeIndex]))
        {
            return false;
        }
    }

    return true;
}

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

void
VertexFormat::PushVertexAttribute(
    int                 attributeLocation,
    std::string         attributeName,
    VertexAttributeType attributeType,
    bool                attributeNormalized,
    int                 attributeBindingIndex,
    int                 attributeDivision)
{
    if (mVertexAttributeFinished)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Vertex attribute has finished initialization.");
    }

    // Check the vertex attribute has been pushed in order.
    if (attributeLocation != int(mVertexAttributeList.size()))
    {
        // NOTE(Wuxiang): It is not supported for out of order attribute registration.
        // The reason is that in order to correctly count offset for individual
        // vertex attribute, you have to input vertex index in the order of layout location.
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }

    // Initialize offset storage for specific binding index.
    while (attributeBindingIndex >= int(mVertexAttributeStrideList.size()))
    {
        mVertexAttributeStrideList.push_back(0);
    }

    // NOTE(Wuxiang): mVertexAttributeOffset is summed.
    mVertexAttributeList.push_back(
        VertexAttribute(
            attributeLocation, attributeName, attributeType,
            attributeNormalized,
            mVertexAttributeStrideList[attributeBindingIndex],
            attributeBindingIndex, attributeDivision));
    mVertexAttributeStrideList[attributeBindingIndex] += VertexAttributeSize[int(mVertexAttributeList.back().mType)];
}

void
VertexFormat::FinishVertexAttribute()
{
    mVertexAttributeFinished = true;
}

int
VertexFormat::GetVertexBufferStride(int attributeBindingIndex) const
{
    if (mVertexAttributeFinished)
    {
        return mVertexAttributeStrideList.at(attributeBindingIndex);
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Vertex attribute has not finished initialization.");
    }
}

}
