#pragma once

#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>
#include <FalconEngine/Platform/Direct3D/Direct3DBuffer.h>

namespace FalconEngine
{

class Renderer;
class UniformBuffer;

class FALCON_ENGINE_API PlatformUniformBuffer : public PlatformBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformUniformBuffer(Renderer *renderer, const UniformBuffer *uniformBuffer);
    virtual ~PlatformUniformBuffer();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *, unsigned int bindingIndex);

    void
    Disable(Renderer *);
};

}

#endif
