#include <FalconEngine/Graphics/Renderer/Resources/VertexAttribute.h>

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

}
