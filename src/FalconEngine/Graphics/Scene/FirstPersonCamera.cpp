#include <FalconEngine/Graphics/Scene/FirstPersonCamera.h>

#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>
#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(FirstPersonCamera, Camera);

FirstPersonCamera::FirstPersonCamera(const Handedness *handedness) :
    Camera(handedness)
{
}

FirstPersonCamera::FirstPersonCamera(const Handedness *handedness, const Viewport& viewport, float nearPlane, float farPlane):
    Camera(handedness, viewport, nearPlane, farPlane)
{
}

FirstPersonCamera::FirstPersonCamera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane, float farPlane):
    Camera(handedness, fovy, aspectRatio, nearPlane, farPlane)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
FirstPersonCamera::Update(GameEngineInput *input, double elapsed)
{
    auto tSecond = elapsed / 1000;

    // Mouse
    {
        auto mouse = input->GetMouseState();
        auto mousePositionDiff = mouse->GetPositionDiff();

        // NOTE(Wuxiang): 360 degree need 0.8 seconds. I test it myself.
        static auto yawDegreeRotationPerSecond = 36 / 0.8;
        static auto pitchDegreeRotationPerSecond = 36 / 0.8;
        // static auto yawDegreeRotationPerSecondMax = 360 / 0.8;
        // static auto pitchDegreeRotationPerSecondMax = 360 / 0.8;

        auto pitchDegreeRotation = float(mousePositionDiff.y * mSensitivity * pitchDegreeRotationPerSecond * tSecond);
        auto yawDegreeRotation = -float(mousePositionDiff.x * mSensitivity * yawDegreeRotationPerSecond * tSecond);

        // NOTE(Wuxiang): Camera is not allowed to do front / back flip movement.
        auto pitchDegreePrevious = Degree(mPitch);
        auto pitchDegree = pitchDegreePrevious + pitchDegreeRotation;
        mPitch = Radian(Clamp<float>(pitchDegree, -90, 90));
        auto pitchQuaternion = Quaternion::CreateFromAxisAngle(Vector3f::UnitX, mPitch);

        auto yawDegreePrevious = Degree(mYaw);
        auto yawDegree = yawDegreePrevious + yawDegreeRotation;
        mYaw = Radian(Clamp<float>(DegreeNormalize(yawDegree), -360, 360));
        auto yawQuaternion = Quaternion::CreateFromAxisAngle(Vector3f::UnitY, mYaw);

        auto pitchYawQuaternion = yawQuaternion * pitchQuaternion;

        // NOTE(Wuxiang): Inspired by NumberXaero's answer
        // https://www.gamedev.net/topic/653628-quaternion-camera-performs-unwanted-roll/
        auto forward = GetForward() * pitchYawQuaternion;

        auto rollQuaternion = Quaternion::CreateFromAxisAngle(forward, 0);

        SetOrientation(rollQuaternion * pitchYawQuaternion);
    }

    // Keyboard
    {
        auto keyboard = input->GetKeyboardState();
        auto distanceMeter = float(mSpeed * tSecond);

        if (keyboard->KeyPressed(Key::S))
        {
            MoveBackward(distanceMeter);
        }

        if (keyboard->KeyPressed(Key::W))
        {
            MoveForward(distanceMeter);
        }

        if (keyboard->KeyPressed(Key::A))
        {
            MoveLeft(distanceMeter);
        }

        if (keyboard->KeyPressed(Key::D))
        {
            MoveRight(distanceMeter);
        }
    }

    Camera::Update(elapsed);
}

}
