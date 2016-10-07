#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Math/Matrix4f.h>
#include <FalconEngine/Math/Vector3f.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine {

class FALCON_ENGINE_GRAPHICS_ITEM Transform
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/

    static const Transform Identity;

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/

    Transform();
    virtual ~Transform();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    inline const Matrix4f& Rotation() const;
    inline bool            RotationIsValid() const;
    void                   SetRotation(const Matrix4f& rotation);

    void                   SetScaleIdentity();
    inline const Vector3f& Scale() const;
    void                   SetScale(const Vector3f& scale);
    inline const float&    ScaleIsomorphic() const;
    inline bool            ScaleIsIsomorphic() const;
    void                   SetScaleIsomorphic(const float& scale);

    inline const Vector3f& Translation() const;
    void                   SetTranslation(const Vector4f& translation);
    void                   SetTranslation(const Vector3f& translation);

    void                   SetMatrixIdentity();
    inline bool            MatrixIsIdentity() const;
    inline const Matrix4f& Matrix() const;
    void                   SetMatrix(const Matrix4f& matrix);
    const Matrix4f&        InverseMatrix() const;

    Transform              InverseTransform() const;

    inline Vector3f        operator* (const Vector3f& vector) const;
    inline Vector4f        operator* (const Vector4f& vector) const;
    Transform              operator* (const Transform& transform) const;

protected:

    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void UpdateMatrix();

private:
    Matrix4f         m_matrix;
    bool             m_matrixIsIdentity;

    mutable Matrix4f m_inverseMatrix;
    mutable bool     m_inverseMatrixIsValid;

    // @Reference:
    // David Eberly, 2004, P168
    // David Eberly, 2006, P50, (2.59)

    // @Summary: M (general) or R (rotation)
    // @Remark: "m_rotation" is not necessarily represent a rotation matrix. It only
    // represents valid rotation matrix when "m_rotationIsValid" is true. Otherwise,
    // it represents the general case of a 4 * 4 matrix.
    Matrix4f         m_rotationOrMatrix;
    bool             m_rotationIsValid;

    // @Summary: S diagonal matrix as a vector
    Vector3f         m_scale;
    bool             m_scaleIsIsomorphic;

    // @Summary: T matrix as a vector
    Vector3f         m_translation;
};

#include "Transform.inl"

}
