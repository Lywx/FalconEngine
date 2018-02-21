#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <map>
#include <memory>
#include <string>

#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

class Renderer;

FALCON_ENGINE_CLASS_BEGIN PlatformShader final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShader(Renderer *, Shader * shader);
    ~PlatformShader();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *) const;

    void
    Disable(Renderer *) const;

private:
    void
    CreateShaderFromString(int shaderIndex, GLenum shaderType, const std::string & shaderSource);

    void
    LinkProgram();

    void
    DeleteProgram() const;

    GLuint
    GetProgram() const;

    // @remark This function is primarily used in debugging.
    void
    CollectUniformActive();

    // @remark This function modify the shader rather than the platform shader.
    void
    CollectUniformLocation(Shader * shader) const;

    void
    CollectUniformBufferBlockIndex(Shader * shader) const;

    void
    RegisterUniformBufferBindingIndex(Shader * shader) const;

private:
    GLuint mProgram;
    GLuint mShaders[int(ShaderType::Count)];
    int    mShaderNum;
};
FALCON_ENGINE_CLASS_END

}

#endif