#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace FalconEngine {

// Assume vector are column vector
class Vector4 : public glm::vec4
{
public:
    const static Vector4 One;
    const static Vector4 Zero;
    const static Vector4 UnitX;
    const static Vector4 UnitY;
    const static Vector4 UnitZ;
    const static Vector4 UnitW;

    Vector4();

    Vector4(const glm::vec3& vec3, const float w);

    // Copy Constructor
    Vector4(const Vector4& v);

    // Implicit Conversion
    Vector4(const glm::vec4& v);
};

}
