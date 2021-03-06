#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DResource.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformBuffer :
public PlatformResource
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformBuffer(Renderer * renderer, const Buffer * buffer);
    virtual ~PlatformBuffer();

public:
    void
    Flush(Renderer *, int64_t offset, int64_t size);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    CreateBuffer(ID3D11Device1 * device);

    virtual void
    CreateResource(ID3D11Device1 * device) override final;

    virtual void
    CreateResourceView(ID3D11Device1 * device) override final;

protected:
    // NOTE(Wuxiang): mBufferObj doesn't need to be release in destructor, because
    // its base pointer is released in PlatformResource.
    Microsoft::WRL::ComPtr<ID3D11Buffer> mBufferObj;
    const Buffer *mBufferPtr;
};
FALCON_ENGINE_CLASS_END

}
#endif