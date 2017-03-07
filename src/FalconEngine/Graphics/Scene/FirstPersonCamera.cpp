#include <FalconEngine/Graphics/Scene/FirstPersonCamera.h>

#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>
#include <FalconEngine/Input/MouseState.h>

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

        auto yawDegreeRotation = float(yawDegreeRotationPerSecond * tSecond);
        auto pitchDegreeRotation = float(pitchDegreeRotationPerSecond * tSecond);

        auto pitchDegreePrevious = Degree(mPitch);
        pitchDegreePrevious = pitchDegreePrevious + mousePositionDiff.y * mMouseSensitivity * pitchDegreeRotation;

        // NOTE(Wuxiang): Camera is not allowed to do front / back flip movement.
        mPitch = Radian(Clamp<float>(pitchDegreePrevious, -90, 90));

        auto yawDegreePrevious = Degree(mYaw);
        yawDegreePrevious -= mousePositionDiff.x * mMouseSensitivity * yawDegreeRotation;

        mYaw = Radian(Clamp<float>(DegreeNormalize(yawDegreePrevious), -360, 360));

        SetRotation(mPitch, mYaw, mRoll);
    }

    // Keyboard
    {
        auto keyboard = input->GetKeyboardState();

        static auto meterPerSecond = 3.0;
        auto meterDistance = float(meterPerSecond * tSecond);

        if (keyboard->KeyPressed(Key::S))
        {
            MoveBackward(meterDistance);
        }

        if (keyboard->KeyPressed(Key::W))
        {
            MoveForward(meterDistance);
        }

        if (keyboard->KeyPressed(Key::A))
        {
            MoveLeft(meterDistance);
        }

        if (keyboard->KeyPressed(Key::D))
        {
            MoveRight(meterDistance);
        }
    }

    Camera::Update(elapsed);
}

}
