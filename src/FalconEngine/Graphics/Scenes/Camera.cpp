#include <FalconEngine/Graphics/Scenes/Camera.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Camera::Camera(const Handedness *handedness)
    : Camera(handedness, PiOver4, 1.77777f)
{
}

Camera::Camera(const Handedness *handedness, const Viewport& viewport, float nearPlane /*=0.1f*/, float farPlane /*=1000.f*/)
    : Camera(handedness, PiOver4, viewport.Aspect(), nearPlane, farPlane)
{
}

Camera::Camera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane /*=0.1f*/, float farPlane /*=1000.f*/)
    : m_position(Vector3f::Zero)
    , m_rotation(Quaternion::Identity)
    , m_view(Matrix4f::Identity)
    , m_world(Matrix4f::Identity)
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
const Vector3f& Camera::Position() const
{
    return m_position;
}

Vector3f Camera::Forward() const
{
    return m_handedness->Forward(m_view);
}

Vector3f Camera::Backward() const
{
    return m_handedness->Backward(m_view);
}

Vector3f Camera::Left() const
{
    return m_handedness->Left(m_view);
}

Vector3f Camera::Right() const
{
    return m_handedness->Right(m_view);
}

Vector3f Camera::Up() const
{
    return m_handedness->Up(m_view);
}

Vector3f Camera::Down() const
{
    return m_handedness->Down(m_view);
}

const Quaternion& Camera::Rotation() const
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

void Camera::Rotate(const Matrix4f& rotation)
{
    m_world = rotation * m_world;
    m_view = glm::inverse(m_world);
}

void Camera::Rotate(float pitch, float yaw, float roll)
{
    Quaternion rotation_yaw   = Quaternion::FromAxisAngle(Vector3f::UnitY, yaw);
    Quaternion rotation_pitch = Quaternion::FromAxisAngle(Vector3f::UnitX, pitch);
    Quaternion rotation_roll  = Quaternion::FromAxisAngle(Vector3f::UnitZ, roll);

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

const Matrix4f& Camera::World() const
{
    return m_world;
}

const Matrix4f& Camera::View() const
{
    return m_view;
}

const Matrix4f& Camera::Projection() const
{
    return m_projection;
}

void Camera::SetWorld(const Matrix4f& world)
{
    m_world = world;
    m_view = glm::inverse(m_world);
}

void Camera::SetView(const Matrix4f& view)
{
    m_view = view;
}

void Camera::SetProjection(const Matrix4f& projection)
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

void Camera::SetPosition(const Vector3f& position)
{
    m_position = position;
    m_world = Matrix4f::CreateTranslation(position) * m_world;
    m_view = glm::inverse(m_world);
}

void Camera::SetPerspectiveProjection(float fovy, float aspectRatio, float nearPlane, float farPlane)
{
    m_near = nearPlane;
    m_far = farPlane;
    m_projection = m_handedness->CreatePerspectiveFieldOfView(fovy, aspectRatio, nearPlane, farPlane);
}

void Camera::LookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up)
{
    m_position = from;
    m_view = m_handedness->CreateLookAt(from, to, up);
    m_world = glm::inverse(m_view);
    m_rotation = Quaternion::FromRotationMatrix(m_world);
}

/************************************************************************/
/* Camera Update                                                        */
/************************************************************************/
void Camera::Update(double elapsed)
{
    m_world = Matrix4f::FromRotation(m_rotation) *  Matrix4f::CreateTranslation(m_position);
    m_view = glm::inverse(m_world);
}

}
