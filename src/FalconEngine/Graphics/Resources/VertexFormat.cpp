#include <FalconEngine/Graphics/Resources/VertexFormat.h>

#include <cassert>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

VertexFormat::VertexFormat(int numAttributes)
{
}

VertexFormat::~VertexFormat()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

void VertexFormat::SetAttribute(size_t attribute,
                                size_t attributeOffset,
                                VertexAttributeType attributeType,
                                VertexAttributeUsage attributeUsage,
                                size_t attributeUsageIndex)
{
    assert(0 <= attribute && attribute < m_attributeNum,
           "Invalid index in SetAttribute\n");

#ifdef _DEBUG
    if (attribute > 0)
    {
        assert(attributeOffset > m_attributeElements[attribute - 1].Offset,
               "Offsets must be increasing with attribute index.\n");
    }
    else
    {
        assert(attributeOffset == 0,
               "The offset of the first attribute must be zero.\n");
    }
#endif

    VertexFormatElement& element = m_attributeElements[attribute];

    element.Offset     = attributeOffset;
    element.Type       = attributeType;
    element.Usage      = attributeUsage;
    element.UsageIndex = attributeUsageIndex;
}

void VertexFormat::GetAttribute(size_t attribute,
                                size_t& attributeOffset,
                                VertexAttributeType& attributeType,
                                VertexAttributeUsage& attributeUsage,
                                size_t& attributeUsageIndex) const
{
}

int VertexFormat::GetAttributeIndex(VertexAttributeUsage usage,
                                    size_t usageIndex) const
{
    for (int i = 0; i < m_attributeNum; ++i)
    {
        if (m_attributeElements[i].Usage == usage
                &&  m_attributeElements[i].UsageIndex == usageIndex)
        {
            return i;
        }
    }

    return -1;
}

void VertexFormat::SetStride(size_t stride)
{
    assert(stride > 0, "Stride must be positive\n");
    m_stride = stride;
}

}
