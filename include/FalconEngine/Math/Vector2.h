#pragma once

#include <glm/vec2.hpp>

namespace FalconEngine
{

// Assume vector are column vector
class Vector2f : public glm::vec2
{
public:
    static const Vector2f One;
    static const Vector2f Zero;
    static const Vector2f UnitX;
    static const Vector2f UnitY;

    Vector2f();

    Vector2f(const float& x, const float& y);

    // Implicit Conversion
    Vector2f(const glm::vec2& v);
};

/// Represents a point in 2D space
class Vector2i : public glm::ivec2
{
public:
    static const Vector2i Zero;

    Vector2i();

    Vector2i(const int x, const int y);

    Vector2i(const float x, const float y);

    // Implicit Conversion
    Vector2i(const glm::ivec2 v);

    // Explicit Conversion
    explicit operator glm::ivec2() const;
    explicit operator Vector2f() const;
};

}