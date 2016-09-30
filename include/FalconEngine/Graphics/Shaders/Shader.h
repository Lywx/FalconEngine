#pragma once

#include <memory>
#include <string>

#include <FalconEngine/Graphics/Renderers/RendererExtensions.h>

namespace FalconEngine {

class Shader
{
public:
    Shader();
    Shader(const std::wstring vertexShaderPath, const std::wstring fragmentShaderPath);

    // Copy Operation
    Shader(const Shader& rhs);
    Shader& operator=(const Shader& rhs);

    // Move Operation
    Shader(Shader&& rhs) noexcept;
    Shader& operator=(Shader&& rhs) noexcept;

    virtual ~Shader();

    GLuint ProgramId() const { return m_programId; }
    bool   ProgramInUse() const { return m_programInUse; }

    void UseBegin();
    void UseEnd();

private:
    GLuint  m_programId = 0;
    bool    m_programInUse = false;
    size_t *m_programRef;

    GLuint m_vertexShaderId = 0;
    GLuint m_fragmentShaderId = 0;

    void           CopyShader(const Shader& shader) noexcept;
    virtual void DoCopyShader(const Shader& shader) noexcept;
    void           GeldShader(Shader& shader) noexcept;
    virtual void DoGeldShader(Shader& shader) noexcept;
    void           DeleteShader();
    virtual void DoDeleteShader();
};

typedef std::shared_ptr<Shader> ShaderPtr;

}
