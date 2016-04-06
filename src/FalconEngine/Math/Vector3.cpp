#include <FalconEngine/Vector3.h>

namespace FalconEngine {
namespace Math {

const Vector3 Vector3::One   = glm::vec3(1.f, 1.f, 1.f);
const Vector3 Vector3::Zero  = glm::vec3(0.f, 0.f, 0.f);
const Vector3 Vector3::UnitX = glm::vec3(1.f, 0.f, 0.f);
const Vector3 Vector3::UnitY = glm::vec3(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ = glm::vec3(0.f, 0.f, 1.f);

/* static */
Vector3 Vector3::Normalize(const Vector3& v)
{
    return glm::normalize(glm::vec3(v.x, v.y, v.z));
}

/* static */
Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
    return glm::cross(v1, v2);
}

/* static */
float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
    return glm::dot<float>(v1, v2);
}

}
}
