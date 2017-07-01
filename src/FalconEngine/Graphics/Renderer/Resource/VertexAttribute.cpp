#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexAttribute::VertexAttribute(unsigned int location, const std::string& name, VertexAttributeType type, bool normalized, unsigned int offset, unsigned int bindingIndex, unsigned int division) :
    mBindingIndex(bindingIndex),
    mDivision(division),
    mLocation(location),
    mName(name),
    mNormalized(normalized),
    mType(type),
    mOffset(offset),
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
    // NOTE(Wuxiang): Binding index is not required to be the same.
    return mLocation == rhs.mLocation
           && mChannel == rhs.mChannel
           && mDivision == rhs.mDivision
           && mName == rhs.mName
           && mNormalized == rhs.mNormalized
           && mType == rhs.mType;
}

}
