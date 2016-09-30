#pragma once

#include <FalconEngine/Math/Matrix4f.h>
#include <FalconEngine/Math/Vector3f.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine {

class Transform
{
public:
    Transform();
    virtual ~Transform();

    void SetIdentity();

    inline const Matrix4f& Matrix() const;
    void SetMatrix(const Matrix4f& matrix);

    inline const Matrix4f& Rotation() const;
    void SetRotation(const Matrix4f& rotation);

    inline const Vector3f& Translation() const;
    void SetTranslation(const Vector3f& translation);

    inline const Vector3f& Scaling() const;
    void SetScaling(const Vector3f& scale);
    void SetIsomorphicScaling(float scale);

    inline Vector4f operator* (const Vector4f& vector) const;
    inline Transform operator* (const Transform& transform) const;

private:
    Matrix4f m_matrix;

    Vector3f m_translation;
    Vector3f m_scale;
};

#include "Transform.inl"

}
