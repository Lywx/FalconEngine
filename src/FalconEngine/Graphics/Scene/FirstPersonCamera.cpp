#include <FalconEngine/Graphics/Scene/FirstPersonCamera.h>

#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Math/Function.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(FirstPersonCamera, Camera);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
FirstPersonCamera::FirstPersonCamera(const Coordinate coordinate, const Handedness *handedness) :
    PlayerCamera(coordinate, handedness)
{
    Reset();
}

FirstPersonCamera::FirstPersonCamera(const Coordinate coordinate, const Handedness *handedness, const Viewport& viewport, float nearPlane, float farPlane):
    PlayerCamera(coordinate, handedness, viewport, nearPlane, farPlane)
{
    Reset();
}

FirstPersonCamera::FirstPersonCamera(const Coordinate coordinate, const Handedness *handedness, float fovy, float aspectRatio, float nearPlane, float farPlane) :
    PlayerCamera(coordinate, handedness, fovy, aspectRatio, nearPlane, farPlane)
{
    Reset();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
FirstPersonCamera::MoveForward(float distance)
{
    mPosition += GetForward() * distance;
}

void
FirstPersonCamera::MoveBackward(float distance)
{
    mPosition += GetBackward() * distance;
}

void
FirstPersonCamera::MoveLeft(float distance)
{
    mPosition += GetLeft() * distance;
}

void
FirstPersonCamera::MoveRight(float distance)
{
    mPosition += GetRight() * distance;
}

void
FirstPersonCamera::MoveUp(float distance)
{
    mPosition += GetUp() * distance;
}

void
FirstPersonCamera::MoveDown(float distance)
{
    mPosition += GetDown() * distance;
}

void
FirstPersonCamera::Update(GameEngineInput *input, double elapsed)
{
    auto tSecond = elapsed / 1000;

    auto mouse = input->GetMouseState();
    auto mousePositionDiff = mouse->GetPositionDiff();
    auto keyboard = input->GetKeyboardState();

    // Update camera orientation.
    {
        // NOTE(Wuxiang): 360 degree need 0.8 seconds. I tested it myself.
        static auto yawDegreeRotationPerSecondMax = 360 / 0.8;
        static auto pitchDegreeRotationPerSecondMax = 360 / 0.8;

        auto pitchDegreeRotation = float(mousePositionDiff.y * mMouseSensitivity * mMouseSensitivityAdjust * pitchDegreeRotationPerSecondMax * tSecond);
        auto yawDegreeRotation = -float(mousePositionDiff.x * mMouseSensitivity * mMouseSensitivityAdjust * yawDegreeRotationPerSecondMax * tSecond);

        // NOTE(Wuxiang): Camera is not allowed to do front / back flip movement.
        auto pitchDegreePrevious = Degree(mPitchRadian);
        auto pitchDegree = pitchDegreePrevious + pitchDegreeRotation;
        pitchDegree = Clamp<float>(pitchDegree, -90, 90);
        mPitchRadian = Radian(pitchDegree);
        auto pitchQuaternion = Quaternion::CreateFromAxisAngle(mCoordinate.GetAxisX(), mPitchRadian);

        auto yawDegreePrevious = Degree(mYawRadian);
        auto yawDegree = yawDegreePrevious + yawDegreeRotation;
        yawDegree = DegreeNormalize<float>(yawDegree, -180, 180);
        mYawRadian = Radian(yawDegree);
        auto yawQuaternion = Quaternion::CreateFromAxisAngle(mCoordinate.GetAxisY(), mYawRadian);

        auto pitchYawQuaternion = yawQuaternion * pitchQuaternion;

        // NOTE(Wuxiang): Inspired by NumberXaero's answer
        // https://www.gamedev.net/topic/653628-quaternion-camera-performs-unwanted-roll/
        auto forward = GetForward() * pitchYawQuaternion;
        auto rollQuaternion = Quaternion::CreateFromAxisAngle(forward, 0);

        SetOrientation(rollQuaternion * pitchYawQuaternion);
    }

    // Update camera position.
    {
        // NEW(Wuxiang): 2017-05-19 17:11 Add keyboard mapping support.
        auto flyDistanceMeter = float(mFlySpeed * tSecond);

        if (keyboard->KeyPressed(Key::S))
        {
            MoveBackward(flyDistanceMeter);
        }

        if (keyboard->KeyPressed(Key::W))
        {
            MoveForward(flyDistanceMeter);
        }

        if (keyboard->KeyPressed(Key::A))
        {
            MoveLeft(flyDistanceMeter);
        }

        if (keyboard->KeyPressed(Key::D))
        {
            MoveRight(flyDistanceMeter);
        }
    }

    Camera::Update(elapsed);
}

void
FirstPersonCamera::Reset()
{
    mPitchRadian = 0.0f;
    mYawRadian   = 0.0f;
    mRollRadian  = 0.0f;

    mFlySpeed = 10.0f;
}

}
