#pragma once

#include <FalconEngine/MathInclude.h>

#include <FalconEngine/Math/Function.h>
#include <FalconEngine/Math/Matrix4f.h>
#include <FalconEngine/Math/Vector3f.h>

namespace FalconEngine
{

class Handedness
{
public:
    Handedness();
    virtual ~Handedness();

    virtual Vector3f Right(const Matrix4f& view) const = 0;
    virtual inline Vector3f Left(const Matrix4f& view) const;

    virtual Vector3f Up(const Matrix4f& view) const = 0;
    virtual inline Vector3f Down(const Matrix4f& view) const;

    virtual Vector3f Forward(const Matrix4f& view) const = 0;
    virtual inline Vector3f Backward(const Matrix4f& view) const;

    virtual Matrix4f CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const = 0;
    virtual void CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix4f& result) const = 0;

    virtual Matrix4f CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const = 0;
    virtual void CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix4f& result) const = 0;

    virtual Matrix4f CreateLookAt(const Vector3f& eyePosition, const Vector3f& targetPosition, const Vector3f& up) const = 0;
    virtual void CreateLookAt(const Vector3f& eyePosition, const Vector3f& targetPosition, const Vector3f& up, Matrix4f& result) const = 0;
};

#include "Handedness.inl"

class HandednessLeft : public Handedness
{
public:
    // @Summary: Extract right vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f Right(const Matrix4f & view) const override;

    // @Summary: Extract up vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f Up(const Matrix4f & view) const override;

    // @Summary: Extract forward vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f Forward(const Matrix4f & view) const override;

    // @Summary: Create Left-handed symmetric perspective transform matrix, assuming vector on the right side.
    Matrix4f CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const override;

    // @Summary: Create left-handed symmetric perspective transform matrix, assuming vector on the right side.
    void     CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix4f& result) const override;

    // @Summary: Create left-handed symmetric perspective transform matrix based on the field of view, assuming the vector is on the right side.
    Matrix4f CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const override;

    // @Summary: Create left-handed perspective matrix based on the field of view, assuming the vector is on the right side.
    void     CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix4f &result) const override;

    // @Summary: Create left-handed view transform matrix, assuming the vector is on the right side.
    Matrix4f CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const override;

    // @Summary: Create left-handed view transform matrix, assuming the vector is on the right side.
    void     CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const override;
};

class HandednessRight : public Handedness
{
public:
    // @Summary: Extract right vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f Right(const Matrix4f & view) const override;

    // @Summary: Extract up vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f Up(const Matrix4f & view) const override;

    // @Summary: Extract forward vector from the view matrix, assuming the view transform matrix is in the form of vector on the right
    Vector3f Forward(const Matrix4f & view) const override;

    // @Summary: Create right-handed symmetric perspective transform matrix, assuming vector on the right side.
    Matrix4f CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax) const override;

    // @Summary: Create right-handed symmetric perspective transform matrix, assuming vector on the right side.
    void     CreatePerspective(const float& width, const float& height, const float& dmin, const float& dmax, Matrix4f& result) const override;

    // @Summary: Create right-handed symmetric perspective transform matrix based on the field of view, assuming the vector is on the right side.
    Matrix4f CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax) const override;

    // @Summary: Create right-handed perspective matrix based on the field of view, assuming the vector is on the right side.
    void     CreatePerspectiveFieldOfView(const float& fovy, const float& aspectRatio, const float& dmin, const float& dmax, Matrix4f &result) const override;

    // @Summary: Create right-handed view transform matrix, assuming the vector is on the right side.
    Matrix4f CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up) const override;

    // @Summary: Create left-handed view transform matrix, assuming the vector is on the right side.
    void     CreateLookAt(const Vector3f & eyePosition, const Vector3f & targetPosition, const Vector3f & up, Matrix4f & result) const override;
};

}
