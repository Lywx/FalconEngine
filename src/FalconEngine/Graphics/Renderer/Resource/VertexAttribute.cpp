#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexAttribute::VertexAttribute(int location, std::string name, VertexAttributeType type, bool normalized, int offset, int bindingIndex, int division) :
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
