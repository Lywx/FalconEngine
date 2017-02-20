#include <FalconEngine/Graphics/Renderers/Shaders/ShaderVertexAttribute.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(ShaderVertexAttribute, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderVertexAttribute::ShaderVertexAttribute(int location, std::string name, ShaderVertexAttributeType type, bool normalized, int offset) :
    mLocation(location),
    mName(name),
    mNormalized(normalized),
    mType(type),
    mChannel(ShaderAttributeChannels[int(type)]),
    mOffset(offset)
{
}

ShaderVertexAttribute::~ShaderVertexAttribute()
{
}

}
