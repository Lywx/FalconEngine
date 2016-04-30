#include <FalconEngine/Graphics/Shader.h>
#include <FalconEngine/Graphics/ShaderBrewer.h>

namespace FalconEngine {
namespace Graphics {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Shader::Shader()
    : m_programRef(new size_t(1))
{
}

Shader::Shader(const std::wstring vertexShaderPath, const std::wstring fragmentShaderPath)
    : Shader()
{
    auto vertexShaderSource = ShaderBrewer::ReadShaderSource(vertexShaderPath, ShaderStage::VertexShader);
    m_vertexShaderId = ShaderBrewer::CompileShader(static_cast<const GLchar *>(vertexShaderSource.c_str()), ShaderStage::VertexShader);

    auto fragmentShaderSource = ShaderBrewer::ReadShaderSource(fragmentShaderPath, ShaderStage::FragmentShader);
    m_fragmentShaderId = ShaderBrewer::CompileShader(static_cast<const GLchar *>(fragmentShaderSource.c_str()), ShaderStage::FragmentShader);

    ShaderBrewer::LinkShaderProgram(m_programId, m_vertexShaderId, m_fragmentShaderId);
}

Shader::Shader(const Shader& rhs)
{
    ++*rhs.m_programRef;

    CopyShader(rhs);
}

Shader& Shader::operator=(const Shader &rhs)
{
    // Path 1: will run if-clause. It is the case when lhs is the last reference
    // of a specific shader and rhs is a different shader.
    //
    // Path 2: don't run if-clause. It is the case when lhs is not the last
    // reference and lhs is assigned to a shader. When the lhs != rhs, lhs will
    // copy its own members.

    ++*rhs.m_programRef;

    if (--*m_programRef == 0)
    {
        DeleteShader();
    }

    CopyShader(rhs);

    return *this;
}

Shader::Shader(Shader&& rhs) noexcept
{
    // Moving won't change ref count, because the remainder will be gelded.
    CopyShader(rhs);
    GeldShader(rhs);
}

Shader& Shader::operator=(Shader&& rhs) noexcept
{
    if (this != &rhs)
    {
        CopyShader(rhs);
        GeldShader(rhs);
    }

    return *this;
}

Shader::~Shader()
{
    if (--*m_programRef == 0)
    {
        DeleteShader();
    }
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Shader::UseBegin()
{
    if (m_programId == 0)
    {
        throw std::runtime_error("Cannot begin using when program is not initialized.");
    }

    m_programInUse = true;

    glUseProgram(m_programId);
}

void Shader::UseEnd()
{
    if (m_programId == 0)
    {
        throw std::runtime_error("Cannot end using when program is not initialized.");
    }

    glUseProgram(0);

    m_programInUse = false;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void Shader::CopyShader(const Shader& shader) noexcept
{
    DoCopyShader(shader);
}

void Shader::DoCopyShader(const Shader& shader) noexcept
{
    m_programRef       = shader.m_programRef;
    m_programInUse     = shader.m_programInUse;
    m_programId        = shader.m_programId;
    m_vertexShaderId   = shader.m_vertexShaderId;
    m_fragmentShaderId = shader.m_fragmentShaderId;
}

void Shader::GeldShader(Shader& shader) noexcept
{
    DoGeldShader(shader);
}

void Shader::DoGeldShader(Shader& shader) noexcept
{
    // Must not delete m_programRef, because that is safe to leave alone.
    shader.m_programId    = 0;
    shader.m_programInUse = false;

    shader.m_vertexShaderId = 0;
    shader.m_fragmentShaderId = 0;
}

void Shader::DeleteShader()
{
    DoDeleteShader();
}

void Shader::DoDeleteShader()
{
    glDetachShader(m_programId, m_vertexShaderId);
    glDetachShader(m_programId, m_fragmentShaderId);

    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);

    glDeleteProgram(m_programId);
}


}
}
