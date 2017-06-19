#pragma once

#include <FalconEngine/Graphics/Scene/PlayerCamera.h>

namespace FalconEngine
{

class GameEngineInput;

// @summary Free-flying First-person camera.
class FALCON_ENGINE_API FirstPersonCamera : public PlayerCamera
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit FirstPersonCamera(const Handedness *handedness);
    FirstPersonCamera(const Handedness *handedness, const Viewport& viewport, float nearPlane, float farPlane);
    FirstPersonCamera(const Handedness *handedness, float fovy, float aspectRatio, float nearPlane, float farPlane);

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    /************************************************************************/
    /* Camera Operation                                                     */
    /************************************************************************/
    void
    MoveForward(float distance);

    void
    MoveBackward(float distance);

    void
    MoveLeft(float distance);

    void
    MoveRight(float distance);

    void
    MoveUp(float distance);

    void
    MoveDown(float distance);

    virtual void
    Update(GameEngineInput *input, double elapsed);

    void
    Reset();

public:
    /************************************************************************/
    /* Camera Data                                                          */
    /************************************************************************/
    float mPitchRadian;
    float mYawRadian;
    float mRollRadian;

    /************************************************************************/
    /* Control  Data                                                        */
    /************************************************************************/
    float mFlySpeed;                                                         // Meter per second
};

}
