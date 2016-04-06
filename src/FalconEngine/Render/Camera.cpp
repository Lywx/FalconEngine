#include <FalconEngine/Camera.h>
#include <FalconEngine/Math.h>

namespace FalconEngine {
namespace Render {

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
/* Public Members                                                       */
/************************************************************************/
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

} // Render
} // FalconEngine
