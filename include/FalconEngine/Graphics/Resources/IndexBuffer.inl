inline void IndexBuffer::SetOffset(int offset)
{
    if (offset >= 0)
    {
        m_offset = offset;
    }
    else
    {
        throw std::invalid_argument("The offset must be nonnegative\n");
    }
}

inline int IndexBuffer::GetOffset() const
{
    return m_offset;
}
