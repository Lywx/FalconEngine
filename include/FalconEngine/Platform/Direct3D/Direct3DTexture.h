#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>
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
    Enable(Renderer * renderer,
           int textureUnit,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(Renderer * renderer,
            int textureUnit,
            const TextureShaderMaskList & textureShaderMaskList);

    using PlatformResource::Map;

    void *
    Map(Renderer * renderer,
        int textureIndex,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    using PlatformResource::Unmap;

    void
    Unmap(Renderer * renderer,
          int textureIndex);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    int
    GetSubresourceIndex(int mipmapIndex, int mipmapLevel, int textureIndex);

    int
    GetSubresourceIndex(int mipmapIndex, int textureIndex);

protected:
    std::array<int, 3> mDimension;
    int mMipmapLevel;
    const Texture *mTexturePtr;
};
FALCON_ENGINE_CLASS_END

}

#endif
