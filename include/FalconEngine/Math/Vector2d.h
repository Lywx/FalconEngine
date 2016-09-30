#pragma once

#include <glm/vec2.hpp>

#include "Vector2f.h"

namespace FalconEngine {

/// Represents a point in 2D space
class Vector2d : public glm::ivec2
{
public:
    static const Vector2d Zero;

    Vector2d();

    Vector2d(const int x, const int y);

    Vector2d(const float x, const float y);

    // Implicit Conversion
    Vector2d(const glm::ivec2 v);

    // Explicit Conversion
    explicit operator glm::ivec2() const;
    explicit operator Vector2f() const;
};

}