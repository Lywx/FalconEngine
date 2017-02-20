#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>

#include <fstream>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Shader, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Shader::Shader()
{
}

Shader::~Shader()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
Shader::ContainUniform(std::string uniformName) const
{
    return mUniformTable.find(uniformName) != mUniformTable.end();
}

int
Shader::GetUniformNum() const
{
    return int(mUniformTable.size());
}

ShaderUniform&
Shader::GetUniform(string uniformName)
{
    return mUniformTable.at(uniformName);
}

int
Shader::GetUniformLocation(std::string uniformName) const
{
    return mUniformTable.at(uniformName).mLocation;
}

void
Shader::PushUniform(std::string uniformName, ShaderUniformType uniformType)
{
    mUniformTable[uniformName] = ShaderUniform(uniformName, uniformType);
}

int Shader::GetShaderNum() const
{
    return int(mSourceTable.size());
}

std::string
Shader::GetShaderSource(int shaderIndex) const
{
    return mSourceTable.at(shaderIndex);
}

ShaderType
Shader::GetShaderType(int shaderIndex) const
{
    return ShaderType(shaderIndex);
}

void
Shader::PushShaderFile(ShaderType shaderType, const std::string& shaderFilename)
{
    ifstream shaderStream;
    shaderStream.open(shaderFilename.c_str(), ios_base::in);

    if (shaderStream)
    {
        string shaderLine, shaderBuffer;
        while (getline(shaderStream, shaderLine))
        {
            shaderBuffer.append(shaderLine);
            shaderBuffer.append("\r\n");
        }

        mSourceTable[int(shaderType)] = move(shaderBuffer);
    }
    else
    {
        cerr << typeid(Shader).name() << ": Error loading shader \"" << shaderFilename << "\"." << endl;
    }
}

}
