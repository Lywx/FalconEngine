#pragma once

#include <glm/vec2.hpp>

#include <FalconEngine/Math/Vector3f.h>

namespace FalconEngine {

/// Represents a point in 3D space
class Vector3d : public glm::ivec3
{
public:
    static const Vector3d Zero;

    Vector3d();

    Vector3d(const int x, const int y, const int z);

    Vector3d(const float x, const float y, const int z);

    // Implicit Conversion
    Vector3d(glm::ivec3 v);

    // Explicit Conversion
    explicit operator glm::ivec3() const;
    explicit operator Vector3f() const;
};

}
