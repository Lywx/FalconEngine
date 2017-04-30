#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <unordered_map>

#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

enum class ShaderUniformType;

// @remark The integer number is used to index into the shader source table, which
// is referred as shader type index.
enum class ShaderType
{
    VertexShader   = 0,
    GeometryShader = 1,
    FragmentShader = 2,

    Count,
};

enum ShaderIndex
{
    VertexShaderIndex   = 0,
    GeometryShaderIndex = 1,
    FragmentShaderIndex = 2,
};

class ShaderSource;
using ShaderSourceSharedPtr = std::shared_ptr<ShaderSource>;
using ShaderSourceSharedPtrMap = std::unordered_map<int, ShaderSourceSharedPtr>;

using ShaderUniformMap = std::unordered_map<std::string, ShaderUniform>;

// @remark Shader contains information about input vertex variables, output
// fragment variables and uniform variables. Sharing shaders for different
// primitive set is allowed (which is done by setting shader in the visual effect),
// so that one should think about what is responsible for updating shader uniform
// variable for each update (which is done by setting shader uniform in visual
// effect instance).
class Shader
{
    friend class PlatformShader;

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
    ContainUniform(std::string uniformName) const;

    int
    GetUniformNum() const;

    ShaderUniform&
    GetUniform(std::string uniformName);

    int
    GetUniformLocation(std::string uniformName) const;

    void
    PushUniform(std::string uniformName, ShaderUniformType uniformType);

    /************************************************************************/
    /* Composition Management                                               */
    /************************************************************************/
    int
    GetShaderNum() const;

    ShaderSource *
    GetShaderSource(int shaderIndex) const;

    ShaderType
    GetShaderType(int shaderIndex) const;

    void
    PushShaderFile(ShaderType shaderType, const std::string& shaderPath);

private:
    ShaderSourceSharedPtrMap mSourceTable;
    ShaderUniformMap         mUniformTable;
};

}
