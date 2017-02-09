#include <FalconEngine/Graphics/Shaders/ShaderVertexAttribute.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(ShaderVertexAttribute, Object);

ShaderVertexAttribute::ShaderVertexAttribute(std::string name, ShaderVertexAttributeType type, bool normalized) :
    ShaderVertexAttribute(0, name, type, normalized)
{
}

ShaderVertexAttribute::ShaderVertexAttribute(int location, std::string name, ShaderVertexAttributeType type, bool normalized) :
    mLocation(location),
    mName(name),
    mNormalized(normalized),
    mType(type)
{
}

ShaderVertexAttribute::~ShaderVertexAttribute()
{
}

}
