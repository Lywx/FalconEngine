#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <map>
#include <memory>
#include <string>

#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{
class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformShader final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShader(Renderer * renderer, Shader * shader);
    ~PlatformShader();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer * renderer) const;

    void
    Disable(Renderer * renderer) const;

protected:
    void
    CreateShaderFromString(ID3D11Device4 * device,
                           int shaderIndex,
                           ShaderType shaderType,
                           const std::string & shaderSource);

    void
    SetShader(int shaderIndex, ID3D11DeviceChild * shader);

private:
    int mShaderNum;
    ID3D11DeviceChild *mShaders[int(ShaderType::Count)];
};
FALCON_ENGINE_CLASS_END

}

#endif