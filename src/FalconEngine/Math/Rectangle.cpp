#include <FalconEngine/Math/Rectangle.h>
#include <FalconEngine/Math.h>

namespace FalconEngine {
namespace Math {

const Rectangle Rectangle::Zero(0.f, 0.f, 0.f, 0.f);

Rectangle
Rectangle::From(float left, float top, float right, float bottom)
{
    Rectangle r(left, top, right - left, bottom - top);
    return r;
}

Rectangle::Rectangle()
    : m_left(0.f)
    , m_top(0.f)
    , m_width(0.f)
    , m_height(0.f)
{
}

Rectangle::Rectangle(int left, int top, int width, int height)
    : m_left(static_cast<float>(left))
    , m_top(static_cast<float>(top))
    , m_width(static_cast<float>(width))
    , m_height(static_cast<float>(height))
{
}

Rectangle::Rectangle(float left, float top, float width, float height)
    : m_left(left)
    , m_top(top)
    , m_width(width)
    , m_height(height)
{
}

bool
Rectangle::operator == (const Rectangle& r) const
{
    return IsEqual(m_left, r.Left())
           && IsEqual(m_top, r.Top())
           && IsEqual(m_width, r.Width())
           && IsEqual(m_height, r.Height());
}

bool
Rectangle::operator != (const Rectangle& r) const
{
    return !IsEqual(m_left, r.Left())
           || !IsEqual(m_top, r.Top())
           || !IsEqual(m_width, r.Width())
           || !IsEqual(m_height, r.Height());
}

bool
Rectangle::IsEmpty() const
{
    return IsEqual(m_width, 0.f) || IsEqual(m_height, 0.f);
}

Point2
Rectangle::Center() const
{
    return Point2(m_left + m_width * 0.5f,
                  m_top + m_height * 0.5f);
}

bool
Rectangle::Contains(float x, float y) const
{
    return x >= Left()
           && x <= Right()
           && y >= Top()
           && y <= Bottom();
}

bool
Rectangle::Contains(const Rectangle& rect) const
{
    if (rect.Top() < Top()
            || rect.Bottom() > Bottom()
            || rect.Left() < Left()
            || rect.Right() > Right())
    {
        return false;
    }

    return true;
}

bool
Rectangle::Contains(const Point2& point) const
{
    return Contains(
               static_cast<float>(point.x),
               static_cast<float>(point.y));
}

bool
Rectangle::Contains(const Vector2& position) const
{
    return Contains(position.x, position.y);
}

bool
Rectangle::Intersects(const Rectangle& rect) const
{
    return Left() < rect.Right()
           && Right() > rect.Left()
           && Top() < rect.Bottom()
           && Bottom() > rect.Top();
}

void
Rectangle::Constrain(Vector2& p, const Vector2& size/*=point::Zero*/) const
{
    float halfWidth = size.x * 0.5f;
    float halfHeight = size.y * 0.5f;

    if (p.x - halfWidth < m_left)
    {
        p.x = m_left;
    }

    if (p.x + halfWidth > Right())
    {
        p.x = Right() - size.x;
    }

    if (p.y - halfHeight < m_top)
    {
        p.y = m_top;
    }

    if (p.y + halfHeight >= Bottom())
    {
        p.y = Bottom() - size.y;
    }
}

void
Rectangle::Clip(const Rectangle& clip)
{
    if (m_left < clip.Left())
    {
        auto offset = clip.Left() - m_left;
        m_width -= offset;
        m_left = clip.Left();
    }

    if (m_top < clip.Top())
    {
        auto offset = clip.Top() - m_top;
        m_height -= offset;
        m_top = clip.Top();
    }

    if (Right() > clip.Right())
    {
        auto offset = Right() - clip.Right();
        m_width -= offset;
    }

    if (Bottom() > clip.Bottom())
    {
        auto offset = Bottom() - clip.Bottom();
        m_height -= offset;
    }
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
Rectangle::Offset(const Point2& point)
{
    Offset(static_cast<float>(point.x), static_cast<float>(point.y));
}

Rectangle&
Rectangle::operator + (const Rectangle& rhs)
{
    m_left += rhs.Left();
    m_top += rhs.Top();
    m_width += rhs.Width();
    m_height += rhs.Height();
    return *this;
}

Rectangle
Rectangle::operator + (const Rectangle& rhs) const
{
    return Rectangle(m_left + rhs.Left(), m_top + rhs.Top(), m_width + rhs.Width(), m_height + rhs.Height());
}

}
}
