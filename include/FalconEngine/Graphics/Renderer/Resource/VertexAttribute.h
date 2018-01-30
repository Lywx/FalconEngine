#pragma once

#include <FalconEngine/Core/Common.h>

#include <string>
#include <map>
#include <vector>

namespace FalconEngine
{

enum class VertexAttributeType
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

const int VertexAttributeChannels[int(VertexAttributeType::Count)] =
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
const int VertexAttributeSize[int(VertexAttributeType::Count)] =
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

#pragma warning(disable: 4251)
class FALCON_ENGINE_API VertexAttribute
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexAttribute(unsigned int        location,
                    const std::string&  name,
                    VertexAttributeType type,
                    bool                normalized,
                    unsigned int        stride,
                    unsigned int        bindingIndex,
                    unsigned int        division);
    virtual ~VertexAttribute();

public:
    bool
    IsCompatible(const VertexAttribute& rhs) const;

public:
    // NOTE(Wuxiang): Initialized on construction.

    // Vertex attribute buffer binding index.
    unsigned int        mBindingIndex;

    // NOTE(Wuxiang) If divisor is non-zero, the attribute advances once per
    // divisor instances of the set(s) of vertices being rendered.

    // Vertex attribute update division when instancing.
    unsigned int        mDivision;
    // Vertex attribute layout location.
    unsigned int        mLocation;

    // Vertex attribute name.
    std::string         mName;
    // Vertex attribute should be normalized or not.
    bool                mNormalized;
    // Vertex attribute type.
    VertexAttributeType mType;

    // Vertex attribute's offset between each valid value of the same
    // attribute in the vertex buffer.
    unsigned int        mStride;

    // Vertex attribute dimension. Initialized based on mType.
    int                 mChannel;
};
#pragma warning(default: 4251)

}
