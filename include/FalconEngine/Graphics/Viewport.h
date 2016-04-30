#pragma once

#include <FalconEngine/Math/Rectangle.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Matrix.h>

namespace FalconEngine {
namespace Graphics {

/// Describe the clip space region.
class Viewport
{
public:
    Viewport();

    Viewport
    (
        const float& left,
        const float& top,
        const float& right,
        const float& bottom,
        const float& minDepth,
        const float& maxDepth,
        const float& titleSafeRatio = 0.8f
    );

    Viewport(const Viewport& rhs);

    float Viewport::Left()   const { return m_left; }
    float Viewport::Right()  const { return m_right; }
    float Viewport::Top()    const { return m_top; }
    float Viewport::Bottom() const { return m_bottom; }

    float Viewport::Width() const { return m_right - m_left; }
    float Viewport::Height() const { return m_bottom - m_top; }

    float Viewport::Aspect() const { return Width() / Height(); }

    float Viewport::MinDepth() const { return m_minDepth; }
    float Viewport::MaxDepth() const { return m_maxDepth; }

    Math::Vector2 Center() const { return Math::Vector2(Left() + Width() / 2, Top() + Height() / 2); }
    Math::Rectangle TitleSafeArea() const { return m_titleSafeArea; }

    Viewport& operator = (const Viewport& rhs);

    ///
    /// Project
    ///
    /// Projects a world space position unto the viewport 2D space.
    ///
    /// worldPosition - A 3D space position
    /// projection  - The projection matrix
    /// view - The camera's view matrix
    /// world - The world matrix
    ///
    /// returns a vector3 in which x,y will be screen coordinates.
    ///
    Math::Vector3 Project(const Math::Vector3& worldPosition, const Math::Matrix& projection, const Math::Matrix& view, const Math::Matrix& world) const;

    ///
    /// Unproject
    ///
    /// Converts a screen position into a world space position. Typically unproject is used to generate a ray that spans the view frustum.
    /// Unproject the screen coordinate the first time using 0.0 as the Z value, and a second time using 1.0 as the Z value, then calculate
    /// a direction vector between these two world space points and normalize it. The resulting ray may be used to perform interesection testing.
    ///
    /// screenPosition - A screen space position, the z component represents a ratio of depth.
    /// projection  - The projection matrix
    /// view - The camera's view matrix
    /// world - The world matrix
    ///
    /// Returns a world space position.
    ///
    Math::Vector3 Unproject(const Math::Vector3& screenPosition, const Math::Matrix& projection, const Math::Matrix& view, const Math::Matrix& world) const;


protected:

    float m_left;
    float m_top;
    float m_right;
    float m_bottom;

    float m_minDepth;
    float m_maxDepth;

    float m_titleSafeRatio;
    Math::Rectangle m_titleSafeArea;

    void CalculateTitleSafeArea();
};

}
}
