#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{


/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Vector3f Vector3f::Zero  = glm::vec3(0.f, 0.f, 0.f);
const Vector3f Vector3f::One   = glm::vec3(1.f, 1.f, 1.f);

const Vector3f Vector3f::UnitX = glm::vec3(1.f, 0.f, 0.f);
const Vector3f Vector3f::UnitY = glm::vec3(0.f, 1.f, 0.f);
const Vector3f Vector3f::UnitZ = glm::vec3(0.f, 0.f, 1.f);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector3f::Vector3f() : glm::vec3() {}

Vector3f::Vector3f(const float& x) : glm::vec3(x)
{
}

Vector3f::Vector3f(const float& x, const float& y, const float& z) : glm::vec3(x, y, z) {};

// Implicit Conversion
Vector3f::Vector3f(const glm::vec3& v) : glm::vec3(v)
{
}

// Explicit Conversion
Vector3f::operator glm::vec3() const
{
    return glm::vec3(x, y, z);
}

Vector3f::operator Vector3i() const
{
    return Vector3i(int(x), int(y), int(z));
}

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
static const Vector3i Zero = glm::ivec3(0, 0, 0);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector3i::Vector3i() : glm::ivec3() {}

Vector3i::Vector3i(const int x, const int y, const int z) : glm::ivec3(x, y, z) {}

Vector3i::Vector3i(const float x, const float y, const int z) : glm::ivec3(x, y, z) {}

/************************************************************************/
/* Conversion Members                                                   */
/************************************************************************/
Vector3i::Vector3i(glm::ivec3 v) : glm::ivec3(v) { }

// Explicit Conversion
Vector3i::operator glm::ivec3() const
{
    return glm::ivec3(x, y, z);
}

Vector3i::operator Vector3f() const
{
    return Vector3f(float(x), float(y), float(z));
}

}
