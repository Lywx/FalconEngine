inline int Buffer::GetElementNum() const
{
    return m_elementNum;
}

inline void Buffer::SetElementNum(int elementNum)
{
    m_elementNum = elementNum;
}

inline int Buffer::GetElementSize() const
{
    return m_elementSize;
}

inline BufferUsage Buffer::GetUsage() const
{
    return m_usage;
}

inline int Buffer::GetByteNum() const
{
    return m_byteNum;
}

inline char *Buffer::GetData() const
{
    return m_data;
}
