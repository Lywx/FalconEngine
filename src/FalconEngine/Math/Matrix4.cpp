#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Matrix3.h>
#include <FalconEngine/Math/Vector4.h>
#include <FalconEngine/Math/Quaternion.h>

#include <glm/gtc/type_ptr.hpp>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
Matrix4f Matrix4f::Zero = glm::mat4(0.0, 0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 0.0);

Matrix4f Matrix4f::Identity = glm::mat4(1.0, 0.0, 0.0, 0.0,
                                        0.0, 1.0, 0.0, 0.0,
                                        0.0, 0.0, 1.0, 0.0,
                                        0.0, 0.0, 0.0, 1.0);

Matrix4f
Matrix4f::Inverse(const Matrix4f& mat)
{
    return glm::inverse(mat);
}

Matrix4f
Matrix4f::Transpose(const Matrix4f& mat)
{
    return glm::transpose(mat);
}

Matrix4f
Matrix4f::CreateRotationX(const float& radians)
{
    const float cosine = cos(radians);
    const float sine = sin(radians);

    // ref Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P277
    return Matrix4f(1.0, 0.0, 0.0, 0.0,
                    0.0, cosine, -sine, 0.0,
                    0.0, sine, cosine, 0.0,
                    0.0, 0.0, 0.0, 1.0);
}

void
Matrix4f::CreateRotationX(const float& radians, Matrix4f& transform)
{
    transform = CreateRotationX(radians);
}

Matrix4f
Matrix4f::CreateRotationY(const float& radians)
{
    const float cosine = cos(radians);
    const float sine = sin(radians);

    // @ref Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P277
    return Matrix4f(cosine, 0.0, -sine, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    sine, 0.0, cosine, 0.0,
                    0.0, 0.0, 0.0, 1.0);

}

void
Matrix4f::CreateRotationY(const float& radians, Matrix4f& transform)
{
    transform = CreateRotationY(radians);
}

Matrix4f
Matrix4f::CreateRotationZ(const float& radians)
{
    const float cosine = cos(radians);
    const float sine = sin(radians);

    // @ref Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P277
    return Matrix4f(cosine, -sine, 0.0, 0.0,
                    sine, cosine, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);

}

void
Matrix4f::CreateRotationZ(const float& radians, Matrix4f& transform)
{
    transform = CreateRotationZ(radians);
}

Matrix4f
Matrix4f::CreateRotation(const Quaternion& q)
{
    Matrix4f result = Identity;

    // @ref Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P284, (8.20)
    result[0][0] = 1.f - 2.f * (q.y * q.y + q.z * q.z);
    result[1][0] = 2.f * (q.x * q.y - q.w * q.z);
    result[2][0] = 2.f * (q.x * q.z + q.w * q.y);

    result[0][1] = 2.f * (q.x * q.y + q.w * q.z);
    result[1][1] = 1.f - 2.f * (q.x * q.x + q.z * q.z);
    result[2][1] = 2.f * (q.y * q.z - q.w * q.x);

    result[0][2] = 2.f * (q.x * q.z - q.w * q.y);
    result[1][2] = 2.f * (q.y * q.z + q.w * q.x);
    result[2][2] = 1.f - 2.f * (q.x * q.x + q.y * q.y);

    return result;
}

Matrix4f
Matrix4f::CreateScaleIsomorphic(const float& scale)
{
    return Matrix4f(scale, 0.0f, 0.0f, 0.0f,
                    0.0f, scale, 0.0f, 0.0f,
                    0.0f, 0.0f, scale, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.f);
}

Matrix4f
Matrix4f::CreateScale(const float& scaleX, const float& scaleY, const float& scaleZ)
{
    return Matrix4f(scaleX, 0.0f, 0.0f, 0.0f,
                    0.0f, scaleY, 0.0f, 0.0f,
                    0.0f, 0.0f, scaleZ, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.f);
}

Matrix4f
Matrix4f::CreateTranslation(const float& x, const float& y, const float& z)
{
    return CreateTranslation(Vector3f(x, y, z));
}

Matrix4f
Matrix4f::CreateTranslation(const Vector3f& v)
{
    Matrix4f result = Identity;

    result[3][0] = v.x;
    result[3][1] = v.y;
    result[3][2] = v.z;

    return result;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Matrix4f::Matrix4f() : glm::mat4() { }

Matrix4f::Matrix4f(const glm::vec4& v0,
                   const glm::vec4& v1,
                   const glm::vec4& v2,
                   const glm::vec4& v3)
    : glm::mat4(v0, v1, v2, v3)
{
}

Matrix4f::Matrix4f(
    const float& x0, const float& y0, const float& z0, const float& w0,
    const float& x1, const float& y1, const float& z1, const float& w1,
    const float& x2, const float& y2, const float& z2, const float& w2,
    const float& x3, const float& y3, const float& z3, const float& w3)
    : glm::mat4(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3)
{
}

Matrix4f::~Matrix4f()
{
}

// Implicit Conversion
Matrix4f::Matrix4f(const glm::mat4& m) :
    glm::mat4(m)
{
}

Matrix4f::operator glm::mat4() const
{
    return glm::mat4(this->operator[](0),
                     this->operator[](1),
                     this->operator[](2),
                     this->operator[](3));

}

// Explicit Conversion
Matrix4f::operator Matrix3f() const
{
    return Matrix3f(*this);
}

/************************************************************************/
/* Operator Members                                                     */
/************************************************************************/

Vector3f operator*(const Matrix4f& matrix,  const Vector3f& vector)
{
    return Vector3f(matrix * Vector4f(vector));
}

}
