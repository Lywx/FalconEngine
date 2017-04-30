#include <FalconEngine/Math/Vector4.h>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Vector4f Vector4f::Zero  = Vector4f(0.f, 0.f, 0.f, 0.f);
const Vector4f Vector4f::UnitX = Vector4f(1.f, 0.f, 0.f, 0.f);
const Vector4f Vector4f::UnitY = Vector4f(0.f, 1.f, 0.f, 0.f);
const Vector4f Vector4f::UnitZ = Vector4f(0.f, 0.f, 1.f, 0.f);
const Vector4f Vector4f::UnitW = Vector4f(0.f, 0.f, 0.f, 1.f);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector4f::Vector4f()
{
}

Vector4f::Vector4f(const float x, const float y, const float z, const float w)
    : glm::vec4(x, y, z, w)
{
}

Vector4f::Vector4f(const Vector3f& v, const float w)
    : glm::vec4(v, w)
{
}

// Implicit Conversion
Vector4f::Vector4f(const glm::vec4& v)
    : glm::vec4(v)
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector4i::Vector4i()
{
}

Vector4i::Vector4i(const int x, const int y, const int z, const int w)
    : glm::ivec4(x, y, z, w)
{
}

}
