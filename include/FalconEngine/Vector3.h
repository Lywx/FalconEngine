#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace FalconEngine {
namespace Math {

// Assume vector are column vector
struct Vector3 : glm::vec3
{
    const static Vector3 One;
    const static Vector3 Zero;
    const static Vector3 UnitX;
    const static Vector3 UnitY;
    const static Vector3 UnitZ;
    const static Vector3 UnitW;

    static Vector3 Normalize(const Vector3& v);
    static Vector3 Cross(const Vector3& v1, const Vector3& v2);
    static float   Dot(const Vector3& v1, const Vector3& v2);

    Vector3() : glm::vec3() {}
    Vector3(const float& x, const float& y, const float& z) : glm::vec3(x, y, z) {};

    // Copy Constructor
    Vector3(const Vector3& v) : glm::vec3(v) {};

    // Implicit Conversion
    Vector3(const glm::vec3& v) : glm::vec3(v) {};
};

}
}
