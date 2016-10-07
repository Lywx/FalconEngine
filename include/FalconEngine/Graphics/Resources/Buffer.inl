inline size_t Buffer::ElementNum() const
{
    return m_elementNum;
}

inline void Buffer::ElementNum(int elementNum)
{
    m_elementNum = elementNum;
}

inline size_t Buffer::ElementSize() const
{
    return m_elementSize;
}

inline BufferUsage Buffer::Usage() const
{
    return m_usage;
}

inline size_t Buffer::ByteNum() const
{
    return m_byteNum;
}

inline char *Buffer::Data() const
{
    return m_data;
}
