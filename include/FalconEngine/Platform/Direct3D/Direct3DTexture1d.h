#pragma once

#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DTexture.h>

namespace FalconEngine
{

class Renderer;
class Texture1d;

FALCON_ENGINE_CLASS_BEGIN PlatformTexture1d final :
public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture1d(Renderer * renderer, const Texture1d * texture);
    ~PlatformTexture1d();

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
    ID3D11Texture1D *mTextureObj;
    const Texture1d *mTexturePtr;
};
FALCON_ENGINE_CLASS_END

}


#endif
