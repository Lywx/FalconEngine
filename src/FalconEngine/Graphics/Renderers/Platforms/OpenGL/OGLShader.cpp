#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLShader.h>

#include <iostream>
#include <fstream>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformShader::PlatformShader(Shader *shader) :
    mProgram(0),
    mShaderNum(0)
{
    // Initialize to zero.
    std::fill_n(mShaders, int(ShaderType::Count), 0);

    // Compile all shader source.
    for (int shaderIndex = 0; shaderIndex < shader->GetShaderNum(); ++shaderIndex)
    {
        auto shaderSource = shader->GetShaderSource(shaderIndex);
        auto shaderType = shader->GetShaderType(shaderIndex);

        // Compile for each part of shader
        CreateFromString(OpenGLShaderType[int(shaderType)], shaderSource);
    }

    // Link all the part together.
    LinkProgram();

    CreateVertexAttributeArray(shader);

    // Look up all the declared uniform location.
    CollectUniformLocation(shader);
}

PlatformShader::~PlatformShader()
{
    glDeleteProgram(mProgram);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformShader::CreateFromString(GLenum shaderType, const string& shaderSource)
{
    GLuint shader = glCreateShader(shaderType);

    const char *sourcePtr = shaderSource.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);

    // Check whether the shader loads fine
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);

        cerr << typeid(Shader).name() << ": Compile: " << infoLog << endl;
        delete[] infoLog;
    }

    mShaders[mShaderNum++] = shader;
}

void
PlatformShader::CreateFromFile(GLenum shaderType, const string& shaderFilename)
{
    ifstream fstream;
    fstream.open(shaderFilename.c_str(), ios_base::in);

    if (fstream)
    {
        string line, buffer;
        while (getline(fstream, line))
        {
            buffer.append(line);
            buffer.append("\r\n");
        }

        // Copy to source
        CreateFromString(shaderType, buffer);
    }
    else
    {
        cerr << typeid(Shader).name() << ": Error loading shader \"" << shaderFilename << "\"." << endl;
    }
}

void
PlatformShader::LinkProgram()
{
    mProgram = glCreateProgram();

    // Avoid attach empty shaders
    if (mShaders[VertexShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[VertexShaderIndex]);
    }

    if (mShaders[GeometryShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[GeometryShaderIndex]);
    }

    if (mShaders[FragmentShaderIndex] != 0)
    {
        glAttachShader(mProgram, mShaders[FragmentShaderIndex]);
    }

    // Link and check whether the program links fine
    GLint status;
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(mProgram, infoLogLength, nullptr, infoLog);

        cerr << typeid(Shader).name() << ": Link: " << infoLog << endl;
        delete[] infoLog;
    }

    // Remove the unnecessary shader handle.
    glDeleteShader(mShaders[VertexShaderIndex]);
    glDeleteShader(mShaders[GeometryShaderIndex]);
    glDeleteShader(mShaders[FragmentShaderIndex]);
}

void
PlatformShader::DeleteProgram() const
{
    glDeleteProgram(mProgram);
}

GLuint
PlatformShader::GetProgram() const
{
    return mProgram;
}

void
PlatformShader::Enable() const
{
    glUseProgram(mProgram);
}

void
PlatformShader::Disable() const
{
    glUseProgram(0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/

void
PlatformShader::CollectVertexAttributeLocation(Shader *shader) const
{
    for (auto& vertexAttrib : shader->mVertexAttributeVector)
    {
        GLint vertexAttriLocation = glGetAttribLocation(mProgram, vertexAttrib.mName.c_str());
        if (vertexAttriLocation == -1)
        {
            ThrowRuntimeException("The vertex attribute could not be found.");
        }

        vertexAttrib.mLocation = vertexAttriLocation;
    }
}

void
PlatformShader::CreateVertexAttributeArray(Shader *shader)
{
    glCreateVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    for (auto& vertexAttrib : shader->mVertexAttributeVector)
    {
        glVertexAttribFormat(vertexAttrib.mLocation, vertexAttrib.mChannel,
                             OpenGLShaderAttributeType[int(vertexAttrib.mType)],
                             vertexAttrib.mNormalized, vertexAttrib.mOffset);
        glEnableVertexAttribArray(vertexAttrib.mLocation);
    }

    glBindVertexArray(0);
}

void
PlatformShader::CollectUniformLocation(Shader *shader) const
{
    for (auto& uniformNameValuePair : shader->mUniformTable)
    {
        GLint uniformLocation = glGetUniformLocation(mProgram, uniformNameValuePair.first.c_str());
        if (uniformLocation == -1)
        {
            ThrowRuntimeException("The location could not be found.");
        }

        uniformNameValuePair.second.mLocation = uniformLocation;
    }
}

}
