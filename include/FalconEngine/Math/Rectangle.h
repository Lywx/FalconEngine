#pragma once

#include <FalconEngine/Math/Common.h>

#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

// @summary axis-aligned rectangle in 2D space
class FALCON_ENGINE_API Rectangle
{
public:
    static const Rectangle Zero;

    static Rectangle
    CreateBounds(float left, float top, float right, float bottom);

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

    Vector2i
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
    Contains(const Vector2i& position) const;

    void
    Inflate(float x, float y);

    void
    Contract(float x, float y);

    void
    Offset(float x, float y);

    void
    Offset(const Vector2i& vec);

public:
    float mLeft;
    float mTop;

    float mWidth;
    float mHeight;
};

bool operator==(const Rectangle&lhs, const Rectangle& rhs);
bool operator!=(const Rectangle&lhs, const Rectangle& rhs);

inline float
Rectangle::GetRight() const
{
    return mLeft + mWidth;
}

inline void
Rectangle::SetRight(float right)
{
    auto offsetPlusWidth = right - mLeft;
    auto offsetForLeft = offsetPlusWidth - mWidth;
    mLeft += offsetForLeft;
}

inline float
Rectangle::GetBottom() const
{
    return mTop + mHeight;
}

inline void
Rectangle::SetBottom(float bottom)
{
    mTop = bottom - mHeight;
}

inline Vector2f
Rectangle::GetPosition() const
{
    return Vector2f(mLeft, mTop);
}

inline void
Rectangle::SetPosition(const Vector2f& position)
{
    mLeft = position.x;
    mTop = position.y;
}

inline Vector2f
Rectangle::GetSize() const
{
    return Vector2f(mWidth, mHeight);
}

inline void
Rectangle::SetSize(const Vector2f& size)
{
    mWidth = size.x;
    mHeight = size.y;
}

inline Vector4f
Rectangle::GetExtents() const
{
    return glm::vec4(mLeft, mTop, GetRight(), GetBottom());
}

inline void
Rectangle::SetExtents(const Vector4f extents)
{
    mLeft   = extents.x;
    mTop    = extents.y;
    mWidth  = extents.z - mLeft;
    mHeight = extents.w - mTop;
}

inline Vector2i
Rectangle::GetCenter() const
{
    return Vector2i(mLeft + mWidth * 0.5f,
                    mTop + mHeight * 0.5f);
}

inline void
Rectangle::SetCenter(const Vector2f& center)
{
    mLeft = center.x - mWidth / 2;
    mTop  = center.y - mHeight / 2;
}

}