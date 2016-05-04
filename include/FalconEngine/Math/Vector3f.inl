#pragma once

/* static */
inline Vector3f Vector3f::Normalize(const Vector3f& v)
{
    if (v == Zero)
    {
        throw std::runtime_error("try to normalize zero vector");
    }

    return glm::normalize(glm::vec3(v.x, v.y, v.z));
}

/* static */
inline Vector3f Vector3f::Cross(const Vector3f& v1, const Vector3f& v2)
{
    return glm::cross(v1, v2);
}

/* static */
inline float Vector3f::Dot(const Vector3f& v1, const Vector3f& v2)
{
    return glm::dot<float>(v1, v2);
}
