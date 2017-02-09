#pragma once

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>

#include <map>
#include <memory>
#include <string>

#include <FalconEngine/Graphics/Shaders/Shader.h>

namespace FalconEngine
{

class PlatformShader
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformShader(const Shader *shader);
    ~PlatformShader();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateFromString(GLenum shaderType, const std::string& shaderSource);

    void
    CreateFromFile(GLenum shaderType, const std::string& shaderFilename);

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

private:
    GLuint mProgram;
    int    mShaderNum;
    GLuint mShaders[int(ShaderType::Count)];
};

typedef std::shared_ptr<PlatformShader> PlatformShaderSharedPtr;

}
