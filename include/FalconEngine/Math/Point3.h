#pragma once

#include <glm/vec2.hpp>

#include "Vector3.h"

namespace FalconEngine {
namespace Math {

/// Represents a point in 3D space
struct Point3 : glm::ivec3
{
    static const Point3 Zero;

    Point3() : glm::ivec3() {}
    Point3(const int x, const int y, const int z) : glm::ivec3(x, y, z) {}
    Point3(const float x, const float y, const int z) : glm::ivec3(x, y, z) {}

    operator Vector3() const
    {
        return Vector3(static_cast<float>(x),
                       static_cast<float>(y),
                       static_cast<float>(z));
    }
};

}
}
