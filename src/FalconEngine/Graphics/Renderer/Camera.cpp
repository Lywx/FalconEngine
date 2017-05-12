#include <FalconEngine/Graphics/Renderer/Camera.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Camera, Object);
FALCON_ENGINE_RTTI_IMPLEMENT_EXPORT(Camera);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Camera::Camera(const Handedness *handedness)
    : Camera(handedness, PiOver4, 1.77777f)
{
}

Camera::Camera(const Handedness *handedness, const Viewport& viewport, float nearPlane /*=0.1f*/, float farPlane /*=1000.f*/)
    : Camera(handedness, PiOver4, viewport.GetAspect(), nearPlane, farPlane)
{
}

Camera::Camera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane /*=0.1f*/, float farPlane /*=1000.f*/) :
    mAspectRatio(aspectRatio),
    mFarPlane(farPlane),
    mNearPlane(nearPlane),
    mFovy(fovy),
    mPosition(Vector3f::Zero),
    mOrientation(Quaternion::Identity),
    mView(Matrix4f::Identity),
    mWorld(Matrix4f::Identity),
    mHandedness(handedness)
{
    mProjection = mHandedness->CreatePerspectiveFieldOfView(mFovy, mAspectRatio, mNearPlane, mFarPlane);
}

Camera::~Camera()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

const Vector3f&
Camera::GetPosition() const
{
    return mPosition;
}

Vector3f
Camera::GetForward() const
{
    return mHandedness->Forward(mView);
}

Vector3f
Camera::GetBackward() const
{
    return mHandedness->Backward(mView);
}

Vector3f
Camera::GetLeft() const
{
    return mHandedness->Left(mView);
}

Vector3f
Camera::GetRight() const
{
    return mHandedness->Right(mView);
}

Vector3f
Camera::GetUp() const
{
    return mHandedness->Up(mView);
}

Vector3f
Camera::GetDown() const
{
    return mHandedness->Down(mView);
}

void
Camera::MoveForward(float distance)
{
    mPosition += GetForward() * distance;
}

void
Camera::MoveBackward(float distance)
{
    mPosition += GetBackward() * distance;
}

void
Camera::MoveLeft(float distance)
{
    mPosition += GetLeft() * distance;
}

void
Camera::MoveRight(float distance)
{
    mPosition += GetRight() * distance;
}

void
Camera::MoveUp(float distance)
{
    mPosition += GetUp() * distance;
}

void
Camera::MoveDown(float distance)
{
    mPosition += GetDown() * distance;
}

void
Camera::SetRotation(const Matrix4f& rotation)
{
    mWorld = rotation * mWorld;
    mView = Matrix4f::Inverse(mWorld);
}

void
Camera::SetRotation(const Quaternion& rotation)
{
    mOrientation = mOrientation * rotation;
}

const Quaternion&
Camera::GetOrientation() const
{
    return mOrientation;
}

void
Camera::SetOrientation(float pitch, float yaw, float roll)
{
    Quaternion rotationPitch = Quaternion::CreateFromAxisAngle(Vector3f::UnitX, pitch);
    Quaternion rotationYaw   = Quaternion::CreateFromAxisAngle(Vector3f::UnitY, yaw);
    Quaternion rotationRoll  = Quaternion::CreateFromAxisAngle(Vector3f::UnitZ, roll);

    mOrientation = rotationPitch * rotationYaw * rotationRoll;
}

void
Camera::SetOrientation(const Quaternion& orientation)
{
    mOrientation = orientation;
}

float
Camera::GetNear() const
{
    return mNearPlane;
}

float
Camera::GetFar() const
{
    return mFarPlane;
}

const Matrix4f&
Camera::GetWorld() const
{
    return mWorld;
}

const Matrix4f&
Camera::GetView() const
{
    return mView;
}

const Matrix4f&
Camera::GetProjection() const
{
    return mProjection;
}

void
Camera::SetWorld(const Matrix4f& world)
{
    mWorld = world;
    mView = Matrix4f::Inverse(mWorld);
}

void
Camera::SetView(const Matrix4f& view)
{
    mView = view;
}

void
Camera::SetProjection(const Matrix4f& projection)
{
    mProjection = projection;
}

float
Camera::GetVerticalFieldOfView() const
{
    return mFovy;
}

float
Camera::GetHorizontalFieldOfView() const
{
    return 2.f * atan(mAspectRatio * tan(mFovy * 0.5f) );
}

void Camera::SetPosition(const Vector3f& position)
{
    mPosition = position;
    mWorld = Matrix4f::CreateTranslation(position) * mWorld;
    mView = Matrix4f::Inverse(mWorld);
}

void
Camera::SetProjectionPerspectiveFieldOfView(float fovy, float aspectRatio, float nearPlane, float farPlane)
{
    mNearPlane = nearPlane;
    mFarPlane = farPlane;
    mProjection = mHandedness->CreatePerspectiveFieldOfView(fovy, aspectRatio, nearPlane, farPlane);
}

void
Camera::SetProjectionPerspective(float width, float height, float nearPlane, float farPlane)
{
    mNearPlane = nearPlane;
    mFarPlane = farPlane;
    mProjection = mHandedness->CreatePerspective(width, height, nearPlane, farPlane);
}

void
Camera::SetProjectionOrthogonal(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    mNearPlane = nearPlane;
    mFarPlane = farPlane;
    mProjection = mHandedness->CreateOrthogonal(left, right, bottom, top, nearPlane, farPlane);
}

void
Camera::LookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up)
{
    mPosition = from;
    mView = mHandedness->CreateLookAt(from, to, up);
    mWorld = Matrix4f::Inverse(mView);
    mOrientation = Quaternion::CreateFromRotationMatrix(mWorld);
}

void
Camera::Update(double /* elapsed */)
{
    mWorld = Matrix4f::CreateTranslation(mPosition) * Matrix4f::CreateRotation(mOrientation);
    mView = Matrix4f::Inverse(mWorld);
}

}
