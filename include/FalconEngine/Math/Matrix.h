#pragma once

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FalconEngine {

class Quaternion;
class Vector3f;

/// 4x4 matrix in column major format:
///
/// (0.0, 1.0, 2.0, 3.0,
///  0.1, 1.1, 2.1, 3.1,
///  0.2, 1.2, 2.2, 3.2,
///  0.3, 1.3, 2.3, 3.3)
class Matrix : public glm::mat4
{
public:
    static Matrix Zero;
    static Matrix Identity;

    Matrix() : glm::mat4() { }

    Matrix(const glm::mat4& m) : glm::mat4(m) { }

    Matrix
    (
        const glm::vec4& v0,
        const glm::vec4& v1,
        const glm::vec4& v2,
        const glm::vec4& v3
    ) : glm::mat4(v0, v1, v2, v3) {}

    Matrix
    (
        const float& x0, const float& y0, const float& z0, const float& w0,
        const float& x1, const float& y1, const float& z1, const float& w1,
        const float& x2, const float& y2, const float& z2, const float& w2,
        const float& x3, const float& y3, const float& z3, const float& w3
    ) : glm::mat4(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3) { }

    static Matrix CreateRotationX(const float& radians);
    static void   CreateRotationX(const float& radians, Matrix& transform);

    static Matrix CreateRotationY(const float& radians);
    static void   CreateRotationY(const float& radians, Matrix& transform);

    static Matrix CreateRotationZ(const float& radians);
    static void   CreateRotationZ(const float& radians, Matrix& transform);

    /// Convert quaternion to rotation matrix
    ///
    /// Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P284
    static Matrix FromRotation(const Quaternion& q);

    /// Create 4x4 rotation matrix from fixed axis angle.
    static Matrix CreateRotation(const float& pitch, const float& yaw, const float& roll);

    static Matrix CreateIsomorphicScaling(const float& scale);
    static Matrix CreateNonisomorphicScaling(const float& scaleX, const float& scaleY, const float& scaleZ);

    static Matrix CreateTranslation(const float& x, const float& y, const float& z);

    /// Create 4x4 Translation Transform Matrix. Column vector is assumed for use of
    /// the transform. Transform matrix is as the following form:
    ///
    /// (1.0, 0.0, 0.0, v.x,
    ///  0.0, 1.0, 0.0, v.y,
    ///  0.0, 0.0, 1.0, v.z,
    ///  0.0, 0.0, 0.0, 1.0)
    static Matrix CreateTranslation(const Vector3f& v);
};

}
