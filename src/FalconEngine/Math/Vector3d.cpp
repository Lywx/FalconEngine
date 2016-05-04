#include <FalconEngine/Math/Vector3d.h>

namespace FalconEngine {

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
static const Vector3d Zero = glm::ivec3(0, 0, 0);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector3d::Vector3d() : glm::ivec3() {}

Vector3d::Vector3d(const int x, const int y, const int z) : glm::ivec3(x, y, z) {}

Vector3d::Vector3d(const float x, const float y, const int z) : glm::ivec3(x, y, z) {}

/************************************************************************/
/* Conversion Members                                                   */
/************************************************************************/
Vector3d::Vector3d(glm::ivec3 v) : glm::ivec3(v) { }

Vector3d::operator Vector3f() const
{
    return Vector3f(static_cast<float>(x),
                    static_cast<float>(y),
                    static_cast<float>(z));
}

}