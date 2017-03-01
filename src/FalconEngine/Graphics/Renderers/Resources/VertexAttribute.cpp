#include <FalconEngine/Graphics/Renderers/Resources/VertexAttribute.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexAttribute::VertexAttribute(int location, std::string name, VertexAttributeType type, bool normalized, int offset, int bindingIndex) :
    mBindingIndex(bindingIndex),
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
