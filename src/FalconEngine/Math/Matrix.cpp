#include <FalconEngine/Math/Matrix.h>
#include <FalconEngine/Math/Quaternion.h>

namespace FalconEngine {
namespace Math {

Matrix Matrix::Identity = glm::mat4(1.0, 0.0, 0.0, 0.0,
                                    0.0, 1.0, 0.0, 0.0,
                                    0.0, 0.0, 1.0, 0.0,
                                    0.0, 0.0, 0.0, 1.0);

Matrix Matrix::Zero = glm::mat4(0.0, 0.0, 0.0, 0.0,
                                0.0, 0.0, 0.0, 0.0,
                                0.0, 0.0, 0.0, 0.0,
                                0.0, 0.0, 0.0, 0.0);

Matrix Matrix::CreateRotationX(const float& radians)
{
    const float cosine = cos(radians);
    const float sine = sin(radians);

    return Matrix(1.0, 0.0   , 0.0   , 0.0,
                  0.0, cosine, -sine , 0.0,
                  0.0, sine  , cosine, 0.0,
                  0.0, 0.0   , 0.0   , 1.0);
}

void Matrix::CreateRotationX(const float& radians, Matrix& transform)
{
    transform = CreateRotationX(radians);
}

Matrix Matrix::CreateRotationY(const float& radians)
{
    const float cosine = cos(radians);
    const float sine = sin(radians);

    return Matrix(cosine, 0.0, sine  , 0.0,
                  0.0   , 1.0, 0.0   , 0.0,
                  -sine , 0.0, cosine, 0.0,
                  0.0   , 0.0, 0.0   , 1.0);

}

void Matrix::CreateRotationY(const float& radians, Matrix& transform)
{
    transform = CreateRotationY(radians);
}

Matrix Matrix::CreateRotationZ(const float& radians)
{
    const float cosine = cos(radians);
    const float sine = sin(radians);

    return Matrix(cosine, -sine , 0.0, 0.0,
                  sine  , cosine, 0.0, 0.0,
                  0.0   , 0.0   , 1.0, 0.0,
                  0.0   , 0.0   , 0.0, 1.0);

}

void Matrix::CreateRotationZ(const float& radians, Matrix& transform)
{
    transform = CreateRotationZ(radians);
}

Matrix Matrix::FromRotation(const Quaternion& q)
{
    Matrix result = Matrix::Identity;

    result[0][0] = 1.f - 2.f * (q.y * q.y + q.z * q.z);
    result[1][0] = 2.f * (q.x * q.y + q.w * q.z);
    result[2][0] = 2.f * (q.x * q.z - q.w * q.y);

    result[0][1] = 2.f * (q.x * q.y - q.w * q.z);
    result[1][1] = 1.f - 2.f * (q.x * q.x + q.z * q.z);
    result[2][1] = 2.f * (q.y * q.z + q.w * q.x);

    result[0][2] = 2.f * (q.x * q.z + q.w * q.y);
    result[1][2] = 2.f * (q.y * q.z - q.w * q.x);
    result[2][2] = 1.f - 2.f * (q.x * q.x + q.y * q.y);

    return result;

}

Matrix Matrix::CreateRotation(const float& pitch, const float& yaw, const float& roll)
{
    Quaternion rotation_yaw   = Quaternion::FromAxisAngle(Vector3::UnitY, yaw);
    Quaternion rotation_pitch = Quaternion::FromAxisAngle(Vector3::UnitX, pitch);
    Quaternion rotation_roll  = Quaternion::FromAxisAngle(Vector3::UnitZ, roll);

    Quaternion rotation = rotation_yaw * rotation_pitch * rotation_roll;

    return FromRotation(rotation);
}

Matrix Matrix::CreateIsomorphicScaling(const float& scale)
{
    return Matrix(scale, 0.0f , 0.0f , 0.0f,
                  0.0f , scale, 0.0f , 0.0f,
                  0.0f , 0.0f , scale, 0.0f,
                  0.0f , 0.0f , 0.0f , 1.f);
}

Matrix Matrix::CreateNonisomorphicScaling(const float& scaleX, const float& scaleY, const float& scaleZ)
{
    return Matrix(scaleX, 0.0f  , 0.0f  , 0.0f,
                  0.0f  , scaleY, 0.0f  , 0.0f,
                  0.0f  , 0.0f  , scaleZ, 0.0f,
                  0.0f  , 0.0f  , 0.0f  , 1.f);
}

Matrix Matrix::CreateTranslation(const float& x, const float& y, const float& z)
{
    return CreateTranslation(Vector3(x, y, z));
}

Matrix Matrix::CreateTranslation(const Vector3& v)
{
    Matrix result = Matrix::Identity;

    result[3][0] = v.x;
    result[3][1] = v.y;
    result[3][2] = v.z;

    return result;
}

}
}
