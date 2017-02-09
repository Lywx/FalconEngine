#include <FalconEngine/Graphics/Renderers/Viewport.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Viewport::Viewport()
    : mLeft(0.f),
      mBottom(0.f),
      mRight(0.f),
      mTop(0.f),
      mMinDepth(0.f),
      mMaxDepth(0.f),
      mTitleSafeRatio(0.f)
{
}

Viewport::Viewport(const float& left, const float& bottom, const float& right, const float& top, const float& minDepth, const float& maxDepth, const float& titleSafeRatio /*= 0.8f*/)
    : mLeft(left),
      mBottom(bottom),
      mRight(right),
      mTop(top),
      mMinDepth(minDepth),
      mMaxDepth(maxDepth),
      mTitleSafeRatio(titleSafeRatio)
{
    CalculateTitleSafeArea();
}

Viewport::Viewport(const Viewport& rhs)
    : mLeft(rhs.mLeft),
      mBottom(rhs.mBottom),
      mRight(rhs.mRight),
      mTop(rhs.mTop),
      mMinDepth(rhs.mMinDepth),
      mMaxDepth(rhs.mMaxDepth),
      mTitleSafeRatio(rhs.mTitleSafeRatio)
{
    CalculateTitleSafeArea();
}

void
Viewport::Set(const float& left, const float& bottom, const float& right, const float& top, const float& minDepth, const float& maxDepth, const float& titleSafeRatio)
{
    mLeft = left;
    mBottom = bottom;
    mRight = right;
    mTop = top;
    mMinDepth = minDepth;
    mMaxDepth = maxDepth;
    mTitleSafeRatio = titleSafeRatio;

    CalculateTitleSafeArea();
}

Vector3f
Viewport::Project(const Vector3f& worldPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const
{
    Matrix4f transform = projection * view * world;
    Vector4f clipPosition = transform * Vector4f(worldPosition, 1);

    // NOTE(Wuxiang): OpenGL's NDC uses left-handed coordinate system. The
    // perspective transformation invert the coordinate system.
    Vector4f ndcPosition;

    // Perspective division
    if (clipPosition.w > 0.f)
    {
        ndcPosition = clipPosition / clipPosition.w;
    }

    Vector3f screenPosition;

    // @ref David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006, P56
    // @ref Andre LaMothe Tricks of the 3D Game Programming Gurus_ Advanced 3D Graphics and Rasterization, 2003, P555

    // NOTE(Wuxiang): Screen space transform, (0, 0) is the bottom-left corner.
    // x = [-1, 1] -> [left, right], y = [-1, 1] -> [bottom, top]. The formula is
    // the same as the one used in glViewport.
    screenPosition.x = mLeft + GetWidth() * 0.5f * (1.f + ndcPosition.x);
    screenPosition.y = mBottom + GetHeight() * 0.5f * (1.f + ndcPosition.y);

    // NOTE(Wuxiang): Linear mapping simulate the glDepthRange.
    screenPosition.z = 0.5f * (mMaxDepth - mMinDepth) * ndcPosition.z + 0.5f * (mMinDepth + mMaxDepth);

    return screenPosition;
}

Vector3f
Viewport::Unproject(const Vector3f& screenPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const
{
    Vector4f ndcPosition;

    // Inverse of screen space transform.
    ndcPosition.x = 2.f * (screenPosition.x - mLeft) / GetWidth() - 1.f;
    ndcPosition.y = 2.f * (screenPosition.y - mBottom) / GetHeight() - 1.f;

    // Inverse of glDepthRange linear mapping.
    ndcPosition.z = (2.f * screenPosition.z - mMaxDepth - mMinDepth) / (mMaxDepth - mMinDepth);
    ndcPosition.w = 1.f;

    Matrix4f inverseTransform = Matrix4f::Inverse(projection * view * world);
    Vector4f worldPosition = inverseTransform * ndcPosition;

    // Perspective division, because we need 3-dimension coordinate rather than
    // the homogeneous coordinates.
    worldPosition /= worldPosition.w;

    // Using glm::vec3(glm::vec4)
    return Vector3f(worldPosition);
}

void
Viewport::CalculateTitleSafeArea()
{
    const float titleSafeWidth = GetWidth() * (1.f - mTitleSafeRatio);
    const float titleSafeHight = GetHeight() * (1.f - mTitleSafeRatio);

    mTitleSafeArea = Rectangle(mLeft + titleSafeWidth * 0.5f, mTop + titleSafeHight * 0.5f, GetWidth() - titleSafeWidth, GetHeight() - titleSafeHight);
}

}
