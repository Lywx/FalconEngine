#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <string>
#include <map>
#include <vector>

namespace FalconEngine
{

enum class ShaderVertexAttributeType
{
    None,

    Float,
    FloatVec2,
    FloatVec3,
    FloatVec4,

    Int,
    IntVec2,
    IntVec3,
    IntVec4,

    Count,
};

class ShaderVertexAttribute : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderVertexAttribute(std::string name, ShaderVertexAttributeType type, bool normalized);
    ShaderVertexAttribute(int location, std::string name, ShaderVertexAttributeType type, bool normalized);
    virtual ~ShaderVertexAttribute();

public:
    int                       mLocation;
    std::string               mName;
    bool                      mNormalized;
    ShaderVertexAttributeType mType;
};

typedef std::map<std::string, ShaderVertexAttribute> ShaderVertexAttributeTable;
typedef std::vector<ShaderVertexAttribute>           ShaderVertexAttributeVector;

}
