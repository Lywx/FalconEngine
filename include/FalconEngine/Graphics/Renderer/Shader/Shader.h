#pragma once

#include <FalconEngine/Core/Macro.h>

#include <algorithm>
#include <unordered_map>

#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

enum class ShaderUniformType;

// @remark The integer number is used to index into the shader source table, which
// is referred as shader type index.
enum class ShaderType : unsigned int
{
//                                          Direct3D
    VertexShader = 0x01,                 // Vertex Shader 0
    TessellationControlShader = 0x02,    // Hull Shader 1
    TessellationEvaluationShader = 0x04, // Domain Shader 2
    GeometryShader = 0x08,               // Geometry Shader 3
    FragmentShader = 0x10,               // Pixel Shader 4
    ComputeShader = 0x20,                // Compute Shader 5

    Count = 6,
};

inline unsigned int
operator|(const ShaderType& lhs, const ShaderType& rhs)
{
    return unsigned int(lhs) | unsigned int(rhs);
}

inline bool
ShaderTypeEnabled(unsigned int shaderMask, ShaderType shaderType)
{
    return bool(shaderMask & unsigned int(shaderType));
}

enum ShaderIndex
{
    VertexShaderIndex,
    TessellationControlShaderIndex,
    TessellationEvaluationShaderIndex,
    GeometryShaderIndex,
    FragmentShaderIndex,
    ComputeShaderIndex,
};

class ShaderSource;

// @remark Shader contains information about input vertex variables, output
// fragment variables and uniform variables. Sharing shaders for different
// primitive set is allowed (which is done by setting shader in the visual effect),
// so that one should think about what is responsible for updating shader uniform
// variable for each update (which is done by setting shader uniform in visual
// effect instance).
FALCON_ENGINE_CLASS_BEGIN Shader final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Shader();
    ~Shader();

    /************************************************************************/
    /* Uniform Management                                                   */
    /************************************************************************/
    bool
    ContainUniform(const std::string & uniformName) const;

    int
    GetUniformNum() const;

    ShaderUniform&
    GetUniform(const std::string & uniformName);

    auto
    GetUniformBegin()
    {
        return mUniformTable.begin();
    }

    auto
    GetUniformEnd()
    {
        return mUniformTable.end();
    }

    auto
    GetUniformBegin() const
    {
        return mUniformTable.cbegin();
    }

    auto
    GetUniformEnd() const
    {
        return mUniformTable.cend();
    }

    int
    GetUniformLocation(const std::string & uniformName) const;

    bool
    IsUniformEnabled(const std::string & uniformName) const;

    void
    PushUniform(const std::string & uniformName, ShaderUniformType uniformType);

    /************************************************************************/
    /* Composition Management                                               */
    /************************************************************************/
    int
    GetShaderNum() const;

    ShaderSource *
    GetShaderSource(int shaderIndex) const;

    auto
    GetShaderSourceBegin() const
    {
        return mSourceTable.cbegin();
    }

    auto
    GetShaderSourceEnd() const
    {
        return mSourceTable.cend();
    }

    auto
    GetShaderSourceBegin()
    {
        return mSourceTable.begin();
    }

    auto
    GetShaderSourceEnd()
    {
        return mSourceTable.end();
    }

    ShaderType
    GetShaderType(int shaderIndex) const;

    void
    PushShaderFile(ShaderType shaderType, const std::string & shaderPath);

private:
    std::unordered_map<int, std::shared_ptr<ShaderSource>> mSourceTable;
    std::unordered_map<std::string, ShaderUniform>         mUniformTable;
};
FALCON_ENGINE_CLASS_END

}
