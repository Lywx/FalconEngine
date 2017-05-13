#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Math/Rectangle.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class Matrix4f;

// @summary Describe the clip space region.
class FALCON_ENGINE_API Viewport
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Viewport();

    // @note the coordinate should follow OpenGl convention that top should be
    // higher (numerically) than bottom.
    Viewport(const float& left,
             const float& bottom,
             const float& right,
             const float& top,
             const float& minDepth,
             const float& maxDepth,
             const float& titleSafeRatio = 0.8f);
    Viewport(const Viewport& rhs);

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    float
    GetWidth() const;

    float
    GetHeight() const;

    float
    GetAspect() const;

    Vector2f
    GetCenter() const;

    void
    Set(const float& left,
        const float& bottom,
        const float& right,
        const float& top,
        const float& minDepth,
        const float& maxDepth,
        const float& titleSafeRatio = 0.8f);

    // @summary Projects a world space position unto the viewport 2D space.
    // @param worldPosition - A 3D space position
    // @param projection - The projection matrix
    // @param view - The camera's view matrix
    // @param world - The world matrix
    // @return A vector3 in which x, y, z will be in window (or screen) coordinates.
    // The range for x, y, z in window coordinate would be [left, right], [bottom, top] and [0, 1] respectively.
    Vector3f
    Project(const Vector3f& worldPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const;

    // @summary Converts a screen position into a world space position. Typically unproject is used to generate a ray that spans the view frustum.
    // Unproject the screen coordinate the first time using 0.0 as the Z value, and a second time using 1.0 as the Z value, then calculate
    // a direction vector between these two world space points and normalize it. The resulting ray may be used to perform intersection testing.
    //
    // @param screenPosition - A screen space position, the z component represents
    // a ratio of depth. The range for x, y, z in window coordinate would be
    // [left, right], [bottom, top] and [0, 1] respectively.
    // @param projection - The projection matrix
    // @param view - The camera's view matrix
    // @param world - The world matrix
    // @return A world space position.
    Vector3f
    Unproject(const Vector3f& screenPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const;

private:
    void
    CalculateTitleSafeArea();

public:
    float     mLeft;
    float     mBottom;
    float     mRight;
    float     mTop;

    float     mMinDepth;
    float     mMaxDepth;

    float     mTitleSafeRatio;
    Rectangle mTitleSafeArea;
};

inline float
Viewport::GetWidth() const
{
    return mRight - mLeft;
}

inline float
Viewport::GetHeight() const
{
    return mBottom - mTop;
}

inline float
Viewport::GetAspect() const
{
    return GetWidth() / GetHeight();
}

inline Vector2f
Viewport::GetCenter() const
{
    return Vector2f(mLeft + GetWidth() / 2, mTop + GetHeight() / 2);
}

}
