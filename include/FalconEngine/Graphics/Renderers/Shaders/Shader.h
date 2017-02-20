#pragma once

#include <unordered_map>

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniform.h>
#include <FalconEngine/Graphics/Renderers/Shaders/VertexAttribute.h>

namespace FalconEngine
{

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
    VertexShaderIndex = 0,
    GeometryShaderIndex = 1,
    FragmentShaderIndex = 2,
};

// @remark Shader contains information about input vertex variables, output
// fragment variables and uniform variables. Sharing shaders for different
// primitive set is allowed (which is done by setting shader in the visual effect),
// so that one should think about what is responsible for updating shader uniform
// variable for each update (which is done by setting shader uniform in visual
// effect instance).
class Shader : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Shader();
    ~Shader();

    /************************************************************************/
    /* Uniform Management                                                   */
    /************************************************************************/
    void
    PushUniform(std::string uniformName, ShaderUniformType uniformType);

    int
    GetUniformNum() const;

    ShaderUniform *
    GetUniform(std::string uniformName) const;

    /************************************************************************/
    /* Composition Management                                               */
    /************************************************************************/
    int
    GetShaderNum() const;

    std::string
    GetShaderSource(int shaderIndex) const;

    ShaderType
    GetShaderType(int shaderIndex) const;

    void
    PushShaderFile(ShaderType shaderType, const std::string& shaderFilename);

public:
    ShaderUniformTable          mUniformTable;

private:
    std::unordered_map<int, std::string> mSourceTable;
};

typedef std::shared_ptr<Shader> ShaderSharedPtr;

}