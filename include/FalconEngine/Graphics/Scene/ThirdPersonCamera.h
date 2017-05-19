#pragma once

#include <FalconEngine/Graphics/Scene/PlayerCamera.h>

namespace FalconEngine
{

class GameEngineInput;

enum class ThirdPersonCameraMode
{
    None,
    Pan,
    Rotate,
    Zoom,
};

class ThirdPersonCamera;
using ThirdPersonCameraSharedPtr = std::shared_ptr<ThirdPersonCamera>;

class FALCON_ENGINE_API ThirdPersonCamera : public PlayerCamera
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit ThirdPersonCamera(const Handedness *handedness);
    ThirdPersonCamera(const Handedness *handedness, const Viewport& viewport, float nearPlane, float farPlane);
    ThirdPersonCamera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane, float farPlane);

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    /************************************************************************/
    /* Camera Setup                                                         */
    /************************************************************************/
    void
    SetTarget(Vector3f target);

    /************************************************************************/
    /* Camera Operation                                                     */
    /************************************************************************/
    // @summary Move the target position to the left related to camera.
    void
    PanLeft(float distance);

    // @summary Move the target position to the right related to camera.
    void
    PanRight(float distance);

    // @summary Move the target position to the top related to camera.
    void
    PanUp(float distance);

    // @summary Move the target position to the bottom related to camera.
    void
    PanDown(float distance);

    virtual void
    Update(GameEngineInput *input, double elapsed);

    void
    Reset();

public:
    /************************************************************************/
    /* Camera Data                                                          */
    /************************************************************************/
    float                 mAzimuthalRadian;                                  // Theta in spherical coordinate.
    float                 mPolarRadian;                                      // Phi in spherical coordinate.
    float                 mRadialDistance;                                   // R in spherical coordinate.

    Vector3f              mOrigin;                                           // Origin of third person camera.

    /************************************************************************/
    /* Control Data                                                         */
    /************************************************************************/
    ThirdPersonCameraMode mMode = ThirdPersonCameraMode::None;

    float                 mPanSpeed;                                         // Pixel per second
    float                 mRotateSpeed;
    float                 mZoomSpeed;                                        // Meter per second
};

}
