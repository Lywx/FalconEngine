#include <FalconEngine/Platform/OpenGL/OglShader.h>
#include <FalconEngine/Platform/OpenGL/OglShaderProcessor.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Core/Path.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShader::PlatformShader(Shader *shader) :
    mProgram(0),
    mShaderNum(0)
{
    // Initialize to zero.
    std::fill_n(mShaders, int(ShaderType::Count), 0);

    // Compile all shader source.
    for (auto shaderIter = shader->GetShaderSourceBegin(); shaderIter != shader->GetShaderSourceEnd(); ++shaderIter)
    {
        auto shaderIndex = shaderIter->first;
        auto shaderType = shader->GetShaderType(shaderIndex);
        auto shaderSource = shaderIter->second.get();
        PlatformShaderProcessor::ProcessShaderExtension(shaderSource);

        // Compile for each part of shader
        CreateFromString(shaderIndex, OpenGLShaderType[int(shaderType)], shaderSource->mSource);
    }

    // Link all the part together.
    LinkProgram();

    // Look up all the declared uniform location.
    CollectUniformLocation(shader);
}

PlatformShader::~PlatformShader()
{
    glDeleteProgram(mProgram);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShader::CreateFromString(int shaderIndex, GLenum shaderType, const string& shaderSource)
{
    GLuint shader = glCreateShader(shaderType);

    const char *source = shaderSource.c_str();
    glShaderSource(shader, 1, &source, nullptr);

    // Check whether the shader loads fine
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
        string infoLogString(infoLog);
        delete[] infoLog;

        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Shader compile error: " + infoLogString);
    }

    mShaders[shaderIndex] = shader;
    ++mShaderNum;
}

void
PlatformShader::LinkProgram()
{
    mProgram = glCreateProgram();

    // Avoid attach empty shaders
    if (mShaders[VertexShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[VertexShaderIndex]);
    }

    if (mShaders[GeometryShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[GeometryShaderIndex]);
    }

    if (mShaders[FragmentShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[FragmentShaderIndex]);
    }

    // Link and check whether the program links fine
    GLint status;
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(mProgram, infoLogLength, nullptr, infoLog);
        string infoLogString(infoLog);
        delete[] infoLog;

        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Shader link error: " + infoLogString);
    }

    // Remove the unnecessary shader handle.
    if (mShaders[VertexShaderIndex] != 0)
    {
        glDeleteShader(mShaders[VertexShaderIndex]);
    }

    if (mShaders[GeometryShaderIndex] != 0)
    {
        glDeleteShader(mShaders[GeometryShaderIndex]);
    }

    if (mShaders[FragmentShaderIndex] != 0)
    {
        glDeleteShader(mShaders[FragmentShaderIndex]);
    }
}

void
PlatformShader::DeleteProgram() const
{
    glDeleteProgram(mProgram);
}

GLuint
PlatformShader::GetProgram() const
{
    return mProgram;
}

void
PlatformShader::Enable() const
{
    glUseProgram(mProgram);
}

void
PlatformShader::Disable() const
{
    glUseProgram(0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformShader::CollectUniformActive()
{
    const GLsizei nameBufferSize = 64; // Maximum variable name number in GLSL
    GLchar nameArray[nameBufferSize];  // Variable name in GLSL
    GLsizei nameLength;                // Variable name length in GLSL

    GLint uniformNum;
    glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &uniformNum);
    GameEngineDebugger::OutputString(string("Uniforms Active: ") + std::to_string(uniformNum) + "\n");

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)
    for (auto uniformIndex = 0; uniformIndex < uniformNum; ++uniformIndex)
    {
        glGetActiveUniform(mProgram, GLuint(uniformIndex), nameBufferSize, &nameLength, &size, &type, nameArray);

        GameEngineDebugger::OutputString("Uniform #" + std::to_string(uniformIndex) + " Type:" + std::to_string(type) + " Name: " + string(nameArray) + "\n");
    }
}

void
PlatformShader::CollectUniformLocation(Shader *shader) const
{
    for (auto uniformIter = shader->GetUniformBegin();
            uniformIter != shader->GetUniformEnd();
            ++uniformIter)
    {
        ShaderUniform& uniform = uniformIter->second;
        GLint uniformLocation = glGetUniformLocation(mProgram, uniform.mName.c_str());

        if (uniformLocation == -1)
        {
            GameEngineDebugger::OutputStringFormat("Failed to find shader uniform \"%s\"'s location.\n",
                                          uniform.mName.c_str());

            uniform.mEnabled = false;
        }
        else
        {
            uniform.mEnabled = true;
        }

        // NOTE(Wuxiang): If the uniform is not found, the uniform location
        // would be -1. If -1 is passed to later pipeline, it will get
        // ignored.
        //
        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml
        // If location is a value other than -1 and it does not represent
        // a valid uniform variable location in the current program object,
        // an error will be generated, and no changes will be made to the
        // uniform variable storage of the current program object.
        // If location is equal to -1, the data passed in will be silently
        // ignored and the specified uniform variable will not be changed.
        uniform.mLocation = uniformLocation;
        uniform.mInitialized = true;
    }
}

}
