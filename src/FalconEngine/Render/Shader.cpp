#include <FalconEngine/Shader.h>

namespace FalconEngine {
namespace Render {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Shader::Shader(const GLchar *vertex_shader_path, const GLchar *fragment_shader_path)
    : m_programInUse(false)
{
    std::string vertex_shader_source = ShaderBrewer::ReadShaderSource(vertex_shader_path, ShaderStage::VertexShader);
    m_vertexShaderId = ShaderBrewer::CompileShader(static_cast<const GLchar *>(vertex_shader_source.c_str()), ShaderStage::VertexShader);

    std::string fragment_shader_source = ShaderBrewer::ReadShaderSource(fragment_shader_path, ShaderStage::FragmentShader);
    m_fragmentShaderId = ShaderBrewer::CompileShader(static_cast<const GLchar *>(fragment_shader_source.c_str()), ShaderStage::FragmentShader);

    ShaderBrewer::LinkShaderProgram(m_programId, m_vertexShaderId, m_fragmentShaderId);
}

Shader::~Shader()
{
    DeleteInternal();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Shader::UseBegin()
{
    m_programInUse = true;

    glUseProgram(m_programId);
}

void Shader::UseEnd()
{
    glUseProgram(0);

    m_programInUse = false;
}

void Shader::Delete()
{
    if (m_programInUse)
    {
        throw std::runtime_error("Cannot destruct when program is in used.");
    }

    DeleteInternal();
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void Shader::DeleteInternal()
{
    glDetachShader(m_programId, m_vertexShaderId);
    glDetachShader(m_programId, m_fragmentShaderId);

    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);

    glDeleteProgram(m_programId);

    m_programId = 0;
    m_vertexShaderId = 0;
    m_fragmentShaderId = 0;
}

} // Render
} // FalconEngine
