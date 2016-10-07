#pragma once

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.inl>

namespace FalconEngine {

class Quaternion;
class Vector3f;

// @Summary: 4x4 matrix in column major format:
//
// (0.0, 1.0, 2.0, 3.0,
//  0.1, 1.1, 2.1, 3.1,
//  0.2, 1.2, 2.2, 3.2,
//  0.3, 1.3, 2.3, 3.3)
class Matrix4f : public glm::mat4
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static Matrix4f Zero;
    static Matrix4f Identity;

    static Matrix4f     Inverse(const Matrix4f& mat);
    static Matrix4f     Transpose(const Matrix4f& mat);

    static Matrix4f CreateRotationX(const float& radians);
    static void     CreateRotationX(const float& radians, Matrix4f& transform);

    static Matrix4f CreateRotationY(const float& radians);
    static void     CreateRotationY(const float& radians, Matrix4f& transform);

    static Matrix4f CreateRotationZ(const float& radians);
    static void     CreateRotationZ(const float& radians, Matrix4f& transform);

    // @Summary: Convert quaternion to rotation matrix
    //
    // Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P284
    static Matrix4f FromRotation(const Quaternion& q);

    // @Summary: Create 4x4 rotation matrix from fixed axis angle.
    static Matrix4f CreateRotation(const float& pitch, const float& yaw, const float& roll);

    static Matrix4f CreateScaleIsomorphic(const float& scale);
    static Matrix4f CreateScale(const float& scaleX, const float& scaleY, const float& scaleZ);

    static Matrix4f CreateTranslation(const float& x, const float& y, const float& z);

    // @Summary: Create 4x4 Translation Transform Matrix. Column vector is assumed for use of
    // the transform. Transform matrix is as the following form:
    //
    // (1.0, 0.0, 0.0, v.x,
    //  0.0, 1.0, 0.0, v.y,
    //  0.0, 0.0, 1.0, v.z,
    //  0.0, 0.0, 0.0, 1.0)
    static Matrix4f CreateTranslation(const Vector3f& v);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Matrix4f();
    virtual ~Matrix4f();

    Matrix4f(const glm::vec4& v0, const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3);

    Matrix4f(
        const float& x0, const float& y0, const float& z0, const float& w0,
        const float& x1, const float& y1, const float& z1, const float& w1,
        const float& x2, const float& y2, const float& z2, const float& w2,
        const float& x3, const float& y3, const float& z3, const float& w3);

    // Implicit Conversion
    Matrix4f(const glm::mat4& m);
    operator glm::mat4();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const float *Ptr() const;
};

/************************************************************************/
/* Operator Members                                                     */
/************************************************************************/
Vector3f operator*(const Matrix4f& matrix, const Vector3f& vector);

}