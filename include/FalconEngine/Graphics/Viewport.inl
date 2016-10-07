inline float Viewport::Left() const
{
    return m_left;
}

inline float Viewport::Right() const
{
    return m_right;
}

inline float Viewport::Top() const
{
    return m_top;
}

inline float Viewport::Bottom() const
{
    return m_bottom;
}

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
    return Vector2f(Left() + Width() / 2, Top() + Height() / 2);
}

inline Rectangle2f Viewport::TitleSafeArea() const
{
    return m_titleSafeArea;
}

