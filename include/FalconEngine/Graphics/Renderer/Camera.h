#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/Viewport.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Quaternion.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Camera : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Camera(const Handedness *handedness);
    Camera(const Handedness *handedness, const Viewport& viewport, float near = 0.1f, float far = 1000.f);
    Camera(const Handedness *handedness, float fovy, float aspect, float near = 0.1f, float far = 1000.f);
    virtual ~Camera();

    /************************************************************************/
    /* Camera Position                                                      */
    /************************************************************************/
    const Vector3f&
    GetPosition() const;

    void
    SetPosition(const Vector3f& position);

    /************************************************************************/
    /* Camera Orientation                                                   */
    /************************************************************************/
    Vector3f
    GetForward() const;

    Vector3f
    GetBackward() const;

    Vector3f
    GetLeft() const;

    Vector3f
    GetRight() const;

    Vector3f
    GetUp() const;

    Vector3f
    GetDown() const;

    void
    SetRotation(const Matrix4f& rotation);

    void
    SetRotation(const Quaternion& rotation);

    const Quaternion&
    GetOrientation() const;

    // NOTE(Wuxiang): This method intrinsically suffers from Gimbal Lock.
    void
    SetOrientation(float pitch, float yaw, float roll);

    void
    SetOrientation(const Quaternion& orientation);

    /************************************************************************/
    /* Camera Setup                                                         */
    /************************************************************************/
    float
    GetVerticalFieldOfView() const;

    float
    GetHorizontalFieldOfView() const;

    float
    GetNear() const;

    float
    GetFar() const;

    const Matrix4f&
    GetWorld() const;

    void
    SetWorld(const Matrix4f& world);

    const Matrix4f&
    GetView() const;

    const Matrix4f&
    GetViewProjection() const;

    void
    SetView(const Matrix4f& view);

    const Matrix4f&
    GetProjection() const;

    void
    SetProjection(const Matrix4f& projection);

    void
    SetProjectionPerspectiveFieldOfView(float fovy, float aspect, float near, float far);

    void
    SetProjectionPerspective(float width, float height, float near, float far);

    void
    SetProjectionOrthogonal(float left, float right, float bottom, float top, float near, float far);

    // @summary Set up camera position and orientation from the parameters.
    // @param from - world coordinate of camera position.
    // @param to - world coordinate of target position.
    // @param up - world coordinate of up vector.
    virtual void
    LookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up);

    /************************************************************************/
    /* Camera Operation                                                     */
    /************************************************************************/
    virtual void
    Update(double elapsed);

protected:
    /************************************************************************/
    /* Constant Data                                                        */
    /************************************************************************/
    // TODO(Wuxiang): No support for updating those data after construction for now.

    float              mAspect;
    float              mNear;
    float              mFar;
    float              mFovy;                                                   // Vertical field of view

    /************************************************************************/
    /* Storage Data                                                         */
    /************************************************************************/
    // Each update converts storage data into transform data.

    Vector3f           mPosition;                                               // Storage for camera world space position
    Quaternion         mOrientation;                                            // Storage for camera world space rotation

    /************************************************************************/
    /* Transform Data                                                       */
    /************************************************************************/
    Matrix4f           mProjection;                                             // Projection transform matrix for the camera.
    Matrix4f           mView;                                                   // View transform matrix for the camera.
    Matrix4f           mViewProjection;                                         // View projection matrix for saving extra computation.
    Matrix4f           mWorld;                                                  // World transform matrix for the camera position.

private:
    const Handedness  *mHandedness;
};

}
