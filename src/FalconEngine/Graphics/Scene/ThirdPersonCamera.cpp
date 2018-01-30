#include <FalconEngine/Graphics/Scene/ThirdPersonCamera.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEngineGraphics.h>
#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>
#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(ThirdPersonCamera, Camera);

ThirdPersonCamera::ThirdPersonCamera(const Coordinate coordinate, const Handedness *handedness) :
    PlayerCamera(coordinate, handedness)
{
    Reset();
}

ThirdPersonCamera::ThirdPersonCamera(const Coordinate coordinate, const Handedness *handedness, const Viewport& viewport, float nearPlane, float farPlane) :
    PlayerCamera(coordinate, handedness, viewport, nearPlane, farPlane)
{
    Reset();
}

ThirdPersonCamera::ThirdPersonCamera(const Coordinate coordinate, const Handedness *handedness, float fovy, float aspectRatio, float nearPlane, float farPlane) :
    PlayerCamera(coordinate, handedness, fovy, aspectRatio, nearPlane, farPlane)
{
    Reset();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
ThirdPersonCamera::SetTarget(Vector3f target)
{
    mOrigin = target;
}

void
ThirdPersonCamera::PanLeft(float distance)
{
    // NOTE(Wuxiang): Pan operation move the camera in opposite direction.
    mOrigin += -GetLeft() * distance;
}

void
ThirdPersonCamera::PanRight(float distance)
{
    // NOTE(Wuxiang): Pan operation move the camera in opposite direction.
    mOrigin += -GetRight() * distance;
}

void
ThirdPersonCamera::PanUp(float distance)
{
    // NOTE(Wuxiang): Pan operation move the camera in opposite direction.
    mOrigin += -GetUp() * distance;
}

void
ThirdPersonCamera::PanDown(float distance)
{
    // NOTE(Wuxiang): Pan operation move the camera in opposite direction.
    mOrigin += -GetDown() * distance;
}

void
ThirdPersonCamera::Update(double elapsed)
{
    // NOTE(Wuxiang): The spherical coordinate computation here won't be affected by
    // the sign of azimuthal angle and polar angle. Regardless of the sign of angles,
    // the computation yield correct r vector pointed from origin to target.

    auto z = mRadialDistance * glm::sin(mAzimuthalRadian) * glm::cos(mPolarRadian);
    auto x = mRadialDistance * glm::sin(mAzimuthalRadian) * glm::sin(mPolarRadian);
    auto y = mRadialDistance * glm::cos(mAzimuthalRadian);
    auto r = mCoordinate.GetAxisX() * x +
             mCoordinate.GetAxisY() * y +
             mCoordinate.GetAxisZ() * z;

    mPosition = mOrigin + r;

    auto pitchRadian = abs(mAzimuthalRadian) - PiOver2;
    auto pitchQuaternion = Quaternion::CreateFromAxisAngle(mCoordinate.GetAxisX(), pitchRadian);
    auto yawRadian = mPolarRadian;
    auto yawQuaternion = Quaternion::CreateFromAxisAngle(mCoordinate.GetAxisY(), yawRadian);
    auto pitchYawQuaternion = yawQuaternion * pitchQuaternion;

    // NOTE(Wuxiang): Inspired by NumberXaero's answer
    // https://www.gamedev.net/topic/653628-quaternion-camera-performs-unwanted-roll/
    auto forward = GetForward() * pitchYawQuaternion;
    auto rollQuaternion = Quaternion::CreateFromAxisAngle(forward, 0);

    SetOrientation(rollQuaternion * pitchYawQuaternion);

    Camera::Update(elapsed);
}

void
ThirdPersonCamera::Update(GameEngineInput *input, double elapsed)
{
    auto tSecond = elapsed / 1000;

    auto mouse = input->GetMouseState();
    auto mousePositionDiff = mouse->GetPositionDiff();
    auto keyboard = input->GetKeyboardState();

    // Update camera control scheme (Blender style control scheme).
    {
        // NEW(Wuxiang): 2017-05-16 15:35 Add keyboard mapping support.
        auto keyCtrlPressed = keyboard->KeyPressed(Key::LeftControl) || keyboard->KeyPressed(Key::RightControl);
        auto keyShiftPressed = keyboard->KeyPressed(Key::LeftShift) || keyboard->KeyPressed(Key::RightShift);
        auto middleButtonPressed = mouse->ButtonPressed(MouseButton::MiddleButton);

        if (keyShiftPressed && middleButtonPressed)
        {
            mMode = ThirdPersonCameraMode::Pan;
        }
        else if (keyCtrlPressed && middleButtonPressed)
        {
            mMode = ThirdPersonCameraMode::Zoom;
        }
        else if (middleButtonPressed)
        {
            mMode = ThirdPersonCameraMode::Rotate;
        }
        else
        {
            mMode = ThirdPersonCameraMode::None;
        }
    }

    // Update camera position and orientation based on modes.
    switch (mMode)
    {
    case ThirdPersonCameraMode::None:
        break;

    case ThirdPersonCameraMode::Pan:
    {
        Vector2f panDistancePixel = mousePositionDiff * mMouseSensitivity * mMouseSensitivityAdjust
                                    * mPanSpeed * float(tSecond);

        // Pan distance in window space.
        Vector3f panDistanceWindow = Vector3f(panDistancePixel, 0);

        static auto sMasterRenderer = Renderer::GetInstance();
        auto viewport = sMasterRenderer->GetViewport();

        // Target position in window space.
        Vector3f targetPositionWindow = viewport->Project(mOrigin, mProjection, mView);

        // Target modified position in window space. Because we don't move the
        // objects in world space, we need to reverse the transform to move the
        // camera itself. Hence we use the - sign.
        Vector3f targetPositionFinalWindow = targetPositionWindow - panDistanceWindow;

        mOrigin = viewport->Unproject(targetPositionFinalWindow, mProjection, mView);

        break;
    }

    case ThirdPersonCameraMode::Rotate:
    {
        static auto azimuthalDegreeRotationPerSecondMax = 360 / 0.8;
        static auto polarDegreeRotationPerSecondMax = 360 / 0.8;

        auto azimuthalDegreeRotation = float(mousePositionDiff.y * mMouseSensitivity * mMouseSensitivityAdjust * azimuthalDegreeRotationPerSecondMax * tSecond);
        auto polarDegreeRotation = -float(mousePositionDiff.x * mMouseSensitivity * mMouseSensitivityAdjust * polarDegreeRotationPerSecondMax * tSecond);

        auto azimuthalDegreePrevious = Degree(mAzimuthalRadian);
        auto azimuthalDegree = azimuthalDegreePrevious + azimuthalDegreeRotation;
        azimuthalDegree = DegreeNormalize<float>(azimuthalDegree, 0, 180);
        mAzimuthalRadian = Radian(azimuthalDegree);

        auto polarDegreePrevious = Degree(mPolarRadian);
        auto polarDegree = polarDegreePrevious + polarDegreeRotation;
        polarDegree = DegreeNormalize<float>(polarDegree, -180, 180);
        mPolarRadian = Radian(polarDegree);

        break;
    }

    case ThirdPersonCameraMode::Zoom:
    {
        auto zoomDistance = mousePositionDiff.y * mMouseSensitivity * mMouseSensitivityAdjust
                            * mZoomSpeed * float(tSecond);
        mRadialDistance += zoomDistance;

        // Don't allow distance to go below zero.
        if (mRadialDistance < 0)
        {
            mRadialDistance = 0;
        }

        break;
    }

    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    Update(elapsed);
}

void
ThirdPersonCamera::Reset()
{
    mAzimuthalRadian = 0.0f;
    mPolarRadian = 0.0f;
    mRadialDistance = 0.0f;

    mOrigin = Vector3f::Zero;

    mPanSpeed = 500.0f;
    mRotateSpeed = 1.0f;
    mZoomSpeed = 100.0f;
}

}
