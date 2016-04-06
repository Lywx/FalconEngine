#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

namespace FalconEngine {
namespace Render {

enum class ShaderStage
{
    VertexShader   = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER
};

static const std::map<ShaderStage, char *> ShaderStageStrings =
{
    { ShaderStage::VertexShader  , "Vertex Shader" },
    { ShaderStage::FragmentShader, "Fragment Shader" }
};

class ShaderBrewer
{
public:
    static std::string ReadShaderSource(const GLchar *shaderPath, const ShaderStage shaderStage)
    {
        std::string   shaderSource;
        std::ifstream shaderSourceFile;

        shaderSourceFile.exceptions(std::ifstream::badbit);
        try
        {
            shaderSourceFile.open(shaderPath);
            std::stringstream sourceStream;
            sourceStream << shaderSourceFile.rdbuf();
            shaderSourceFile.close();
            shaderSource = sourceStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "Error: " << GetShaderStageString(shaderStage) << "file not successfully read." << std::endl;
        }

        return shaderSource;
    }

    static GLuint CompileShader(const GLchar *shaderSource, const ShaderStage shaderStage)
    {
        GLint  shaderCompilationSuccess;
        GLchar shaderLog[512];
        GLuint shaderId = glCreateShader(static_cast<int>(shaderStage));

        glShaderSource(shaderId, 1, &shaderSource, nullptr);
        glCompileShader(shaderId);

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompilationSuccess);
        if (!shaderCompilationSuccess)
        {
            glGetShaderInfoLog(shaderId, 512, nullptr, shaderLog);
            std::cout << "Error: " << GetShaderStageString(shaderStage) << "source compilation failed.\n" << shaderLog << std::endl;
        }

        return shaderId;
    }

    static void LinkShaderProgram(GLuint& programId, GLuint vertexShaderId, GLuint fragmentShaderId)
    {
        GLint  programLinkingSuccess;
        GLchar programLog[512];

        programId = glCreateProgram();
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);
        glLinkProgram(programId);
        glGetProgramiv(programId, GL_LINK_STATUS, &programLinkingSuccess);
        if (!programLinkingSuccess)
        {
            glGetProgramInfoLog(programId, 512, nullptr, programLog);
            std::cout << "Error: Shader program linking failed\n" << programLog << std::endl;
        }
    };

private:
    static const char *GetShaderStageString(const ShaderStage shaderStage)
    {
        return ShaderStageStrings.at(shaderStage);
    }
};

class Shader
{
public:
    Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath);
    ~Shader();

    GLuint ProgramId() const { return m_programId; }
    bool ProgramInUse() const { return m_programInUse; }

    GLuint VertexShaderId() const { return m_vertexShaderId; }
    GLuint FragmentShaderId() const { return m_fragmentShaderId; }

    void UseBegin();
    void UseEnd();

    void Delete();

private:
    GLuint m_programId;
    bool m_programInUse;

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

    void DeleteInternal();
};

} // Render
} // FalconEngine
