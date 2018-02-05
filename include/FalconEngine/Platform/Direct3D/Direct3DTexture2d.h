#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DTexture1d.h>

namespace FalconEngine
{

class Renderer;
class Texture2d;

FALCON_ENGINE_CLASS_BEGIN PlatformTexture2d final :
public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2d(Renderer * renderer, const Texture2d * texture);
    virtual ~PlatformTexture2d();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void *
    Map(Renderer * renderer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode synchronization,
        int64_t offset,
        int64_t size);

    void
    Unmap(Renderer * renderer);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    CreateTexture(ID3D11Device4 * device);

    void
    CreateShaderResourceView(ID3D11Device4 * device);

    void
    CreateRenderTargetView(ID3D11Device4 * device);

protected:
    ID3D11Texture2D *mTextureObj;
    const Texture2d *mTexturePtr;
};
FALCON_ENGINE_CLASS_END

}


#endif
