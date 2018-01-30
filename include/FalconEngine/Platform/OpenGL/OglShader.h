#pragma once

#include <FalconEngine/Platform/OpenGL/Common.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <map>
#include <memory>
#include <string>

#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformShader
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformShader(Shader *shader);
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
    Enable() const;

    void
    Disable() const;

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