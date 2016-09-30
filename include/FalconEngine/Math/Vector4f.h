#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace FalconEngine {

// Assume vector are column vector
class Vector3f;
class Vector4f : public glm::vec4
{
public:
    const static Vector4f One;
    const static Vector4f Zero;
    const static Vector4f UnitX;
    const static Vector4f UnitY;
    const static Vector4f UnitZ;
    const static Vector4f UnitW;

    Vector4f();

    Vector4f(const float x, const float y, const float z, const float w);

    Vector4f(const Vector3f& v, const float w);

    // Implicit Conversion
    Vector4f(const glm::vec4& v);
};

}
