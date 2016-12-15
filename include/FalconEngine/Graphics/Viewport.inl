inline float Viewport::Width() const
{
    return m_right - m_left;
}

inline float Viewport::Height() const
{
    return m_bottom - m_top;
}

inline float Viewport::Aspect() const
{
    return Width() / Height();
}

inline float Viewport::MinDepth() const
{
    return m_minDepth;
}

inline float Viewport::MaxDepth() const
{
    return m_maxDepth;
}

inline Vector2f Viewport::Center() const
{
    return Vector2f(m_left + Width() / 2, m_top + Height() / 2);
}

