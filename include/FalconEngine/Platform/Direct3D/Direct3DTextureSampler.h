#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformSampler
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformSampler(Renderer *renderer, const Sampler *sampler);
    ~PlatformSampler();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *renderer, int textureUnit);

    void
    Disable(Renderer *renderer, int textureUnit);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Create(ID3D11Device4 *device);

private:
    const Sampler      *mSampler;
    ID3D11SamplerState *mSampleState;
};

}

#endif