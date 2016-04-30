#pragma once

#include <FalconEngine/Graphics/Viewport.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Quaternion.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine {
namespace Graphics {

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
    const Math::Vector3& Position() const;

    Math::Vector3 Forward() const;
    Math::Vector3 Backward() const;

    Math::Vector3 Left() const;
    Math::Vector3 Right() const;

    Math::Vector3 Up() const;
    Math::Vector3 Down() const;

    const Math::Quaternion& Rotation() const;

    void MoveForward(float distance);
    void MoveBack(float distance);

    void MoveLeft(float distance);
    void MoveRight(float distance);

    void MoveUp(float distance);
    void MoveDown(float distance);

    void Rotate(const Math::Matrix& rotation);
    void Rotate(float pitch, float yaw, float roll);

    /************************************************************************/
    /* Camera Setup                                                         */
    /************************************************************************/
    float Near() const;
    float Far() const;

    const Math::Matrix& World() const;
    const Math::Matrix& View() const;
    const Math::Matrix& Projection() const;

    void SetWorld(const Math::Matrix& world);
    void SetView(const Math::Matrix& view);
    void SetProjection(const Math::Matrix& projection);

    float VerticalFieldOfView() const;
    float HorizontalFieldOfView() const;

    void SetPerspectiveProjection(float fovy, float aspectRatio, float nearPlane, float farPlane);

    // NEW
    // void SetOrthogonalProjection();

    void SetPosition(const Math::Vector3& position);

    virtual void LookAt(const Math::Vector3& from, const Math::Vector3& to, const Math::Vector3& up);

    /************************************************************************/
    /* Camera Update                                                        */
    /************************************************************************/
    virtual void Update(double elapsed);

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
