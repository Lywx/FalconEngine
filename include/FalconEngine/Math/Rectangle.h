#pragma once

#include <FalconEngine/Math/Vector2d.h>
#include <FalconEngine/Math/Vector2f.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine
{

// @Summary: axis-aligned rectangle in 2D space
class Rectangle
{
public:
    static const Rectangle Zero;

    static Rectangle CreateBounds(float left, float top, float right, float bottom);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Rectangle();
    Rectangle(int left, int top, int width, int height);
    Rectangle(float left, float top, float width, float height);

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    float
    GetRight() const;

    float
    GetBottom() const;

    Vector2f
    GetPosition() const;

    Vector2f
    GetSize() const;

    Vector4f
    GetExtents() const;

    Vector2d
    GetCenter() const;

    void
    SetRight(float right);

    void
    SetBottom(float bottom);

    void
    SetPosition(const Vector2f& position);

    void
    SetSize(const Vector2f& size);

    void
    SetExtents(const Vector4f extents);

    void
    SetCenter(const Vector2f& center);

    bool
    Empty() const;

    bool
    Contains(float x, float y) const;

    bool
    Intersects(const Rectangle& rect) const;

    bool
    Contains(const Vector2f& position) const;

    bool
    Contains(const Rectangle& rect) const;

    bool
    Contains(const Vector2d& position) const;

    void
    Inflate(float x, float y);

    void
    Contract(float x, float y);

    void
    Offset(float x, float y);

    void
    Offset(const Vector2d& vec);

public:
    float m_left;
    float m_top;

    float m_width;
    float m_height;
};

bool operator==(const Rectangle&lhs, const Rectangle& rhs);
bool operator!=(const Rectangle&lhs, const Rectangle& rhs);

inline float
Rectangle::GetRight() const
{
    return m_left + m_width;
}

inline void
Rectangle::SetRight(float right)
{
    auto offsetPlusWidth = right - m_left;
    auto offsetForLeft = offsetPlusWidth - m_width;
    m_left += offsetForLeft;
}

inline float
Rectangle::GetBottom() const
{
    return m_top + m_height;
}

inline void
Rectangle::SetBottom(float bottom)
{
    m_top = bottom - m_height;
}

inline Vector2f
Rectangle::GetPosition() const
{
    return Vector2f(m_left, m_top);
}

inline void
Rectangle::SetPosition(const Vector2f& position)
{
    m_left = position.x;
    m_top = position.y;
}

inline Vector2f
Rectangle::GetSize() const
{
    return Vector2f(m_width, m_height);
}

inline void
Rectangle::SetSize(const Vector2f& size)
{
    m_width = size.x;
    m_height = size.y;
}

inline Vector4f
Rectangle::GetExtents() const
{
    return glm::vec4(m_left, m_top, GetRight(), GetBottom());
}

inline void
Rectangle::SetExtents(const Vector4f extents)
{
    m_left   = extents.x;
    m_top    = extents.y;
    m_width  = extents.z - m_left;
    m_height = extents.w - m_top;
}

inline Vector2d
Rectangle::GetCenter() const
{
    return Vector2d(m_left + m_width * 0.5f,
                    m_top + m_height * 0.5f);
}

inline void
Rectangle::SetCenter(const Vector2f& center)
{
    m_left = center.x - m_width / 2;
    m_top  = center.y - m_height / 2;
}

}