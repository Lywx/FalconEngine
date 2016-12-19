#include <FalconEngine/Graphics/Viewport.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Viewport::Viewport()
    : m_left(0.f),
      m_top(0.f),
      m_right(0.f),
      m_bottom(0.f),
      m_minDepth(0.f),
      m_maxDepth(0.f),
      m_titleSafeRatio(0.f)
{
}

Viewport::Viewport(const float& left, const float& top, const float& right, const float& bottom, const float& minDepth, const float& maxDepth, const float& titleSafeRatio /*= 0.8f*/)
    : m_left(left),
      m_top(top),
      m_right(right),
      m_bottom(bottom),
      m_minDepth(minDepth),
      m_maxDepth(maxDepth),
      m_titleSafeRatio(titleSafeRatio)
{
    CalculateTitleSafeArea();
}

Viewport::Viewport(const Viewport& rhs)
    : m_left(rhs.m_left),
      m_top(rhs.m_top),
      m_right(rhs.m_right),
      m_bottom(rhs.m_bottom),
      m_minDepth(rhs.m_minDepth),
      m_maxDepth(rhs.m_maxDepth),
      m_titleSafeRatio(rhs.m_titleSafeRatio)
{
    CalculateTitleSafeArea();
}

// Projects a world space (3D) position into screen space (2D).
// Parameter:
//     worldPosition: world position from 3d space.
//     projection: projection transform matrix
//     view: view transform matrix
//     world: world transform matrix
Vector3f Viewport::Project(const Vector3f& worldPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const
{
    Matrix4f transform = projection * view * world;
    Vector4f ndcPosition = transform * Vector4f(worldPosition, 1);

    Vector3f screenPosition;
    screenPosition.x = m_left + GetWidth() * 0.5f * (1.f + ndcPosition.x);
    screenPosition.y = m_top + GetHeight() * 0.5f * (1.f - ndcPosition.y);
    screenPosition.z = m_minDepth + ndcPosition.z;

    return screenPosition;
}

// Projects a screen space position (2D) into a world space position (3D).
//
// The Z component of screenPosition will be used as a ratio of the depth of the
// view frustum, using 0.f means the world space position returned will be at
// the near plane, using 1.f will place it at the far plane.
Vector3f Viewport::Unproject(const Vector3f& screenPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const
{
    Vector4f ndcPosition;

    // Inverse of windows transform, see Viewport::Project.
    ndcPosition.x = 2.f * (screenPosition.x - m_left) / GetWidth() - 1.f;
    ndcPosition.y = 2.f * (screenPosition.y - m_top) / GetHeight() - 1.f;
    ndcPosition.z = screenPosition.z - m_minDepth;
    ndcPosition.w = 1.f;

    Matrix4f inverseTransform = glm::inverse(projection * view * world);
    Vector4f worldPosition = inverseTransform * ndcPosition;

    worldPosition /= worldPosition.w;

    // Using glm::vec3(glm::vec4)
    return Vector3f(worldPosition);
}

void Viewport::CalculateTitleSafeArea()
{
    const float titleSafeWidth = GetWidth() * (1.f - m_titleSafeRatio);
    const float titleSafeHight = GetHeight() * (1.f - m_titleSafeRatio);

    m_titleSafeArea = Rectangle(m_left + titleSafeWidth * 0.5f, m_top + titleSafeHight * 0.5f, GetWidth() - titleSafeWidth, GetHeight() - titleSafeHight);
}

}
