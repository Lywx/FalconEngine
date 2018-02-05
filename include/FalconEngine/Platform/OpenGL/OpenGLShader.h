#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <map>
#include <memory>
#include <string>

#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

class Renderer;

class FALCON_ENGINE_API PlatformShader
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShader(Renderer *, Shader *shader);
    ~PlatformShader();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateFromString(int shaderIndex, GLenum shaderType, const std::string& shaderSource);

    void
    LinkProgram();

    void
    DeleteProgram() const;

    GLuint
    GetProgram() const;

    void
    Enable(Renderer *) const;

    void
    Disable(Renderer *) const;

    // @remark This function is primarily used in debugging.
    void
    CollectUniformActive();

protected:

    // @remark This function modify the shader rather than the platform shader.
    void
    CollectUniformLocation(Shader *shader) const;

private:
    GLuint mProgram;
    int    mShaderNum;
    GLuint mShaders[int(ShaderType::Count)];
};

typedef std::shared_ptr<PlatformShader> PlatformShaderSharedPtr;

}

#endif