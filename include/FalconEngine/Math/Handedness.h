#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Math/Function.h>
#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

// @summary Handedness controls how the matrix is interpreted using different
// handedness representation.
class FALCON_ENGINE_API Handedness
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Handedness();
    virtual ~Handedness();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @param View transform matrix. If you use world transform here you would get wrong result. If you use world view conpound matrix you would get the world
    virtual Vector3f
    Right(const Matrix4f& view) const = 0;

    // @param View transform matrix. If you use world transform here you would get wrong result.
    Vector3f
    Left(const Matrix4f& view) const;

    // @param View transform matrix. If you use world transform here you would get wrong result.
    virtual Vector3f
    Up(const Matrix4f& view) const = 0;

    // @param View transform matrix. If you use world transform here you would get wrong result.
    Vector3f
    Down(const Matrix4f& view) const;

    // @param View transform matrix. If you use world transform here you would get wrong result.
    virtual Vector3f
    Forward(const Matrix4f& view) const = 0;

    // @param View transform matrix. If you use world transform here you would get wrong result.
    Vector3f
    Backward(const Matrix4f& view) const;

    // @remark Provide OpenGL version of z coordinate [-1, 1] in clip space.
    virtual Matrix4f
    CreatePerspective(float width, float height, float dmin, float dmax) const = 0;

    virtual void
    CreatePerspective(float width, float height, float dmin, float dmax, Matrix4f& result) const = 0;

    // @remark Provide OpenGL version of z coordinate [-1, 1] in clip space.
    virtual Matrix4f
    CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax) const = 0;

    virtual void
    CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax, Matrix4f& result) const = 0;

    // @remark Provide OpenGL version of z coordinate [-1, 1] in clip space.
    virtual Matrix4f
    CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax) const = 0;

    virtual void
    CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax, Matrix4f& result) const = 0;

    virtual Matrix4f
    CreateLookAt(const Vector3f& eyePosition, const Vector3f& targetPosition, const Vector3f& up) const = 0;

    virtual void
    CreateLookAt(const Vector3f& eyePosition, const Vector3f& targetPosition, const Vector3f& up, Matrix4f& result) const = 0;
};

class HandednessLeft : public Handedness
{
public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Extract right vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f
    Right(const Matrix4f & view) const override;

    // @summary Extract up vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f
    Up(const Matrix4f & view) const override;

    // @summary Extract forward vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f
    Forward(const Matrix4f & view) const override;

    // @summary Create Left-handed symmetric perspective transform matrix, assuming vector on the right side.
    Matrix4f
    CreatePerspective(float width, float height, float dmin, float dmax) const override;

    // @summary Create left-handed symmetric perspective transform matrix, assuming vector on the right side.
    void
    CreatePerspective(float width, float height, float dmin, float dmax, Matrix4f& result) const override;

    // @summary Create left-handed symmetric perspective transform matrix based on the field of view, assuming the vector is on the right side.
    Matrix4f
    CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax) const override;

    // @summary Create left-handed perspective matrix based on the field of view, assuming the vector is on the right side.
    void
    CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax, Matrix4f &result) const override;

    Matrix4f
    CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax) const override;

    void
    CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax, Matrix4f& result) const override;

    // @summary Create left-handed view transform matrix, assuming the vector is on the right side.
    Matrix4f
    CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const override;

    // @summary Create left-handed view transform matrix, assuming the vector is on the right side.
    void
    CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const override;
};

class FALCON_ENGINE_API HandednessRight : public Handedness
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static Handedness *GetInstance()
    {
        static HandednessRight sHandedness;
        return &sHandedness;
    }

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Extract right vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f
    Right(const Matrix4f & view) const override;

    // @summary Extract up vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f
    Up(const Matrix4f & view) const override;

    // @summary Extract forward vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f
    Forward(const Matrix4f & view) const override;

    // @summary Create right-handed symmetric perspective transform matrix, assuming vector on the right side.
    // @remark Compatible with glFrustum.
    Matrix4f
    CreatePerspective(float width, float height, float dmin, float dmax) const override;

    // @summary Create right-handed symmetric perspective transform matrix, assuming vector on the right side.
    void
    CreatePerspective(float width, float height, float dmin, float dmax, Matrix4f& result) const override;

    // @summary Create right-handed symmetric perspective transform matrix based on the field of view, assuming the vector is on the right side.
    Matrix4f
    CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax) const override;

    // @summary Create right-handed perspective matrix based on the field of view, assuming the vector is on the right side.
    void
    CreatePerspectiveFieldOfView(float fovy, float aspectRatio, float dmin, float dmax, Matrix4f &result) const override;

    Matrix4f
    CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax) const override;

    void
    CreateOrthogonal(float left, float right, float bottom, float top, float dmin, float dmax, Matrix4f& result) const override;

    // @summary Create right-handed view transform matrix, assuming the vector is on the right side.
    Matrix4f
    CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const override;

    // @summary Create left-handed view transform matrix, assuming the vector is on the right side.
    void
    CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const override;
};

inline Vector3f Handedness::Left(const Matrix4f& view) const
{
    return -Right(view);
};

inline Vector3f Handedness::Down(const Matrix4f& view) const
{
    return -Up(view);
};

inline Vector3f Handedness::Backward(const Matrix4f& view) const
{
    return -Forward(view);
};

}
