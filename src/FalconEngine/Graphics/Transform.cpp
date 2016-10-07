#include <FalconEngine/Graphics/Transform.h>

namespace FalconEngine {

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/

const Transform Transform::Identity;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Transform::Transform()
    : m_matrix(Matrix4f::Identity),
      m_matrixIsIdentity(true),
      m_inverseMatrix(Matrix4f::Identity),
      m_inverseMatrixIsValid(false),
      m_rotationOrMatrix(Matrix4f::Identity),
      m_rotationIsValid(true),
      m_scale(Vector3f::One),
      m_scaleIsIsomorphic(true),
      m_translation(Vector3f::Zero)
{
}

Transform::~Transform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Transform::SetRotation(const Matrix4f& rotation)
{
    m_rotationOrMatrix = rotation;
    m_rotationIsValid = true;

    m_matrixIsIdentity = false;

    UpdateMatrix();
}

void Transform::SetScaleIdentity()
{
    assert(m_rotationIsValid, "Matrix is not a rotation\n");

    // Corresponds to 3 * 3 identity scale matrix
    m_scale = Vector3f::One;
    m_scaleIsIsomorphic = true;

    UpdateMatrix();
}

void Transform::SetScale(const Vector3f& scale)
{
    assert(m_rotationIsValid, "Matrix is not a rotation\n");
    assert(scale != Vector3f::Zero, "Scales must be nonzero\n");

    m_matrixIsIdentity = false;

    m_scale = scale;
    m_scaleIsIsomorphic = false;

    UpdateMatrix();
}

void Transform::SetScaleIsomorphic(const float& scale)
{
    assert(m_rotationIsValid, "Matrix is not a rotation\n");
    assert(scale != 0.0f, "Scale must be nonzero\n");

    m_matrixIsIdentity = false;

    m_scale = Vector3f(scale, scale, scale);
    m_scaleIsIsomorphic = true;

    UpdateMatrix();
}

void Transform::SetTranslation(const Vector4f& translation)
{
    SetTranslation(Vector3f(translation));
}

void Transform::SetTranslation(const Vector3f& translation)
{
    m_translation = translation;

    m_matrixIsIdentity = false;

    UpdateMatrix();
}

void Transform::SetMatrixIdentity()
{
    m_matrixIsIdentity = true;

    m_rotationOrMatrix = Matrix4f::Identity;
    m_rotationIsValid = true;

    m_scale = Vector3f::One;
    m_scaleIsIsomorphic = true;

    m_translation = Vector3f::Zero;

    UpdateMatrix();
}

void Transform::SetMatrix(const Matrix4f& matrix)
{
    m_scaleIsIsomorphic = false;

    m_rotationOrMatrix = matrix;
    m_rotationIsValid = false;

    m_matrixIsIdentity = false;

    UpdateMatrix();
}

const Matrix4f& Transform::InverseMatrix() const
{
    if (!m_inverseMatrixIsValid)
    {
        if (MatrixIsIdentity())
        {
            m_inverseMatrix = Matrix4f::Identity;
        }
        else
        {
            m_inverseMatrix = Matrix4f::Inverse(m_matrix);
        }

        m_inverseMatrixIsValid = true;
    }

    return m_inverseMatrix;
}

Transform Transform::InverseTransform() const
{
    if (MatrixIsIdentity())
    {
        return Identity;
    }

    Transform inverse;
    Vector3f  invTrans;

    if (RotationIsValid())
    {
        Matrix4f invRot = Matrix4f::Transpose(m_rotationOrMatrix);
        inverse.SetRotation(invRot);

        // See David Eberly, 2004, Notes on "Inverse Transform 1"
        if (ScaleIsIsomorphic())
        {
            float invScale = 1.0f / ScaleIsomorphic();
            inverse.SetScaleIsomorphic(invScale);

            invTrans = -invScale * (invRot * Translation());
        }
        else
        {
            Vector3f invScale(1.0f / Scale()[0], 1.0f / Scale()[1], 1.0f / Scale()[2]);
            inverse.SetScale(invScale);

            invTrans = invRot * Translation();
            invTrans[0] *= -invScale[0];
            invTrans[1] *= -invScale[1];
            invTrans[2] *= -invScale[2];
        }
    }
    else
    {
        Matrix4f invMat = Matrix4f::Inverse(m_rotationOrMatrix);
        inverse.SetMatrix(invMat);

        // The part outside 3 * 3 region won't affect inverse translation computation
        invTrans = -(invMat * Translation());
    }

    inverse.SetTranslation(invTrans);

    return inverse;
}

Matrix4f RotationTimesScale(const Matrix4f& rotation, const Vector3f& scale)
{
    // (0.0, 1.0, 2.0,   (v.0  0    0
    //  0.1, 1.1, 2.1,    0    v.1  0
    //  0.2, 1.2, 2.2, *  0    0    v.2)
    //  0  , 0  , 0  )

    auto v0 = rotation[0] * scale[0];
    auto v1 = rotation[1] * scale[1];
    auto v2 = rotation[2] * scale[2];

    // 4th column is not involved in calculation
    auto& v3 = rotation[3];

    return Matrix4f(v0, v1, v2, v3);
}

Transform Transform::operator*(const Transform& transform) const
{
    if (MatrixIsIdentity())
    {
        return transform;
    }

    if (transform.MatrixIsIdentity())
    {
        return *this;
    }

    Transform product;

    if (RotationIsValid() && transform.RotationIsValid())
    {
        if (ScaleIsIsomorphic())
        {
            product.SetRotation(Rotation() * transform.Rotation());
            product.SetTranslation(ScaleIsomorphic() * (Rotation() * Vector4f(transform.Translation())) + Vector4f(Translation()));

            // Both are isomorphic scale
            if (transform.ScaleIsIsomorphic())
            {
                product.SetScaleIsomorphic(ScaleIsomorphic() * transform.ScaleIsomorphic());
            }

            // Only this are isomorphic scale
            else
            {
                product.SetScale(ScaleIsomorphic() * transform.Scale());
            }

            return product;
        }
    }

    // In all remaining cases, the matrix cannot be written as R * S * X + T.
    Matrix4f lhs = RotationIsValid()
                   ? RotationTimesScale(Rotation(), Scale())
                   : m_rotationOrMatrix;
    Matrix4f rhs = transform.RotationIsValid()
                   ? RotationTimesScale(transform.Rotation(), transform.Scale())
                   : transform.m_rotationOrMatrix;

    product.SetMatrix(lhs * rhs);
    product.SetTranslation(lhs * transform.Translation() + Translation());

    return product;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/

void Transform::UpdateMatrix()
{
    if (m_matrixIsIdentity)
    {
        m_matrix = Matrix4f::Identity;
    }
    else
    {
        if (m_rotationIsValid)
        {
            // 1st row
            m_matrix[0][0] = m_rotationOrMatrix[0][0] * m_scale[0];
            m_matrix[1][0] = m_rotationOrMatrix[1][0] * m_scale[1];
            m_matrix[2][0] = m_rotationOrMatrix[2][0] * m_scale[2];

            // 2nd row
            m_matrix[0][1] = m_rotationOrMatrix[0][1] * m_scale[0];
            m_matrix[1][1] = m_rotationOrMatrix[1][1] * m_scale[1];
            m_matrix[2][1] = m_rotationOrMatrix[2][1] * m_scale[2];

            // 3rd row
            m_matrix[0][2] = m_rotationOrMatrix[0][2] * m_scale[0];
            m_matrix[1][2] = m_rotationOrMatrix[1][2] * m_scale[1];
            m_matrix[2][2] = m_rotationOrMatrix[2][2] * m_scale[2];
        }
        else
        {
            // 1st row
            m_matrix[0][0] = m_rotationOrMatrix[0][0];
            m_matrix[1][0] = m_rotationOrMatrix[1][0];
            m_matrix[2][0] = m_rotationOrMatrix[2][0];

            // 2nd row
            m_matrix[0][1] = m_rotationOrMatrix[0][1];
            m_matrix[1][1] = m_rotationOrMatrix[1][1];
            m_matrix[2][1] = m_rotationOrMatrix[2][1];

            // 3rd row
            m_matrix[0][2] = m_rotationOrMatrix[0][2];
            m_matrix[1][2] = m_rotationOrMatrix[1][2];
            m_matrix[2][2] = m_rotationOrMatrix[2][2];
        }

        // Last column
        m_matrix[3][0] = m_translation[0];
        m_matrix[3][1] = m_translation[1];
        m_matrix[3][2] = m_translation[2];

        // The last row of m_matrix is always (0,0,0,1) for an affine
        // transformation, so it is set once in the constructor.  It is not
        // necessary to reset it here.
        //     m_matrix[0][3] = 0;
        //     m_matrix[1][3] = 0;
        //     m_matrix[2][3] = 0;
        //     m_matrix[3][3] = 1;
    }

    m_inverseMatrixIsValid = false;
}

}
