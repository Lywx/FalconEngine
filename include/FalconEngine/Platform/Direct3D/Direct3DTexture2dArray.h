#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DTexture2d.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformTexture2dArray :
PlatformTexture2d
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2dArray(Renderer *, const Texture2dArray * textureArray);
    virtual ~PlatformTexture2dArray();

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    CreateTexture(ID3D11Device4 * device);

protected:
    ID3D11Texture2D *mTextureObj;
    const Texture2dArray *mTexturePtr;
};
FALCON_ENGINE_CLASS_END

}

#endif