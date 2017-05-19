#include <FalconEngine/Math/Handedness.h>

namespace FalconEngine
{

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
/* Handedness Right Members                                              */
/************************************************************************/

Vector3f
HandednessRight::Right(const Matrix4f & view) const
{
    return Vector3f(view[0][0], view[1][0], view[2][0]);
};

Vector3f
HandednessRight::Up(const Matrix4f & view) const
{
    return Vector3f(view[0][1], view[1][1], view[2][1]);
};

Vector3f
HandednessRight::Forward(const Matrix4f & view) const
{
    // NOTE(Wuxiang): The basis is right-handed so that {r, u, -f} = {x, y, z}.
    return -Vector3f(view[0][2], view[1][2], view[2][2]);
};

Matrix4f
HandednessRight::CreatePerspective(float width, float height, float dmin, float dmax) const
{
    Matrix4f result;

    // @ref Dave Shreiner, etc OpenGL Programming Guide, 8th, 2013, P228
    // @ref David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006, P137
    // @ref https://www.opengl.org/sdk/docs/man2/xhtml/glFrustum.xml
    result = Matrix4f::Zero;

    // NOTE(Wuxiang): Map x, y from into [-1, 1] in right-handed system.
    result[0][0] = 2.0f * dmin / width;
    result[1][1] = 2.0f * dmin / height;

    // NOTE(Wuxiang): Map z from [-near, -far] into [-1, 1] in right-handed system,
    // for illustration of coordinate system I am using, refer to Dave Shreiner, etc OpenGL Programming Guide, 8th, 2013, P230, Figure 5.14
    result[2][2] = -(dmax + dmin) / (dmax - dmin);
    result[3][2] = -2.0f * dmin * dmax / (dmax - dmin);
    result[2][3] = -1.0f;

    return result;
}

void
HandednessRight::CreatePerspective(float width, float height, float dmin, float dmax, Matrix4f& result) const
{
    result = CreatePerspective(width, height, dmin, dmax);
}

Matrix4f
HandednessRight::CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax) const
{
    assert(0.f <= fovy && fovy <= Pi);
    assert(0.f < dmin);
    assert(0.f < dmax);
    assert(dmin <= dmax);

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

    // theta_u in Latex
    float thetaU = fovy / 2.f;

    // Based on P47, Figure 2.16 (c), red triangle annotation, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
    //
    // Assumed relations:
    // 1. dmin / rmax = 2 * dmin / width
    // 2. dmin / umax = 2 * dmin / height
    float dminOverUmax = 1.f / tanf(thetaU);
    float dminOverRmax = dminOverUmax / aspectRatio;

    // This matrix computation is derived from the formula created by CreatePerspective method.
    result[0][0] = dminOverRmax;
    result[1][1] = dminOverUmax;
    result[2][2] = -(dmax + dmin) / (dmax - dmin);
    result[3][2] = -2.0f * dmin * dmax / (dmax - dmin);
    result[2][3] = -1.f;

    return result;
}

void
HandednessRight::CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax, Matrix4f &result) const
{
    result = CreatePerspectiveFieldOfView(fovy, aspectRatio, dmin, dmax);
}

Matrix4f
HandednessRight::CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax) const
{
    Matrix4f result;

    // @ref Dave Shreiner, etc OpenGL Programming Guide, 8th, 2013, P231
    // @ref https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    result = Matrix4f::Zero;

    // NOTE(Wuxiang): Map x, y from into [-1, 1] in right-handed system.
    result[0][0] = 2.0f / (right - left);
    result[1][1] = 2.0f / (top - bottom);

    // NOTE(Wuxiang): Map z from [-near, -far] into [-1, 1] in right-handed system,
    // for illustration of coordinate system I am using, refer to Dave Shreiner, etc OpenGL Programming Guide, 8th, 2013, P230, Figure 5.14
    result[2][2] = -2.0f / (dmax - dmin);

    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(dmin + dmax) / (dmax - dmin);
    result[3][3] = 1.0f;

    return result;
}

void
HandednessRight::CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax, Matrix4f& result) const
{
    result = CreateOrthogonal(left, right, bottom, top, dmin, dmax);
}

// @test Have the same result as glm::lookAt.
Matrix4f
HandednessRight::CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const
{
    // Assumed relations:
    // D = normal(targetPosition - eyePosition)
    // R = normal(cross(D, up))
    // U = cross(R, D)
    //
    // * cross is right-handed cross product operation because glm::cross is right_handed.
    //
    // Based on P135, H_view, David H. Eberly 3D Game Engine Design_ A Practical Approach to Real-Time Computer Graphics, 2nd, 2006
    // Assumed matrix form in column vector convention:
    // R.x             R.y            R.z          -dot(R, eye)
    // U.x             U.y            U.z          -dot(U, eye)
    //-D.x            -D.y           -D.z           dot(D, eye)
    // 0               0              0             1

    // NOTE(Wuxiang): D equals to result of inverting sign of z coordinates.
    Vector3f d = Vector3f::Normalize(targetPosition - eyePosition);
    Vector3f r = Vector3f::Normalize(Vector3f::Cross(d, up));
    Vector3f u = Vector3f::Cross(r, d);

    Matrix4f result = Matrix4f::Identity;
    result[0][0] = r.x;
    result[1][0] = r.y;
    result[2][0] = r.z;
    result[3][0] = -Vector3f::Dot(r, eyePosition);

    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[3][1] = -Vector3f::Dot(u, eyePosition);

    // NOTE(Wuxiang): You need to invert the sign of 'D axis' coordinate to get the z
    // coordinate in right-handed coordinate system.
    result[0][2] = -d.x;
    result[1][2] = -d.y;
    result[2][2] = -d.z;
    result[3][2] = Vector3f::Dot(d, eyePosition);

    return result;
}

void
HandednessRight::CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const
{
    result = CreateLookAt(eyePosition, targetPosition, up);
}

}
