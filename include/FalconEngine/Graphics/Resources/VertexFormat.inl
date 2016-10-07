size_t VertexFormat::GetAttributeOffset(int attribute) const
{
    if (0 <= attribute && attribute < m_attributeNum)
    {
        return m_attributeElements[attribute].Offset;
    }
    else
    {
        assert(false, "Invalid index in GetOffset\n");
        return 0;
    }
}

VertexAttributeType VertexFormat::GetAttributeType(int attribute) const
{
    if (0 <= attribute && attribute < m_attributeNum)
    {
        return m_attributeElements[attribute].Type;
    }
    else
    {
        assert(false, "Invalid index in GetAttributeType\n");
        return VertexAttributeType::NONE;
    }
}

VertexAttributeUsage VertexFormat::GetAttributeUsage(int attribute) const
{
    if (0 <= attribute && attribute < m_attributeNum)
    {
        return m_attributeElements[attribute].Usage;
    }
    else
    {
        assert(false, "Invalid index in GetAttributeUsage\n");
        return VertexAttributeUsage::NONE;
    }
}

size_t VertexFormat::GetAttributeUsageIndex(int attribute) const
{
    if (0 <= attribute && attribute < m_attributeNum)
    {
        return m_attributeElements[attribute].UsageIndex;
    }
    else
    {
        assert(false, "Invalid index in GetUsageIndex\n");
        return 0;
    }

}

int VertexFormat::GetAttributeNum() const
{
    return m_attributeNum;
}

inline size_t VertexFormat::GetStride() const
{
    return m_stride;
}
