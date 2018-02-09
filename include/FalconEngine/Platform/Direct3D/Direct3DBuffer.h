#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DMapping.h>
#include <FalconEngine/Platform/Direct3D/Direct3DResource.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformBuffer : public PlatformResource
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformBuffer(Renderer *renderer, const Buffer *buffer);
    virtual ~PlatformBuffer();

public:
    void
    Flush(Renderer *, int64_t offset, int64_t size);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    CreateBuffer(ID3D11Device4 *device);

    virtual void
    CreateResource(ID3D11Device4 *device) override;

protected:
    ID3D11Buffer *mBufferObj;
    const Buffer *mBufferPtr;
};

}
#endif