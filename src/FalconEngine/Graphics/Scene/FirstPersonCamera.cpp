#include <FalconEngine/Graphics/Scene/FirstPersonCamera.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(FirstPersonCamera, Camera);

FirstPersonCamera::FirstPersonCamera(const Handedness *handedness) :
    Camera(handedness),
    mPitch(0), mYaw(0), mRoll(0)
{
}

FirstPersonCamera::FirstPersonCamera(const Handedness *handedness, const Viewport& viewport, float nearPlane, float farPlane):
    Camera(handedness, viewport, nearPlane, farPlane),
    mYaw(0), mRoll(0), mPitch(0)
{
}

FirstPersonCamera::FirstPersonCamera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane, float farPlane):
    Camera(handedness, fovy, aspectRatio, nearPlane, farPlane),
    mYaw(0), mRoll(0), mPitch(0)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
FirstPersonCamera::Update(double elapsed)
{
    SetRotation(mPitch, mYaw, mRoll);

    Camera::Update(elapsed);
}

}
