#pragma once

#include <FalconEngine/Core/Objects/Object.h>
#include <memory>
#include <cassert>

namespace FalconEngine {

//@Summary: Vertex Attribute Types in OpenGL
//@Reference: Graham Sellers, etc OpenGL SuperBible, 7th, 2015, P477
enum class VertexAttributeType
{
    NONE,

    BYTE,
    SHORT,
    INT,
    FIXED,
    UNSIGNED_BYTE,
    UNSIGNED_SHORT,
    UNSIGNED_INT,
    HALF_FLOAT,
    FLOAT,
    DOUBLE,

    ENUM_COUNT,
};

//@Summary:
enum class VertexAttributeUsage
{
    NONE,

    POSITION,      // Attr 0
    NORMAL,        // Attr 2
    TANGENT,       // Attr 14
    BINORMAL,      // Attr 15
    TEXCOORD,      // Attr 8-15
    COLOR,         // Attr 3-4
    BLENDINDICES,  // Attr 7
    BLENDWEIGHT,   // Attr 1
    FOGCOORD,      // Attr 5
    PSIZE,         // Attr 6

    ENUM_COUNT
};

class VertexFormat : public Object
{
protected:
    class VertexFormatElement
    {
    public:
        size_t               Offset;
        VertexAttributeType  Type;
        VertexAttributeUsage Usage;
        size_t               UsageIndex;
    };

public:
    //@Summary: the maximum number of attributes for a vertex format.
    enum
    {
        MAX_ATTRIBUTE_NUM = 16,
        MAX_TEXCOORD_NUM  = 8,
        MAX_COLOR_NUM     = 2,
    };

    VertexFormat(int numAttributes);
    virtual ~VertexFormat();

    int                 m_attributeNum;
    VertexFormatElement m_attributeElements[MAX_ATTRIBUTE_NUM];
    int                 m_stride;

    static int s_componentSize[AT_QUANTITY];
    static int s_componentNum[AT_QUANTITY];
    static int s_typeSize[AT_QUANTITY];

    void SetAttribute(size_t               attribute,
                      size_t               attributeOffset,
                      VertexAttributeType  attributeType,
                      VertexAttributeUsage attributeUsage,
                      size_t               attributeUsageIndex);

    void GetAttribute(size_t                attribute,
                      size_t&               attributeOffset,
                      VertexAttributeType&  attributeType,
                      VertexAttributeUsage& attributeUsage,
                      size_t&               attributeUsageIndex) const;

    inline int                  GetAttributeNum() const;

    // Return the index of the specified attribute usage.  The specified
    // usage index is currently used only for color channels and texture
    // coordinates.  When the attribute usage occurs in the format, the return
    // value is an index i for which 0 <= i < GetNumAttributes().  If the
    // attribute usage does not occur in the format, the return value is -1.
    int                         GetAttributeIndex(VertexAttributeUsage usage,
            size_t usageIndex = 0) const;

    inline size_t               GetAttributeOffset(int attribute) const;
    inline VertexAttributeType  GetAttributeType(int attribute) const;
    inline VertexAttributeUsage GetAttributeUsage(int attribute) const;
    inline size_t               GetAttributeUsageIndex(int attribute) const;

    void                        SetStride(size_t stride);
    inline size_t               GetStride() const;
};


typedef std::shared_ptr<VertexFormat> VertexFormatPtr;

#include "VertexFormat.inl"

}
