#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformSampler final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformSampler(Renderer * renderer, const Sampler * sampler);
    ~PlatformSampler();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer * renderer, int textureUnit, unsigned int shaderMask);

    void
    Disable(Renderer * renderer, int textureUnit, unsigned int shaderMask);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Create(ID3D11Device1 * device);

private:
    const Sampler *mSampler;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> mSampleState;
};
FALCON_ENGINE_CLASS_END

}

#endif