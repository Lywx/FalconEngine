#include <FalconEngine/Math/Vector3f.h>
#include <FalconEngine/Math/Vector3d.h>

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

Vector3f::operator Vector3d() const
{
    return Vector3d(int(x), int(y), int(z));
};

}
