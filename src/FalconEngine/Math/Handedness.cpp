#include <FalconEngine/Math/Handedness.h>

namespace FalconEngine {

/************************************************************************/
/* Handedness Members                                                   */
/************************************************************************/

Handedness::Handedness()
{
}

Handedness::~Handedness()
{
}

/************************************************************************/
/* HandednessLeft Members                                               */
/************************************************************************/

Vector3f HandednessLeft::Right(const Matrix4f & view) const
{
    return Vector3f(view[0][0], view[1][0], view[2][0]);
};

Vector3f HandednessLeft::Up(const Matrix4f & view) const
{
    return Vector3f(view[0][1], view[1][1], view[2][1]);
};

Vector3f HandednessLeft::Forward(const Matrix4f & view) const
{
    return -Vector3f(view[0][2], view[1][2], view[2][2]);
};

Matrix4f HandednessLeft::CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const
{
    Matrix4f result;

    result = Matrix4f::Zero;

    result[0][0] = 2.f * dmin / width;
    result[1][1] = 2.f * dmin / height;
    result[2][2] = dmax / (dmax - dmin);
    result[2][3] = 1.f;

    result[3][2] = -dmin * dmax / (dmax - dmin);

    return result;
}

void HandednessLeft::CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix4f& result) const
{
    result = CreatePerspective(width, height, dmin, dmax);
}

Matrix4f HandednessLeft::CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const
{
    assert(0.f <= fovy && fovy <= Pi);
    assert(0.f < dmin);
    assert(0.f < dmax);
    assert(dmin <= dmax);

    float theta_u = fovy / 2.f;

    Matrix4f result = Matrix4f::Zero;

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

void HandednessLeft::CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix4f &result) const
{
    result = CreatePerspectiveFieldOfView(fovy, aspectRatio, dmin, dmax);
}

Matrix4f HandednessLeft::CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const
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

    Vector3f d = Vector3f::Normalize(targetPosition - eyePosition);
    Vector3f r = Vector3f::Normalize(Vector3f::Cross(up, d));
    Vector3f u = Vector3f::Cross(d, r);

    Matrix4f result = Matrix4f::Identity;
    result[0][0] = r.x;
    result[1][0] = r.y;
    result[2][0] = r.z;
    result[3][0] = -Vector3f::Dot(r, eyePosition);

    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[3][1] = -Vector3f::Dot(u, eyePosition);

    result[0][2] = d.x;
    result[1][2] = d.y;
    result[2][2] = d.z;
    result[3][2] = -Vector3f::Dot(d, eyePosition);

    return result;
}

void HandednessLeft::CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const
{
    result = CreateLookAt(eyePosition, targetPosition, up);
}

/************************************************************************/
/* HandednessRight Members                                              */
/************************************************************************/

Vector3f HandednessRight::Right(const Matrix4f & view) const
{
    return Vector3f(view[0][0], view[1][0], view[2][0]);
};

Vector3f HandednessRight::Up(const Matrix4f & view) const
{
    return Vector3f(view[0][1], view[1][1], view[2][1]);
};

Vector3f HandednessRight::Forward(const Matrix4f & view) const
{
    return Vector3f(view[0][2], view[1][2], view[2][2]);
};

Matrix4f HandednessRight::CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const
{
    Matrix4f result;

    result = Matrix4f::Zero;

    result[0][0] = 2.f * dmin / width;
    result[1][1] = 2.f * dmin / height;
    result[2][2] = dmax / (dmax - dmin);
    result[2][3] = -1.f;

    result[3][2] = dmin * dmax / (dmax - dmin);

    return result;
}

void HandednessRight::CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix4f& result) const
{
    result = CreatePerspective(width, height, dmin, dmax);
}

Matrix4f HandednessRight::CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const
{
    assert(0.f <= fovy && fovy <= Pi);
    assert(0.f < dmin);
    assert(0.f < dmax);
    assert(dmin <= dmax);

    float theta_u = fovy / 2.f;

    Matrix4f result = Matrix4f::Zero;

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

void HandednessRight::CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix4f &result) const
{
    result = CreatePerspectiveFieldOfView(fovy, aspectRatio, dmin, dmax);
}

Matrix4f HandednessRight::CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const
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

    Vector3f d = Vector3f::Normalize(targetPosition - eyePosition);
    Vector3f r = Vector3f::Normalize(Vector3f::Cross(up, d));
    Vector3f u = Vector3f::Cross(d, r);

    Matrix4f result = Matrix4f::Identity;

    result[0][0] = r.x;
    result[1][0] = r.y;
    result[2][0] = r.z;
    result[3][0] = -Vector3f::Dot(r, eyePosition);

    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[3][1] = -Vector3f::Dot(u, eyePosition);

    result[0][2] = d.x;
    result[1][2] = d.y;
    result[2][2] = d.z;
    result[3][2] = Vector3f::Dot(d, eyePosition);

    return result;
}

void HandednessRight::CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const
{
    result = CreateLookAt(eyePosition, targetPosition, up);
}

}
