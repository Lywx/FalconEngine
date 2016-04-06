#pragma once

#include "Handedness.h"
#include "Vector3.h"
#include "Viewport.h"
#include "Quaternion.h"

namespace FalconEngine {
namespace Render {

class Camera
{
public:
    Camera(const Math::Handedness *handedness);

    Camera(const Math::Handedness *handedness, const Viewport& viewport, float nearPlane = 0.1f, float farPlane = 1000.f);

    Camera(const Math::Handedness *handedness, float fovy, float aspectRatio, float nearPlane = 0.1f, float farPlane = 1000.f);

    virtual ~Camera();

    /************************************************************************/
    /* Camera Movement                                                      */
    /************************************************************************/
    const Math::Vector3& Position() const
    {
        return m_position;
    }

    Math::Vector3 Forward() const
    {
        return m_handedness->Forward(m_view);
    }

    Math::Vector3 Backward() const
    {
        return m_handedness->Backward(m_view);
    }

    Math::Vector3 Left() const
    {
        return m_handedness->Left(m_view);
    }

    Math::Vector3 Right() const
    {
        return m_handedness->Right(m_view);
    }

    Math::Vector3 Up() const
    {
        return m_handedness->Up(m_view);
    }

    Math::Vector3 Down() const
    {
        return m_handedness->Down(m_view);
    }

    const Math::Quaternion& Rotation() const { return m_rotation; }

    void MoveForward(float distance)
    {
        m_position += Forward() * distance;
    }

    void MoveBack(float distance)
    {
        m_position += Backward() * distance;
    }

    void MoveLeft(float distance)
    {
        m_position += Left() * distance;
    }

    void MoveRight(float distance)
    {
        m_position += Right() * distance;
    }

    void MoveUp(float distance)
    {
        m_position += Up() * distance;
    }

    void MoveDown(float distance)
    {
        m_position += Down() * distance;
    }

    void Rotate(const Math::Matrix& rotation)
    {
        m_world = rotation * m_world;
        m_view = glm::inverse(m_world);
    }

    void Rotate(float pitch, float yaw, float roll)
    {
        Math::Quaternion rotation_yaw   = Math::Quaternion::FromAxisAngle(Math::Vector3::UnitY, yaw);
        Math::Quaternion rotation_pitch = Math::Quaternion::FromAxisAngle(Math::Vector3::UnitX, pitch);
        Math::Quaternion rotation_roll  = Math::Quaternion::FromAxisAngle(Math::Vector3::UnitZ, roll);

        m_rotation = rotation_yaw * rotation_pitch * rotation_roll;
    }

    /************************************************************************/
    /* Camera Setup                                                         */
    /************************************************************************/
    float Near() const { return m_near; }

    float Far() const { return m_far; }

    const Math::Matrix& World() const { return m_world; }

    const Math::Matrix& View() const { return m_view; }

    const Math::Matrix& Projection() const { return m_projection; }

    void SetWorld(const Math::Matrix& world)
    {
        m_world = world;
        m_view = glm::inverse(m_world);
    }

    void SetView(const Math::Matrix& view)
    {
        m_view = view;
    }

    void SetProjection(const Math::Matrix& projection)
    {
        m_projection = projection;
    }

    float VerticalFieldOfView() const
    {
        return m_fovy;
    }

    float HorizontalFieldOfView() const
    {
        return 2.f * atan(m_aspectRatio * tan(m_fovy * 0.5f) );
    }

    void SetPerspectiveProjection(float fovy, float aspectRatio, float nearPlane, float farPlane);

    // NEW
    // void SetOrthogonalProjection();

    void SetPosition(const Math::Vector3& position);

    virtual void LookAt(const Math::Vector3& from, const Math::Vector3& to, const Math::Vector3& up);

    /************************************************************************/
    /* Camera Update                                                        */
    /************************************************************************/
    virtual void Update(float deltaTime)
    {
        m_world = Math::Matrix::FromRotation(m_rotation) *  Math::Matrix::CreateTranslation(m_position);
        m_view = glm::inverse(m_world);
    }

protected:
    Math::Vector3 m_position;

    Math::Quaternion m_rotation;

    Math::Matrix m_projection;

    // View transform matrix for the camera. View matrix store the axis
    // direction of local coordinate system: forward, up and right.
    Math::Matrix m_view;

    // World transform matrix for the camera position.
    Math::Matrix m_world;

    float m_near;

    float m_far;

    // Vertical field of view
    float m_fovy;

    float m_aspectRatio;

private:
    const Math::Handedness *m_handedness;
};

} // Render
} // FalconEngine
