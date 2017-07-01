#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <string>
#include <map>
#include <vector>

namespace FalconEngine
{

enum class FALCON_ENGINE_API VertexAttributeType
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
    VertexAttribute(unsigned int location, const std::string& name, VertexAttributeType type, bool normalized, unsigned int offset, unsigned int bindingIndex, unsigned int division);
    virtual ~VertexAttribute();

public:
    bool
    IsCompatible(const VertexAttribute& rhs) const;

public:
    // NOTE(Wuxiang): Initialized on construction.
    unsigned int        mBindingIndex;                                        // Vertex attribute buffer binding index.

    // NOTE(Wuxiang) If divisor is non-zero, the attribute advances once per
    // divisor instances of the set(s) of vertices being rendered.
    unsigned int        mDivision;                                            // Vertex attribute update division when instancing.
    unsigned int        mLocation;                                            // Vertex attribute layout location.
    std::string         mName;                                                // Vertex attribute name.
    bool                mNormalized;                                          // Vertex attribute should be normalized or not.
    VertexAttributeType mType;                                                // Vertex attribute type.
    unsigned int        mOffset;                                              // Vertex attribute's offset into first valid value in the whole vertex buffer.

    // NOTE(Wuxiang): Initialized based on mType.
    int                 mChannel;                                             // Vertex attribute dimension.
};
#pragma warning(default: 4251)

}
