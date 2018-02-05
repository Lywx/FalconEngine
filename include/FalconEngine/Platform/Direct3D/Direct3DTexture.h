#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DResource.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

namespace FalconEngine
{

class Renderer;
class Texture;

FALCON_ENGINE_CLASS_BEGIN PlatformTexture :
public PlatformResource
{
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
protected:
    explicit PlatformTexture(Renderer * renderer, const Texture * texture);
public:
    virtual ~PlatformTexture();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer * renderer, int textureUnit);

    void
    Disable(Renderer * renderer, int textureUnit);

protected:
    ID3D11RenderTargetView   *mRenderTargetView;
    ID3D11ShaderResourceView *mShaderResourceView;
};
FALCON_ENGINE_CLASS_END

}


#endif
