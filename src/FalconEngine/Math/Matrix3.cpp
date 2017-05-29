#include <FalconEngine/Math/Matrix3.h>
#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
Matrix3f
Matrix3f::Zero = glm::mat3(0.0, 0.0, 0.0,
                           0.0, 0.0, 0.0,
                           0.0, 0.0, 0.0);

Matrix3f
Matrix3f::Identity = glm::mat3(1.0, 0.0, 0.0,
                               0.0, 1.0, 0.0,
                               0.0, 0.0, 1.0);

Matrix3f
Matrix3f::Inverse(const Matrix3f& mat)
{
    return glm::inverse<float, glm::highp, glm::tmat3x3>(mat);
}

Matrix3f
Matrix3f::Transpose(const Matrix3f& mat)
{
    return glm::transpose<float, glm::highp, glm::tmat3x3>(mat);
}

Matrix3f::Matrix3f() :
    glm::mat3()
{

}

Matrix3f::Matrix3f(const glm::vec3& v0,
                   const glm::vec3& v1,
                   const glm::vec3& v2) :
    glm::mat3(v0, v1, v2)
{
}

Matrix3f::Matrix3f(
    const float& x0, const float& y0, const float& z0,
    const float& x1, const float& y1, const float& z1,
    const float& x2, const float& y2, const float& z2) :
    glm::mat3(x0, y0, z0, x1, y1, z1, x2, y2, z2)
{
}

// Explicit Conversion
Matrix3f::Matrix3f(const Matrix4f& m) :
    Matrix3f(glm::vec3(m[0]), glm::vec3(m[1]), glm::vec3(m[2]))
{
}

Matrix3f::~Matrix3f()
{
}

// Implicit Conversion
Matrix3f::Matrix3f(const glm::mat3& m) :
    glm::mat3(m)
{
}

Matrix3f::operator glm::mat3()
{
    return glm::mat3(this->operator[](0),
                     this->operator[](1),
                     this->operator[](2));

}

}
