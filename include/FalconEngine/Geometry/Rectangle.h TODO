#pragma once

#include <FalconEngine/Math/Vector2d.h>
#include <FalconEngine/Math/Vector2f.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine {

//@Summary: axis-aligned rectangle in 2D space
class Rectangle
{
public:
    static const Rectangle Zero;
    static Rectangle FromBounds(float left, float top, float right, float bottom);

    Rectangle();
    Rectangle(int left, int top, int width, int height);
    Rectangle(float left, float top, float width, float height);

    float Top() const { return m_top; }
    float& Top() { return m_top; }

    float Left() const { return m_left; }
    float& Left() { return m_left; }

    float Width() const { return m_width; }
    float& Width() { return m_width; }

    float Height() const { return m_height; }
    float& Height() { return m_height; }

    float GetRight() const { return m_left + m_width; }
    void SetRight(float right)
    {
        auto offsetPlusWidth = right - m_left;
        auto offsetForLeft = offsetPlusWidth - m_width;
        m_left += offsetForLeft;
    }

    float GetBottom() const { return m_top + m_height; }
    void SetBottom(float bottom)
    {
        m_top = bottom - m_height;
    }

    Vector2f GetPosition() const { return Vector2f(m_left, m_top); }
    void SetPosition(const Vector2f& position)
    {
        m_left = position.x;
        m_top = position.y;
    }

    Vector2f GetSize() const { return Vector2f(m_width, m_height); }
    void SetSize(const Vector2f& size)
    {
        m_width = size.x;
        m_height = size.y;
    }

    Vector4f GetExtents() const { return glm::vec4(m_left, m_top, GetRight(), GetBottom()); }
    void SetExtents(const Vector4f extents)
    {
        m_left   = extents.x;
        m_top    = extents.y;
        m_width  = extents.z - m_left;
        m_height = extents.w - m_top;
    }

    bool operator == (const Rectangle& r) const;
    bool operator != (const Rectangle& r) const;

    bool IsEmpty() const;
    Vector2d Center() const;

    virtual bool Contains(float x, float y) const;
    virtual bool Intersects(const Rectangle& rect) const;

    bool Contains(const Vector2f& position) const;
    bool Contains(const Rectangle& rect) const;
    bool Contains(const Vector2d& point) const;

    void Inflate(float x, float y);
    void Contract(float x, float y);

    void Offset(float x, float y);
    void Offset(const Vector2d& point);

    Rectangle& operator + (const Rectangle& rhs);
    Rectangle operator + (const Rectangle& rhs) const;

    void Constrain(Vector2f& p, const Vector2f& size = Vector2f::Zero) const;

    // Clip rectangle based on another rectangle. The edge case is based on the idea of inconsistency clipping.
    void Clip(const Rectangle& clip);

protected:

    float m_left;
    float m_top;

    float m_width;
    float m_height;
};

}