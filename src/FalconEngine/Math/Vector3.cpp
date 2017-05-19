#include <FalconEngine/Math/Vector3.h>

#include <string>

#include <FalconEngine/Math/Vector2.h>

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

/* static */ Vector3f
Vector3f::Cross(const Vector3f& v1, const Vector3f& v2)
{
    return glm::cross(v1, v2);
}

/* static */
float
Vector3f::Dot(const Vector3f& v1, const Vector3f& v2)
{
    return glm::dot<float, glm::highp, glm::tvec3>(v1, v2);
}

/* static */ Vector3f
Vector3f::Normalize(const Vector3f& v)
{
    if (v == Zero)
    {
        throw std::invalid_argument("Cannot normalize a zero vector\n");
    }

    auto vec = glm::vec3(v);
    return glm::normalize(vec);
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector3f::Vector3f() :
    glm::vec3()
{
}

Vector3f::Vector3f(float x) :
    glm::vec3(x)
{
}

Vector3f::Vector3f(Vector2f v, float z) :
    glm::vec3(v, z)
{
}

Vector3f::Vector3f(float x, float y, float z) :
    glm::vec3(x, y, z)
{
}

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

std::string
to_string(const Vector3f& v)
{
    return std::string("(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")");
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

std::string
to_string(const Vector3i& v)
{
    return std::string("(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")");
}

}
