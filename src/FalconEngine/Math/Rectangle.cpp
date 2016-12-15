#include <FalconEngine/Math/Rectangle.h>
#include <FalconEngine/Math/Function.h>

namespace FalconEngine
{

const Rectangle Rectangle::Zero(0.f, 0.f, 0.f, 0.f);

Rectangle
Rectangle::CreateBounds(float left, float top, float right, float bottom)
{
    Rectangle r(left, top, right - left, bottom - top);
    return r;
}

Rectangle::Rectangle() :
    m_left(0.f),
    m_top(0.f),
    m_width(0.f),
    m_height(0.f)
{
}

Rectangle::Rectangle(int left, int top, int width, int height) :
    m_left(static_cast<float>(left)),
    m_top(static_cast<float>(top)),
    m_width(static_cast<float>(width)),
    m_height(static_cast<float>(height))
{
}

Rectangle::Rectangle(float left, float top, float width, float height) :
    m_left(left),
    m_top(top),
    m_width(width),
    m_height(height)
{
}

bool
Rectangle::Empty() const
{
    return Equal(m_width, 0.f) || Equal(m_height, 0.f);
}

bool
Rectangle::Contains(float x, float y) const
{
    return x >= m_left
           && x <= GetRight()
           && y >= m_top
           && y <= GetBottom();
}

bool
Rectangle::Contains(const Rectangle& rect) const
{
    if (rect.m_top < m_top
            || rect.GetBottom() > GetBottom()
            || rect.m_left < m_left
            || rect.GetRight() > GetRight())
    {
        return false;
    }

    return true;
}

bool
Rectangle::Contains(const Vector2d& position) const
{
    return Contains(
               static_cast<float>(position.x),
               static_cast<float>(position.y));
}

bool
Rectangle::Contains(const Vector2f& position) const
{
    return Contains(position.x, position.y);
}

bool
Rectangle::Intersects(const Rectangle& rect) const
{
    return m_left < rect.GetRight()
           && GetRight() > rect.m_left
           && m_top < rect.GetBottom()
           && GetBottom() > rect.m_top;
}

void
Rectangle::Inflate(float x, float y)
{
    m_left -= x * 0.5f;
    m_width += x;

    m_top -= y * 0.5f;
    m_height += y;
}

void
Rectangle::Contract(float x, float y)
{
    m_left += x * 0.5f;
    m_width -= x;

    m_top += y * 0.5f;
    m_height -= y;
}

void
Rectangle::Offset(float x, float y)
{
    m_left += x;
    m_top += y;
}

void
Rectangle::Offset(const Vector2d& vec)
{
    Offset(static_cast<float>(vec.x),
           static_cast<float>(vec.y));
}

bool
operator==(const Rectangle& lhs, const Rectangle& rhs)
{
    return Equal(lhs.m_left, rhs.m_left)
           && Equal(lhs.m_top, rhs.m_top)
           && Equal(lhs.m_width, rhs.m_width)
           && Equal(lhs.m_height, rhs.m_height);
}

bool
operator!=(const Rectangle& lhs, const Rectangle& rhs)
{
    return !(lhs == rhs);
}

}