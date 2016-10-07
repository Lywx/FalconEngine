inline const Matrix4f& Transform::Rotation() const
{
    assert(m_rotationIsValid, "Matrix is not a rotation\n");

    return m_rotationOrMatrix;
}

inline bool Transform::RotationIsValid() const
{
    return m_rotationIsValid;
}

inline bool Transform::ScaleIsIsomorphic() const
{
    return m_scaleIsIsomorphic;
}

inline const Vector3f& Transform::Scale() const
{
    return m_scale;
}

const float& Transform::ScaleIsomorphic() const
{
    return m_scale[0];
}

inline const Vector3f& Transform::Translation() const
{
    return m_translation;
}

inline bool Transform::MatrixIsIdentity() const
{
    return m_matrixIsIdentity;
}

inline const Matrix4f& Transform::Matrix() const
{
    return m_matrix;
}

inline Vector3f Transform::operator*(const Vector3f& vector) const
{
    return m_matrix * vector;
}

inline Vector4f Transform::operator* (const Vector4f& vector) const
{
    return m_matrix * vector;
}

