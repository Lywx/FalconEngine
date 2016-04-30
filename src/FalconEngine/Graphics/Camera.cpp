#include <FalconEngine/Graphics.h>
#include <FalconEngine/Math.h>

namespace FalconEngine {
namespace Graphics {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Camera::Camera(const Math::Handedness *handedness)
    : Camera(handedness, Math::PiOver4, 1.77777f)
{
}

Camera::Camera(const Math::Handedness *handedness, const Viewport& viewport, float nearPlane /*=0.1f*/, float farPlane /*=1000.f*/)
    : Camera(handedness, Math::PiOver4, viewport.Aspect(), nearPlane, farPlane)
{
}

Camera::Camera(const Math::Handedness *handedness, float fovy, float aspectRatio, float nearPlane /*=0.1f*/, float farPlane /*=1000.f*/)
    : m_view(Math::Matrix::Identity)
    , m_world(Math::Matrix::Identity)
    , m_rotation(Math::Quaternion::Identity)
    , m_position(Math::Vector3::Zero)
    , m_near(nearPlane)
    , m_far(farPlane)
    , m_fovy(fovy)
    , m_aspectRatio(aspectRatio)
    , m_handedness(handedness)
{
    m_projection = m_handedness->CreatePerspectiveFieldOfView(m_fovy, m_aspectRatio, m_near, m_far);
}

Camera::~Camera()
{
}

/************************************************************************/
/* Camera Movement                                                      */
/************************************************************************/
const Math::Vector3& Camera::Position() const
{
    return m_position;
}

Math::Vector3 Camera::Forward() const
{
    return m_handedness->Forward(m_view);
}

Math::Vector3 Camera::Backward() const
{
    return m_handedness->Backward(m_view);
}

Math::Vector3 Camera::Left() const
{
    return m_handedness->Left(m_view);
}

Math::Vector3 Camera::Right() const
{
    return m_handedness->Right(m_view);
}

Math::Vector3 Camera::Up() const
{
    return m_handedness->Up(m_view);
}

Math::Vector3 Camera::Down() const
{
    return m_handedness->Down(m_view);
}

const Math::Quaternion& Camera::Rotation() const
{
    return m_rotation;
}

void Camera::MoveForward(float distance)
{
    m_position += Forward() * distance;
}

void Camera::MoveBack(float distance)
{
    m_position += Backward() * distance;
}

void Camera::MoveLeft(float distance)
{
    m_position += Left() * distance;
}

void Camera::MoveRight(float distance)
{
    m_position += Right() * distance;
}

void Camera::MoveUp(float distance)
{
    m_position += Up() * distance;
}

void Camera::MoveDown(float distance)
{
    m_position += Down() * distance;
}

void Camera::Rotate(const Math::Matrix& rotation)
{
    m_world = rotation * m_world;
    m_view = glm::inverse(m_world);
}

void Camera::Rotate(float pitch, float yaw, float roll)
{
    Math::Quaternion rotation_yaw   = Math::Quaternion::FromAxisAngle(Math::Vector3::UnitY, yaw);
    Math::Quaternion rotation_pitch = Math::Quaternion::FromAxisAngle(Math::Vector3::UnitX, pitch);
    Math::Quaternion rotation_roll  = Math::Quaternion::FromAxisAngle(Math::Vector3::UnitZ, roll);

    m_rotation = rotation_yaw * rotation_pitch * rotation_roll;
}

/************************************************************************/
/* Camera Setup                                                         */
/************************************************************************/
float Camera::Near() const
{
    return m_near;
}

float Camera::Far() const
{
    return m_far;
}

const Math::Matrix& Camera::World() const
{
    return m_world;
}

const Math::Matrix& Camera::View() const
{
    return m_view;
}

const Math::Matrix& Camera::Projection() const
{
    return m_projection;
}

void Camera::SetWorld(const Math::Matrix& world)
{
    m_world = world;
    m_view = glm::inverse(m_world);
}

void Camera::SetView(const Math::Matrix& view)
{
    m_view = view;
}

void Camera::SetProjection(const Math::Matrix& projection)
{
    m_projection = projection;
}

float Camera::VerticalFieldOfView() const
{
    return m_fovy;
}

float Camera::HorizontalFieldOfView() const
{
    return 2.f * atan(m_aspectRatio * tan(m_fovy * 0.5f) );
}

void Camera::SetPosition(const Math::Vector3& position)
{
    m_position = position;
    m_world = Math::Matrix::CreateTranslation(position) * m_world;
    m_view = glm::inverse(m_world);
}

void Camera::SetPerspectiveProjection(float fovy, float aspectRatio, float nearPlane, float farPlane)
{
    m_near = nearPlane;
    m_far = farPlane;
    m_projection = m_handedness->CreatePerspectiveFieldOfView(fovy, aspectRatio, nearPlane, farPlane);
}

void Camera::LookAt(const Math::Vector3& from, const Math::Vector3& to, const Math::Vector3& up)
{
    m_position = from;
    m_view = m_handedness->CreateLookAt(from, to, up);
    m_world = glm::inverse(m_view);
    m_rotation = Math::Quaternion::FromRotationMatrix(m_world);
}

/************************************************************************/
/* Camera Update                                                        */
/************************************************************************/
void Camera::Update(double elapsed)
{
    m_world = Math::Matrix::FromRotation(m_rotation) *  Math::Matrix::CreateTranslation(m_position);
    m_view = glm::inverse(m_world);
}

}
}