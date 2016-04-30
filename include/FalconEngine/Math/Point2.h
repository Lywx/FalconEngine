#pragma once

#include <glm/vec2.hpp>

#include "Vector2.h"

namespace FalconEngine {
namespace Math {

/// Represents a point in 2D space
struct Point2 : glm::ivec2
{
    static const Point2 Zero;

    Point2() : glm::ivec2() {}
    Point2(const int x, const int y) : glm::ivec2(x, y) {}
    Point2(const float x, const float y) : glm::ivec2(x, y) {}

    operator Vector2() const
    {
        return Vector2(static_cast<float>(x),
                       static_cast<float>(y));
    }
};

}
}