#pragma once

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace FalconEngine
{

// Assume vector are column vector
class Vector3i;
class Vector3f : public glm::vec3
{
public:
    const static Vector3f Zero;
    const static Vector3f One;

    const static Vector3f UnitX;
    const static Vector3f UnitY;
    const static Vector3f UnitZ;

    // @summary Right handed cross product.
    static Vector3f Cross(const Vector3f& v1, const Vector3f& v2);
    static float    Dot(const Vector3f& v1, const Vector3f& v2);
    static Vector3f Normalize(const Vector3f& v);

    Vector3f();
    explicit Vector3f(const float& x);
    Vector3f(const float& x, const float& y, const float& z);

    // Implicit Conversion
    Vector3f(const glm::vec3& v);

    // Explicit Conversion
    explicit operator glm::vec3() const;
    explicit operator Vector3i() const;
};

std::string
to_string(const Vector3f& v);

/// Represents a point in 3D space
class Vector3i : public glm::ivec3
{
public:
    static const Vector3i Zero;

    Vector3i();
    Vector3i(const int x, const int y, const int z);
    Vector3i(const float x, const float y, const int z);

    // Implicit Conversion
    Vector3i(glm::ivec3 v);

    // Explicit Conversion
    explicit operator glm::ivec3() const;
    explicit operator Vector3f() const;
};

std::string
to_string(const Vector3i& v);

}
