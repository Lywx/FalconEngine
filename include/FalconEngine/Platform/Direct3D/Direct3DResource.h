#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DRendererData.h>
#include <FalconEngine/Platform/Win32/Win32Exception.h>

namespace FalconEngine
{

class Renderer;

// @summary Base class of all resource object in Direct3D.
//
// @remark The derived class is supposed to assign mResourceObj after the resource
// creation is complete.
FALCON_ENGINE_CLASS_BEGIN PlatformResource
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformResource(Renderer * renderer, const Object * resource);
    virtual ~PlatformResource();

public:
    void *
    Map(Renderer * renderer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(Renderer * renderer);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    // @remark Implementer should initialize resource pointer in base class.
    virtual void
    CreateResource(ID3D11Device4 * device) = 0;

    // @remark This method is assumed to be called after all the filed is set
    // correctly, like mBindFlag, mFormat etc.
    void
    CreateResourceView(ID3D11Device4 * device);

    void
    CreateResourceViewAsTexture1d(ID3D11Device4 * device,
                                  D3D11_RESOURCE_DIMENSION dimension,
                                  const Texture * texture);

    void
    CreateResourceViewAsTexture2d(ID3D11Device4 * device,
                                  D3D11_RESOURCE_DIMENSION dimension,
                                  const Texture * texture);

    void
    CreateDepthStencilView(ID3D11Device4 * device, D3D11_RESOURCE_DIMENSION dimension);

    void
    CreateShaderResourceView(ID3D11Device4 * device, D3D11_RESOURCE_DIMENSION dimension);

    void
    CreateRenderTargetView(ID3D11Device4 * device, D3D11_RESOURCE_DIMENSION dimension);

    void
    CreateUnorderedAccessView(ID3D11Device4 * device, D3D11_RESOURCE_DIMENSION dimension);

protected:
    UINT mBindFlag;
    UINT mCpuFlag;
    DXGI_FORMAT mFormat;
    UINT mMiscFlags;
    D3D11_USAGE mUsage;

    ID3D11DepthStencilView *mDepthStencilView;
    ID3D11RenderTargetView *mRenderTargetView;
    ID3D11ShaderResourceView *mShaderResourceView;
    ID3D11UnorderedAccessView *mUnorderedAccessView;

    ID3D11Resource *mResourceObj;
    const Object *mResourcePtr;
};
FALCON_ENGINE_CLASS_END

}

#define FALCON_ENGINE_RESOURCE_MAP_IMPLEMENT(resource, InterfaceKlass) \
void * \
Map(Renderer *renderer, \
    ResourceMapAccessMode access, \
    ResourceMapFlushMode flush, \
    ResourceMapSyncMode sync, \
    int64_t offset, \
    int64_t size) \
{ \
    return PlatformResource::Map<InterfaceKlass>(renderer, resource, access, \
        flush, sync, offset, size); \
}

#define FALCON_ENGINE_RESOURCE_UNMAP_IMPLEMENT(resource, InterfaceKlass) \
void \
Unmap(Renderer * renderer) \
{ \
    return PlatformResource::Unmap<InterfaceKlass>(renderer, resource); \
}

#endif
