#include <FalconEngine/Graphics/Transform.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Transform::Transform()
    : m_matrix(Matrix4f::Identity)
    , m_translation(Vector3f::Zero)
    , m_scale(Vector3f::One)
{
}

Transform::~Transform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Transform::SetIdentity()
{
    m_matrix = Matrix4f::Identity;
    m_translation = Vector3f::Zero;
    m_scale = Vector3f::One;
}

void Transform::SetMatrix(const Matrix4f& matrix)
{
    m_matrix = matrix;
}

void Transform::SetRotation(const Matrix4f& rotation)
{
    m_matrix = rotation;

    // TODO
}

void Transform::SetTranslation(const Vector3f& translation)
{
    m_translation = translation;

    // TODO
    m_matrix[3][0] = m_translation[0];
    m_matrix[3][1] = m_translation[1];
    m_matrix[3][2] = m_translation[2];
}

void Transform::SetScaling(const Vector3f& scale)
{
    m_scale = scale;

    // TODO
    //m_Matrix =
}

void Transform::SetIsomorphicScaling(float scale)
{
    // TODO
}

}
