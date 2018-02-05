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
        BufferAccessMode access,
        BufferFlushMode flush,
        BufferSynchronizationMode synchronization,
        int64_t offset,
        int64_t size)
    {
        // TODO(Wuxiang): Add mipmap support.
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        D3DCheckSuccess(renderer->mData->GetContext()->Map(resource, 0,
                        Direct3DBufferAccessMode[int(access)],
                        0, &mappedSubresource));
        return mappedSubresource.pData;
    }

    template <typename T>
    void
    Unmap(Renderer * renderer,
          T *        resource)
    {
        renderer->mData->GetContext()->Unmap(resource, 0);
    }

};
FALCON_ENGINE_CLASS_END

}


#endif
