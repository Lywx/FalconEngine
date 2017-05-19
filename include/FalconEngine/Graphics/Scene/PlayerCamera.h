#pragma once

#include <FalconEngine/Graphics/Renderer/Camera.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlayerCamera : public Camera
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using Camera::Camera;

public:
    float mMouseSensitivity = 1.0f; // Mouse sensitivity govern all mouse interaction.
    float mMouseSensitivityAdjust = 1.0f / 10.0f;
};

}
