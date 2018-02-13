#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <vector>

#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DTexture1d.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformTexture1dArray :
public PlatformTexture1d
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture1dArray(Renderer *, const Texture1dArray * textureArray);
    virtual ~PlatformTexture1dArray();
};
FALCON_ENGINE_CLASS_END

}

#endif