#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexAttribute::VertexAttribute(unsigned int        location,
                                 const std::string&  name,
                                 VertexAttributeType type,
                                 bool                normalized,
                                 unsigned int        stride,
                                 unsigned int        bindingIndex,
                                 unsigned int        division) :
    mBindingIndex(bindingIndex),
    mDivision(division),
    mLocation(location),
    mName(name),
    mNormalized(normalized),
    mType(type),
    mStride(stride),
    mChannel(VertexAttributeChannels[int(type)])
{
}

VertexAttribute::~VertexAttribute()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
VertexAttribute::IsCompatible(const VertexAttribute& rhs) const
{
    // NOTE(Wuxiang): Binding index and name is not required to be the same.
    return mLocation == rhs.mLocation
           && mChannel == rhs.mChannel
           && mDivision == rhs.mDivision
           && mNormalized == rhs.mNormalized
           && mType == rhs.mType;
}

}
