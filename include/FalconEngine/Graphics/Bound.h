#pragma once

#include <FalconEngine/Graphics/Point3.h>
#include <FalconEngine/Graphics/Transform.h>

namespace FalconEngine {

// @Summary: represents a sphere of the specified center and radius.
class Bound
{
public:
    Bound();
    ~Bound();

    // Assignment.
    Bound& operator= (const Bound& bound);

    // Member access.  Any Bound must define a center and a radius.
    inline void SetCenter(const Point3& center);
    inline void SetRadius(float radius);
    inline const Point3& GetCenter() const;
    inline float GetRadius() const;

    // Operations on bounding volumes.
    int WhichSide(const HPlane& plane) const;
    void GrowToContain(const Bound& bound);
    void TransformBy(const Transform& transform, Bound& bound);
    void ComputeFromData(int numElements, int stride, const char *data);

    // Test for intersection of linear component and bound (points of
    // intersection not computed).  The linear component is parameterized by
    // P + t*D, where P is a point on the component (the origin) and D is a
    // unit-length direction vector.  The interval [tmin,tmax] is
    //   line:     tmin = -Mathf::MAX_REAL, tmax = Mathf::MAX_REAL
    //   ray:      tmin = 0.0f, tmax = Mathf::MAX_REAL
    //   segment:  tmin >= 0.0f, tmax > tmin
    bool TestIntersection(const Point3& origin, const AVector& direction,
                          float tmin, float tmax) const;

    // Test for intersection of the two stationary bounds.
    bool TestIntersection(const Bound& bound) const;

    // Test for intersection of the two moving bounds.  Velocity0 is that of
    // the calling Bound and velocity1 is that of the input bound.
    bool TestIntersection(const Bound& bound, float tmax,
                          const AVector& velocity0, const AVector& velocity1) const;

private:
    Point3 m_center;
    float m_radius;
};

#include "Bound.inl"

}
