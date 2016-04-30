#include <FalconEngine/Graphics/Viewport.h>

namespace FalconEngine {
namespace Graphics {

Viewport::Viewport()
    : m_left(0.f)
    , m_top(0.f)
    , m_right(0.f)
    , m_bottom(0.f)
    , m_minDepth(0.f)
    , m_maxDepth(0.f)
    , m_titleSafeRatio(0.f)
{
}

Viewport::Viewport(const float& left, const float& top, const float& right, const float& bottom, const float& minDepth, const float& maxDepth, const float& titleSafeRatio /*= 0.8f*/)
    : m_left(left)
    , m_top(top)
    , m_right(right)
    , m_bottom(bottom)
    , m_minDepth(minDepth)
    , m_maxDepth(maxDepth)
    , m_titleSafeRatio(titleSafeRatio)
{
    CalculateTitleSafeArea();
}

Viewport::Viewport(const Viewport& rhs)
    : m_left(rhs.m_left)
    , m_top(rhs.m_top)
    , m_right(rhs.m_right)
    , m_bottom(rhs.m_bottom)
    , m_minDepth(rhs.m_minDepth)
    , m_maxDepth(rhs.m_maxDepth)
    , m_titleSafeRatio(rhs.m_titleSafeRatio)
{
    CalculateTitleSafeArea();
}

Viewport& Viewport::operator = (const Viewport& rhs)
{
    m_left           = rhs.m_left;
    m_top            = rhs.m_top;
    m_right          = rhs.m_right;
    m_bottom         = rhs.m_bottom;
    m_minDepth       = rhs.m_minDepth;
    m_maxDepth       = rhs.m_maxDepth;
    m_titleSafeRatio = rhs.m_titleSafeRatio;

    CalculateTitleSafeArea();

    return *this;
}

// Projects a world space (3D) position into screen space (2D).
// Parameter:
//     worldPosition: world position from 3d space.
//     projection: projection transform matrix
//     view: view transform matrix
//     world: world transform matrix
Math::Vector3 Viewport::Project(const Math::Vector3& worldPosition, const Math::Matrix& projection, const Math::Matrix& view, const Math::Matrix& world) const
{
    Math::Matrix transform = projection * view * world;
    Math::Vector4 ndcPosition = transform * Math::Vector4(worldPosition, 1);

    Math::Vector3 screenPosition;
    screenPosition.x = m_left + Width() * 0.5f * (1.f + ndcPosition.x);
    screenPosition.y = m_top + Height() * 0.5f * (1.f - ndcPosition.y);
    screenPosition.z = m_minDepth + ndcPosition.z;

    return screenPosition;
}

// Projects a screen space position (2D) into a world space position (3D).
//
// The Z component of screenPosition will be used as a ratio of the depth of the
// view frustum, using 0.f means the world space position returned will be at
// the near plane, using 1.f will place it at the far plane.
Math::Vector3 Viewport::Unproject(const Math::Vector3& screenPosition, const Math::Matrix& projection, const Math::Matrix& view, const Math::Matrix& world) const
{
    Math::Vector4 ndcPosition;

    // Inverse of windows transform, see Viewport::Project.
    ndcPosition.x = 2.f * (screenPosition.x - m_left) / Width() - 1.f;
    ndcPosition.y = 2.f * (screenPosition.y - m_top) / Height() - 1.f;
    ndcPosition.z = screenPosition.z - m_minDepth;
    ndcPosition.w = 1.f;

    Math::Matrix inverseTransform = glm::inverse(projection * view * world);
    Math::Vector4 worldPosition = inverseTransform * ndcPosition;

    worldPosition /= worldPosition.w;

    // Using glm::vec3(glm::vec4)
    return Math::Vector3(worldPosition);
}

void Viewport::CalculateTitleSafeArea()
{
    const float titleSafeWidth = Width() * (1.f - m_titleSafeRatio);
    const float titleSafeHight = Height() * (1.f - m_titleSafeRatio);

    m_titleSafeArea = Math::Rectangle(m_left + titleSafeWidth * 0.5f, m_top + titleSafeHight * 0.5f, Width() - titleSafeWidth, Height() - titleSafeHight);
}

}
}
