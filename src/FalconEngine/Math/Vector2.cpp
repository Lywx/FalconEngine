#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Vector2f Vector2f::Zero  = Vector2f(0.f, 0.f);
const Vector2f Vector2f::One   = Vector2f(1.f, 1.f);
const Vector2f Vector2f::UnitX = Vector2f(1.f, 0.f);
const Vector2f Vector2f::UnitY = Vector2f(0.f, 1.f);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector2f::Vector2f()
{
}

Vector2f::Vector2f(const float& x, const float& y)
    : glm::vec2(x, y)
{
}

// Implicit Conversion
Vector2f::Vector2f(const glm::vec2& v)
    : glm::vec2(v)
{
}

std::string
to_string(const Vector2f& v)
{
    return std::string("(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")");
}

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Vector2i Vector2i::Zero = glm::ivec2(0.f, 0.f);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector2i::Vector2i() :
    glm::ivec2()
{
}

Vector2i::Vector2i(const int x, const int y) :
    glm::ivec2(x, y)
{
}

Vector2i::Vector2i(const float x, const float y) :
    glm::ivec2(x, y)
{
}

Vector2i::Vector2i(const glm::ivec2 v) :
    glm::ivec2(v)
{
}

Vector2i::operator Vector2f() const
{
    return Vector2f(float(x), float(y));
}

Vector2i::operator glm::ivec2() const
{
    return glm::ivec2(x, y);
}

std::string
to_string(const Vector2i& v)
{
    return std::string("(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")");
}

}
