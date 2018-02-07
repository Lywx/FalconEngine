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

FALCON_ENGINE_CLASS_BEGIN PlatformResource
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformResource(Renderer * renderer);
    virtual ~PlatformResource();

protected:
    template <typename T>
    void *
    Map(Renderer * renderer,
        T *        resource,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size)
    {
        _UNUSED(flush);
        _UNUSED(sync);
        _UNUSED(size);

        // TODO(Wuxiang): Add mipmap support.
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        D3DCheckSuccess(renderer->mData->GetContext()->Map(
                            resource,
                            0,
                            Direct3DResourceMapMode[int(access)],
                            0,
                            &mappedSubresource));
        return mappedSubresource.pData + offset;
    }

    template <typename T>
    void
    Unmap(Renderer * renderer,
          T *        resource)
    {
        renderer->mData->GetContext()->Unmap(resource, 0);
    }

protected:
    UINT mCpuFlag;
    UINT mMiscFlags;
    D3D11_USAGE mUsage;

    ID3D11RenderTargetView *mRenderTargetView;
    ID3D11ShaderResourceView *mShaderResourceView;
    ID3D11UnorderedAccessView *mUnorderedAccessView;

    ID3D11Resource *mResourceObj;
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
