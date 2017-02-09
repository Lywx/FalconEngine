#pragma once

#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Quaternion.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Graphics/Renderers/Viewport.h>

namespace FalconEngine
{

class Camera
{
public:

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Camera(const Handedness *handedness);
    Camera(const Handedness *handedness, const Viewport& viewport, float nearPlane = 0.1f, float farPlane = 1000.f);
    Camera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane = 0.1f, float farPlane = 1000.f);
    virtual ~Camera();

    /************************************************************************/
    /* Camera Position and Orientation                                      */
    /************************************************************************/
    const Vector3f&
    GetPosition() const;

    void
    SetPosition(const Vector3f& position);

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
    MoveForward(float distance);

    void
    MoveBackward(float distance);

    void
    MoveLeft(float distance);

    void
    MoveRight(float distance);

    void
    MoveUp(float distance);

    void
    MoveDown(float distance);

    const Quaternion&
    Rotation() const;

    void
    SetRotation(const Matrix4f& rotation);

    void
    SetRotation(float pitch, float yaw, float roll);

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

    void
    SetView(const Matrix4f& view);

    const Matrix4f&
    GetProjection() const;

    void
    SetProjection(const Matrix4f& projection);

    void
    SetProjectionPerspectiveFieldOfView(float fovy, float aspectRatio, float nearPlane, float farPlane);

    void
    SetProjectionPerspective(float width, float height, float nearPlane, float farPlane);

    void
    SetProjectionOrthogonal(float width, float height, float nearPlane, float farPlane);

    virtual void
    LookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up);

    virtual void
    Update(double elapsed);

protected:
    /************************************************************************/
    /* Static Data                                                          */
    /************************************************************************/
    // TODO(Wuxiang): No support for updating those data after construction for now.

    float              mAspectRatio;
    float              mFarPlane;
    float              mNearPlane;
    float              mFovy;                                                   // Vertical field of view

    /************************************************************************/
    /* Storage Data                                                         */
    /************************************************************************/
    // Each update converts storage data into transform data.

    Vector3f           mPosition;                                               // Storage for position
    Quaternion         mRotation;                                               // Storage for rotation

    /************************************************************************/
    /* Transform Data                                                       */
    /************************************************************************/
    Matrix4f           mProjection;                                             // Projection transform matrix for the camera.
    Matrix4f           mView;                                                   // View transform matrix for the camera.
    Matrix4f           mWorld;                                                  // World transform matrix for the camera position.

private:
    const Handedness  *mHandedness;
};

}
