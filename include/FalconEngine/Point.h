#pragma once

#include <glm/vec2.hpp>

#include "Vector2.h"

namespace FalconEngine {
namespace Math {

/// Represents a point in 2D space
struct Point : glm::ivec2
{
    static const Point Zero;

    Point() : glm::ivec2() {}
    Point(const int x, const int y) : glm::ivec2(x, y) {}
    Point(const float x, const float y) : glm::ivec2(x, y) {}

    operator Vector2() const
    {
        return Vector2(static_cast<float>(x),
                       static_cast<float>(y));
    }
};

}
}