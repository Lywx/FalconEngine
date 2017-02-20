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

const int ShaderAttributeChannels[int(ShaderVertexAttributeType::Count)] =
{
    0,  // None

    1,  // Float
    2,  // FloatVec2
    3,  // FloatVec3
    4,  // FloatVec4

    1,  // Int
    2,  // IntVec2
    3,  // IntVec2
    4   // IntVec4
};

// @summary Attribute sizeof operation result in byte.
const int ShaderAttributeSize[int(ShaderVertexAttributeType::Count)] =
{
    0,  // None

    4,  // Float
    8,  // FloatVec2
    12, // FloatVec3
    16, // FloatVec4

    4,  // Int
    8,  // IntVec2
    12, // IntVec2
    16  // IntVec4
};

class ShaderVertexAttribute : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderVertexAttribute(int location, std::string name, ShaderVertexAttributeType type, bool normalized, int offset);
    virtual ~ShaderVertexAttribute();

public:
    int                       mLocation;
    std::string               mName;
    bool                      mNormalized;
    ShaderVertexAttributeType mType;
    int                       mChannel;
    int                       mOffset;
};

typedef std::map<std::string, ShaderVertexAttribute> ShaderVertexAttributeTable;
typedef std::vector<ShaderVertexAttribute>           ShaderVertexAttributeVector;

}
