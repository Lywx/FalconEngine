#include <FalconEngine/Math/Vector2f.h>

namespace FalconEngine {

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

}
