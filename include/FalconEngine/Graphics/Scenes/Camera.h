#pragma once

#include <FalconEngine/Graphics/Viewport.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Quaternion.h>
#include <FalconEngine/Math/Vector3f.h>

namespace FalconEngine {

class Camera
{
public:
    Camera(const Handedness *handedness);
    Camera(const Handedness *handedness, const Viewport& viewport, float nearPlane = 0.1f, float farPlane = 1000.f);
    Camera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane = 0.1f, float farPlane = 1000.f);

    virtual ~Camera();

    /************************************************************************/
    /* Camera Movement                                                      */
    /************************************************************************/
    const Vector3f& Position() const;

    Vector3f Forward() const;
    Vector3f Backward() const;

    Vector3f Left() const;
    Vector3f Right() const;

    Vector3f Up() const;
    Vector3f Down() const;

    const Quaternion& Rotation() const;

    void MoveForward(float distance);
    void MoveBack(float distance);

    void MoveLeft(float distance);
    void MoveRight(float distance);

    void MoveUp(float distance);
    void MoveDown(float distance);

    void Rotate(const Matrix4f& rotation);
    void Rotate(float pitch, float yaw, float roll);

    /************************************************************************/
    /* Camera Setup                                                         */
    /************************************************************************/
    float Near() const;
    float Far() const;

    const Matrix4f& World() const;
    const Matrix4f& View() const;
    const Matrix4f& Projection() const;

    void SetWorld(const Matrix4f& world);
    void SetView(const Matrix4f& view);
    void SetProjection(const Matrix4f& projection);

    float VerticalFieldOfView() const;
    float HorizontalFieldOfView() const;

    void SetPerspectiveProjection(float fovy, float aspectRatio, float nearPlane, float farPlane);

    // NEW
    // void SetOrthogonalProjection();

    void SetPosition(const Vector3f& position);

    virtual void LookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up);

    /************************************************************************/
    /* Camera Update                                                        */
    /************************************************************************/
    virtual void Update(double elapsed);

protected:
    Vector3f m_position;

    Quaternion m_rotation;

    Matrix4f m_projection;

    // View transform matrix for the camera. View matrix store the axis
    // direction of local coordinate system: forward, up and right.
    Matrix4f m_view;

    // World transform matrix for the camera position.
    Matrix4f m_world;

    float m_near;

    float m_far;

    // Vertical field of view
    float m_fovy;

    float m_aspectRatio;

private:
    const Handedness *m_handedness;
};

}
