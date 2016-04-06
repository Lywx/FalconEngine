#pragma once

#include "Math.h"
#include "Matrix.h"
#include "Vector3.h"

namespace FalconEngine {
namespace Math {

class Handedness
{
public:
    Handedness() { }
    virtual ~Handedness() { }

    virtual Vector3 Right(const Matrix& view) const = 0;
    virtual Vector3 Left(const Matrix& view) const { return -Right(view); };

    virtual Vector3 Up(const Matrix& view) const = 0;
    virtual Vector3 Down(const Matrix& view) const { return -Up(view); };

    virtual Vector3 Forward(const Matrix& view) const = 0;
    virtual Vector3 Backward(const Matrix& view) const { return -Forward(view); };

    virtual Matrix CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const = 0;
    virtual void CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix& result) const = 0;

    virtual Matrix CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const = 0;
    virtual void CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix& result) const = 0;

    virtual Matrix CreateLookAt(const Vector3& eyePosition, const Vector3& targetPosition, const Vector3& up) const = 0;
    virtual void CreateLookAt(const Vector3& eyePosition, const Vector3& targetPosition, const Vector3& up, Matrix& result) const = 0;
};

class LeftHandedness : public Handedness
{
public:
    /// Extract right vector from the view matrix, assuming the view transfrom matrix is in the form of vector on the right
    Vector3 Right(const Matrix & view) const override
    {
        return Vector3(view[0][0], view[1][0], view[2][0]);
    };

    /// Extract up vector from the view matrix, assuming the view transfrom matrix is in the form of vector on the right
    Vector3 Up(const Matrix & view) const override
    {
        return Vector3(view[0][1], view[1][1], view[2][1]);
    };

    /// Extract forward vector from the view matrix, assuming the view transfrom matrix is in the form of vector on the right
    Vector3 Forward(const Matrix & view) const override
    {
        return -Vector3(view[0][2], view[1][2], view[2][2]);
    };

    /// Create Left-handed symmetric perspective transform matrix, assuming vector on the right side.
    Matrix CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const override
    {
        Matrix result;

        result = Matrix::Zero;

        result[0][0] = 2.f * dmin / width;
        result[1][1] = 2.f * dmin / height;
        result[2][2] = dmax / (dmax - dmin);
        result[2][3] = 1.f;

        result[3][2] = -dmin * dmax / (dmax - dmin);

        return result;
    }

    /// Create left-handed symmetric perspective transform matrix, assuming vector on the right side.
    void CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix& result) const override
    {
        result = CreatePerspective(width, height, dmin, dmax);
    }

    /// Create left-handed symmetric perspective transform matrix based on the field of view, assuming the vector is on the right side.
    Matrix CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const override
    {
        assert(0.f <= fovy && fovy <= Math::Pi);
        assert(0.f < dmin);
        assert(0.f < dmax);
        assert(dmin <= dmax);

        float theta_u = fovy / 2.f;

        Matrix result = Matrix::Zero;

        // Based on P47, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
        //
        // Assumed relations:
        // 1. 1 / tan(theta_u) = dmin / umax
        // 2. umin = -umax
        // 3. rmin = -rmax
        // 4. height = umax - umin = 2 * umax (symmetric)
        // 5. rho = width / height
        // 6. width = height * rho

        // Based on P47, Figure 2.16 (c), red triangle annotation, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
        //
        // Assumed relations:
        // 1. dmin / rmax = 2 * dmin / width
        // 2. dmin / umax = 2 * dmin / height
        float dminOverUmax = 1.f / tanf(theta_u);
        float dminOverRmax = dminOverUmax / aspectRatio;

        // This matrix is comparable to the ones created by CreatePerspective method.
        result[0][0] = dminOverRmax;
        result[1][1] = dminOverUmax;
        result[2][2] = dmax / (dmax - dmin);
        result[2][3] = 1.f;

        result[3][2] = -(dmin * dmax) / (dmax - dmin);

        return result;
    }

    /// Create left-handed perspective matrix based on the field of view, assuming the vector is on the right side.
    void CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix &result) const override
    {
        result = CreatePerspectiveFieldOfView(fovy, aspectRatio, dmin, dmax);
    }

    /// Create left-handed view transform matrix, assuming the vector is on the right side.
    Matrix CreateLookAt(const Vector3 & eyePosition, const Vector3 & targetPosition, const Vector3 & up) const override
    {
        // Assumed relations:
        // D = normal(targetPosition - eyePosition)
        // R = normal(cross(up, D))
        // U = cross(D, R)
        //
        // * cross is left-handed cross product operation
        //
        // Based on P135, H_view, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
        // Assumed matrix form:
        // R.x             R.y            R.z          -dot(R, eye)
        // U.x             U.y            U.z          -dot(U, eye)
        // D.x             D.y            D.z          -dot(D, eye)
        // 0               0              0             1

        Vector3 d = Vector3::Normalize(targetPosition - eyePosition);
        Vector3 r = Vector3::Normalize(Vector3::Cross(up, d));
        Vector3 u = Vector3::Cross(d, r);

        Matrix result = Matrix::Identity;
        result[0][0] = r.x;
        result[1][0] = r.y;
        result[2][0] = r.z;
        result[3][0] = -Vector3::Dot(r, eyePosition);

        result[0][1] = u.x;
        result[1][1] = u.y;
        result[2][1] = u.z;
        result[3][1] = -Vector3::Dot(u, eyePosition);

        result[0][2] = d.x;
        result[1][2] = d.y;
        result[2][2] = d.z;
        result[3][2] = -Vector3::Dot(d, eyePosition);

        return result;
    }

    /// Create left-handed view transform matrix, assuming the vector is on the right side.
    void CreateLookAt(const Vector3 & eyePosition, const Vector3 & targetPosition, const Vector3 & up, Matrix & result) const override
    {
        result = CreateLookAt(eyePosition, targetPosition, up);
    }
};

class RightHandedness : public Handedness
{
    /// Extract right vector from the view matrix, assuming the view transfrom matrix is in the form of vector on the right
    Vector3 Right(const Matrix & view) const override
    {
        return Vector3(view[0][0], view[1][0], view[2][0]);
    };

    /// Extract up vector from the view matrix, assuming the view transfrom matrix is in the form of vector on the right
    Vector3 Up(const Matrix & view) const override
    {
        return Vector3(view[0][1], view[1][1], view[2][1]);
    };

    /// Extract forward vector from the view matrix, assuming the view transfrom matrix is in the form of vector on the right
    Vector3 Forward(const Matrix & view) const override
    {
        return Vector3(view[0][2], view[1][2], view[2][2]);
    };

    /// Create right-handed symmetric perspective transform matrix, assuming vector on the right side.
    Matrix CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const override
    {
        Matrix result;

        result = Matrix::Zero;

        result[0][0] = 2.f * dmin / width;
        result[1][1] = 2.f * dmin / height;
        result[2][2] = dmax / (dmax - dmin);
        result[2][3] = -1.f;

        result[3][2] = dmin * dmax / (dmax - dmin);

        return result;
    }

    /// Create right-handed symmetric perspective transform matrix, assuming vector on the right side.
    void CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix& result) const override
    {
        result = CreatePerspective(width, height, dmin, dmax);
    }

    /// Create right-handed symmetric perspective transform matrix based on the field of view, assuming the vector is on the right side.
    Matrix CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const override
    {
        assert(0.f <= fovy && fovy <= Math::Pi);
        assert(0.f < dmin);
        assert(0.f < dmax);
        assert(dmin <= dmax);

        float theta_u = fovy / 2.f;

        Matrix result = Matrix::Zero;

        // Based on P47, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
        //
        // Assumed relations:
        // 1. 1 / tan(theta_u) = dmin / umax
        // 2. umin = -umax
        // 3. rmin = -rmax
        // 4. height = umax - umin = 2 * umax (symmetric)
        // 5. rho = width / height
        // 6. width = height * rho

        // Based on P47, Figure 2.16 (c), red triangle annotation, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
        //
        // Assumed relations:
        // 1. dmin / rmax = 2 * dmin / width
        // 2. dmin / umax = 2 * dmin / height
        float dminOverUmax = 1.f / tanf(theta_u);
        float dminOverRmax = dminOverUmax / aspectRatio;

        // This matrix is comparable to the ones created by CreatePerspective method.
        result[0][0] = dminOverRmax;
        result[1][1] = dminOverUmax;
        result[2][2] = dmax / (dmax - dmin);
        result[2][3] = -1.f;

        result[3][2] = (dmin * dmax) / (dmax - dmin);

        return result;
    }

    /// Create right-handed perspective matrix based on the field of view, assuming the vector is on the right side.
    void CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix &result) const override
    {
        result = CreatePerspectiveFieldOfView(fovy, aspectRatio, dmin, dmax);
    }

    /// Create right-handed view transform matrix, assuming the vector is on the right side.
    Matrix CreateLookAt(const Vector3 & eyePosition, const Vector3 & targetPosition, const Vector3 & up) const override
    {
        // Assumed relations:
        // D = normal(targetPosition - eyePosition)
        // R = normal(cross(up, D))
        // U = cross(D, R)
        //
        // * cross is right-handed cross product operation
        //
        // Based on P135, H_view, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
        // Assumed matrix form:
        // R.x             R.y            R.z          -dot(R, eye)
        // U.x             U.y            U.z          -dot(U, eye)
        //-D.x            -D.y           -D.z           dot(D, eye)
        // 0               0              0             1

        Vector3 d = Vector3::Normalize(targetPosition - eyePosition);
        Vector3 r = Vector3::Normalize(Vector3::Cross(up, d));
        Vector3 u = Vector3::Cross(d, r);

        Matrix result = Matrix::Identity;

        result[0][0] = r.x;
        result[1][0] = r.y;
        result[2][0] = r.z;
        result[3][0] = -Vector3::Dot(r, eyePosition);

        result[0][1] = u.x;
        result[1][1] = u.y;
        result[2][1] = u.z;
        result[3][1] = -Vector3::Dot(u, eyePosition);

        result[0][2] = d.x;
        result[1][2] = d.y;
        result[2][2] = d.z;
        result[3][2] = Vector3::Dot(d, eyePosition);

        return result;
    }

    /// Create left-handed view transform matrix, assuming the vector is on the right side.
    void CreateLookAt(const Vector3 & eyePosition, const Vector3 & targetPosition, const Vector3 & up, Matrix & result) const override
    {
        result = CreateLookAt(eyePosition, targetPosition, up);
    }
};

}
}
