/* static */
inline Vector3f Vector3f::Normalize(const Vector3f& v)
{
    if (v == Zero)
    {
        throw std::invalid_argument("Cannot normalize a zero vector\n");
    }

    auto vec = glm::vec3(v);
    return glm::normalize(vec);
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
