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
    mLeft(0.f),
    mTop(0.f),
    mWidth(0.f),
    mHeight(0.f)
{
}

Rectangle::Rectangle(int left, int top, int width, int height) :
    mLeft(static_cast<float>(left)),
    mTop(static_cast<float>(top)),
    mWidth(static_cast<float>(width)),
    mHeight(static_cast<float>(height))
{
}

Rectangle::Rectangle(float left, float top, float width, float height) :
    mLeft(left),
    mTop(top),
    mWidth(width),
    mHeight(height)
{
}

bool
Rectangle::Empty() const
{
    return Equal(mWidth, 0.f) || Equal(mHeight, 0.f);
}

bool
Rectangle::Contains(float x, float y) const
{
    return x >= mLeft
           && x <= GetRight()
           && y >= mTop
           && y <= GetBottom();
}

bool
Rectangle::Contains(const Rectangle& rect) const
{
    if (rect.mTop < mTop
            || rect.GetBottom() > GetBottom()
            || rect.mLeft < mLeft
            || rect.GetRight() > GetRight())
    {
        return false;
    }

    return true;
}

bool
Rectangle::Contains(const Vector2i& position) const
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
    return mLeft < rect.GetRight()
           && GetRight() > rect.mLeft
           && mTop < rect.GetBottom()
           && GetBottom() > rect.mTop;
}

void
Rectangle::Inflate(float x, float y)
{
    mLeft -= x * 0.5f;
    mWidth += x;

    mTop -= y * 0.5f;
    mHeight += y;
}

void
Rectangle::Contract(float x, float y)
{
    mLeft += x * 0.5f;
    mWidth -= x;

    mTop += y * 0.5f;
    mHeight -= y;
}

void
Rectangle::Offset(float x, float y)
{
    mLeft += x;
    mTop += y;
}

void
Rectangle::Offset(const Vector2i& vec)
{
    Offset(static_cast<float>(vec.x),
           static_cast<float>(vec.y));
}

bool
operator==(const Rectangle& lhs, const Rectangle& rhs)
{
    return Equal(lhs.mLeft, rhs.mLeft)
           && Equal(lhs.mTop, rhs.mTop)
           && Equal(lhs.mWidth, rhs.mWidth)
           && Equal(lhs.mHeight, rhs.mHeight);
}

bool
operator!=(const Rectangle& lhs, const Rectangle& rhs)
{
    return !(lhs == rhs);
}

}