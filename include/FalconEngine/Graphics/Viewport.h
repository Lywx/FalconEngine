#pragma once

#include <FalconEngine/Math/Rectangle2f.h>
#include <FalconEngine/Math/Vector2f.h>
#include <FalconEngine/Math/Vector3f.h>
#include <FalconEngine/Math/Vector4f.h>
#include <FalconEngine/Math/Matrix4f.h>

namespace FalconEngine {

// @Summary: Describe the clip space region.
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

    inline float Left() const;

    inline float Right() const;

    inline float Top() const;

    inline float Bottom() const;

    inline float Width() const;

    inline float Height() const;

    inline float Aspect() const;

    inline float MinDepth() const;

    inline float MaxDepth() const;

    inline Vector2f Center() const;

    Viewport& operator= (const Viewport& rhs);

    // @Summary: Projects a world space position unto the viewport 2D space.
    //
    // @Params:
    // worldPosition - A 3D space position
    // projection - The projection matrix
    // view - The camera's view matrix
    // world - The world matrix
    //
    // @Return: A vector3 in which x,y will be screen coordinates.
    Vector3f Project(const Vector3f& worldPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const;

    // @Summary: Converts a screen position into a world space position. Typically unproject is used to generate a ray that spans the view frustum.
    // Unproject the screen coordinate the first time using 0.0 as the Z value, and a second time using 1.0 as the Z value, then calculate
    // a direction vector between these two world space points and normalize it. The resulting ray may be used to perform interesection testing.
    //
    // @Params:
    // screenPosition - A screen space position, the z component represents a ratio of depth.
    // projection - The projection matrix
    // view - The camera's view matrix
    // world - The world matrix
    //
    // @Return: A world space position.
    Vector3f Unproject(const Vector3f& screenPosition, const Matrix4f& projection, const Matrix4f& view, const Matrix4f& world) const;


protected:

    float m_left;
    float m_top;
    float m_right;
    float m_bottom;

    float m_minDepth;
    float m_maxDepth;

    float m_titleSafeRatio;
    Rectangle2f m_titleSafeArea;

    void CalculateTitleSafeArea();
};

#include "Viewport.inl"

}
