#pragma once

#include <glm/vec2.hpp>

namespace FalconEngine {

// Assume vector are column vector
struct Vector2f : glm::vec2
{
    static const Vector2f One;
    static const Vector2f Zero;
    static const Vector2f UnitX;
    static const Vector2f UnitY;

    Vector2f() : glm::vec2() {};
    Vector2f(const float& x, const float& y) : glm::vec2(x, y) {};

    // Implicit Conversion
    Vector2f(const glm::vec2& v) : glm::vec2(v) {};
};

}