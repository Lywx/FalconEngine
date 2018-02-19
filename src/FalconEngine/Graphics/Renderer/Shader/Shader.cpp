#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

#include <fstream>
#include <iostream>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_API const ShaderType
ShaderTypeList [int(ShaderType::Count)] =
{
    ShaderType::VertexShader,
    ShaderType::TessellationControlShader,
    ShaderType::TessellationEvaluationShader,
    ShaderType::GeometryShader,
    ShaderType::FragmentShader,
    ShaderType::ComputeShader,
};

FALCON_ENGINE_API const std::unordered_map<int, ShaderType>
ShaderTypeMap =
{
    { VertexShaderIndex, ShaderType::VertexShader },
    { TessellationControlShaderIndex, ShaderType::TessellationControlShader },
    { TessellationEvaluationShaderIndex, ShaderType::TessellationEvaluationShader },
    { GeometryShaderIndex, ShaderType::GeometryShader },
    { FragmentShaderIndex, ShaderType::FragmentShader },
    { ComputeShaderIndex, ShaderType::ComputeShader },
};

FALCON_ENGINE_API const int
ShaderIndexList[int(ShaderType::Count)] =
{
    VertexShaderIndex,
    TessellationControlShaderIndex,
    TessellationEvaluationShaderIndex,
    GeometryShaderIndex,
    FragmentShaderIndex,
    ComputeShaderIndex,
};

FALCON_ENGINE_API const std::unordered_map<ShaderType, int>
ShaderIndexMap =
{
    { ShaderType::VertexShader, VertexShaderIndex },
    { ShaderType::TessellationControlShader, TessellationControlShaderIndex },
    { ShaderType::TessellationEvaluationShader, TessellationEvaluationShaderIndex },
    { ShaderType::GeometryShader, GeometryShaderIndex },
    { ShaderType::FragmentShader, FragmentShaderIndex },
    { ShaderType::ComputeShader, ComputeShaderIndex },
};

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Shader::Shader()
{
}

Shader::~Shader()
{
    FALCON_ENGINE_RENDERER_UNBIND(this);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
Shader::ContainUniform(const std::string& uniformName) const
{
    return mUniformTable.find(uniformName) != mUniformTable.end();
}

int
Shader::GetUniformNum() const
{
    return int(mUniformTable.size());
}

ShaderUniform&
Shader::GetUniform(const string& uniformName)
{
    return mUniformTable.at(uniformName);
}

int
Shader::GetUniformLocation(const string& uniformName) const
{
    return mUniformTable.at(uniformName).mLocation;
}

bool
Shader::IsUniformEnabled(const string& uniformName) const
{
    return mUniformTable.at(uniformName).mEnabled;
}

void
Shader::PushUniform(const string& uniformName, ShaderUniformType uniformType)
{
    mUniformTable.insert({ uniformName, ShaderUniform(uniformName, uniformType) });
}

/************************************************************************/
/* Uniform Buffer Management                                            */
/************************************************************************/
bool
Shader::ContainUniformBuffer(const std::string& uniformBufferName) const
{
    return mUniformBufferTable.find(uniformBufferName) != mUniformBufferTable.end();
}

void
Shader::PushUniformBuffer(const std::string& uniformBufferName, size_t uniformBufferSize)
{
    mUniformBufferTable.insert({ uniformBufferName, std::make_shared<UniformBuffer>(uniformBufferName, uniformBufferSize) });
}

/************************************************************************/
/* Composition Management                                               */
/************************************************************************/
int
Shader::GetShaderNum() const
{
    return int(mSourceTable.size());
}

ShaderSource *
Shader::GetShaderSource(int shaderIndex) const
{
    return mSourceTable.at(shaderIndex).get();
}

ShaderSource *
Shader::GetShaderSource(ShaderType shaderType) const
{
    return GetShaderSource(ShaderIndexMap.at(shaderType));
}

void
Shader::PushShaderFile(ShaderType shaderType, const std::string& shaderPath)
{
    auto assetManager = AssetManager::GetInstance();
    auto shaderSource = assetManager->LoadShaderSource(shaderPath);

    if (shaderSource)
    {
        mSourceTable[ShaderIndexMap.at(shaderType)] = shaderSource;
    }
    else
    {
        std::cerr << "Error loading shader \"" << shaderPath << "\"." << endl;
    }
}

}
