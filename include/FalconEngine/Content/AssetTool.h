#pragma once

#include <FalconEngine/Core/Macro.h>

#include <string>

#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

namespace FalconEngine
{

class Shader;

FALCON_ENGINE_CLASS_BEGIN AssetTool final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    AssetTool();
    ~AssetTool();

public:
    /************************************************************************/
    /* OpenGL Members                                                       */
    /************************************************************************/
    void
    OGLValidateShader(Shader & shader);

    /************************************************************************/
    /* Direct3D Members                                                     */
    /************************************************************************/
    void
    D3DBakeShader(const std::string & shaderFilePath);

    void
    D3DSetShaderCompiler(const std::string & fxcCompilerPath);

private:
    ShaderType
    GetShaderType(const std::string & shaderFilePath);

    /************************************************************************/
    /* OpenGL Members                                                       */
    /************************************************************************/
    void
    OGLInitializeContextPlatform();

    /************************************************************************/
    /* Direct3D Members                                                     */
    /************************************************************************/
private:
    std::string mFxcCompilerPath;
};
FALCON_ENGINE_CLASS_END

}

