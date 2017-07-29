#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

#include <fstream>
#include <iostream>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

using namespace std;

namespace FalconEngine
{

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

int Shader::GetShaderNum() const
{
    return int(mSourceTable.size());
}

ShaderSource *
Shader::GetShaderSource(int shaderIndex) const
{
    return mSourceTable.at(shaderIndex).get();
}

ShaderType
Shader::GetShaderType(int shaderIndex) const
{
    return ShaderType(shaderIndex);
}

void
Shader::PushShaderFile(ShaderType shaderType, const std::string& shaderPath)
{
    auto assetManager = AssetManager::GetInstance();
    auto shaderSource = assetManager->LoadShaderSource(shaderPath);

    if (shaderSource)
    {
        mSourceTable[int(shaderType)] = shaderSource;
    }
    else
    {
        std::cerr << "Error loading shader \"" << shaderPath << "\"." << endl;
    }
}

}
