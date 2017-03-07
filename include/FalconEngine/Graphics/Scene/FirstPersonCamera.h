#pragma once

#include <FalconEngine/Graphics/Renderer/Camera.h>

namespace FalconEngine
{

class FirstPersonCamera;
using FirstPersonCameraSharedPtr = std::shared_ptr<FirstPersonCamera>;

class FirstPersonCamera : public Camera
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
    virtual void
    Update(double elapsed) override;

public:
    float mPitch;
    float mYaw;
    float mRoll;
};

}
