#include <FalconEngine/Math/Vector2d.h>

namespace FalconEngine {

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Vector2d Vector2d::Zero = glm::ivec2(0.f, 0.f);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Vector2d::Vector2d() : glm::ivec2() {}

Vector2d::Vector2d(const int x, const int y) : glm::ivec2(x, y) {}

Vector2d::Vector2d(const float x, const float y) : glm::ivec2(x, y) {}

Vector2d::Vector2d(const glm::ivec2 v) : glm::ivec2(v) {}

Vector2d::operator Vector2f() const
{
    return Vector2f(float(x), float(y));
}

Vector2d::operator glm::ivec2() const
{
    return glm::ivec2(x, y);
}

}
