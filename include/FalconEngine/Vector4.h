#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace FalconEngine {
namespace Math {

// Assume vector are column vector
struct Vector4 : glm::vec4
{
    const static Vector4 One;
    const static Vector4 Zero;
    const static Vector4 UnitX;
    const static Vector4 UnitY;
    const static Vector4 UnitZ;
    const static Vector4 UnitW;

    Vector4() : glm::vec4() {};

    Vector4(const glm::vec3& vec3, const float w) : glm::vec4(vec3, w) {};

    // Copy Constructor
    Vector4(const Vector4& v) : glm::vec4(v) {};

    // Implicit Conversion
    Vector4(const glm::vec4& v) : glm::vec4(v) {};
};

}
}
