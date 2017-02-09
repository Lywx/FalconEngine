#include <FalconEngine/Graphics/Shaders/Shader.h>

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
int
Shader::GetAttributeNum() const
{
    return int(mAttributeVector.size());
}

ShaderVertexAttribute&
Shader::GetAttribute(int attributeIndex)
{
    return mAttributeVector.at(attributeIndex);
}

void
Shader::PushAttribute(int attributeLocation, std::string attributeName, ShaderVertexAttributeType attributeType, bool attributeNormalized)
{
    mAttributeVector.push_back(ShaderVertexAttribute(attributeLocation, attributeName, attributeType, attributeNormalized));
}

void
Shader::PushUniform(std::string uniformName, ShaderUniformType uniformType)
{
    mUniformHandleTable[uniformName] = make_unique<ShaderUniform>(uniformName, uniformType);
}

int
Shader::GetUniformNum() const
{
    return int(mUniformHandleTable.size());
}

ShaderUniform *
Shader::GetUniform(string uniformName) const
{
    // TODO(Wuxiang 2017-01-25 13:33): Not done!
    return mUniformHandleTable.at(uniformName).get();
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
