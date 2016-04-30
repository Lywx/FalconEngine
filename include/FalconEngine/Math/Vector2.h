#pragma once

#include <glm/vec2.hpp>

namespace FalconEngine {
namespace Math {

// Assume vector are column vector
struct Vector2 : glm::vec2
{
    static const Vector2 One;
    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;

    Vector2() : glm::vec2() {};
    Vector2(const float& x, const float& y) : glm::vec2(x, y) {};

    // Implicit Conversion
    Vector2(const glm::vec2& v) : glm::vec2(v) {};
};

}
}