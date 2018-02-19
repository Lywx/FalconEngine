#include <FalconEngine/Platform/OpenGL/OpenGLShader.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>
#include <FalconEngine/Platform/OpenGL/OpenGLShaderProcessor.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShader::PlatformShader(Renderer *, Shader *shader) :
    mProgram(0),
    mShaders(),
    mShaderNum(0)
{
    std::fill_n(mShaders, int(ShaderType::Count), 0);

    // Compile all shader source.
    for (auto shaderIter = shader->GetShaderSourceBegin(); shaderIter != shader->GetShaderSourceEnd(); ++shaderIter)
    {
        auto shaderIndex = shaderIter->first;
        auto shaderType = ShaderTypeMap.at(shaderIndex);
        auto shaderSource = shaderIter->second.get();
        PlatformShaderProcessor::ProcessShaderExtension(shaderSource);

        // Compile for each part of shader
        CreateShaderFromString(shaderIndex, OpenGLShaderType[ShaderIndexMap.at(shaderType)], shaderSource->mSource);
    }

    // Link all the part together.
    LinkProgram();

    // Look up all the declared uniform location.
    CollectUniformBufferIndex(shader);
    CollectUniformLocation(shader);
}

PlatformShader::~PlatformShader()
{
    DeleteProgram();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShader::Enable(Renderer *) const
{
    glUseProgram(mProgram);
}

void
PlatformShader::Disable(Renderer *) const
{
    glUseProgram(0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformShader::CreateShaderFromString(int shaderIndex, GLenum shaderType, const string& shaderSource)
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

    // Attach the shader handle.
    for (auto shaderIndex : ShaderIndexList)
    {
        if (mShaders[shaderIndex] != 0)
        {
            glAttachShader(mProgram, mShaders[shaderIndex]);
        }
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

    // Remove the shader handle.
    for (auto shaderIndex : ShaderIndexList)
    {
        if (mShaders[shaderIndex] != 0)
        {
            glDeleteShader(mShaders[shaderIndex]);
        }
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

void
PlatformShader::CollectUniformBufferIndex(Shader *shader) const
{
    for (auto uniformIter = shader->GetUniformBufferBegin();
            uniformIter != shader->GetUniformBufferEnd();
            ++uniformIter)
    {
        auto const& uniformBuffer = uniformIter->second;
        auto const uniformBlockName = uniformBuffer->GetName();
        const GLuint uniformBlockIndex = glGetUniformBlockIndex(mProgram, uniformBlockName.c_str());
        if (uniformBlockIndex == GL_INVALID_INDEX)
        {
            GameEngineDebugger::OutputStringFormat(
                "Failed to find shader uniform buffer \"%s\"'s location.\n",
                uniformBlockName.c_str());
        }
        else
        {
            uniformBuffer->SetBlockIndex(uniformBlockIndex);

            GLint uniformBlockSize;
            glGetActiveUniformBlockiv(mProgram, uniformBlockIndex,
                                      GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);

            auto uniformBlockSizeExpected = int(uniformBuffer->GetCapacitySize());
            if (uniformBlockSize != uniformBlockSizeExpected)
            {
                GameEngineDebugger::OutputStringFormat(
                    "Failed to match shader uniform buffer size for uniform block '%s'. Expected: %d, Allocated: %d.\n",
                    uniformBlockName.c_str(), uniformBlockSizeExpected, uniformBlockSize);
            }
        }
    }

}

}

#endif