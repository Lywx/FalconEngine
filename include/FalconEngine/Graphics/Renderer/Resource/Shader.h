#pragma once

#include <FalconEngine/Core/Macro.h>

#include <algorithm>
#include <unordered_map>

#include <FalconEngine/Graphics/Renderer/Resource/ShaderMetadata.h>
#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

// @remark The integer number is used to index into the shader source table, which
// is referred as shader type index.
enum class ShaderType : unsigned int
{
//                                          Direct3D
    VertexShader = 0x01,                 // Vertex Shader   : 0
    TessellationControlShader = 0x02,    // Hull Shader     : 1
    TessellationEvaluationShader = 0x04, // Domain Shader   : 2
    GeometryShader = 0x08,               // Geometry Shader : 3
    FragmentShader = 0x10,               // Pixel Shader    : 4
    ComputeShader = 0x20,                // Compute Shader  : 5

    Count = 6,
};

FALCON_ENGINE_API const extern ShaderType
ShaderTypeList[int(ShaderType::Count)];

FALCON_ENGINE_API const extern std::unordered_map<int, ShaderType>
ShaderTypeMap;

inline bool
GetShaderEnabled(unsigned int shaderMask, ShaderType shaderType)
{
    return (shaderMask & unsigned int(shaderType)) != 0u;
}

inline unsigned int
GetShaderMask(ShaderType shaderType)
{
    return unsigned int(shaderType);
}

inline unsigned int
operator|(ShaderType lhs, ShaderType rhs)
{
    return GetShaderMask(lhs) | GetShaderMask(rhs);
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

FALCON_ENGINE_API const extern int
ShaderIndexList[int(ShaderType::Count)];

FALCON_ENGINE_API const extern std::unordered_map<ShaderType, int>
ShaderIndexMap;

class ShaderSource;
enum class UniformType;

// NOTE(Wuxiang): Shader contains information about input vertex variables, output
// fragment variables and uniform variables. Sharing shaders for different
// primitive set is allowed (which is done by setting shader in the visual effect),
// so that one should think about what is responsible for updating shader uniform
// variable for each update (which is done by setting shader uniform in visual
// effect instance).
//
// NOTE(Wuxiang): Shader has one-to-one relation with Visual Effect Pass in
// rendering pipeline. Visual Effect Pass is responsible for holding anything related to
// states for a pass in Visual Effect. In that case, shader uniform and shader
// uniform buffer might be stored in the Visual Effect Pass. But considering the
// possibility of sharing Shader cross different Visual Effects and cross different
// Visual Effect Passes, you could avoid redundant uniform and uniform buffer
// data updating in OpenGL. The that is specific to OpenGL, Direct3D doesn't have
// this concept. So the uniform, uniform buffer binding is only relevant to specific
// API. It is usually not good to encapsulate API specific concept into interface class.
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
    ContainUniformMeta(const std::string & uniformName) const;

    const UniformMetadata&
    GetUniformMeta(const std::string & uniformName);

    void
    SetUniformMeta(const std::string & uniformName);

    auto
    GetUniformMetaBegin()
    {
        return mUniformMetadataTable.begin();
    }

    auto
    GetUniformMetaEnd()
    {
        return mUniformMetadataTable.end();
    }

    auto
    GetUniformMetaBegin() const
    {
        return mUniformMetadataTable.cbegin();
    }

    auto
    GetUniformMetaEnd() const
    {
        return mUniformMetadataTable.cend();
    }

    /************************************************************************/
    /* Uniform Buffer Management                                            */
    /************************************************************************/
    bool
    ContainUniformBufferMeta(const std::string & uniformBufferName) const;

    void
    SetUniformBufferMeta(const std::string & uniformBufferName,
                         size_t uniformBufferSize,
                         int uniformBufferBindingIndex);

    auto
    GetUniformBufferMetaBegin()
    {
        return mUniformBufferMetadataTable.begin();
    }

    auto
    GetUniformBufferMetaEnd()
    {
        return mUniformBufferMetadataTable.end();
    }

    auto
    GetUniformBufferMetaBegin() const
    {
        return mUniformBufferMetadataTable.cbegin();
    }

    auto
    GetUniformBufferMetaEnd() const
    {
        return mUniformBufferMetadataTable.cend();
    }

    const UniformBufferMetadata&
    GetUniformBufferMeta(const std::string & uniformBufferName) const;

    /************************************************************************/
    /* Composition Management                                               */
    /************************************************************************/
    int
    GetShaderNum() const;

    ShaderSource *
    GetShaderSource(int shaderIndex) const;

    ShaderSource *
    GetShaderSource(ShaderType shaderType) const;

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

    void
    PushShaderFile(ShaderType shaderType, const std::string & shaderPath);

private:
    /************************************************************************/
    /* Source Members                                                       */
    /************************************************************************/
    std::unordered_map<int, std::shared_ptr<ShaderSource>> mSourceTable;

    /************************************************************************/
    /* Metadata Members                                                     */
    /************************************************************************/
    std::unordered_map<std::string, UniformMetadata> mUniformMetadataTable;
    std::unordered_map<std::string, UniformBufferMetadata> mUniformBufferMetadataTable;
};
FALCON_ENGINE_CLASS_END

}
