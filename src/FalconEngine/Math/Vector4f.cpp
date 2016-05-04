#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine {

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Vector4 Vector4::Zero  = glm::vec4(0.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::UnitX = glm::vec4(1.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::UnitY = glm::vec4(0.f, 1.f, 0.f, 0.f);
const Vector4 Vector4::UnitZ = glm::vec4(0.f, 0.f, 1.f, 0.f);
const Vector4 Vector4::UnitW = glm::vec4(0.f, 0.f, 0.f, 1.f);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Vector4::Vector4() : glm::vec4() {};

Vector4::Vector4(const glm::vec3& vec3, const float w) : glm::vec4(vec3, w) {};

// Copy Constructor
Vector4::Vector4(const Vector4& v) : glm::vec4(v) {};

// Implicit Conversion
Vector4::Vector4(const glm::vec4& v) : glm::vec4(v) {};
}