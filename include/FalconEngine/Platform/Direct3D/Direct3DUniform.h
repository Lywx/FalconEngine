#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
namespace FalconEngine
{

class Uniform;

FALCON_ENGINE_CLASS_BEGIN PlatformUniform
{
public:
    static void
    UpdateContext(Uniform *)
    {
        // NOTE(Wuxiang): Direct3D 11 doesn't support Uniform variable.
    }
};
FALCON_ENGINE_CLASS_END
}

#endif