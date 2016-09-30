#pragma once

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace FalconEngine {

// Assume vector are column vector
class Vector3d;
class Vector3f : public glm::vec3
{
public:
    const static Vector3f Zero;
    const static Vector3f One;

    const static Vector3f UnitX;
    const static Vector3f UnitY;
    const static Vector3f UnitZ;

    Vector3f();

    Vector3f(const float& x);

    Vector3f(const float& x, const float& y, const float& z);

    // Implicit Conversion
    Vector3f(const glm::vec3& v);

    // Explicit Conversion
    explicit operator glm::vec3() const;
    explicit operator Vector3d() const;

    static Vector3f Cross(const Vector3f& v1, const Vector3f& v2);
    static float    Dot(const Vector3f& v1, const Vector3f& v2);
    static Vector3f Normalize(const Vector3f& v);
};

#include "Vector3f.inl"

}
